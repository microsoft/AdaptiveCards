#pragma once

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
        Underscore,
        Asterisk,
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

    enum EmphasisType
    {
        Italic = 0x1,
        Bold   = 0x2,
    };

    struct Emphasis
    {
        int m_emphCnts;
        unsigned m_idx;
        Emphasis(unsigned int empCnts, unsigned idx) : 
            m_emphCnts(empCnts), m_idx(idx){};
    };

    std::vector<std::string> m_tokenizedString;

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
    std::vector<Emphasis> m_leftLookUpTable;
    std::vector<Emphasis> m_rightLookUpTable;
    int m_LeftEmphasisDetecting;
};
}
