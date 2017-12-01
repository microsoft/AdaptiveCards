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
    MarkDownParser (const std::string &txt) : m_currentDelimiterType (Init), 
        m_currentWordIndex(0), m_lookBehind(Init), m_delimiterCnts(0), m_EmphasisState (EmphasisNotDetected), 
        m_checkLookAhead(false), m_checkIntraWord(false), m_isRightEmphasisDetecting(false), m_text(txt), 
        m_textBegin(m_text.begin()), m_curPos(m_text.begin()), m_textEnd(m_text.end()), m_LeftEmphasisDetecting(0),
        m_leftLookUpTable (), m_rightLookUpTable (), m_tokenizedString(1, "") {};

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
        EmphasisDetected = 0x1,  
        // state for a emphasis delimiter run 
        EmphasisDetecting = 0x2,   
        EmphasisOn = EmphasisDetected | EmphasisDetecting,
        // state for when a empahsis delimiter run is ended 
        EmphasisEnded = 0x4,       
        // init state for emphasis detection 
        EmphasisNotDetected = 0x8,
        EmphasisOff = EmphasisEnded | EmphasisNotDetected,
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
    bool IsMarkDownDelimiter(char ch);
    void GetCh(char ch);
    void PutBackCh();
    void GenSymbolTable();
    void UpdateState();
    int AdjustEmphasisCounts(int leftOver, std::list<Emphasis>::iterator left_itr, 
            std::list<Emphasis>::iterator right_itr);

    DelimiterType m_currentDelimiterType;
    unsigned int m_currentWordIndex;
    int m_lookBehind;
    int m_delimiterCnts;
    int m_EmphasisState;
    bool m_checkLookAhead;
    bool m_checkIntraWord;
    bool m_isRightEmphasisDetecting;

    std::string m_text;
    std::string::iterator m_textBegin;
    std::string::iterator m_curPos;
    std::string::iterator m_textEnd;
    int m_LeftEmphasisDetecting;
    std::list<Emphasis> m_leftLookUpTable;
    std::list<Emphasis> m_rightLookUpTable;
    std::vector<std::string> m_tokenizedString;
};
}
