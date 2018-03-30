#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "MarkDownParsedResult.h"
#include "MarkDownBlockParser.h"
#include "MarkDownHtmlGenerator.h"

AdaptiveSharedNamespaceStart
class MarkDownParser
{
public:
    MarkDownParser(const std::string &txt); 

    std::string TransformToHtml();

private:
    void ParseBlock();
    std::string EscapeText();
    std::string m_text;
    MarkDownParsedResult m_parsedResult;
};
AdaptiveSharedNamespaceEnd
