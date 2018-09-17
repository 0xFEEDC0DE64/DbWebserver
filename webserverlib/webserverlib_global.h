#pragma once

#include <QtGlobal>

#if defined(WEBSERVERLIB_LIBRARY)
#  define WEBSERVERLIB_EXPORT Q_DECL_EXPORT
#else
#  define WEBSERVERLIB_EXPORT Q_DECL_IMPORT
#endif
