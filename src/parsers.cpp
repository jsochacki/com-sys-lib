#include <com_sys_lib/inc/parsers.h>

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
         template struct CSLDECLSPEC csv_header_data<uint32_t>;
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

               std::shared_ptr<csv_header_data<uint16_t>> phd = nullptr;
               std::shared_ptr<smdm::codespec<double>>    cs  = nullptr;

               uint32_t row;
               uint32_t column;

               /// Get info from header about header row count, data row count,
               // and column countr
               try
               {
                  phd = get_csv_header_data<uint16_t, uint16_t>(buffer,
                                                                lbufsize,
                                                                fp);
                  if(phd == nullptr)
                     throw std::invalid_argument("Exception: function "
                                                 "get_csv_header_data call "
                                                 "failed for some reason that "
                                                 "I currently don't protect "
                                                 "against.  Please look into "
                                                 "this function and your use "
                                                 "of it.");
               }
               catch(ex::csv_files::wrong_header_string& ex)
               {
                  return EXIT_FAILURE;
               }
               catch(const std::invalid_argument& ex)
               {
                  return EXIT_FAILURE;
               }

               try
               {
                  cs = std::make_shared<smdm::codespec<double>>(phd);

                  if(cs == nullptr)
                     throw std::invalid_argument("Exception: struct allocation"
                                                 " for codespec "
                                                 "failed for some reason that "
                                                 "I currently don't protect "
                                                 "against.  Please look into "
                                                 "this function and your use "
                                                 "of it.");
               }
               catch(const std::invalid_argument& ex)
               {
                  return EXIT_FAILURE;
               }

               if(phd->header_rows > 0)
               {
                  row = 0;

                  while(row < phd->header_rows)
                  {
                     fgets(buffer, lbufsize, fp);
                     column = 0;
                     cv     = std::strtok(buffer, ",");
                     while(cv != nullptr)
                     {
                        cs->add_information(cv);
                        cv = std::strtok(nullptr, ",");
                        ++column;
                     }
                     ++row;
                  }
               }

               cs->print_codespec();

               if(phd->data_rows > 0)
               {
                  row = 0;

                  while(row < phd->data_rows)
                  {
                     fgets(buffer, lbufsize, fp);
                     column = 0;
                     cv     = std::strtok(buffer, ",");
                     while(cv != nullptr)
                     {
                        printf("header cv row %d, column %d, is %s\n",
                               row,
                               column,
                               cv);
                        cv = std::strtok(nullptr, ",");
                        ++column;
                     }
                     ++row;
                  }
               }
               fclose(fp);
            }
         }
#ifdef com_sys_lib_EXPORTS
         template std::shared_ptr<csv_header_data<uint8_t>>
            CSLDECLSPEC get_csv_header_data<uint8_t>(char*    buffer,
                                                     uint32_t lbufsize,
                                                     FILE*    fp);
         template std::shared_ptr<csv_header_data<uint16_t>>
            CSLDECLSPEC get_csv_header_data<uint16_t>(char*    buffer,
                                                      uint32_t lbufsize,
                                                      FILE*    fp);
         template std::shared_ptr<csv_header_data<uint32_t>>
            CSLDECLSPEC get_csv_header_data<uint32_t>(char*    buffer,
                                                      uint32_t lbufsize,
                                                      FILE*    fp);
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
