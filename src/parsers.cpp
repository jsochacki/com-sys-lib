#include <com_sys_lib/inc/parsers.h>

namespace com_sys_lib
{
   namespace parsers
   {
      namespace cli
      {
         void CSLDECLSPEC
         display_arguements(int argc, char* argv[])
         {
            int counter;
            printf("Program Name Is: %s", argv[0]);
            if(argc == 1)
               printf("\nNo Extra Command Line Argument Passed Other Than "
                      "Program Name");
            if(argc >= 2)
            {
               printf("\nNumber Of Arguments Passed: %d", argc);
               printf("\n----Following Are The Command Line Arguments "
                      "Passed----");
               for(counter = 0; counter < argc; counter++)
                  printf("\nargv[%d]: %s", counter, argv[counter]);
            }
         }
      }   // namespace cli
      namespace csv_files
      {
         /**
          * Returns nullptr on failure and file id otherwise
          */
         FILE* CSLDECLSPEC
         get_file_id(std::string filename)
         {
            FILE* fp = nullptr;

            fp = fopen(filename.c_str(), "r");

            if(fp == nullptr)
            {
               printf("Unable to open file %s becuase %s \n",
                      filename.c_str(),
                      std::strerror(errno));
               return nullptr;
            }
            return fp;
         }

         int CSLDECLSPEC
         parse_codespec_file(std::string filename)
         {
            FILE* fp = get_file_id(filename);
            if(fp != nullptr)
            {
               const uint16_t lbufsize
                  = com_sys_lib::constants::build::MAX_FILE_READ_BUFFER_SIZE;
               char* cv;
               char  buffer[lbufsize];

               struct smdm::codespec<double, uint16_t> cs(buffer, lbufsize, fp);
               cs.print_codespec();

               fclose(fp);
            }
         }
#ifdef com_sys_lib_EXPORTS
#endif
      }   // namespace csv_files
      namespace error_handling
      {
         template<typename SType>
         void CSLDECLSPEC
         compare_strings(SType expected_in, SType received_in)
         {
            std::string expected = expected_in;
            std::string received = received_in;

            try
            {
               if(expected.compare(received))
                  throw ex::csv_files::wrong_header_string(expected, received);
            }
            catch(ex::csv_files::wrong_header_string& ex)
            {
               printf("%s", ex.what());
               ex.print_error();
               throw;
            }
         }
#ifdef com_sys_lib_EXPORTS
         template void compare_strings<std::string>(std::string expected_in,
                                                    std::string received_in);
         template void compare_strings<char*>(char* expected_in,
                                              char* received_in);
#endif
      }   // namespace error_handling
   }      // namespace parsers
}   // namespace com_sys_lib
