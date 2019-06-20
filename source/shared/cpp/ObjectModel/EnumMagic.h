// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "pch.h"

namespace AdaptiveSharedNamespace
{
    struct CaseInsensitiveEqualTo
    {
        bool operator()(const std::string& lhs, const std::string& rhs) const noexcept
        {
            return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](unsigned char a, unsigned char b) {
                return std::toupper(a) == std::toupper(b);
            });
        }
    };

    struct CaseInsensitiveHash
    {
        size_t operator()(const std::string& keyval) const noexcept
        {
            return std::accumulate(keyval.cbegin(), keyval.cend(), size_t{0}, [](size_t acc, unsigned char c) {
                return acc + std::toupper(c);
            });
        }
    };

    struct EnumHash
    {
        template<typename T> size_t operator()(const T& t) const noexcept { return static_cast<size_t>(t); }
    };

    namespace EnumHelpers
    {
        // Manage mapping T<->std::string using two internal unordered_maps.
        template<typename T> class EnumMapping
        {
        public:
            // Initialize with a single list -> automatically generate reverse mapping
            EnumMapping(const std::initializer_list<std::pair<T, std::string>>& t) :
                _enumToString{t.begin(), t.end()}, _stringToEnum(t.size())
            {
                _GenerateStringToEnumMap();
            }

            // Initialize with two lists -> t1 is our forward list and t2 contains additional terms to use in addition
            // to the generated reverse mapping
            EnumMapping(const std::initializer_list<std::pair<T, std::string>>& t1,
                        const std::initializer_list<std::pair<std::string, T>>& t2) :
                _enumToString{t1.begin(), t1.end()},
                _stringToEnum(t2.begin(), t2.end())
            {
                _GenerateStringToEnumMap();
            }

            const std::string toString(T t) const { return _enumToString.at(t); }
            T fromString(const std::string& str) const { return _stringToEnum.at(str); }

        private:
            inline void _GenerateStringToEnumMap()
            {
                for (const auto& kv : _enumToString)
                {
                    _stringToEnum.emplace(kv.second, kv.first);
                }
            }

            const std::unordered_map<T, std::string, EnumHash> _enumToString;
            std::unordered_map<std::string, T, CaseInsensitiveHash, CaseInsensitiveEqualTo> _stringToEnum;
        };
    }

// Provides forward declaration for EnumHelpers mapping accessor as well as global mapping functions.
#define DECLARE_ADAPTIVECARD_ENUM(ENUMTYPE)                 \
    namespace EnumHelpers                                   \
    {                                                       \
        const EnumMapping<ENUMTYPE>& get##ENUMTYPE##Enum(); \
    }                                                       \
    const std::string ENUMTYPE##ToString(const ENUMTYPE t); \
    ENUMTYPE ENUMTYPE##FromString(const std::string& t);

#define _DEFINE_ADAPTIVECARD_ENUM_INVARIANT(ENUMTYPE, ...)                \
    namespace EnumHelpers                                                 \
    {                                                                     \
        const EnumMapping<ENUMTYPE>& get##ENUMTYPE##Enum()                \
        {                                                                 \
            static const EnumMapping<ENUMTYPE> generatedEnum __VA_ARGS__; \
            return generatedEnum;                                         \
        }                                                                 \
    }                                                                     \
    const std::string ENUMTYPE##ToString(const ENUMTYPE t) { return EnumHelpers::get##ENUMTYPE##Enum().toString(t); }

// Define mapping functions for ENUMTYPE. Throw an exception if caller passes in a string that doesn't map
#define DEFINE_ADAPTIVECARD_ENUM_THROW(ENUMTYPE, ...)                \
    _DEFINE_ADAPTIVECARD_ENUM_INVARIANT(ENUMTYPE, __VA_ARGS__);      \
    ENUMTYPE ENUMTYPE##FromString(const std::string& t)              \
    {                                                                \
        try                                                          \
        {                                                            \
            return EnumHelpers::get##ENUMTYPE##Enum().fromString(t); \
        }                                                            \
        catch (const std::out_of_range&)                             \
        {                                                            \
            throw std::out_of_range("Invalid " #ENUMTYPE ": " + t);  \
        }                                                            \
    }

// Define mapping from string function for ENUMTYPE. Use the specified DEFAULT when a caller passes in a string that
// doesn't map.
#define DEFINE_ADAPTIVECARD_ENUM_DEFAULT(ENUMTYPE, DEFAULT, ...)     \
    _DEFINE_ADAPTIVECARD_ENUM_INVARIANT(ENUMTYPE, __VA_ARGS__);      \
    ENUMTYPE ENUMTYPE##FromString(const std::string& t)              \
    {                                                                \
        try                                                          \
        {                                                            \
            return EnumHelpers::get##ENUMTYPE##Enum().fromString(t); \
        }                                                            \
        catch (const std::out_of_range&)                             \
        {                                                            \
            return DEFAULT;                                          \
        }                                                            \
    }

// Provide definition for ENUMTYPE using supplied initializer list. If list is of form { {ENUMTYPE, "string" }, ...},
// automatically generate reverse mapping. If list is of form { { {ENUMTYPE, "string"}, ...}, { {"string", ENUMTYPE} ,
// ..}}, use a union of the supplied second list and the reverse of the first list.
#define DEFINE_ADAPTIVECARD_ENUM(ENUMTYPE, ...) \
    DEFINE_ADAPTIVECARD_ENUM_DEFAULT(ENUMTYPE, ENUMTYPE::Default, __VA_ARGS__)

}
