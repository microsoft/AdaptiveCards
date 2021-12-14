// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "MarkDownParsedResult.h"
#include "MarkDownBlockParser.h"
#include "MarkDownHtmlGenerator.h"

namespace AdaptiveCards
{
class MarkDownParser
{
public:
    MarkDownParser(const std::string& txt);

    std::string TransformToHtml();

    std::string GetRawText() const;

    bool HasHtmlTags();

    bool IsEscaped() const;

private:
    void ParseBlock();
    std::string EscapeText();
    std::string m_text;
    MarkDownParsedResult m_parsedResult;
    bool m_hasHTMLTag;
    bool m_isEscaped;
};
} // namespace AdaptiveCards
