#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "MarkDownTokenizer.h"
#include "MarkDownHtmlGenerator.h"

namespace AdaptiveCards
{
class MarkDownParser
{
public:
    MarkDownParser(const std::string &txt); 

    typedef std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> EmphasisList;
    typedef EmphasisList::iterator EmphasisListInterator;
    typedef  std::list<std::shared_ptr<MarkDownHtmlGenerator>> TokenList;
    //typedef LinkList::iterator LinkListInterator;

    std::string TransformToHtml();

private:
    void Tokenize();
    std::string GenerateHtmlString();
    void GetCh(char ch);

    std::string m_text;
    std::string::iterator m_curPos;
    TokenList m_tokenizedString = TokenList();
    EmphasisList m_emphasisLookUpTable;
    std::string m_currentToken = "";
};
}
