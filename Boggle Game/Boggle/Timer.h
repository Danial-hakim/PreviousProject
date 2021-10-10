#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

class Timer
{
public:
    void start();
    

    void stop();
   

    double elapsedMilliseconds();
   

    int elapsedSeconds();
   

    int convertToCountDown();

    void setGameTime(int gameTime);
   
    // below are public for tests only. when set to private game works as intended
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    int m_gameTime = 10;
    bool m_bRunning = false;
};
