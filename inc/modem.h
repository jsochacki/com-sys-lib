#ifndef MODEM_H_
#define MODEM_H_
/**
 * @file modem.h
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
 * @brief This is the files that holds a general assortment of modem functions
 *
 * @details
 *  Currently it just holds some modem structures and things that are good for
 *  system level analysis rather them actual modulator / demodulator functions
 *
 */

#include <cerrno>      // For error handling
#include <cstdio>      // For printf, fprintf, fopen, and fclose
#include <cstdlib>     // For strtof, atoi, atof, exceptions and EXIT_FAILURE
#include <cstring>     // For strerror
#include <exception>   // For advanced exceptions
#include <memory>      // For std::shared_ptr
#include <string>      // For string functionality
#include <vector>      // For vector

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/exceptions.h>

namespace com_sys_lib
{
   namespace modem
   {
      namespace system
      {
         template<typename Type>
         struct CSLDECLSPEC codespec
         {
            public:
            codespec();

            std::vector<std::string> information;
            std::vector<uint8_t>     id;
            std::vector<std::string> name;
            std::vector<Type>        esno_qef_dB;
            std::vector<Type>        spectral_efficiency_bits_per_Hz;
            std::vector<Type>        ldpc_rate;
            std::vector<Type>        bch_rate;
            std::vector<Type>
                                     encoded_spectral_efficiency_data_bits_per_symbol_transmitted;
            std::vector<std::string> modulation;
            std::vector<std::string> ldpc_code_identifier;
            std::vector<Type>        ebno_qef_dB;
         };
      }   // namespace system
   }      // namespace modem
}   // namespace com_sys_lib

#endif /* MODEM_H_ */
