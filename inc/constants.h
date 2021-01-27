#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstdint>

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>

namespace com_sys_lib
{
   namespace constants
   {
      namespace physics
      {
         CSLDECLSPEC constexpr double speed_of_light{static_cast<double>(299792458)};
         CSLDECLSPEC constexpr double boltzmanns_constant{ 1.38064852e-23 };
         CSLDECLSPEC constexpr double zero_c_in_kelvin{ 273.15 };
      }   // namespace physics
   }      // namespace constants
}   // namespace com_sys_lib

#endif /* CONSTANTS_H_ */
