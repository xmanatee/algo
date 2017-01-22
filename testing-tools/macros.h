#pragma once

#ifdef TESTING
#include <iostream>
#define WE(x) std::cerr << "DBG:" << x << std::endl
#define WO(x) std::cout << "DBG:" << x << std::endl

#else
#define WE(x)
#define WO(x)

#endif

