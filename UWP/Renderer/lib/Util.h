#pragma once
#include <wrl.h>
#include <string>

HRESULT StringToHSTRING(const std::string in, HSTRING* out);

HRESULT HSTRINGToString(HSTRING in, std::string &out);

bool Boolify(const boolean value);