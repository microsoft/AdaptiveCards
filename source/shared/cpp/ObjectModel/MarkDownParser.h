#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "MarkDownParsedResult.h"
#include "MarkDownBlockParser.h"
#include "MarkDownHtmlGenerator.h"

namespace AdaptiveSharedNamespace {
class MarkDownParser
{
public:
    MarkDownParser(const std::string &txt);

    std::string TransformToHtml();

    bool HasHtmlTags();

private:
    void ParseBlock();
    std::string EscapeText();
    std::string m_text;
    MarkDownParsedResult m_parsedResult;
    bool m_hasHTMLTag;
};
}
