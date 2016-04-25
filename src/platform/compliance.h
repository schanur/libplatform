#ifndef PLATFORM_COMPLIANCE_H
#define PLATFORM_COMPLIANCE_H

#include "os_detect.h"

#ifdef PLATFORM_WINDOWS
  #ifndef __func__
    #define __func__ __FUNCTION__
  #endif
#endif

#endif /* PLATFORM_COMPLIANCE_H */
