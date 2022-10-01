#include "adc.hpp"

#include <fcntl.h>   // define O_WONLY and O_RDONLY
#include <unistd.h>  // close()

namespace hyped::io {
    
uint16_t resetAndRead4(int file_descriptor)
{
  char buf[4];                              // buffer size 4 for fs value
  lseek(file_descriptor, 0, SEEK_SET);      // reset file pointer
  read(file_descriptor, buf, sizeof(buf));  // actually consume new data, changes value in buffer
  return std::atoi(buf);
}

Adc::Adc(const uint32_t pin) : pin_(pin)
{
}

uint16_t Adc::read()
{
  char buf[100];
  snprintf(buf, sizeof(buf), "/sys/bus/iio/devices/iio:device0/in_voltage%i_raw", pin_);
  file_ = open(buf, O_RDONLY);
  if (file_ < 0) { /* TODO: log that there is a problem reading raw voltage for pin_*/ ;}
  /* TODO: log the file descriptor */
  const uint16_t val = resetAndRead4(file_);
  /* TODO: log the value */ 
  close(file_);
  return val;
}

}  // namespace hyped::io