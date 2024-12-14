#ifndef TIMER_H
#define TIMER_H

#include <chess_types.h>

/**
 * @brief This class represents the timer of the chess game
 */
class Timer {
 public:
  Timer();
  ~Timer();

  /**
   * @brief Start the timer
   * @return 0 on success, negative error code on failure
   */
  int start();

  /**
   * @brief Stop the timer
   * @return 0 on success, negative error code on failure
   */
  int stop();

  /**
   * @brief Is the timer stopped
   * @return True if the timer is stopped, false otherwise
   */
  bool isStopped() { return this->stopped; }

  /**
   * @brief Is the timer paused
   * @return True if the timer is paused, false otherwise
   */
  bool isPaused() { return this->paused; }

  /**
   * @brief Pause the timer
   * @return 0 on success, negative error code on failure
   */
  int pause();

  /**
   * @brief Resume the timer
   * @return 0 on success, negative error code on failure
   */
  int resume();

  /**
   * @brief Get the elapsed time
   * @return The elapsed time
   */
  uint32_t getElapsedTime();

  /**
   * @brief Set the elapsed time
   * @param time The time to set
   */
  void setElapsedTime(uint32_t time);

  /**
   * @brief Get the elapsed time as a string
   * @return The elapsed time as a string
   */
  void toString(char* buff);

 private:
  char buff[8];
  uint32_t startTime = 0;
  uint32_t elapsedTime = 0;
  bool stopped = true;
  bool paused = false;
};

#endif  // TIMER_H