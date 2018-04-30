//
// Created by josh reuben on 29/04/2018.
//

#include <mutex>
#include <thread>
#include <fstream>
#include <vector>
#include <queue>

#include <iostream>
#include <chrono>
#include <future>
#include <numeric>

namespace concurrency {
    std::mutex m; // used to protect access to shared data
    int sh;  // shared data

    void f() {
        std::unique_lock<std::mutex> lck{m}; // acquire the mutex m
        // ... manipulate shared data ...
        sh += 5;
    }

    struct F {               // functor
        void operator()(){}  // call operator
    };

    void user() {
        std::thread t1 {f};      // f() executes in separate thread
        std::thread t2 {F()};    // F()() executes in separate thread

        t1.join();          // wait for t1
        t2.join();          // wait for t2
    }
    void f2(std::vector<double>&& v){}

    struct F2 {
        std::vector<double>& v;
        F2(std::vector<double>& vv) :v{vv} { }
        void operator()() {}
    };

    void f3(const std::vector<double>&& v, double* res) {} // WTF: variadic template only works with &&

    class F3 {
    public:
        F3(const std::vector<double>& vv, double* p) :v{vv}, res{p} { }
        void operator()() {}          // place result in *res
    private:
        const std::vector<double>& v;         // source of input
        double* res;               // target for output
    };

    void user2() { // pass functions / functors + values + retvals to threads
        std::vector<double> some_vec {1,2,3,4,5,6,7,8,9};
        std::vector<double> vec2 {10,11,12,13,14};

        double res1;
        double res2;

        std::thread t1 {f3, some_vec, &res1};             // f(some_vec) executes in a separate thread
        std::thread t2 {F3{vec2, &res2}};     // F(vec2)() executes in a separate thread

        t1.join();
        t2.join();

        std::cout << res1 << ' ' << res2 << '\n';
    }

    void chronoUser(){
        using namespace std::chrono;
        auto t0 = high_resolution_clock::now();
        std::this_thread::sleep_for(milliseconds{20});
        auto t1 = high_resolution_clock::now();
        std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed\n";
    }

    class Message {   // object to be communicated
        // ...
    };

    std::queue<Message> mqueue;          // the queue of messages
    std::condition_variable mcond;       // the variable communicating events
    std::mutex mmutex;                   // the locking mechanism

    void consumer() {
        while(true) {
            std::unique_lock<std::mutex> lck{mmutex};             // acquire mmutex
            mcond.wait(lck); /* do nothing */;   // release lck and wait;
            // re-acquire lck upon wakeup
            auto m = mqueue.front();                    // get the message
            mqueue.pop();
            lck.unlock();                               // release lck
            // ... process m ...
        }
    }
    void producer() {
        while(true) {
            Message m;
            // ... fill the message ...
            std::unique_lock<std::mutex> lck {mmutex};  // protect operations
            mqueue.push(m);
            mcond.notify_one();               // notify
        }                                      // release lock (at end of scope)
    }

    template <typename X>
    void f(std::promise<X>& px) { // a task: place the result in px
        try {
            X res;
            // ... compute a value for res ...
            px.set_value(res);
        } catch (...) {
            // pass the exception to the future's thread:
            px.set_exception(std::current_exception());
        }
    }

    template <typename X>
    void g(std::future<X>& fx) {       // a task: get the result from fx
        // ...
        try {
            X v = fx.get();  // if necessary, wait for the value to get computed
            // ... use v ...
        } catch (...) {
            // ... handle error ...
        }
    }

    double accum(double* beg, double * end, double init) {
    // compute the sum of [beg:end) starting with the initial value init
        return std::accumulate(beg,end,init);
    }

    double comp2(std::vector<double>& v) {
        using Task_type = double(double*,double*,double);   // type of task

        std::packaged_task<Task_type> pt0 {accum};               // package the task (i.e., accum)
        std::packaged_task<Task_type> pt1 {accum};

        std::future<double> f0 {pt0.get_future()};               // get hold of pt0's future
        std::future<double> f1 {pt1.get_future()};               // get hold of pt1's future

        double* first = &v[0];
        std::thread t1 {std::move(pt0), first, 		first+v.size()/2, 	0};     // start a thread for pt0
        std::thread t2 {std::move(pt1), first+v.size()/2,	first+v.size(),	0};  // start a thread for pt1

        // ...

        return f0.get()+f1.get();       // get the results
    }

    double comp4(std::vector<double>& v)
    // spawn many tasks if v is large enough
    {
        if (v.size()<10000) return std::accumulate(v.begin(), v.end(),0.0);

        auto v0 = &v[0];
        auto sz = v.size();

        auto f0 = std::async(accum,v0,v0+sz/4,0.0);         // first quarter
        auto f1 = std::async(accum,v0+sz/4,v0+sz/2,0.0);    // second quarter
        auto f2 = std::async(accum,v0+sz/2,v0+sz*3/4,0.0);  // third quarter
        auto f3 = std::async(accum,v0+sz*3/4,v0+sz,0.0);    // fourth quarter

        return f0.get()+f1.get()+f2.get()+f3.get();  // collect and combine the results
    }
}

