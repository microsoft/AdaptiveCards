#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

MarkDownParser::MarkDownParser(const std::string &txt) : m_currentDelimiterType(Init), 
    m_currentWordIndex(0), m_lookBehind(Init), m_delimiterCnts(0), m_EmphasisState(EmphasisNotDetected), 
    m_checkLookAhead(false), m_checkIntraWord(false), m_isRightEmphasisDetecting(false), m_text(txt), 
    m_textBegin(m_text.begin()), m_curPos(m_text.begin()), m_textEnd(m_text.end()), m_LeftEmphasisDetecting(0) 
{
    m_leftLookUpTable = std::vector<Emphasis>();
    m_rightLookUpTable = std::vector<Emphasis>();
    m_tokenizedString = std::vector<std::string>(1, "");
}

std::string MarkDownParser::TransformToHtml(void)
{
    GenSymbolTable();
    std::string html;
    if(!m_leftLookUpTable.size() || !m_rightLookUpTable.size())
    {
        return "<p>" + m_text + "</p>";
    }

    std::vector<unsigned int> stk;
    unsigned int top_left = 0, top_right = 0;
    stk.push_back(top_left++);

    unsigned int leftBound = 0, rightBound = 0;

    while(!stk.empty() && top_right < m_rightLookUpTable.size())
    {
        // check if left most emphasis passed a new right emphasis delimiter
        if(top_left < m_leftLookUpTable.size() && m_leftLookUpTable[top_left].m_idx < m_rightLookUpTable[top_right].m_idx)
        {
            stk.push_back(top_left);
            ++top_left;
        }
        else
        {
            // found the left and right delimiter, gen string
            unsigned int curr_left_delim = stk.back();
            int delimCnts = 0, leftOver = 0;
            std::ostringstream left, right;

            if (m_tokenizedString[m_leftLookUpTable[curr_left_delim].m_idx][0] == 
                m_tokenizedString[m_rightLookUpTable[top_right].m_idx][0])
            {
                // check which one will have leftover delims
                leftOver = m_leftLookUpTable[curr_left_delim].m_emphCnts - m_rightLookUpTable[top_right].m_emphCnts;
                if (leftOver >= 0)
                {
                    delimCnts = m_leftLookUpTable[curr_left_delim].m_emphCnts - leftOver;
                    m_leftLookUpTable[curr_left_delim].m_emphCnts = leftOver;
                    m_rightLookUpTable[top_right].m_emphCnts = 0;
                }
                else
                {
                    delimCnts = m_leftLookUpTable[curr_left_delim].m_emphCnts;
                    m_rightLookUpTable[top_right].m_emphCnts = leftOver * (-1);
                    m_leftLookUpTable[curr_left_delim].m_emphCnts = 0; 
                }
            }

            if(delimCnts % 2)
            {
                right << "</em>";
            }

            for(int rpts = 0; rpts < delimCnts / 2; rpts++)
            {
                left << "<strong>";
                right << "</strong>";
            }

            if(delimCnts % 2)
            {
                left << "<em>";
            }
            
            // stich strings between delims
            if (leftBound == 0 && rightBound == 0)
            { 
                std::ostringstream center;
                leftBound = m_leftLookUpTable[curr_left_delim].m_idx;
                rightBound = m_rightLookUpTable[top_right].m_idx;
                for(unsigned int i = leftBound + 1; i < rightBound; i++)
                {
                    center << m_tokenizedString[i];
                }
                html = center.str();
            }
            else
            {
                std::ostringstream leftHtml, rightHtml;
                for(unsigned int i = m_leftLookUpTable[curr_left_delim].m_idx + 1; i < leftBound; i++)
                {
                    leftHtml << m_tokenizedString[i];
                }
                for(unsigned int i = rightBound + 1; i < m_rightLookUpTable[top_right].m_idx; i++)
                {
                    rightHtml << m_tokenizedString[i];
                }
                
                leftBound  =  m_leftLookUpTable[curr_left_delim].m_idx;
                rightBound = m_rightLookUpTable[top_right].m_idx;

                html = leftHtml.str() + html + rightHtml.str();
            }

            // all right delims used, move to next
            if (leftOver >= 0)
            {
                top_right++;
            }
            // all left delims used, pop
            if (leftOver == 0 || m_leftLookUpTable[curr_left_delim].m_emphCnts == 0)
            { 
                stk.pop_back();
            }

            html = left.str() + html + right.str();
        }
    }

    leftBound = std::min(m_leftLookUpTable.front().m_idx, m_rightLookUpTable.front().m_idx);
    Emphasis &leftBoundEmphasis = (leftBound == m_leftLookUpTable.front().m_idx)? m_leftLookUpTable.front() : m_rightLookUpTable.front();
    // if there are unused emphasis, append them
    if(leftBoundEmphasis.m_emphCnts)
    {
        int startIdx = m_tokenizedString[leftBound].size() - leftBoundEmphasis.m_emphCnts;
        html = m_tokenizedString[leftBound].substr(startIdx, std::string::npos) + html;
    }

    for (int idx = leftBound - 1; idx  >= 0; idx--)
    {
        html = m_tokenizedString[idx] + html;
    }

    rightBound = std::max(m_leftLookUpTable.back().m_idx, m_rightLookUpTable.back().m_idx);

    for (int idx = rightBound + 1; idx  < m_tokenizedString.size(); idx++)
    {
        html += m_tokenizedString[idx];
    }

    Emphasis &rightBoundEmphasis = (rightBound == m_leftLookUpTable.back().m_idx)? m_leftLookUpTable.back() : m_rightLookUpTable.back();
    // if there are unused emphasis, append them
    if(rightBoundEmphasis.m_emphCnts)
    {
        int startIdx = m_tokenizedString[rightBound].size() -  rightBoundEmphasis.m_emphCnts;
        html = html + m_tokenizedString[rightBound].substr(startIdx, std::string::npos);
    }

    return "<p>" + html + "</p>";
}


