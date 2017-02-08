#include "pch.h"
#include "util.h"
#include <locale>
#include <codecvt>
#include <string>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace std;

HRESULT UTF8ToHString(const string& in, HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wide = converter.from_bytes(in);
    return HStringReference(wide.c_str()).CopyTo(out);
}

HRESULT HStringToUTF8(const HSTRING& in, string& out)
{
    if (in == nullptr)
    {
        return E_INVALIDARG;
    }
    HString wrapper;
    RETURN_IF_FAILED(wrapper.Set(in));
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    out = converter.to_bytes(wrapper.GetRawBuffer(nullptr));
    return S_OK;
}

bool Boolify(const boolean value)
{
    return value > 0 ? true : false;
}