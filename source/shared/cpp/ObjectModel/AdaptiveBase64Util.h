#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class AdaptiveBase64Util
    {
    private:
        static int DecodedLength(const char* in, size_t in_length);
        static int DecodedLength(const std::string& in);
        static inline int EncodedLength(size_t length);
        static inline int EncodedLength(const std::string& in);
        static inline void StripPadding(std::string* in);
        static inline void a3_to_a4(unsigned char* a4, unsigned char* a3);
        static inline void a4_to_a3(unsigned char* a3, unsigned char* a4);
        static inline unsigned char b64_lookup(unsigned char c);
        static bool Encode(const std::string& in, std::string* out);
        static bool Decode(const std::string& in, std::string* out);

    public:
        static std::string Decode(const std::string& encodedBase64);
        static std::string Encode(const std::string& decodedBase64);

        static std::string ExtractDataFromUri(const std::string& dataUri);
    };
}
