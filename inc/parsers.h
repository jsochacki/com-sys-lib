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

#include <exception>   // For advanced exceptions
#include <memory>      // For std::shared_ptr

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/exceptions.h>
#include <com_sys_lib/inc/modem.h>
#include <com_sys_lib/inc/string_pack.h>
#include <fcntl.h>   // For io.h which has write, open, and close for bin files

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

// This is the section with all the namespace abbreviations

namespace eh = com_sys_lib::parsers::error_handling;

#endif /* PARSERS_H_ */
