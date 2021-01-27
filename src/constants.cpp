#include <com_sys_lib/inc/constants.h>

namespace com_sys_lib
{
   namespace constants
   {
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
   }      // namespace constants
}   // namespace com_sys_lib
