#include <com_sys_lib/inc/constants.h>
#include <com_sys_lib/inc/link_budget.h>

namespace physcons = com_sys_lib::constants::physics;

namespace com_sys_lib
{
   namespace link_budget
   {
      template<typename Type> Type CSLDECLSPEC kb_dbw(void)
      {
         return 10*std::log10(static_cast<Type>(physcons::boltzmanns_constant));
      }
   }
}

