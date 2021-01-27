#ifndef LINK_BUDGET_H_
#define LINK_BUDGET_H_

#include <cmath>

#include <com_sys_lib/inc/com_sys_lib_build_settings.h>

namespace com_sys_lib
{
   namespace link_budget
   {
      template<typename Type> Type CSLDECLSPEC kbT_0C(void);
      template<typename Type>
      Type CSLDECLSPEC kbT_from_K(Type temperature_in_K);
      template<typename Type>
      Type CSLDECLSPEC kbT_from_C(Type temperature_in_C);
      template<typename Type>
      Type CSLDECLSPEC from_C_to_K(Type temperature_in_C);
      template<typename Type> Type CSLDECLSPEC from_w_to_dbw(Type watts);
      template<typename Type> Type CSLDECLSPEC from_w_to_dbm(Type watts);
      template<typename Type> Type CSLDECLSPEC kb_dbw(void);
      template<typename Type>
      Type CSLDECLSPEC N0_from_K(Type temperature_in_K, Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC N0_from_C(Type temperature_in_C, Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC N0_dbw_from_K(Type temperature_in_K,
                                     Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC N0_dbw_from_C(Type temperature_in_C,
                                     Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC N0_dbm_from_K(Type temperature_in_K,
                                     Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC N0_dbm_from_C(Type temperature_in_C,
                                     Type bandwidth_in_Hz);
      template<typename Type>
      Type CSLDECLSPEC lambda_from_f(Type bandwidth_in_Hz);
   }   // namespace link_budget
}   // namespace com_sys_lib

#endif /* LINK_BUDGET_H_ */