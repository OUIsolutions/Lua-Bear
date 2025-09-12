//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.dependencie.h"
//silver_chain_scope_end

#if defined(__linux__) || defined(__APPLE__)
#define  bear_ptr_cast long long
#endif

#ifdef  _WIN32
#define  bear_ptr_cast  long
#endif
