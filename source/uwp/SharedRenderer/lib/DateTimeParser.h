// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "DateTimePreparser.h"

#include <string>

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    class DateTimeParser
    {
    public:
        DateTimeParser(const std::string& language);
        std::string GenerateString(const DateTimePreparser& text);

    private:
        std::string m_languageString;
    };
}
