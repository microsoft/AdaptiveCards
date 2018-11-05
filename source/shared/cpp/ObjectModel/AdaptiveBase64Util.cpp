#include "pch.h"
#include "AdaptiveBase64Util.h"

using namespace AdaptiveSharedNamespace;

const char kBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


int AdaptiveBase64Util::DecodedLength(const char *in, size_t in_length) {
    int numEq = 0;

    const char *in_end = in + in_length;
    while (*--in_end == '=') ++numEq;

    return ((6 * in_length) / 8) - numEq;
}

int AdaptiveBase64Util::DecodedLength(const std::string &in) {
    int numEq = 0;
    int n = in.size();

    for (std::string::const_reverse_iterator it = in.rbegin(); *it == '='; ++it) {
        ++numEq;
    }

    return ((6 * n) / 8) - numEq;
}

int AdaptiveBase64Util::EncodedLength(size_t length) {
    return (length + 2 - ((length + 2) % 3)) / 3 * 4;
}

int AdaptiveBase64Util::EncodedLength(const std::string &in) {
    return EncodedLength(in.length());
}

void AdaptiveBase64Util::StripPadding(std::string *in) {
    while (!in->empty() && *(in->rbegin()) == '=') in->resize(in->size() - 1);
}

void AdaptiveBase64Util::a3_to_a4(unsigned char * a4, unsigned char * a3) {
    a4[0] = (a3[0] & 0xfc) >> 2;
    a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
    a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
    a4[3] = (a3[2] & 0x3f);
}

void AdaptiveBase64Util::a4_to_a3(unsigned char * a3, unsigned char * a4) {
    a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
    a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
    a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}

unsigned char AdaptiveBase64Util::b64_lookup(unsigned char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 71;
    if (c >= '0' && c <= '9') return c + 4;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 255;
}

bool AdaptiveBase64Util::Encode(const std::string &in, std::string *out) {
    int i = 0, j = 0;
    size_t enc_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];

    out->resize(EncodedLength(in));

    int input_len = in.size();
    std::string::const_iterator input = in.begin();

    while (input_len--) {
        a3[i++] = *(input++);
        if (i == 3) {
            a3_to_a4(a4, a3);

            for (i = 0; i < 4; i++) {
                (*out)[enc_len++] = kBase64Alphabet[a4[i]];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            a3[j] = '\0';
        }

        a3_to_a4(a4, a3);

        for (j = 0; j < i + 1; j++) {
            (*out)[enc_len++] = kBase64Alphabet[a4[j]];
        }

        while ((i++ < 3)) {
            (*out)[enc_len++] = '=';
        }
    }

    return (enc_len == out->size());
}

