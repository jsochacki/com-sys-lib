#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#include <cmath>

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/link_budget.h>
#include <gsl/gsl_sf_bessel.h>

namespace mathcons = com_sys_lib::constants::math;
namespace physcons = com_sys_lib::constants::physics;
namespace lb       = com_sys_lib::link_budget;

namespace com_sys_lib
{
   namespace transceiver
   {
      namespace system
      {
         template<typename Type> class CSLDECLSPEC dish_transceiver
         {
            public:
            dish_transceiver(
               Type center_frequency_in_Hz_in = 0, Type bandwidth_in_Hz_in = 0,
               Type dish_diameter_in_m_in = 0, Type antenna_tx_efficiency_in = 0,
               Type antenna_rx_efficiency_in   = 0,
               Type pa_saturated_power_in_W_in = 0, Type pa_feed_loss_in_dB_in = 0,
               Type pa_linear_power_in_W_in = 0, Type tx_carrier_rolloff_in = 0,
               Type rx_carrier_rolloff_in = 0);

            void show_transmit_info(void);

            private:
            Type center_frequency_in_Hz;
            Type bandwidth_in_Hz;
            Type dish_diameter_in_m;
            Type antenna_tx_efficiency;
            Type antenna_rx_efficiency;
            Type pa_saturated_power_in_W;
            Type pa_feed_loss_in_dB;
            Type pa_linear_power_in_W;
            Type tx_carrier_rolloff;
            Type rx_carrier_rolloff;
            //
            // The following are derived quantities
            Type lambda_in_m;
            // The following are derived tx quantities
            Type antenna_tx_half_beam_width_loss_contour;
            Type boresight_tx_gain_in_linear;
            Type boresight_tx_gain_in_dBi;
            Type antenna_tx_loss_at_contour_in_dB;
            Type half_power_tx_beamwidth_in_degrees;
            Type EIRP;
            Type maximum_saturated_PSD_in_dBW_per_Hz;
            // The following are derived rx quantities
            Type boresight_rx_gain_in_dBi;
            Type half_power_rx_beamwidth_in_degrees;
            Type G_by_T;
            Type system_temperature_in_K;
            Type system_temperature_in_dB;
            Type system_rx_noise_figure_in_dB;
            // The following are convenience and or intermediate quantities
            Type pi_d_by_lambda;
         };
      }   // namespace system

   }   // namespace transceiver
}   // namespace com_sys_lib

#endif /* TRANSCEIVER_H_ */
