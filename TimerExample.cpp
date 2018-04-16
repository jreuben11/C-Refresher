//
// Created by josh reuben on 16/04/2018.
//
#include <iostream>
#include "TimerExample.h"

TimerExample::TimerExample(){
    _sw.start();
}

void TimerExample::onTimer(Poco::Timer& timer){
    std::__1::cout << "Callback called after " << _sw.elapsed() / 1000 << " milliseconds." << std::__1::endl;
}
