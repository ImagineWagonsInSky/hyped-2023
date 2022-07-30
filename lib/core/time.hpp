#pragma once

#include <chrono>
#include <cstdint>

namespace hyped::core {

/**
 * @brief Absolute point in time; nanosecond precision.
 */
using TimePoint = std::chrono::high_resolution_clock::time_point;

/**
 * @brief Difference between points in time; nanosecond precision.
 */
using TimeSpan = std::chrono::high_resolution_clock::duration;

/**
 * @brief Time provider allowing the user to obtain the current time of the system.
 * We abtract this away instead of using `Time` directly in order to allow testability.
 */
class ITime {
  virtual TimePoint now() = 0;
};

/**
 * @brief Wrapper around std::chrono::high_resultion_clock in order to work with the
 * ITime interface.
 */
class Time : public ITime {
  Time();
  virtual TimePoint now();
};

}  // namespace hyped::core