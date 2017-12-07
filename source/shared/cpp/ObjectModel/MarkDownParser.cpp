#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

MarkDownParser::MarkDownParser(const std::string &txt) : m_text(txt), m_curPos(m_text.begin())
{
}

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
// push left delims to stack, until matching right delim is found,
// update emphasis counts and type to build string after search is complete
std::string MarkDownParser::TransformToHtml()
{
    GenerateSymbolTable();
    if (!m_leftLookUpTable.size() || !m_rightLookUpTable.size())
    {
        return "<p>" + m_text + "</p>";
    }

    std::vector<std::list<Emphasis>::iterator> DFSSearchStack;
    auto top_left = m_leftLookUpTable.begin(), top_right = m_rightLookUpTable.begin();
    auto curr_left_delim = top_left, right_token_idx = top_right;
    DFSSearchStack.push_back(top_left++);

    while (!DFSSearchStack.empty() && top_right != m_rightLookUpTable.end())
    {
        // keep exploring left until right token is found
        if (top_left != m_leftLookUpTable.end() && top_left->postionInTokenTable < top_right->postionInTokenTable)
        {
            DFSSearchStack.push_back(top_left);
            ++top_left;
        }
        else
        {
            curr_left_delim = DFSSearchStack.back();
            // because of rule #9 & #10 and multiple of 3 rule, left delim can jump ahead of right delim,
            // so need to check this condition.
            if (curr_left_delim->postionInTokenTable > top_right->postionInTokenTable)
            {
                top_right++;
                continue;
            }

            // check if matches are found
            //     mataches are found with left and right emphasis tokens if
            //     1. they are same types
            //     2. neigher of the emphasis tokens are both left and right emphasis tokens, and 
            //        if either or both of them are, then their sum is not multipe of 3 
            //        
            //     if matches are not found
            //     1. search left emphasis tokens first for match because of rule 14 matches on the left side is preferred 
            //        if match is found set left emphasis as the new left emphasis token and proceed to token processing
            //        any non-matching left emphasis will be poped, in this way it always move forward
            //        if still no match is found, 
            //     2. search right
            //        if the right emphasis can be left empahs search matching right emphasis tokens using the right emphasis
            //        as left emphasis
            //        else
            //        use current left emphasis to search, and pop current right emphasis
            if (!(*curr_left_delim->token)->IsMatch(*top_right->token))
            {
                std::vector<std::list<Emphasis>::iterator> store;
                bool isFound = false;
                // search first if matching left emphasis can be found with the right delim
                // if match found, set the new left emphasis token as current token, and
                // process tokens and as of the result, any left emphasis tokens that were searched and not matching 
                // will be no longer considerred in tag processing
                // pop until matching delim is found
                while (!DFSSearchStack.empty() && !isFound)
                {
                    auto leftdelim = DFSSearchStack.back();
                    //curr_left_delim = DFSSearchStack.back();
                    // found left delim 
                    if ((*leftdelim->token)->IsMatch(*top_right->token))
                    {
                        curr_left_delim = leftdelim;
                        isFound = true;
                    }
                    else
                    {
                        DFSSearchStack.pop_back();
                        store.push_back(leftdelim);
                    }
                }

                // if no match found from the left and the right emphasis is both left and right, 
                // and the sum of their emphasises counts is divisible by 3,
                // use current right emphasis as 
                // left emphasis, make the right emphasis, as current left
                // emphasis and start searching from there.
                // during the search if no match found, 
                // this emphasis tokens will be dropped
                if (!isFound)
                {
                    // restore state
                    while (!isFound && !store.empty())
                    {
                        DFSSearchStack.push_back(store.back());
                        store.pop_back();
                    }

                    // check for the reason why we had to backtrack
                    if (DFSSearchStack.back()->type == top_right->type)
                    {
                        //right emphasis becomes left emphasis
                        auto elem_to_be_inserted = curr_left_delim;
                        elem_to_be_inserted++;
                        m_leftLookUpTable.insert(elem_to_be_inserted, *top_right);
                        curr_left_delim = --elem_to_be_inserted;
                        DFSSearchStack.push_back(curr_left_delim);

                        auto elem_to_erase = top_right;
                        top_right++;
                        m_rightLookUpTable.erase(elem_to_erase);
                    }
                    else
                    {
                        // move to next token for right delim tokens
                        top_right++;
                    }
                    // no maching found begin from the start
                    continue;
                }
            }

            int delimCnts = 0, leftOver = 0;
            // check which one has leftover delims
            leftOver = curr_left_delim->m_emphCnts - top_right->m_emphCnts;
            delimCnts = AdjustEmphasisCounts(leftOver, curr_left_delim, top_right);
            right_token_idx = top_right;

            // emphasis found
            if (delimCnts % 2)
            {
                std::shared_ptr<MarkDownEmphasisHtmlGenerator>leftToken = std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(*(curr_left_delim->token));
                if (leftToken)
                {
                    leftToken->PushItalicTag();
                }
                std::shared_ptr<MarkDownEmphasisHtmlGenerator>rightToken = std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(*(top_right->token));
                if (rightToken)
                {
                    rightToken->PushItalicTag();
                }
            }

            // strong emphasis found
            for (int i = 0; i < delimCnts / 2; i++)
            {
                std::shared_ptr<MarkDownEmphasisHtmlGenerator>leftToken = std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(*(curr_left_delim->token));
                if (leftToken)
                {
                    leftToken->PushBoldTag();
                }
                std::shared_ptr<MarkDownEmphasisHtmlGenerator>rightToken = std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(*(top_right->token));
                if (rightToken)
                {
                    rightToken->PushBoldTag();
                }
            }

            // all right delims used, move to next
            if (leftOver >= 0)
            {
                top_right++;
            }

            // all left or right delims used, pop
            if (leftOver == 0 || curr_left_delim->m_emphCnts == 0)
            { 
                DFSSearchStack.pop_back();
                if (DFSSearchStack.empty() && top_left != m_leftLookUpTable.end())
                {
                    DFSSearchStack.push_back(top_left);
                    top_left++;
                }
            }
        }
    }

    return GenerateHtmlString();
}

