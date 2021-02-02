/**
 * @file constants.cpp
 *
 * @author John Sochacki
 * @version 0.0.0
 * @date 1/1/2021
 *
 * @warning
 * @bug
 * @copyright GNU General Public License.v3.0
 *
 * @pre
 * @note
 *
 * @brief This is where all the constants are defined
 *
 * @details
 *  All constants are template variables (which was added in c++14).
 *  In this file you must make sure to add explicit instiations for each type
 *  that you want to appear in the shared library to the #ifdef
 *  com_sys_lib_EXPORTS section
 *
 */
#include <com_sys_lib/inc/constants.h>

namespace com_sys_lib
{
   namespace constants
   {
      namespace math
      {
#ifdef com_sys_lib_EXPORTS
         template float  pi<float>;
         template double pi<double>;
#endif
      }   // namespace math
      namespace physics
      {
         // Explicitly declare all templates for types so they make it into the
         // shared library else they will not
#ifdef com_sys_lib_EXPORTS
         template float  speed_of_light<float>;
         template double speed_of_light<double>;
         template float  boltzmanns_constant<float>;
         template double boltzmanns_constant<double>;
         template float  zero_C_in_kelvin<float>;
         template double zero_C_in_kelvin<double>;
         template float  room_temp_in_C<float>;
         template double room_temp_in_C<double>;
         template float  room_temp_in_K<float>;
         template double room_temp_in_K<double>;
#endif
      }   // namespace physics
      namespace geographical
      {
         // Explicitly declare all templates for types so they make it into the
         // shared library else they will not
#ifdef com_sys_lib_EXPORTS
         template float  mean_earth_radius_in_m<float>;
         template double mean_earth_radius_in_m<double>;
         template float  polar_earth_radius_in_m<float>;
         template double polar_earth_radius_in_m<double>;
         template float  equatorial_earth_radius_in_m<float>;
         template double equatorial_earth_radius_in_m<double>;
#endif
      }   // namespace geographical
   }      // namespace constants
}   // namespace com_sys_lib
