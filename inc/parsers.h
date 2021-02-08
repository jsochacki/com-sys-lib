#ifndef PARSERS_H_
#define PARSERS_H_
/**
 * @file parsers.h
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
 * @brief This is the files that holds a general assortment of parsers
 *
 * @details
 *  Currently we have support for command line arguement parsing and file
 *  parsing
 *
 */

#include <cerrno>    // For error handling
#include <cstdio>    // For printf, fprintf, fopen, and fclose
#include <cstdlib>   // For strtof, atoi, atof, exceptions and EXIT_FAILURE
#include <exception> // For advanced exceptions
#include <cstring>   // For strerror
#include <memory>    // For std::shared_ptr
#include <string>    // For string functionality

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/modem.h>
#include <com_sys_lib/inc/exceptions.h>

#include <fcntl.h>   // For io.h which has write, open, and close for bin files

namespace com_sys_lib
{
   namespace parsers
   {
      namespace csv_files
      {
         template<typename Type>
         struct CSLDECLSPEC csv_header_data
         {
            public:
            csv_header_data(std::string header_entry_1_name_in = "header_rows",
                            Type        header_rows_in         = 0,
                            std::string header_entry_2_name_in = "data_rows",
                            Type        data_rows_in           = 0,
                            std::string header_entry_3_name_in = "columns",
                            Type        columns_in             = 0);

            std::string header_entry_1_name;
            Type        header_rows;
            std::string header_entry_2_name;
            Type        data_rows;
            std::string header_entry_3_name;
            Type        columns;
         };
      }   // namespace csv_files
   }      // namespace parsers
}   // namespace com_sys_lib

namespace com_sys_lib
{
   namespace parsers
   {
      namespace cli
      {
         void CSLDECLSPEC display_arguements(int argc, char* argv[]);
      }
      namespace csv_files
      {
         FILE* CSLDECLSPEC get_file_id(std::string filename);

         template<typename IType, typename BSType>
         std::shared_ptr<csv_header_data<IType>> CSLDECLSPEC
         get_csv_header_data(char* buffer, BSType lbufsize, FILE* fp);

         void CSLDECLSPEC parse_codespec_file(std::string filename);
      }   // namespace csv_files
      namespace error_handling
      {
         template<typename SType>
         int CSLDECLSPEC compare_strings(SType expected_in,
                                           SType received_in);
      }
   }   // namespace parsers
}   // namespace com_sys_lib

#endif /* PARSERS_H_ */
