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

#include <cerrno>      // For error handling
#include <cstdio>      // For printf, fprintf, fopen, and fclose
#include <cstdlib>     // For strtof, atoi, atof, exceptions and EXIT_FAILURE
#include <cstring>     // For strerror
#include <exception>   // For advanced exceptions
#include <memory>      // For std::shared_ptr
#include <string>      // For string functionality

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/exceptions.h>
#include <com_sys_lib/inc/modem.h>
#include <fcntl.h>   // For io.h which has write, open, and close for bin files

namespace smdm = com_sys_lib::modem::system;
namespace eh   = com_sys_lib::parsers::error_handling;
namespace ex   = com_sys_lib::exceptions;

namespace com_sys_lib
{
   namespace parsers
   {
      namespace csv_files
      {
         template<typename IType>
         struct CSLDECLSPEC csv_header_data
         {
            public:
            csv_header_data(std::string header_entry_1_name_in = "header_rows",
                            IType        header_rows_in         = 0,
                            std::string header_entry_2_name_in = "data_rows",
                            IType        data_rows_in           = 0,
                            std::string header_entry_3_name_in = "columns",
                            IType        columns_in             = 0);

            std::string header_entry_1_name;
            IType        header_rows;
            std::string header_entry_2_name;
            IType        data_rows;
            std::string header_entry_3_name;
            IType        columns;
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

         int CSLDECLSPEC parse_codespec_file(std::string filename);
      }   // namespace csv_files
      namespace error_handling
      {
         template<typename SType>
         void CSLDECLSPEC compare_strings(SType expected_in,
                                          SType received_in);
      }
   }   // namespace parsers
}   // namespace com_sys_lib

#endif /* PARSERS_H_ */
