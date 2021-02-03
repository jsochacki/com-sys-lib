#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/transceiver.h>

namespace physcons = com_sys_lib::constants::physics;

namespace com_sys_lib
{
   namespace transceiver
   {
      namespace system
      {
         template<typename Type>
         CSLDECLSPEC
         dish_transceiver<Type>::dish_transceiver(
            Type earth_station_height_above_sea_level_in_m_in,
            Type satellite_height_m_in,
            Type center_frequency_in_Hz_in,
            Type bandwidth_in_Hz_in,
            Type dish_diameter_in_m_in,
            Type antenna_tx_efficiency_in,
            Type antenna_rx_efficiency_in,
            Type pa_saturated_power_in_W_in,
            Type pa_feed_loss_in_dB_in,
            Type pa_linear_power_in_W_in,
            Type tx_carrier_rolloff_in,
            Type rx_carrier_rolloff_in)
            : center_frequency_in_Hz(center_frequency_in_Hz_in)
            , bandwidth_in_Hz(bandwidth_in_Hz_in)
            , dish_diameter_in_m(dish_diameter_in_m_in)
            , antenna_tx_efficiency(antenna_tx_efficiency_in)
            , antenna_rx_efficiency(antenna_rx_efficiency_in)
            , pa_saturated_power_in_W(pa_saturated_power_in_W_in)
            , pa_feed_loss_in_dB(pa_feed_loss_in_dB_in)
            , pa_linear_power_in_W(pa_linear_power_in_W_in)
            , tx_carrier_rolloff(tx_carrier_rolloff_in)
            , rx_carrier_rolloff(rx_carrier_rolloff_in)
         {
            // Set initial values for variables not passed in but used in
            // initialization
            antenna_tx_half_beam_width_loss_contour = 0;

            lambda_in_m = lbconv::lambda_from_f<Type>(center_frequency_in_Hz);

            pi_d_by_lambda
               = mathcons::pi<Type> * (dish_diameter_in_m / lambda_in_m);

            // The following are derived tx quantities

            boresight_tx_gain_in_linear
               = antenna_tx_efficiency * std::pow(pi_d_by_lambda, 2);

            boresight_tx_gain_in_dBi
               = 10 * std::log10(boresight_tx_gain_in_linear);

            antenna_tx_loss_at_contour_in_dB
               = boresight_tx_gain_in_dBi
                 - 10
                      * std::log10(
                         boresight_tx_gain_in_linear
                         * std::pow(
                            2
                               * (static_cast<Type>(gsl_sf_bessel_J1(
                                     pi_d_by_lambda
                                     * std::sin(
                                        antenna_tx_half_beam_width_loss_contour
                                        * (mathcons::pi<Type> / 180))))
                                  / (pi_d_by_lambda
                                     * std::sin(
                                        antenna_tx_half_beam_width_loss_contour
                                        * (mathcons::pi<Type> / 180)))),
                            2));
            /*
                           Type half_power_beamwidth_in_degrees;
                           Type EIRP;
                           Type maximum_saturated_PSD_in_dBW_per_Hz;
                           // The following are derived rx quantities
                           Type boresight_rx_gain_in_dBi;
                           Type half_power_beamwidth_in_degrees;
                           Type G_by_T;
                           Type system_temperature_in_K;
                           Type system_temperature_in_dB;
                           Type system_rx_noise_figure_in_dB;
                           */
         }

         template<typename Type>
         void CSLDECLSPEC
         dish_transceiver<Type>::print_transmit_info(void)
         {
            printf("\n lambda is %f \n", this->lambda_in_m);
            printf("\n boresight tx gain is %f \n",
                   this->boresight_tx_gain_in_dBi);
            printf("\n antenna loss at countour is %f \n",
                   this->antenna_tx_loss_at_contour_in_dB);
         }
         // Explicitly declare all templates for types so they make it into the
         // shared library else they will not
#ifdef com_sys_lib_EXPORTS
         template class dish_transceiver<float>;
         template class dish_transceiver<double>;
#endif
      }   // namespace system

   }   // namespace transceiver
}   // namespace com_sys_lib
