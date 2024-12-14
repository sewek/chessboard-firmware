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
  this->stopped = false;
  return 0;
}

int Timer::stop() {
  this->elapsedTime = 0;
  this->startTime = 0;
  this->stopped = true;
  return 0;
}

int Timer::pause() {
  this->elapsedTime = this->getElapsedTime();
  this->paused = true;
  return 0;
}

int Timer::resume() {
  this->startTime = k_uptime_get_32();
  this->paused = false;
  return 0;
}

uint32_t Timer::getElapsedTime() {
  if (this->stopped) return this->elapsedTime;
  if (this->paused) return this->elapsedTime;
  return this->elapsedTime - ((k_uptime_get_32() - this->startTime) / 1000);
}

void Timer::setElapsedTime(uint32_t time) { this->elapsedTime = time; }

void Timer::toString(char* buff) {
  uint32_t time = this->getElapsedTime();
  uint32_t minutes = time / 60;
  uint32_t seconds = time % 60;
  snprintf(buff, 8, "%02d:%02d", minutes, seconds);
  buff[7] = '\0';
}