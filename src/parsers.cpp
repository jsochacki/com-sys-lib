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

         void CSLDECLSPEC
         parse_codespec_file(std::string filename)
         {
            FILE* fp = get_file_id(filename);
            if(fp != nullptr)
            {
               printf(
                  "constant was  good as you can see %u\n",
                  com_sys_lib::constants::build::MAX_FILE_READ_BUFFER_SIZE);
               fclose(fp);
            }
         }
      }   // namespace csv_files

   }   // namespace parsers
}   // namespace com_sys_lib
