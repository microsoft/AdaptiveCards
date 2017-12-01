#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class MarkDownParser
{
public:
    MarkDownParser (const std::string &txt); 

    enum DelimiterType
    {
        Init,
        Alphanumeric,
        Puntuation,
        Escape,
        WhiteSpace,
        Underscore = 0x8,
        Asterisk   = 0x10,
    };

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

    struct Emphasis
    {
        int m_emphCnts;
        unsigned m_idx;
        std::vector<int> m_tags;
        Emphasis(unsigned int empCnts, unsigned idx) : 
            m_emphCnts(empCnts), m_idx(idx), m_tags(){};
    };

    void SetText(const std::string & txt);
    std::string TransformToHtml();

private:
    bool IsLeftEmphasisDelimiter();
    bool IsRightEmphasisDelimiter();
    bool PushLeftEmphasisToLookUpTableIfValid();
    bool PushRightEmphasisToLookUpTableIfValid();
    bool IsMarkDownDelimiter(char ch);
    DelimiterType GetDelimiterTypeForCharAtCurrentPosition();
    bool IsEmphasisDelimiterRun(MarkDownParser::DelimiterType delimiterRunType);
    void UpdateCurrentEmphasisRunState(MarkDownParser::DelimiterType emphasisType);
    void ResetCurrentEmphasisRunState(MarkDownParser::DelimiterType emphasisType);
    void StartNewTokenCapture();
    void GetCh(char ch);
    void PutBackCh();
    void GenSymbolTable();
    void UpdateState();
    int AdjustEmphasisCounts(int leftOver, std::list<Emphasis>::iterator left_itr, 
            std::list<Emphasis>::iterator right_itr);

    DelimiterType m_currentDelimiterType = Init;
    unsigned int m_currentWordIndex = 0;
    int m_lookBehind = Init;
    int m_delimiterCnts = 0;
    int m_emphasisState = EmphasisNone;
    bool m_checkLookAhead = false;
    bool m_checkIntraWord = false;
    int m_LeftEmphasisDetecting = 0;

    std::string m_text;
    std::string::iterator m_textBegin;
    std::string::iterator m_curPos;
    std::list<Emphasis> m_leftLookUpTable;
    std::list<Emphasis> m_rightLookUpTable;
    std::vector<std::string> m_tokenizedString = std::vector<std::string>(1, "");
};
}
