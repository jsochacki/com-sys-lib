#include "com-sys-lib_export.h"
#include "starting.h"
#include "../include/public_header.h"
#include "../inc/secret_header.h"

namespace com-sys-lib {

std::string DECLSPEC version(void)
{
#ifdef COM-SYS-LIB_EXPORT
   return std::string("0.0.0 SHARED");
#else
   return std::string("0.0.0 NOT SHARED");
#endif
}

std::string DECLSPEC secret(void)
{
   return secret_string;
}

std::string DECLSPEC public(void)
{
   return public_string;
}
}