bool AdaptiveBase64Util::Encode(const char *input, size_t input_length, char *out, size_t out_length) {
    int i = 0, j = 0;
    char *out_begin = out;
    unsigned char a3[3];
    unsigned char a4[4];

    size_t encoded_length = EncodedLength(input_length);

    if (out_length < encoded_length) return false;

    while (input_length--) {
        a3[i++] = *input++;
        if (i == 3) {
            a3_to_a4(a4, a3);

            for (i = 0; i < 4; i++) {
                *out++ = kBase64Alphabet[a4[i]];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            a3[j] = '\0';
        }

        a3_to_a4(a4, a3);

        for (j = 0; j < i + 1; j++) {
            *out++ = kBase64Alphabet[a4[j]];
        }

        while ((i++ < 3)) {
            *out++ = '=';
        }
    }

    return (out == (out_begin + encoded_length));
}

bool AdaptiveBase64Util::Decode(const std::string &in, std::string *out) {
    int i = 0, j = 0;
    size_t dec_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];

    int input_len = in.size();
    std::string::const_iterator input = in.begin();

    out->resize(DecodedLength(in));

    while (input_len--) {
        if (*input == '=') {
            break;
        }

        a4[i++] = *(input++);
        if (i == 4) {
            for (i = 0; i < 4; i++) {
                a4[i] = b64_lookup(a4[i]);
            }

            a4_to_a3(a3, a4);

            for (i = 0; i < 3; i++) {
                (*out)[dec_len++] = a3[i];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) {
            a4[j] = '\0';
        }

        for (j = 0; j < 4; j++) {
            a4[j] = b64_lookup(a4[j]);
        }

        a4_to_a3(a3, a4);

        for (j = 0; j < i - 1; j++) {
            (*out)[dec_len++] = a3[j];
        }
    }

    return (dec_len == out->size());
}

/*
bool Decode(const char *input, size_t input_length, char *out, size_t out_length) {
    int i = 0, j = 0;
    char *out_begin = out;
    unsigned char a3[3];
    unsigned char a4[4];

    size_t decoded_length = DecodedLength(input, input_length);

    if (out_length < decoded_length) return false;

    while (input_length--) {
        if (*input == '=') {
            break;
        }

        a4[i++] = *(input++);
        if (i == 4) {
            for (i = 0; i < 4; i++) {
                a4[i] = b64_lookup(a4[i]);
            }

            a4_to_a3(a3, a4);

            for (i = 0; i < 3; i++) {
                *out++ = a3[i];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) {
            a4[j] = '\0';
        }

        for (j = 0; j < 4; j++) {
            a4[j] = b64_lookup(a4[j]);
        }

        a4_to_a3(a3, a4);

        for (j = 0; j < i - 1; j++) {
            *out++ = a3[j];
        }
    }

    return (out == (out_begin + decoded_length));
}
*/




size_t AdaptiveBase64Util::DecodeBase64(char c)
{
    const size_t alphabetLength{ 'Z' - 'A' + 1 };

    if (isupper(c))
    {
        return c - 'A';
    }
    else if (islower(c))
    {
        return c - 'a' + alphabetLength;
    }
    else if (isdigit(c))
    {
        return c - '0' + (2 * alphabetLength);
    }
    else if (c == '+')
    {
        return 62;
    }
    else if (c == '/')
    {
        return 63;
    }
    else
    {
        return -1;
    }
}

char AdaptiveBase64Util::EncodeBase64(size_t c)
{
    const size_t alphabetLength{ 'Z' - 'A' + 1 };
    if ((c >= 0) && (c < alphabetLength))
    {
        return static_cast<char>(c + 'A');
    }
    else if ((c >= alphabetLength) && (c < 2 * alphabetLength))
    {
        return static_cast<char>((c - alphabetLength) + 'a');
    }
    else if ((c >= 2 * alphabetLength) && (c < (2 * alphabetLength) + 10))
    {
        return static_cast<char>((c - (2 * alphabetLength) + '0'));
    }
    else if (c == 63)
    {
        return '+';
    }
    else if (c == 64)
    {
        return '/';
    }
    else
    {
        return '=';
    }
}

std::string AdaptiveBase64Util::Decode(const std::string& encodedBase64)
{
    std::string decodedString;
    Decode(encodedBase64, &decodedString);
    return decodedString;

    /*
    std::string decodedData;
    size_t dataLength = encodedBase64.length();
    while (dataLength && encodedBase64[dataLength - 1] == '=')
    {
        --dataLength;
    }

    const size_t blockSize = 4;
    for (size_t i = 0; i < dataLength; i += blockSize)
    {
        std::string block = encodedBase64.substr(i, std::min(blockSize, dataLength - i));

        size_t compressedChar{};
        for (size_t j = 0, shift = 18; j < block.size(); ++j, shift -= 6)
        {
            compressedChar = compressedChar | ((DecodeBase64(block[j]) & 0x3f) << shift);
        }

        for (size_t j = 0, shift = 16; j < block.size() - 1; ++j, shift -= 8)
        {
            decodedData.push_back((compressedChar >> shift) & 0xff);
        }
    }

    return decodedData;
    */
}

std::string AdaptiveBase64Util::Encode(const std::string& decodedBase64)
{
    std::string encodedData;

    const size_t blockSize = 3;
    for (int i = 0; i < decodedBase64.length(); i += 3)
    {
        std::string block = decodedBase64.substr(i, std::min(blockSize, decodedBase64.length() - i));

        size_t mergedChar{};
        for (size_t j = 0, shift = 16; j < block.size(); j++, shift -= 8)
        {
            mergedChar = mergedChar | ((block[j] & 0xff) << shift);
        }

        for (size_t j = 0, shift = 18; j < block.size() + 1; ++j, shift -= 6)
        {
            encodedData.push_back(EncodeBase64((mergedChar >> shift) & 0x3f));
        }
    }

    return encodedData;
}

// Format for DataURI is data:[<MediaType>][;base64],data with MediaType and base64 being optional and data is composed of [A-Z a-z 0-9 + /] characters
std::string AdaptiveBase64Util::ExtractDataFromUri(const std::string& dataUri)
{
    size_t comaPosition = dataUri.find_last_of(",");
    return dataUri.substr(comaPosition + 1);
}
