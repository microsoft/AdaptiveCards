#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "LinkState.h"
#include "MarkDownHtmlGenerator.h"

namespace AdaptiveCards
{
class MarkDownParser
{
public:
    MarkDownParser(const std::string &txt); 

    enum EmphasisType
    {
        EmphasisItalic = 1,
        EmphasisBold = 2,
    };

    enum EmphasisState
    {   
        // state for the first encounter of emphasis delimiter 
        EmphasisStart = 0x1,  
        // state for a emphasis delimiter run 
        EmphasisRun = 0x2,   
        InsideEmphasis = EmphasisStart | EmphasisRun,
        // state for when a emphasis delimiter run is ended 
        EmphasisEnd = 0x4,       
        // init state for emphasis detection 
        EmphasisNone = 0x8,
        OutsideEmphasis = EmphasisEnd | EmphasisNone,
        EndOfWords = 0x10,
        BeginOfWords = 0x20,
    };

    typedef std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> EmphasisList;
    typedef EmphasisList::iterator EmphasisListInterator;
    typedef  std::list<std::shared_ptr<MarkDownHtmlGenerator>> TokenList;
    typedef std::list<std::shared_ptr<MarkDownLinkHtmlGenerator>> LinkList;
    //typedef LinkList::iterator LinkListInterator;

    void SetText(const std::string & txt);
    std::string TransformToHtml();

private:

    void EmphasisSyntaxCheck(EmphasisListInterator begin, EmphasisListInterator end);
    void GenerateSymbolTable();
    std::string GenerateHtmlString();

    bool IsLeftEmphasisDelimiter();
    bool IsRightEmphasisDelimiter();
    bool TryCapturingRightEmphasisToken();
    bool TryCapturingLeftEmphasisToken();
    bool IsMarkDownDelimiter(char ch);
    DelimiterType GetDelimiterTypeForCharAtCurrentPosition();
    bool IsEmphasisDelimiterRun(DelimiterType delimiterRunType);
    void UpdateCurrentEmphasisRunState(DelimiterType emphasisType);
    void ResetCurrentEmphasisRunState(DelimiterType emphasisType);
    void GetCh(char ch);
    void CaptureCurrentCollectedStringAsRegularToken();
    void StartNewTokenCapture();
    void CaptureLinkText();
    void UpdateState();

    DelimiterType m_currentDelimiterType = Init;
    int m_lookBehind = Init;
    int m_delimiterCnts = 0;
    int m_emphasisState = EmphasisNone;
    bool m_checkLookAhead = false;
    bool m_checkIntraWord = false;

    std::string m_text;
    std::string::iterator m_curPos;
    TokenList m_tokenizedString;
    TokenList::iterator m_tokenIterator = m_tokenizedString.begin();
    EmphasisList m_emphasisLookUpTable;
    LinkList m_linkLookUpTable;
    std::string m_currentToken = "";
    LinkStateMachine m_linkState;
};
}
