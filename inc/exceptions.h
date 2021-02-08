/**
 * @file exceptions.h
 *
 * @author John Sochacki
 * @version 0.0.0
 * @date 1/1/2021
 *
 * @warning Extremely minimal exceptions
 * @bug A lot
 * @copyright GNU General Public License.v3.0
 *
 * @pre None
 * @note None
 *
 * @brief This is where all of the custom exceptions are defined
 *
 * @details
 *  There is an exception defined for everything basically to keep things
 *  cleaner and more consistant
 *
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <cerrno>   // For error handling
#include <cstdint>
#include <cstdio>      // For printf, fprintf, fopen, and fclose
#include <cstdlib>     // For strtof, atoi, atof, exceptions and EXIT_FAILURE
#include <cstring>     // For strerror
#include <exception>   // For advanced exceptions
#include <memory>      // For std::shared_ptr
#include <string>      // For string functionality

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>

namespace com_sys_lib
{
   namespace exceptions
   {
      namespace csv_files
      {
         struct wrong_header_string : public std::exception
         {
            public:
            wrong_header_string(std::string expected_in, std::string received_in);
            const char* what() const noexcept;
            void print_error(void);
            int return_exit_status(void);

            std::string expected;
            std::string received;
         };
      }   // namespace csv_files
   }      // namespace exceptions
}   // namespace com_sys_lib

#endif /* EXCEPTIONS_H_ */
