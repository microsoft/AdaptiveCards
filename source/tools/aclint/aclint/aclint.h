// aclint.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <sstream>

std::string CSI(const std::string& v)
{
    std::ostringstream oss;
    oss << "\x1B[" << v;
    return oss.str();
}

// TODO: Reference additional headers your program requires here.
