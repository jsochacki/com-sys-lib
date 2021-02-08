/**
 * @file exceptions.cpp
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
 * @brief This is where all of the custom exceptions are defined
 *
 * @details
 *  There is an exception defined for everything basically to keep things
 *  cleaner and more consistant
 *
 */

#include <com_sys_lib/inc/exceptions.h>

namespace com_sys_lib
{
   namespace exceptions
   {
      namespace csv_files
      {
         wrong_header_string::wrong_header_string(std::string expected_in,
                                                  std::string received_in)
            : expected(expected_in)
            , received(received_in)
         {}

         const char*
         wrong_header_string::what() const noexcept
         {
            return "Exception: Wrong csv file header data strings.\n";
         }

         void
         wrong_header_string::print_error(void)
         {
            printf("ERROR: String expected: \"%s\"\n       String "
                   "received: "
                   "\"%s\"\n",
                   expected.c_str(),
                   received.c_str());
         }

         int
         wrong_header_string::return_exit_status(void)
         {
            return EXIT_FAILURE;
         }

#ifdef com_sys_lib_EXPORTS
#endif
      }   // namespace csv_files
   }      // namespace exceptions
}   // namespace com_sys_lib
