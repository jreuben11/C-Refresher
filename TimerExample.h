//
// Created by josh reuben on 16/04/2018.
//

#ifndef LANGUAGE_FEATURES_TIMEREXAMPLE_H
#define LANGUAGE_FEATURES_TIMEREXAMPLE_H
#include "Poco/Stopwatch.h"
#include "Poco/Timer.h"

class TimerExample {
public:
    TimerExample();
    void onTimer(Poco::Timer &timer);

private:
    Poco::Stopwatch _sw;
};
#endif //LANGUAGE_FEATURES_TIMEREXAMPLE_H
