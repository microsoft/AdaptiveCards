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

const char c_base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz"
                                "0123456789+/";

void GetBase64Alphabet(std::map<char, int>* base64AlphabetOut)
{
    static std::map<char, int> base64Alphabet = {
        {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
        {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22},
        {'X', 23}, {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32}, {'h', 33},
        {'i', 34}, {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40}, {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44},
        {'t', 45}, {'u', 46}, {'v', 47}, {'w', 48}, {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55},
        {'4', 56}, {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'+', 62}, {'/', 63},
    };

    *base64AlphabetOut = base64Alphabet;
}

size_t AdaptiveBase64Util::DecodedLength(const char* in, size_t in_length)
{
    int numEq{};

    const char *in_end{ in + in_length };
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
    std::map<char, int> base64Alphabet;
    GetBase64Alphabet(&base64Alphabet);

    if (base64Alphabet.find(c) == base64Alphabet.end())
    {
        return 255;
    }
    return static_cast<unsigned char>(base64Alphabet[c]);
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
                (*out)[enc_len++] = c_base64Alphabet[a4[i]];
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
            (*out)[enc_len++] = c_base64Alphabet[a4[j]];
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
