#pragma once

#include "types.h"

#ifdef _WIN64
#include <sysinfoapi.h>
static inline i32 get_procs_count(void) {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

#else

#include <sys/sysinfo.h>
static inline i32 get_procs_count(void) { return get_nprocs_conf(); }

#endif
