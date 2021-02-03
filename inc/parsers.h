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
#include <cstring>   // For strerror
#include <string>    // For string functionality

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>
#include <com_sys_lib/inc/constants.h>
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

         void CSLDECLSPEC parse_codespec_file(std::string filename);
      }   // namespace csv_files
   }      // namespace parsers
}   // namespace com_sys_lib

#endif /* PARSERS_H_ */
