// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "TextElementProperties.h"

namespace AdaptiveSharedNamespace
{
    class RequiredProperties
    {
    public:
        static RequiredProperties& getInstance()
        {
            static RequiredProperties instance;
            return instance;
        }
        RequiredProperties(const RequiredProperties &) = delete;
        void operator=(const RequiredProperties &) = delete;

    private:
        RequiredProperties();
        std::unordered_map<std::string, std::unordered_set<std::string>> m_requiredProperties;
    };
}
