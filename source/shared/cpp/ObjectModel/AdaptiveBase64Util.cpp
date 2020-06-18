// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#ifdef USE_CPPCORECHECK
#pragma warning(disable : ALL_CPPCORECHECK_WARNINGS)
#endif

#include "AdaptiveBase64Util.h"
#include <map>

/*
* Copyright (C) 2013 Tomas Kislan
* Copyright (C) 2013 Adam Rudd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Portions Copyright Microsoft Corporation
*/

using namespace AdaptiveSharedNamespace;

namespace
{
    const char c_base64EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    const unsigned char c_base64DecodeTable[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Control characters:     0 -  15
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Control characters:    16 -  31
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F, // Printable characters:  32 -  47 (  to /)
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Printable characters:  48 -  63 (0 to ?)
        0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, // Printable characters:  64 -  79 (` to O)
        0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Printable characters:  80 -  95 (P to _)
        0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, // Printable characters:  96 - 111 (@ to o)
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  // Printable characters: 112 - 127 (p to DEL)
    };
}

size_t AdaptiveBase64Util::DecodedLength(const char* in, size_t in_length)
{
    int numEq{};

    const char* in_end{ in + in_length };
    while (*--in_end == '=')
    {
        ++numEq;
    }

    return ((6 * in_length) / 8) - numEq;
}

size_t AdaptiveBase64Util::DecodedLength(const std::string& in)
{
    size_t numEq{};
    size_t n{ in.size() };

    for (auto it = in.rbegin(); (numEq < n) && (*it == '='); ++it)
    {
        ++numEq;
    }

    return ((6 * n) / 8) - numEq;
}

size_t AdaptiveBase64Util::EncodedLength(size_t length)
{
    return ((length + 2 - ((length + 2) % 3)) / 3) * 4;
}

size_t AdaptiveBase64Util::EncodedLength(const std::vector<char>& in)
{
    return EncodedLength(in.size());
}

void AdaptiveBase64Util::StripPadding(std::string* in)
{
    while (!in->empty() && *(in->rbegin()) == '=')
    {
        in->resize(in->size() - 1);
    }
}

void AdaptiveBase64Util::a3_to_a4(unsigned char* a4, unsigned char* a3)
{
    a4[0] = (a3[0] & 0xfc) >> 2;
    a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
    a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
    a4[3] = (a3[2] & 0x3f);
}

void AdaptiveBase64Util::a4_to_a3(unsigned char* a3, unsigned char* a4)
{
    a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
    a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
    a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}

unsigned char AdaptiveBase64Util::b64_lookup(unsigned char c)
{
    if (c < std::size(c_base64DecodeTable))
    {
        return c_base64DecodeTable[c];
    }

    return 0xFF;
}

bool AdaptiveBase64Util::Encode(const std::vector<char>& in, std::string* out)
{
    out->resize(EncodedLength(in));

    size_t input_len{ in.size() };
    auto input = in.begin();

    int i{};
    size_t enc_len{};
    unsigned char a3[3];
    unsigned char a4[4];
    while (input_len--)
    {
        a3[i++] = *(input++);
        if (i == 3)
        {
            a3_to_a4(a4, a3);

            for (i = 0; i < 4; ++i)
            {
                (*out)[enc_len++] = c_base64EncodeTable[a4[i]];
            }

            i = 0;
        }
    }

    if (i)
    {
        for (int j{ i }; j < 3; ++j)
        {
            a3[j] = '\0';
        }

        a3_to_a4(a4, a3);

        for (int j{}; j < i + 1; ++j)
        {
            (*out)[enc_len++] = c_base64EncodeTable[a4[j]];
        }

        while ((i++ < 3))
        {
            (*out)[enc_len++] = '=';
        }
    }

    return (enc_len == out->size());
}

bool AdaptiveBase64Util::Decode(const std::string& in, std::vector<char>* out)
{
    size_t input_len{ in.size() };
    auto input = in.begin();

    out->resize(DecodedLength(in));

    int i{};
    size_t dec_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];
    while (input_len--)
    {
        if (*input == '=')
        {
            break;
        }

        a4[i++] = *(input++);
        if (i == 4)
        {
            for (i = 0; i < 4; ++i)
            {
                a4[i] = b64_lookup(a4[i]);
            }

            a4_to_a3(a3, a4);

            for (i = 0; i < 3; ++i)
            {
                (*out)[dec_len++] = a3[i];
            }

            i = 0;
        }
    }

    if (i)
    {
        for (int j{ i }; j < 4; ++j)
        {
            a4[j] = '\0';
        }

        for (int j{}; j < 4; j++)
        {
            a4[j] = b64_lookup(a4[j]);
        }

        a4_to_a3(a3, a4);

        for (int j{}; j < i - 1; ++j)
        {
            (*out)[dec_len++] = a3[j];
        }
    }

    return (dec_len == out->size());
}

std::vector<char> AdaptiveBase64Util::Decode(const std::string& encodedBase64)
{
    std::vector<char> decodedString;
    Decode(encodedBase64, &decodedString);
    return decodedString;
}

std::string AdaptiveBase64Util::Encode(const std::vector<char>& decodedBase64)
{
    std::string encodedString;
    Encode(decodedBase64, &encodedString);
    return encodedString;
}

// Format for DataURI is data:[<MediaType>][;base64],data with MediaType and base64 being optional and data is composed of [A-Z a-z 0-9 + /] characters
std::string AdaptiveBase64Util::ExtractDataFromUri(const std::string& dataUri)
{
    size_t comaPosition = dataUri.find_last_of(",");
    return dataUri.substr(comaPosition + 1);
}
