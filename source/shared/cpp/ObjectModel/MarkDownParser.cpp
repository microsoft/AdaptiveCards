#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

// adjust number of emphasis counts after maching is done
int MarkDownParser::AdjustEmphasisCounts(int leftOver, std::list<Emphasis>::iterator left_itr, 
        std::list<Emphasis>::iterator right_itr)
{
    int delimCnts = 0;
    if (leftOver >= 0)
    {
        delimCnts = left_itr->m_emphCnts - leftOver;
        left_itr->m_emphCnts = leftOver;
        right_itr->m_emphCnts = 0;
    }
    else
    {
        delimCnts = left_itr->m_emphCnts;
        right_itr->m_emphCnts = leftOver * (-1);
        left_itr->m_emphCnts = 0;
    }
    return delimCnts;
}

// Following the rules speicified in CommonMark (http://spec.commonmark.org/0.27/)
// It generally supports more stricker version of the rules
std::string MarkDownParser::TransformToHtml()
{
    GenSymbolTable ();
    if (!m_leftLookUpTable.size () || !m_rightLookUpTable.size ())
    {
        return "<p>" + m_text + "</p>";
    }

    std::vector<std::list<Emphasis>::iterator> stk;
    auto top_left = m_leftLookUpTable.begin(), top_right = m_rightLookUpTable.begin();
    auto curr_left_delim = top_left, right_token_idx = top_right;
    int lookBehind = (m_tokenizedString[top_left->m_idx][0] == '*')? Asterisk : Underscore; 
    stk.push_back(top_left++);

    while (!stk.empty() && top_right != m_rightLookUpTable.end())
    {
        // check if left most emphasis passed a new right emphasis delimiter
        if (top_left != m_leftLookUpTable.end() && top_left->m_idx < top_right->m_idx)
        {
            stk.push_back(top_left);
            lookBehind |= (m_tokenizedString[top_left->m_idx][0] == '*')? Asterisk : Underscore; 
            ++top_left;
        }
        else
        {
            curr_left_delim = stk.back();
            // because of rule #9 & #10 and multiple of 3 rule, left delim can jump ahead of right delim,
            // so need to check this condition.
            if (curr_left_delim->m_idx > top_right->m_idx)
            {
                top_right++;
                continue;
            }
            int delimCnts = 0, leftOver = 0;
            DelimiterType curr_left_delim_type = (m_tokenizedString[curr_left_delim->m_idx][0] == '*')? Asterisk : Underscore; 
            DelimiterType curr_right_delim_type = (m_tokenizedString[top_right->m_idx][0] == '*')? Asterisk : Underscore; 

            // found the left and right delimiter, gen string
            if (curr_left_delim_type == curr_right_delim_type)
            {
                // rule #9 & #10, sum of delim cnts can't be multipe of 3 
                if (!((curr_left_delim->m_emphCnts + top_right->m_emphCnts) % 3))
                {
                      if (m_tokenizedString.size () != top_right->m_idx + 1)
                      {
                          // check adjcent char is space
                          char right_ch = m_tokenizedString[top_right->m_idx + 1][0];
                          // no need to check the right bound since it's right delim
                          char left_ch =  m_tokenizedString[top_right->m_idx - 1][0];
                          // check if right delim also can be left delim
                          if (!isspace (right_ch) && 
                             !(isalnum(left_ch) && ispunct(right_ch)) && 
                             !(isalnum(left_ch) && curr_right_delim_type == Underscore))
                          {
                              std::vector<std::list<Emphasis>::iterator> store;
                              bool isFound = false;
                              while (!stk.empty() && !isFound)
                              { 
                                  auto leftdelim = stk.back();
                                  DelimiterType left_delim_type = (m_tokenizedString[leftdelim->m_idx][0] == '*')? Asterisk : Underscore; 
                                  // found left delim 
                                  if ((leftdelim->m_emphCnts >= top_right->m_emphCnts) && 
                                     ((leftdelim->m_emphCnts + top_right->m_emphCnts) % 3) &&
                                     (left_delim_type == curr_right_delim_type))
                                  { 
                                      curr_left_delim = leftdelim;
                                      isFound = true;
                                  }
                                  else
                                  {
                                      stk.pop_back();
                                      store.push_back(leftdelim);
                                  }
                              }
                              
                              // if no left delim found
                              if (!isFound)
                              {
                                  // put back everything
                                  while (!isFound && !store.empty())
                                  {
                                      stk.push_back(store.back());
                                      store.pop_back();
                                  }

                                  //right emphasis becomes left emphasis
                                  auto elem_to_be_inserted = curr_left_delim;
                                  elem_to_be_inserted++;
                                  m_leftLookUpTable.insert(elem_to_be_inserted, *top_right);
                                  curr_left_delim = --elem_to_be_inserted;
                                  stk.push_back(curr_left_delim);

                                  auto elem_to_erase = top_right;
                                  // move to next token for right delim tokens
                                  top_right++;
                                  m_rightLookUpTable.erase (elem_to_erase);
                                  // no maching found begin from the start
                                  continue;
                              }
                          }
                      }
                }
                // check which one will have leftover delims
                leftOver = curr_left_delim->m_emphCnts - top_right->m_emphCnts;
                delimCnts = AdjustEmphasisCounts(leftOver, curr_left_delim, top_right);
                right_token_idx = top_right;
                if (leftOver >= 0)
                {
                    lookBehind ^= curr_left_delim_type;
                }
            }
            else
            {
                // Rule #14, when two overraps, prefer left side of the overrap
                if (stk.size () > 1 && lookBehind & curr_right_delim_type) 
                {
                    char ch = (curr_right_delim_type == Asterisk)? '*' :'_';
                    // pop until matching delim is found
                    while (!stk.empty() && m_tokenizedString[curr_left_delim->m_idx][0] != ch)
                    {
                        stk.pop_back();
                        curr_left_delim = stk.back();
                    }

                    leftOver = curr_left_delim->m_emphCnts - top_right->m_emphCnts;
                    delimCnts = AdjustEmphasisCounts(leftOver, curr_left_delim, top_right);
                    right_token_idx = top_right;
                    lookBehind = 0;
                }
            }

            // emphasis found
            if (delimCnts % 2)
            {
                curr_left_delim->m_tags.push_back(EmphasisItalic);
                top_right->m_tags.push_back(EmphasisItalic);
            }

            // strong emphasis found
            for (int rpts = 0; rpts < delimCnts / 2; rpts++)
            {
                curr_left_delim->m_tags.push_back(EmphasisBold);
                top_right->m_tags.push_back(EmphasisBold);
            }

            // all right delims used, move to next
            if (leftOver >= 0)
            {
                top_right++;
            }

            // all left or right delims used, pop
            if (leftOver == 0 || curr_left_delim->m_emphCnts == 0)
            { 
                stk.pop_back();
                if (stk.empty() && top_left != m_leftLookUpTable.end())
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
    for (auto idx = 0; idx < m_tokenizedString.size (); idx++)
    { 
        if (leftItr != m_leftLookUpTable.end() && leftItr->m_idx == idx)
        {
            // if there are unused emphasis, append them 
            if (leftItr->m_emphCnts)
            {
                int startIdx = m_tokenizedString[idx].size () - leftItr->m_emphCnts;
                html << m_tokenizedString[idx].substr (startIdx, std::string::npos);
            }
            // append tags; since left delims, append it in the reverse order
            for (auto itr = leftItr->m_tags.rbegin(); itr != leftItr->m_tags.rend(); itr++)
            { 
                html << ((*itr == EmphasisItalic)? "<em>" : "<strong>");
            }
            leftItr++;
        } 
        else if (rightItr != m_rightLookUpTable.end() && rightItr->m_idx == idx)
        {
            // append tags; 
            for (auto itr = rightItr->m_tags.begin(); itr != rightItr->m_tags.end(); itr++)
            { 
                html << ((*itr == EmphasisItalic)? "</em>" : "</strong>");
            }
            // if there are unused emphasis, append them 
            if (rightItr->m_emphCnts)
            {
                int startIdx = m_tokenizedString[idx].size () - rightItr->m_emphCnts;
                html << m_tokenizedString[idx].substr (startIdx, std::string::npos);
            }
            rightItr++;
        }
        else
        {
            html << m_tokenizedString[idx];
        }
    }

    return "<p>" + html.str () + "</p>";
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

    while (m_delimiterCnts--)
    {
        GetCh(ch);
    }
}

bool MarkDownParser::IsLeftEmphasisDelimiter () 
{
    bool isLeftEmphasisDetecting = ((m_EmphasisState & ~EmphasisOn) && 
                          m_delimiterCnts && 
                          !isspace (*m_curPos) && 
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

bool MarkDownParser::IsRightEmphasisDelimiter ()
{
    bool isRightEmphasisDetected = false;
    if (isspace (*m_curPos) && 
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

        if (m_checkLookAhead || m_checkIntraWord)
            return m_isRightEmphasisDetecting = false;
    }

    if (ispunct(*m_curPos) && m_lookBehind != WhiteSpace)
    {
        if ((m_EmphasisState & EmphasisOff) || 
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

bool MarkDownParser::IsMarkDownDelimiter (char ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

// Updates Emphasis MarkDown State
void MarkDownParser::UpdateState ()
{
    if (IsMarkDownDelimiter (*m_curPos))
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

void MarkDownParser::GenSymbolTable ()
{
    while (m_curPos < m_textEnd)
    {
        UpdateState ();

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

        if ((m_EmphasisState == EmphasisEnded) || 
           ((m_EmphasisState & EmphasisOn) && (m_curPos + 1 == m_textEnd)))
        {
            if (IsRightEmphasisDelimiter () || IsLeftEmphasisDelimiter ())
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

        if (m_EmphasisState & EmphasisOff)
        {
            //store ch and move itr
            if (isspace (*m_curPos))
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
