#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class Base64
    {
    private:
        static size_t DecodeBase64(char c);
        static char EncodeBase64(size_t c);

    public:
        static std::string Decode(const std::string& encodedBase64);
        static std::string Encode(const std::string& decodedBase64);

        static std::string ExtractDataFromUri(const std::string& dataUri);
    };
}
