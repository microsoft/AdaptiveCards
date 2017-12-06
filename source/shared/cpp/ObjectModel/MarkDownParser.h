#pragma once

#include <iomanip>
#include <list>
#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "LinkState.h"

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
        unsigned int postionInTokenTable; 
        bool isLeftAndRightEmphasis; 
        DelimiterType type;
        std::vector<int> m_tags;
        Emphasis(unsigned int empCnts, unsigned int pos, bool emp, DelimiterType type) : 
            m_emphCnts(empCnts), postionInTokenTable(pos), isLeftAndRightEmphasis(emp), type(type), m_tags(){};
    };

    void SetText(const std::string & txt);
    std::string TransformToHtml();

private:
    bool IsMatch(std::list<Emphasis>::iterator &left, std::list<Emphasis>::iterator &right);
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
    int m_lookBehind = Init;
    int m_delimiterCnts = 0;
    int m_emphasisState = EmphasisNone;
    bool m_checkLookAhead = false;
    bool m_checkIntraWord = false;

    std::string m_text;
    std::string::iterator m_curPos;
    std::list<Emphasis> m_leftLookUpTable;
    std::list<Emphasis> m_rightLookUpTable;
    std::list<std::string> m_tokenizedString = std::list<std::string>(1, "");
    std::list<std::string>::iterator m_currentToken = m_tokenizedString.begin();
    std::vector<std::list<std::string>::iterator> m_linkLookUpTable;
    LinkState m_linkState;
};
}
