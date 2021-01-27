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
         template<typename Type>
         CSLDECLSPEC constexpr Type speed_of_light{ static_cast<Type>(
            299792458.0) };
         template<typename Type>
         CSLDECLSPEC constexpr Type boltzmanns_constant{ static_cast<Type>(
            1.38064852e-23) };
         template<typename Type>
         CSLDECLSPEC constexpr Type zero_C_in_kelvin{ static_cast<Type>(
            273.15) };
         template<typename Type>
         CSLDECLSPEC constexpr Type room_temp_in_C{ static_cast<Type>(
            16.85) };
         template<typename Type>
         CSLDECLSPEC constexpr Type room_temp_in_K{ static_cast<Type>(
            290.0) };
      }   // namespace physics
   }      // namespace constants
}   // namespace com_sys_lib

#endif /* CONSTANTS_H_ */
