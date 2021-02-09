/**
 * @file constants.h
 *
 * @author John Sochacki
 * @version 0.0.0
 * @date 1/1/2021
 *
 * @warning Only supports float or double for type
 * @bug A lot
 * @copyright GNU General Public License.v3.0
 *
 * @pre None
 * @note Pi has excessive digits, you only need 16 for double before they are
 *    thrown away.
 *
 * @brief This is where all the constants are defined
 *
 * @details
 *  All constants are template variables (which was added in c++14)
 *
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstdint>

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>

namespace com_sys_lib
{
   namespace constants
   {
      namespace math
      {
         template<typename Type>
         constexpr Type CSLDECLSPEC pi{
            static_cast<Type>(
               3.141592653589793238462643383279502884197169399375105820974944592307816406286)
         };
      }
      namespace physics
      {
         template<typename Type>
         constexpr Type CSLDECLSPEC speed_of_light{ static_cast<Type>(
            299792458.0) };
         template<typename Type>
         constexpr Type CSLDECLSPEC boltzmanns_constant{ static_cast<Type>(
            1.38064852e-23) };
         template<typename Type>
         constexpr Type CSLDECLSPEC zero_C_in_kelvin{ static_cast<Type>(
            273.15) };
         template<typename Type>
         constexpr Type CSLDECLSPEC room_temp_in_C{ static_cast<Type>(16.85) };
         template<typename Type>
         constexpr Type CSLDECLSPEC room_temp_in_K{ static_cast<Type>(290.0) };
      }   // namespace physics
      namespace geographical
      {
         /**
          * # Why earths mean radius isn't 6367 km
          *
          * The Earth is not a perfect sphere but approximately an oblate
          * spheroid (an ellipse rotated around its minor axis) with a larger
          * radius at the equator than at the poles. When only one radius is
          * stated, the International Astronomical Union (IAU) prefers that it
          * be the equatorial radius. The International Union of Geodesy and
          * Geophysics (IUGG) recommends three values: the arithmetic mean (R1)
          * of the radii measured at two equator points and a pole; the
          * authalic radius, which is the radius of a sphere with the same
          * surface area (R2); and the volumetric radius, which is the radius
          * of a sphere having the same volume as the ellipsoid (R3). All three
          * values are about 6,371 kilometres (3,959 mi)
          *
          * */
         template<typename Type>
         constexpr Type CSLDECLSPEC mean_earth_radius_in_m{ static_cast<Type>(
            6371000) };
         template<typename Type>
         constexpr Type CSLDECLSPEC polar_earth_radius_in_m{ static_cast<Type>(
            6356000) };
         template<typename Type>
         constexpr Type CSLDECLSPEC equatorial_earth_radius_in_m{
            static_cast<Type>(6378000)
         };
      }   // namespace geographical
      namespace build
      {
         constexpr uint32_t CSLDECLSPEC MAX_FILE_READ_BUFFER_SIZE{ UINT16_MAX };
      }
   }   // namespace constants
}   // namespace com_sys_lib

// This is the section with all the namespace abbreviations

namespace mathcons = com_sys_lib::constants::math;
namespace physcons = com_sys_lib::constants::physics;
namespace geocons  = com_sys_lib::constants::geographical;

#endif /* CONSTANTS_H_ */
