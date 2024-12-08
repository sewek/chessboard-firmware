/**
 * @file timer.cpp
 * @brief This file contains the implementation of the Timer class
 */

#include "timer.h"

#include <zephyr/kernel.h>

Timer::Timer() {}

Timer::~Timer() {}

int Timer::start() {
  this->startTime = k_uptime_get_32();
  return 0;
}

int Timer::stop() {
  this->elapsedTime = 0;
  return 0;
}

int Timer::pause() {
  this->elapsedTime = this->getElapsedTime();
  return 0;
}

int Timer::resume() {
  this->startTime = k_uptime_get_32();
  return 0;
}

uint32_t Timer::getElapsedTime() {
  return this->elapsedTime + k_uptime_get_32() - this->startTime;
}

void Timer::setElapsedTime(uint32_t time) { this->elapsedTime = time; }
