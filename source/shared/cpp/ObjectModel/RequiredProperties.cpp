// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "RequiredProperties.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

RequiredProperties::RequiredProperties()
{
    m_requiredProperties = {{AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextBlock),
                             {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)}}};
}
