
#ifndef CSLDECLSPEC_H
#define CSLDECLSPEC_H

#ifdef COM_SYS_LIB_BUILD_SETTINGS_H_STATIC_DEFINE
#  define CSLDECLSPEC
#  define COM_SYS_LIB_BUILD_SETTINGS_H_NO_EXPORT
#else
#  ifndef CSLDECLSPEC
#    ifdef com_sys_lib_EXPORTS
        /* We are building this library */
#      define CSLDECLSPEC __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CSLDECLSPEC __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef COM_SYS_LIB_BUILD_SETTINGS_H_NO_EXPORT
#    define COM_SYS_LIB_BUILD_SETTINGS_H_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED
#  define COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED_EXPORT
#  define COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED_EXPORT CSLDECLSPEC COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED
#endif

#ifndef COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED_NO_EXPORT
#  define COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED_NO_EXPORT COM_SYS_LIB_BUILD_SETTINGS_H_NO_EXPORT COM_SYS_LIB_BUILD_SETTINGS_H_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COM_SYS_LIB_BUILD_SETTINGS_H_NO_DEPRECATED
#    define COM_SYS_LIB_BUILD_SETTINGS_H_NO_DEPRECATED
#  endif
#endif

#endif /* CSLDECLSPEC_H */