void MarkDownParser::GetCh(char ch)
{
    // store chars unless it's escape
    if (ch != '\\')
    {
        m_tokenizedString[m_currentWordIndex] += ch;
    }
}

void MarkDownParser::PutBackCh()
{
    m_tokenizedString.pop_back();
    --m_currentWordIndex;
    char ch = (m_currentDelimiterType == Asterisk)? '*' : '_';
    // last ch gets stored; so no need to put back last ch
    if (m_curPos + 1 == m_textEnd)
    { 
        m_delimiterCnts--;
    }

    while(m_delimiterCnts--)
    {
        GetCh(ch);
    }
}

bool MarkDownParser::IsLeftEmphasisDelimiter(void) 
{
    bool isLeftEmphasisDetecting = ((m_EmphasisState & ~EmphasisOn) && 
                          m_delimiterCnts && 
                          !isspace(*m_curPos) && 
                          !(m_lookBehind == Alphanumeric && ispunct(*m_curPos)) && 
                          !(m_lookBehind == Alphanumeric && m_currentDelimiterType == Underscore));
    if (isLeftEmphasisDetecting)
    {
        m_leftLookUpTable.push_back(
            Emphasis(m_delimiterCnts, m_currentWordIndex)); 
        m_LeftEmphasisDetecting += m_delimiterCnts;
    }
    return isLeftEmphasisDetecting;
}

bool MarkDownParser::IsRightEmphasisDelimiter(void)
{
    bool isRightEmphasisDetected = false;
    if(isspace(*m_curPos) && 
       (m_lookBehind != WhiteSpace) && 
       (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {        
        isRightEmphasisDetected  = true;
    }

    if (isalnum(*m_curPos) && m_lookBehind != WhiteSpace)
    {
        if (!m_checkLookAhead && !m_checkIntraWord)
        {
            isRightEmphasisDetected  = true;
        }

        if(m_checkLookAhead || m_checkIntraWord)
            return m_isRightEmphasisDetecting = false;
    }

    if (ispunct(*m_curPos) && m_lookBehind != WhiteSpace)
    {
        if((m_EmphasisState & EmphasisOff) || 
           ((m_EmphasisState & EmphasisOn) && (m_curPos + 1 == m_textEnd))) 
        {
            isRightEmphasisDetected  = true;
        }
    }

    if (isRightEmphasisDetected)
    {
        if (m_LeftEmphasisDetecting)
        {
            m_rightLookUpTable.push_back(
                Emphasis(m_delimiterCnts, m_currentWordIndex)); 
            m_LeftEmphasisDetecting -= m_delimiterCnts;
            return m_isRightEmphasisDetecting = true;
        }
    }

    return m_isRightEmphasisDetecting = false;
}

void MarkDownParser::SetText(const std::string & txt)
{
    m_text = txt;
}

bool MarkDownParser::IsMarkDownDelimiter(char ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

void MarkDownParser::UpdateState(void)
{
    if (IsMarkDownDelimiter(*m_curPos))
    {
        m_EmphasisState = (m_EmphasisState & (EmphasisOff))?
            EmphasisDetected : EmphasisDetecting;
    }
    else
    {
        m_EmphasisState = (m_EmphasisState & EmphasisOn)?
            EmphasisEnded : EmphasisNotDetected;
    }

}

void MarkDownParser::GenSymbolTable(void)
{
    while(m_curPos < m_textEnd)
    {
        UpdateState();

        if (m_EmphasisState & EmphasisOn)
        {
            DelimiterType delimiterType = (*m_curPos == '*')? Asterisk : Underscore;

            if (m_curPos != m_textBegin && (m_EmphasisState & EmphasisDetected))
            {
                m_tokenizedString.push_back("");
                ++m_currentWordIndex;
            }

            if ((m_currentDelimiterType == delimiterType) || (m_EmphasisState & EmphasisDetected))
            {
                if (m_lookBehind != WhiteSpace)
                {
                    m_checkLookAhead = (m_lookBehind == Puntuation);
                    m_checkIntraWord = (m_lookBehind == Alphanumeric && delimiterType == Underscore);
                }
                ++m_delimiterCnts;
            }
            else
            {
                m_EmphasisState = EmphasisDetected;
                m_delimiterCnts = 1;
            }

            m_currentDelimiterType = delimiterType;
        }

        if((m_EmphasisState == EmphasisEnded) || 
           ((m_EmphasisState & EmphasisOn) && (m_curPos + 1 == m_textEnd)))
        {
            if (IsRightEmphasisDelimiter() || IsLeftEmphasisDelimiter())
            {
                // begin new token if new type of delimiter found
                if (m_EmphasisState & EmphasisOff)
                {
                    ++m_currentWordIndex;
                    m_tokenizedString.push_back("");
                }
            }
            else if (m_currentWordIndex)
            {
                PutBackCh();
            }
            m_delimiterCnts = 0;
        }

        if(m_EmphasisState & EmphasisOff)
        {
            //store ch and move itr
            if (isspace(*m_curPos))
            {
                m_lookBehind = WhiteSpace;
            }

            if (isalnum(*m_curPos))
            {
                m_lookBehind = Alphanumeric;
            }

            if (ispunct(*m_curPos))
            {
                m_lookBehind = (*m_curPos == '\\')? Escape : Puntuation;
            }
        }

        GetCh(*m_curPos);
        ++m_curPos; 
    }
}
