#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/link_budget.h>

namespace mathcons = com_sys_lib::constants::math;
namespace physcons = com_sys_lib::constants::physics;
namespace geocons  = com_sys_lib::constants::geographical;

namespace com_sys_lib
{
   namespace link_budget
   {
      namespace conversions
      {
         template<typename Type>
         Type CSLDECLSPEC
         kbT_0C(void)
         {
            return physcons::boltzmanns_constant<
                      Type> * physcons::zero_C_in_kelvin<Type>;
         }

         template<typename Type>
         Type CSLDECLSPEC
         kbT_from_K(Type temperature_in_K)
         {
            return physcons::boltzmanns_constant<Type> * temperature_in_K;
         }

         template<typename Type>
         Type CSLDECLSPEC
         kbT_from_C(Type temperature_in_C)
         {
            return kbT_from_K<Type>(from_C_to_K<Type>(temperature_in_C));
         }

         template<typename Type>
         Type CSLDECLSPEC
         from_C_to_K(Type temperature_in_C)
         {
            return physcons::zero_C_in_kelvin<Type> + temperature_in_C;
         }

         template<typename Type>
         Type CSLDECLSPEC
         from_w_to_dbw(Type watts)
         {
            return 10 * std::log10(static_cast<Type>(watts));
         }

         template<typename Type>
         Type CSLDECLSPEC
         from_w_to_dbm(Type watts)
         {
            return from_w_to_dbw(watts) + static_cast<Type>(30.0);
         }

