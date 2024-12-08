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

 private:
  uint32_t startTime = 0;
  uint32_t elapsedTime = 0;
};

#endif  // TIMER_H