#include <com_sys_lib/inc/modem.h>

namespace com_sys_lib
{
   namespace modem
   {
      namespace system
      {
         template<typename Type, typename IType>
         CSLDECLSPEC
         codespec<Type, IType>::codespec(char*    buffer_in,
                                         uint32_t lbufsize_in,
                                         FILE*    fp_in)
            : buffer(buffer_in)
            , lbufsize(lbufsize_in)
            , fp(fp_in)
         {
            // Allocate Memory
            phd = std::make_shared<csv_header_data<IType>>();

            // Initialize count
            count = 0;

            // Run initialization methods
            get_csv_header_data<IType>();
         }

         template<typename Type, typename IType>
         void CSLDECLSPEC
         codespec<Type, IType>::get_csv_header_data(void)
         {
            std::string cv;

            fgets(buffer, lbufsize, fp);

            // The following convert from char * in the operator=
            cv = std::strtok(buffer, ",");   // Should be the header_rows

            try
            {
               eh::compare_strings<std::string>(cv, phd->header_entry_1_name);
            }
            catch(ex::csv_files::wrong_header_string& ex)
            {
               throw;
            }

            phd->header_rows
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));
            cv = std::strtok(nullptr, ",");   // Should be the string data_rows

            try
            {
               eh::compare_strings<std::string>(cv, phd->header_entry_2_name);
            }
            catch(ex::csv_files::wrong_header_string& ex)
            {
               throw;
            }

            phd->data_rows
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));
            cv = std::strtok(nullptr, ",");   // Should be the string columns

            try
            {
               eh::compare_strings<std::string>(cv, phd->header_entry_3_name);
            }
            catch(ex::csv_files::wrong_header_string& ex)
            {
               throw;
            }

            phd->columns
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));

         }

         template<typename Type, typename IType>
         void CSLDECLSPEC
         codespec<Type, IType>::add_header_information(void)
         {
            //TODO here just read the file and do the work like you do in parser
            //currently 
            std::string lstr;
            lstr = information_in;
            information.push_back(lstr);
         }

         template<typename Type, typename IType>
         int CSLDECLSPEC
         codespec<Type, IType>::add_line(
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
            Type        ebno_qef_dB_in)
         {
            index.push_back(count++);
            id.push_back(id_in);
            name.push_back(name_in);
            esno_qef_dB.push_back(esno_qef_dB_in);
            spectral_efficiency_bits_per_Hz.push_back(
               spectral_efficiency_bits_per_Hz_in);
            ldpc_rate.push_back(ldpc_rate_in);
            bch_rate.push_back(bch_rate_in);
            encoded_spectral_efficiency_data_bits_per_symbol_transmitted.push_back(
               encoded_spectral_efficiency_data_bits_per_symbol_transmitted_in);
            modulation.push_back(modulation_in);
            ldpc_code_identifier.push_back(ldpc_code_identifier_in);
            ebno_qef_dB.push_back(ebno_qef_dB_in);
         }

         template<typename Type, typename IType>
         int CSLDECLSPEC
         codespec<Type, IType>::print_codespec(void)
         {
            IType row, column;

            if(header_rows > 0)
            {
               // First row for this type is information row
               for(auto it : information)
               { printf("Code information %s\n", it); }

               // Second row for this type is header column names
               for(auto it : name) { printf("Header Column Name %s ", it); }
               printf("\n");
            }
            /*
                        if(data_rows > 0)
                        {
                           for(IType row = 0; row < count; ++row)
                           {
                              printf("Code ID: %d\n", id[row]);
                              printf("Code Name: %s\n", name[row]);
                           }
                        }
                        */
         }

#ifdef com_sys_lib_EXPORTS
         template struct CSLDECLSPEC codespec<float, uint16_t>;
         template struct CSLDECLSPEC codespec<double, uint16_t>;
         template struct CSLDECLSPEC codespec<long double, uint16_t>;
         template int CSLDECLSPEC
         codespec<float, uint16_t>::add_information<char*>(
            char* information_in);
         template int CSLDECLSPEC
         codespec<double, uint16_t>::add_information<char*>(
            char* information_in);
         template int CSLDECLSPEC
         codespec<long double, uint16_t>::add_information<char*>(
            char* information_in);
         template int CSLDECLSPEC
         codespec<float, uint16_t>::add_information<std::string>(
            std::string information_in);
         template int CSLDECLSPEC
         codespec<double, uint16_t>::add_information<std::string>(
            std::string information_in);
         template int CSLDECLSPEC
         codespec<long double, uint16_t>::add_information<std::string>(
            std::string information_in);
#endif
      }   // namespace system
   }      // namespace modem
}   // namespace com_sys_lib