std::string MarkDownParser::GenerateHtmlString()
{
    // process tags
    std::ostringstream html;
    for (auto itr = m_tokenizedString.begin();  itr != m_tokenizedString.end(); itr++)
    { 
        html << (*itr)->generateHtmlString();
    }

    return "<p>" + html.str() + "</p>";
}

void MarkDownParser::GetCh(char ch)
{
    // store chars unless it's escape
    if (ch != '\\')
    {
        m_currentToken += ch;
    }
}

void MarkDownParser::StartNewTokenCapture()
{
    m_currentToken.clear();
}

void MarkDownParser::CaptureCurrentCollectedStringAsRegularToken()
{
    if(m_currentToken.empty())
        return;
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(m_currentToken);
    m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));

    m_currentToken.clear();
}

bool MarkDownParser::IsLeftEmphasisDelimiter() 
{
    return ((m_emphasisState & ~InsideEmphasis) && 
             m_delimiterCnts && 
             !isspace(*m_curPos) && 
             !(m_lookBehind == Alphanumeric && ispunct(*m_curPos)) && 
             !(m_lookBehind == Alphanumeric && m_currentDelimiterType == Underscore));
}

// save left emphasis to look up table
// return true, if left emphasis was detected and added
bool MarkDownParser::TryCapturingLeftEmphasisToken()
{
    // left emphasis detected, save emphasis for later reference
    if (IsLeftEmphasisDelimiter())
    {
        std::shared_ptr<MarkDownLeftEmphasisHtmlGenerator> codeGen = 
            std::make_shared<MarkDownLeftEmphasisHtmlGenerator>(m_currentToken, m_delimiterCnts, 
                    false, m_currentDelimiterType);

        m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
        std::list<std::shared_ptr<MarkDownHtmlGenerator>>::iterator token = m_tokenizedString.end();
        --token;
        m_leftLookUpTable.push_back(
            Emphasis(m_delimiterCnts, m_tokenizedString.size() - 1, 
                false, m_currentDelimiterType, token)); 
        return true;
    }
    return false;
}