         template<typename Type>
         Type CSLDECLSPEC
         kb_dbw(void)
         {
            return from_w_to_dbw(
               static_cast<Type>(physcons::boltzmanns_constant<Type>));
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_from_K(Type temperature_in_K, Type bandwidth_in_Hz)
         {
            return kbT_from_K<Type>(temperature_in_K) * bandwidth_in_Hz;
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_from_C(Type temperature_in_C, Type bandwidth_in_Hz)
         {
            return kbT_from_C<Type>(temperature_in_C) * bandwidth_in_Hz;
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_dbw_from_K(Type temperature_in_K, Type bandwidth_in_Hz)
         {
            return from_w_to_dbw<Type>(
               N0_from_K<Type>(temperature_in_K, bandwidth_in_Hz));
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_dbw_from_C(Type temperature_in_C, Type bandwidth_in_Hz)
         {
            return from_w_to_dbw<Type>(
               N0_from_C<Type>(temperature_in_C, bandwidth_in_Hz));
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_dbm_from_K(Type temperature_in_K, Type bandwidth_in_Hz)
         {
            return from_w_to_dbm<Type>(
               N0_from_K<Type>(temperature_in_K, bandwidth_in_Hz));
         }

         template<typename Type>
         Type CSLDECLSPEC
         N0_dbm_from_C(Type temperature_in_C, Type bandwidth_in_Hz)
         {
            return from_w_to_dbm<Type>(
               N0_from_C<Type>(temperature_in_C, bandwidth_in_Hz));
         }

         template<typename Type>
         Type CSLDECLSPEC
         lambda_from_f(Type frequency_in_Hz)
         {
            return physcons::speed_of_light<Type> / frequency_in_Hz;
         }

         template<typename Type>
         Type CSLDECLSPEC
         f_from_lambda(Type wavelength_in_m)
         {
            return physcons::speed_of_light<Type> / wavelength_in_m;
         }

         // Explicitly declare all templates for types so they make it into the
         // shared library else they will not
#ifdef com_sys_lib_EXPORTS
         template float CSLDECLSPEC  kbT_0C<float>(void);
         template double CSLDECLSPEC kbT_0C<double>(void);
         template float CSLDECLSPEC  kbT_from_K<float>(float temperature_in_K);
         template double CSLDECLSPEC
                                    kbT_from_K<double>(double temperature_in_K);
         template float CSLDECLSPEC kbT_from_C<float>(float temperature_in_C);
         template double CSLDECLSPEC
                                    kbT_from_C<double>(double temperature_in_C);
         template float CSLDECLSPEC from_C_to_K<float>(float temperature_in_C);
         template double CSLDECLSPEC
                                     from_C_to_K<double>(double temperature_in_C);
         template float CSLDECLSPEC  from_w_to_dbw<float>(float watts);
         template double CSLDECLSPEC from_w_to_dbw<double>(double watts);
         template float CSLDECLSPEC  from_w_to_dbm<float>(float watts);
         template double CSLDECLSPEC from_w_to_dbm<double>(double watts);
         template float CSLDECLSPEC  kb_dbw<float>(void);
         template double CSLDECLSPEC kb_dbw<double>(void);
         template float CSLDECLSPEC  N0_from_K<float>(float temperature_in_K,
                                                     float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_from_K<double>(double temperature_in_K,
                                                       double bandwidth_in_Hz);
         template float CSLDECLSPEC  N0_from_C<float>(float temperature_in_C,
                                                     float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_from_C<double>(double temperature_in_C,
                                                       double bandwidth_in_Hz);
         template float CSLDECLSPEC
                                     N0_dbw_from_K<float>(float temperature_in_K, float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_dbw_from_K<double>(
            double temperature_in_K, double bandwidth_in_Hz);
         template float CSLDECLSPEC
                                     N0_dbw_from_C<float>(float temperature_in_C, float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_dbw_from_C<double>(
            double temperature_in_C, double bandwidth_in_Hz);
         template float CSLDECLSPEC
                                     N0_dbm_from_K<float>(float temperature_in_K, float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_dbm_from_K<double>(
            double temperature_in_K, double bandwidth_in_Hz);
         template float CSLDECLSPEC
                                     N0_dbm_from_C<float>(float temperature_in_C, float bandwidth_in_Hz);
         template double CSLDECLSPEC N0_dbm_from_C<double>(
            double temperature_in_C, double bandwidth_in_Hz);
         template float CSLDECLSPEC lambda_from_f<float>(float frequency_in_Hz);
         template double CSLDECLSPEC
                                    lambda_from_f<double>(double frequency_in_Hz);
         template float CSLDECLSPEC f_from_lambda<float>(float wavelength_in_m);
         template double CSLDECLSPEC
         f_from_lambda<double>(double wavelength_in_m);
#endif
      }   // namespace conversions
      namespace geometric_calculations
      {
         template<typename Type>
         Type CSLDECLSPEC
         radio_horizon(Type height_above_sea_level_in_m)
         {
            return std::sqrt((2
                              * (geocons::mean_earth_radius_in_m<
                                    Type> * height_above_sea_level_in_m))
                             + std::pow(height_above_sea_level_in_m, 2));
         }

         template<typename Type>
         Type CSLDECLSPEC
         degrees_from_zenith(Type topographical_separation_in_m)
         {
            return (360 * topographical_separation_in_m)
                   / (2
                      * mathcons::pi<
                         Type> * geocons::mean_earth_radius_in_m<Type>);
         }

         template<typename Type>
         Type CSLDECLSPEC
         slant_range(Type height_above_sea_level_in_m,
                     Type satellite_height_in_m, Type degrees_from_zenith)
         {
            return std::sqrt(
               std::pow(geocons::mean_earth_radius_in_m<
                           Type> + height_above_sea_level_in_m,
                        2)
               + std::pow(
                  geocons::mean_earth_radius_in_m<Type> + satellite_height_in_m,
                  2)
               - (2
                  * (geocons::mean_earth_radius_in_m<
                        Type> + height_above_sea_level_in_m)
                  * (geocons::mean_earth_radius_in_m<
                        Type> + satellite_height_in_m)
                  * std::cos((mathcons::pi<Type> / 180)
                     * degrees_from_zenith)));
         }

         // Explicitly declare all templates for types so they make it into the
         // shared library else they will not
#ifdef com_sys_lib_EXPORTS
         template float CSLDECLSPEC
         radio_horizon<float>(float height_above_sea_level_in_m);
         template double CSLDECLSPEC
         radio_horizon<double>(double height_above_sea_level_in_m);
         template long double CSLDECLSPEC
         radio_horizon<long double>(long double height_above_sea_level_in_m);
         template float CSLDECLSPEC
         degrees_from_zenith<float>(float topographical_separation_in_m);
         template double CSLDECLSPEC
         degrees_from_zenith<double>(double topographical_separation_in_m);
         template long double CSLDECLSPEC
                                    degrees_from_zenith<long double>(long double topographical_separation_in_m);
         template float CSLDECLSPEC slant_range<float>(
            float height_above_sea_level_in_m, float satellite_height_in_m,
            float degrees_from_zenith);
         template double CSLDECLSPEC slant_range<double>(
            double height_above_sea_level_in_m, double satellite_height_in_m,
            double degrees_from_zenith);
         template long double CSLDECLSPEC slant_range<long double>(
            long double height_above_sea_level_in_m, long double satellite_height_in_m,
            long double degrees_from_zenith);
#endif
      }   // namespace geometric_calculations
   }      // namespace link_budget
}   // namespace com_sys_lib
