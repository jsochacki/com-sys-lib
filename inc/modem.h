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

#include <exception>   // For advanced exceptions
#include <memory>      // For std::shared_ptr
#include <vector>      // For vector

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/exceptions.h>
#include <com_sys_lib/inc/string_pack.h>

namespace com_sys_lib
{
   namespace modem
   {
      namespace system
      {
         template<typename Type, typename IType>
         struct CSLDECLSPEC codespec
         {
            public:
            codespec(char* buffer_in, uint32_t lbufsize_in, FILE* fp_in);

            void CSLDECLSPEC get_csv_header_data(void);
            void CSLDECLSPEC read_header_information(void);

            void add_line(
               IType       id_in,
               std::string name_in,
               Type        esno_qef_dB_in,
               Type        spectral_efficiency_bits_per_Hz_in,
               Type        ldpc_rate_in,
               Type        bch_rate_in,
               Type
                           encoded_spectral_efficiency_data_bits_per_symbol_transmitted_in,
               std::string modulation_in,
               std::string ldpc_code_identifier_in,
               Type        ebno_qef_dB_in);

            void print_codespec(void);

            // Local Variables

            // Error Checking Variables
            std::string header_entry_1_name;
            std::string header_entry_2_name;
            std::string header_entry_3_name;

            // Accounting variables
            IType              header_rows;
            IType              data_rows;
            IType              columns;
            IType              count;
            std::vector<IType> index;

            // File Variables
            char*    buffer;
            uint32_t lbufsize;
            FILE*    fp;

            // Codespec file variables
            std::vector<std::string> information;
            std::vector<std::string> parameter_strings;
            std::vector<IType>       id;
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

// This is the section with all the namespace abbreviations

namespace smdm = com_sys_lib::modem::system;

#endif /* MODEM_H_ */
