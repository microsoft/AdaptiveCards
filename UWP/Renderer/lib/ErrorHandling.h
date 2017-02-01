#pragma once

#include <sal.h>

#define RETURN_IF_FAILED(hr)        do { if (FAILED(hr)) { return hr;}} while (0, 0)