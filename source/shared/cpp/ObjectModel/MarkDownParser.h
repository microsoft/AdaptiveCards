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
    MarkDownParser(const std::string &txt);

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
        EmphasisDetected = 0x1,
        EmphasisDetecting = 0x2,
        EmphasisOn = EmphasisDetected | EmphasisDetecting,
        EmphasisEnded = 0x4,
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

    bool IsLeftEmphasisDelimiter(void);
    bool IsRightEmphasisDelimiter(void);
    bool IsMarkDownDelimiter(char ch);
    void SetText(const std::string & txt);
    std::string TransformToHtml(void);

private:
    void GetCh(char ch);
    void PutBackCh();
    void GenSymbolTable(void);
    void UpdateState(void);
    int adjustDelimsCntsAndMetaData(int leftOver, std::list<Emphasis>::iterator left_itr, 
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
