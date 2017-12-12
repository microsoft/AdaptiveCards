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
    typedef std::list<std::shared_ptr<MarkDownLinkHtmlGenerator>> LinkList;
    //typedef LinkList::iterator LinkListInterator;

    std::string TransformToHtml();

private:

    void MatchLeftAndRightEmphasises(EmphasisListInterator begin, EmphasisListInterator end);
    void Tokenize();
    std::string GenerateHtmlString();
    void GetCh(char ch);

    std::string m_text;
    std::string::iterator m_curPos;
    TokenList m_tokenizedString = TokenList();
    EmphasisList m_emphasisLookUpTable;
    LinkList m_linkLookUpTable;
    std::string m_currentToken = "";
    LinkStateMachine m_linkState;
};
}