bool MarkDownParser::IsRightEmphasisDelimiter()
{
    if (m_leftLookUpTable.empty() && IsLeftEmphasisDelimiter())
    {
        return false;
    }

    if (isspace(*m_curPos) && 
       (m_lookBehind != WhiteSpace) && 
       (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {        
        return true;
    }

    if (isalnum(*m_curPos) && 
        m_lookBehind != WhiteSpace && 
        m_tokenizedString.size() != 1)
    {
        if (!m_checkLookAhead && !m_checkIntraWord)
        {
            return true;
        }

        if (m_checkLookAhead || m_checkIntraWord)
        {
            return false;
        }
    }

    if (ispunct(*m_curPos) && m_lookBehind != WhiteSpace)
    {
        if ((m_emphasisState & EmphasisEnd) || 
           ((m_emphasisState & InsideEmphasis) && (m_curPos + 1 == m_text.end()))) 
        {
            return true;
        }
    }
    return false;;
}

// save right emphasis to look up table
// return true, if right emphasis was detected and added
bool MarkDownParser::TryCapturingRightEmphasisToken()
{
    if (IsRightEmphasisDelimiter())
    {
        std::shared_ptr<MarkDownRightEmphasisHtmlGenerator> codeGen = 
            std::make_shared<MarkDownRightEmphasisHtmlGenerator>(m_currentToken, m_delimiterCnts, 
                    IsLeftEmphasisDelimiter(), m_currentDelimiterType);

        m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
        std::list<std::shared_ptr<MarkDownHtmlGenerator>>::iterator token = m_tokenizedString.end();
        --token;
        m_leftLookUpTable.push_back(
            Emphasis(m_delimiterCnts, m_tokenizedString.size() - 1, 
                false, m_currentDelimiterType, token)); 
        return true;
    }
    return false;
}

void MarkDownParser::SetText(const std::string & txt)
{
    m_text = txt;
}

bool MarkDownParser::IsMarkDownDelimiter(char ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

// Updates Emphasis MarkDown State
void MarkDownParser::UpdateState()
{
    if (IsMarkDownDelimiter(*m_curPos))
    {
        m_emphasisState = (m_emphasisState & (OutsideEmphasis))?
            EmphasisStart : EmphasisRun;
    }
    else
    {
        m_emphasisState = (m_emphasisState & InsideEmphasis)?
            EmphasisEnd : EmphasisNone;
    }

}

DelimiterType MarkDownParser::GetDelimiterTypeForCharAtCurrentPosition()
{ 
    return (*m_curPos == '*')? Asterisk : Underscore;
}

bool MarkDownParser::IsEmphasisDelimiterRun(DelimiterType emphasisType)
{
    return ((m_currentDelimiterType == emphasisType ) || (m_emphasisState & EmphasisStart));
}

void MarkDownParser::UpdateCurrentEmphasisRunState(DelimiterType emphasisType)
{
    if (m_lookBehind != WhiteSpace)
    {
        m_checkLookAhead = (m_lookBehind == Puntuation);
        m_checkIntraWord = (m_lookBehind == Alphanumeric && emphasisType == Underscore);
    }
    ++m_delimiterCnts;
}

void MarkDownParser::ResetCurrentEmphasisRunState(DelimiterType emphasisType)
{
    m_emphasisState = EmphasisStart;
    m_delimiterCnts = 1;
}
// detects valid emphasis delimiters, when valid delimiters are found, they are added into
// a new space. each new delimiters that are part of the run is appended, in that way,
// it builds tokens of vectors
// each time emphasis tokens are found, they are also added into a lookup table.
// the look up table stores index of the corresponding token in the token vectors, and
// emphasis count and its types that are used in html generation 
void MarkDownParser::GenerateSymbolTable()
{
    while (m_curPos < m_text.end())
    {
        UpdateState();

        if ((m_emphasisState & InsideEmphasis) || 
            (m_linkState.GetState() == LinkState::LinkTextStart) || 
            (m_linkState.GetState() == LinkState::LinkDestinationStart))
        {
            // if new emphasis token found start capturing new token
            if ((m_emphasisState & EmphasisStart) || 
                (m_linkState.GetState() == LinkState::LinkTextStart ||
                (m_linkState.GetState() == LinkState::LinkDestinationStart)))
            { 

                CaptureCurrentCollectedStringAsRegularToken();
            }

            DelimiterType delimiterTypeForNewChar = GetDelimiterTypeForCharAtCurrentPosition(); 

            if(IsEmphasisDelimiterRun(delimiterTypeForNewChar))
            {
                UpdateCurrentEmphasisRunState(delimiterTypeForNewChar);
            }
            else
            {
                ResetCurrentEmphasisRunState(delimiterTypeForNewChar);
            }

            m_currentDelimiterType = delimiterTypeForNewChar;
        }

        if ((m_emphasisState == EmphasisEnd) || 
            ((m_emphasisState & InsideEmphasis) && (m_curPos + 1 == m_text.end())))
        {
            if (!TryCapturingRightEmphasisToken() && 
                !TryCapturingLeftEmphasisToken() &&
                !m_currentToken.empty())
            {
                // no valid emphasis delimiter runs found during current emphasis delimiter run
                // treat them as regular chars 
                CaptureCurrentCollectedStringAsRegularToken();
            }
            m_delimiterCnts = 0;
        }

        if (m_emphasisState & OutsideEmphasis)
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
