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

int MarkDownParser::adjustDelimsCntsAndMetaData(int leftOver, int left_idx, int right_idx)
{
    int delimCnts = 0;
    if (leftOver >= 0)
    {
        delimCnts = m_leftLookUpTable[left_idx].m_emphCnts - leftOver;
        m_leftLookUpTable[left_idx].m_emphCnts = leftOver;
        m_rightLookUpTable[right_idx].m_emphCnts = 0;
    }
    else
    {
        delimCnts = m_leftLookUpTable[left_idx].m_emphCnts;
        m_rightLookUpTable[right_idx].m_emphCnts = leftOver * (-1);
        m_leftLookUpTable[left_idx].m_emphCnts = 0;
    }
    return delimCnts;
}

std::string MarkDownParser::TransformToHtml(void)
{
    GenSymbolTable();
    if(!m_leftLookUpTable.size() || !m_rightLookUpTable.size())
    {
        return "<p>" + m_text + "</p>";
    }

    std::vector<unsigned int> stk;
    unsigned int top_left = 0, top_right = 0, right_token_idx = 0, curr_left_delim = 0;
    int lookBehind = (m_tokenizedString[m_leftLookUpTable[top_left].m_idx][0] == '*')? Asterisk : Underscore; 
    stk.push_back(top_left++);

    while(!stk.empty() && top_right < m_rightLookUpTable.size())
    {
        // check if left most emphasis passed a new right emphasis delimiter
        if(top_left < m_leftLookUpTable.size() && m_leftLookUpTable[top_left].m_idx < m_rightLookUpTable[top_right].m_idx)
        {
            stk.push_back(top_left);
            lookBehind |= (m_tokenizedString[m_leftLookUpTable[top_left].m_idx][0] == '*')? Asterisk : Underscore; 
            ++top_left;
        }
        else
        {
            // found the left and right delimiter, gen string
            curr_left_delim = stk.back();
            int delimCnts = 0, leftOver = 0;
            DelimiterType curr_left_delim_type = (m_tokenizedString[m_leftLookUpTable[curr_left_delim].m_idx][0] == '*')? Asterisk : Underscore; 
            DelimiterType curr_right_delim_type = (m_tokenizedString[m_rightLookUpTable[top_right].m_idx][0] == '*')? Asterisk : Underscore; 

            if (curr_left_delim_type == curr_right_delim_type)
            {
                // rule #9 & #10, sume of delim cnts can't be multipe of 3 
                if (!((m_leftLookUpTable[curr_left_delim].m_emphCnts + m_rightLookUpTable[top_right].m_emphCnts) % 3))
                {

                }
                // check which one will have leftover delims
                leftOver = m_leftLookUpTable[curr_left_delim].m_emphCnts - m_rightLookUpTable[top_right].m_emphCnts;
                delimCnts = adjustDelimsCntsAndMetaData(leftOver, curr_left_delim, top_right);
                right_token_idx = top_right;
                if (leftOver >= 0)
                {
                    lookBehind ^= curr_left_delim_type;
                }
            }
            else
            {
                // Rule #14, when two overraps, prefer left side of the overrap
                if(stk.size() > 1 && lookBehind & curr_right_delim_type) 
                {
                    char ch = (curr_right_delim_type == Asterisk)? '*' :'_';
                    // pop until matching delim is found
                    while(!stk.empty() && m_tokenizedString[m_leftLookUpTable[curr_left_delim].m_idx][0] != ch)
                    {
                        stk.pop_back();
                        curr_left_delim = stk.back();
                    }

                    leftOver = m_leftLookUpTable[curr_left_delim].m_emphCnts - m_rightLookUpTable[top_right].m_emphCnts;
                    delimCnts = adjustDelimsCntsAndMetaData(leftOver, curr_left_delim, top_right);
                    right_token_idx = top_right;
                    lookBehind = 0;
                }
            }

            if(delimCnts % 2)
            {
                m_leftLookUpTable[curr_left_delim].m_tags.push_back(EmphasisItalic);
                m_rightLookUpTable[top_right].m_tags.push_back(EmphasisItalic);
            }

            for(int rpts = 0; rpts < delimCnts / 2; rpts++)
            {
                m_leftLookUpTable[curr_left_delim].m_tags.push_back(EmphasisBold);
                m_rightLookUpTable[top_right].m_tags.push_back(EmphasisBold);
            }

            // all right delims used, move to next
            if (leftOver >= 0)
            {
                top_right++;
            }
            // all left or right delims used, pop
            if (leftOver == 0 || m_leftLookUpTable[curr_left_delim].m_emphCnts == 0)
            { 
                stk.pop_back();
                if(stk.empty() && top_left < m_leftLookUpTable.size())
                {
                    stk.push_back(top_left);
                    top_left++;
                }
            }
        }
    }

    // append all processed tags
    std::ostringstream html;
    auto leftItr = m_leftLookUpTable.begin(), rightItr = m_rightLookUpTable.begin();
    for(auto idx = 0; idx < m_tokenizedString.size(); idx++)
    { 
        if (leftItr != m_leftLookUpTable.end() && leftItr->m_idx == idx)
        {
            // if there are unused emphasis, append them 
            if(leftItr->m_emphCnts)
            {
                int startIdx = m_tokenizedString[idx].size() - leftItr->m_emphCnts;
                html << m_tokenizedString[idx].substr(startIdx, std::string::npos);
            }
            // appends tags; since left delims, append it in the reverse order
            for(auto itr = leftItr->m_tags.rbegin(); itr != leftItr->m_tags.rend(); itr++)
            { 
                html << ((*itr == EmphasisItalic)? "<em>" : "<strong>");
            }
            leftItr++;
        } 
        else if (rightItr != m_rightLookUpTable.end() && rightItr->m_idx == idx)
        {
            // appends tags; 
            for(auto itr = rightItr->m_tags.begin(); itr != rightItr->m_tags.end(); itr++)
            { 
                html << ((*itr == EmphasisItalic)? "</em>" : "</strong>");
            }
            // if there are unused emphasis, append them 
            if(rightItr->m_emphCnts)
            {
                int startIdx = m_tokenizedString[idx].size() - rightItr->m_emphCnts;
                html << m_tokenizedString[idx].substr(startIdx, std::string::npos);
            }
            rightItr++;
        }
        else
        {
            html << m_tokenizedString[idx];
        }


    }

    return "<p>" + html.str() + "</p>";
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
