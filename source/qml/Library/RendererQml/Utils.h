#pragma once

#include "pch.h"
#include "HostConfig.h"

namespace RendererQml
{

    class Utils
    {
    public:

        template <class T, class U>
        static bool IsInstanceOfSmart(U u);

        template <class T, class U>
        static bool IsInstanceOf(U u);

        static int HexStrToInt(const std::string& str);
        static int GetSpacing(const AdaptiveCards::SpacingConfig& spacingConfig, const AdaptiveCards::Spacing spacing);
        static const AdaptiveCards::ContainerStyleDefinition& GetContainerStyle(const AdaptiveCards::ContainerStylesDefinition& containerStyles, AdaptiveCards::ContainerStyle style);

        static bool CaseInsensitiveCompare(const std::string& str1, const std::string& str2);
        static bool IsNullOrWhitespace(const std::string& str);
        static std::string& RightTrim(std::string& str);
        static std::string& LeftTrim(std::string& str);
        static std::string& Trim(std::string& str);
        static std::string& Replace(std::string& str, char what, char with);
        static std::string& Replace(std::string& str, const std::string& what, const std::string& with);
        static std::string& ToLower(std::string& str);
        static bool TryParse(const std::string& str, double& value);
        static bool EndsWith(const std::string& str, const std::string& end);

    private:
        Utils() {}
    };

    template<class T, class U>
    inline bool Utils::IsInstanceOfSmart(U u)
    {
        return std::dynamic_pointer_cast<T>(u) != nullptr;
    }

    template<class T, class U>
    inline bool Utils::IsInstanceOf(U u)
    {
        return dynamic_cast<T>(u) != nullptr;
    }

    class TextUtils
    {
    public:
        static std::string ApplyTextFunctions(const std::string& text, const std::string& lang);
        static std::locale GetValidCultureInfo(const std::string& lang);
        static bool GetLocalTime(const std::string& tzOffset, std::tm& tm, std::tm& lt);

    private:
        static std::regex m_textFunctionRegex;
    };
}
