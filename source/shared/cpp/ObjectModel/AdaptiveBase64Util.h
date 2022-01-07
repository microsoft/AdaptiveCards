// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

#ifdef USE_CPPCORECHECK
#pragma warning(disable : ALL_CPPCORECHECK_WARNINGS)
#endif

namespace AdaptiveCards
{
class AdaptiveBase64Util
{
private:
    static size_t DecodedLength(const char* in, size_t in_length);
    static size_t DecodedLength(const std::string& in);
    static inline size_t EncodedLength(size_t length);
    static inline size_t EncodedLength(const std::vector<char>& in);
    static inline void StripPadding(std::string* in);
    static inline void a3_to_a4(unsigned char* a4, unsigned char* a3);
    static inline void a4_to_a3(unsigned char* a3, unsigned char* a4);
    static inline unsigned char b64_lookup(unsigned char c);
    static bool Encode(const std::vector<char>& in, std::string* out);
    static bool Decode(const std::string& in, std::vector<char>* out);

public:
    static std::vector<char> Decode(const std::string& encodedBase64);
    static std::string Encode(const std::vector<char>& decodedBase64);

    static std::string ExtractDataFromUri(const std::string& dataUri);
};
} // namespace AdaptiveCards
