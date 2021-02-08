#include <com_sys_lib/inc/parsers.h>

namespace eh = com_sys_lib::parsers::error_handling;
namespace ex = com_sys_lib::exceptions;

namespace com_sys_lib
{
   namespace parsers
   {
      namespace csv_files
      {
         template<typename Type>
         CSLDECLSPEC
         csv_header_data<Type>::csv_header_data(
            std::string header_entry_1_name_in,
            Type        header_rows_in,
            std::string header_entry_2_name_in,
            Type        data_rows_in,
            std::string header_entry_3_name_in,
            Type        columns_in)
            : header_entry_1_name(header_entry_1_name_in)
            , header_rows(header_rows_in)
            , header_entry_2_name(header_entry_2_name_in)
            , data_rows(data_rows_in)
            , header_entry_3_name(header_entry_3_name_in)
            , columns(columns_in)
         {}
#ifdef com_sys_lib_EXPORTS
         template struct CSLDECLSPEC csv_header_data<uint8_t>;
         template struct CSLDECLSPEC csv_header_data<uint16_t>;
#endif
      }   // namespace csv_files
   }      // namespace parsers
}   // namespace com_sys_lib

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

         template<typename IType, typename BSType>
         std::shared_ptr<csv_header_data<IType>> CSLDECLSPEC
         get_csv_header_data(char* buffer, BSType lbufsize, FILE* fp)
         {
            std::string cv;
            uint8_t     return_value;

            std::shared_ptr<csv_header_data<IType>> phd
               = std::make_shared<csv_header_data<IType>>();

            fgets(buffer, lbufsize, fp);

            // The following convert from char * in the operator=
            cv = std::strtok(buffer, ",");   // Should be the string
                                             // header_rows

            eh::compare_strings<std::string>(cv, phd->header_entry_1_name);
            phd->header_rows
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));

            cv = std::strtok(nullptr, ",");   // Should be the string data_rows
            eh::compare_strings<std::string>(cv, phd->header_entry_2_name);
            phd->data_rows
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));

            cv = std::strtok(nullptr, ",");   // Should be the string columns
            eh::compare_strings<std::string>(cv, phd->header_entry_3_name);
            phd->columns
               = static_cast<IType>(std::atoi(std::strtok(nullptr, ",")));

            return phd;
         }

         void CSLDECLSPEC
         parse_codespec_file(std::string filename)
         {
            FILE* fp = get_file_id(filename);
            if(fp != nullptr)
            {
               const uint16_t lbufsize
                  = com_sys_lib::constants::build::MAX_FILE_READ_BUFFER_SIZE;
               char* cv;
               char  buffer[lbufsize];

               /// Get info from header about header row count, data row count,
               // and column countr
               std::shared_ptr<csv_header_data<uint16_t>> phd
                  = get_csv_header_data<uint16_t, uint16_t>(buffer,
                                                            lbufsize,
                                                            fp);

               printf("hd data one is %d", phd->header_rows);
               printf("hd data two is %d", phd->data_rows);
               printf("hd data three is %d", phd->columns);

               uint32_t row    = 0;
               uint32_t column = 0;
               while(fgets(buffer, lbufsize, fp))
               {
                  column = 0;
                  row++;
                  cv = std::strtok(buffer, ",");
                  while(cv != nullptr)
                  {
                     printf("cv is %s", cv);
                     cv = std::strtok(nullptr, ",");
                     column++;
                  }
               }
            }
            fclose(fp);
         }
#ifdef com_sys_lib_EXPORTS
         template std::shared_ptr<csv_header_data<uint8_t>>
            CSLDECLSPEC get_csv_header_data<uint8_t, uint8_t>(char*   buffer,
                                                              uint8_t lbufsize,
                                                              FILE*   fp);
         template std::shared_ptr<csv_header_data<uint8_t>> CSLDECLSPEC
         get_csv_header_data<uint8_t, uint16_t>(char*    buffer,
                                                uint16_t lbufsize,
                                                FILE*    fp);
         template std::shared_ptr<csv_header_data<uint16_t>> CSLDECLSPEC
         get_csv_header_data<uint16_t, uint8_t>(char*   buffer,
                                                uint8_t lbufsize,
                                                FILE*   fp);
         template std::shared_ptr<csv_header_data<uint16_t>> CSLDECLSPEC
         get_csv_header_data<uint16_t, uint16_t>(char*    buffer,
                                                 uint16_t lbufsize,
                                                 FILE*    fp);
#endif
      }   // namespace csv_files
      namespace error_handling
      {
         template<typename SType>
         int CSLDECLSPEC
         compare_strings(SType expected_in, SType received_in)
         {
            std::string expected = expected_in;
            std::string received = received_in;

            try
            {
               if(expected.compare(received))
                  throw ex::csv_files::wrong_header_string(expected, received);
            }
            catch(ex::csv_files::wrong_header_string ex)
            {
               printf("%s", ex.what());
               ex.print_error();
               std::terminate();
               return ex.return_exit_status();
            }
            return EXIT_SUCCESS;
         }
#ifdef com_sys_lib_EXPORTS
         template int compare_strings<std::string>(std::string expected_in,
                                                   std::string received_in);
         template int compare_strings<char*>(char* expected_in,
                                             char* received_in);
#endif
      }   // namespace error_handling
   }      // namespace parsers
}   // namespace com_sys_lib
