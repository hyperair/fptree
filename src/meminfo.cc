#include <meminfo.hh>

#ifdef __WIN32__
#   define PSAPI_VERSION 1
#   include <windows.h>
#   include <psapi.h>

long fpt::get_peakmem_kb ()
{
    PROCESS_MEMORY_COUNTERS pmc;

    GetProcessMemoryInfo (GetCurrentProcess (), &pmc, sizeof (pmc));

    return pmc.PeakWorkingSetSize / 1024;
}

#else
#   include <sys/time.h>
#   include <sys/resource.h>

long fpt::get_peakmem_kb ()
{
    rusage res_usage;
    getrusage (RUSAGE_SELF, &res_usage);

    return res_usage.ru_maxrss;
}

#endif
