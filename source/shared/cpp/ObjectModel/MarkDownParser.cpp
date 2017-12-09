#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

MarkDownParser::MarkDownParser(const std::string &txt) : m_text(txt), m_curPos(m_text.begin())
{
}

// Following the rules speicified in CommonMark (http://spec.commonmark.org/0.27/)
// It generally supports more stricker version of the rules
// push left delims to stack, until matching right delim is found,
// update emphasis counts and type to build string after search is complete
std::string MarkDownParser::TransformToHtml()
{
    GenerateSymbolTable();

    if (m_emphasisLookUpTable.empty())
    {
        return "<p>" + m_text + "</p>";
    }

    EmphasisSyntaxCheck(m_emphasisLookUpTable.begin(), m_emphasisLookUpTable.end());

    return GenerateHtmlString();
}

///void MarkDownParser::EmphasisSyntaxCheck(EmphasisListInterator begin, EmphasisListInterator end) 
//// match and update emphasis  tokens
void MarkDownParser::EmphasisSyntaxCheck(EmphasisListInterator begin, EmphasisListInterator end) 
{
    std::vector<std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator> leftEmphasisToExplore;
    auto currentEmphasis = begin; 

    while (!(currentEmphasis == end))
    {
        // keep exploring left until right token is found
        if ((*currentEmphasis)->IsLeftEmphasis() || 
            ((*currentEmphasis)->IsLeftAndRightEmphasis() && leftEmphasisToExplore.empty()))
        {
            if ((*currentEmphasis)->IsLeftAndRightEmphasis() && (*currentEmphasis)->IsRightEmphasis())
            {
                // Reverse Direction Type; right empahsis to left emphasis
                (*currentEmphasis)->ReverseDirectionType();
            }

            leftEmphasisToExplore.push_back(currentEmphasis);
            ++currentEmphasis;
        }
        else if (!leftEmphasisToExplore.empty())
        {
            auto currentLeftEmphasis = leftEmphasisToExplore.back();
            // because of rule #9 & #10 and multiple of 3 rule, left delim can jump ahead of right delim,
            // so need to check this condition.
            //if (curr_left_delim->postionInTokenTable > top_right->postionInTokenTable)
            //{
            //    top_right++;
            //    continue;
            //}

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
            if (!(*currentLeftEmphasis)->IsMatch(*currentEmphasis))
            {
                std::vector<std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator> store;
                bool isFound = false;
                // search first if matching left emphasis can be found with the right delim
                // if match found, set the new left emphasis token as current token, and
                // process tokens and as of the result, any left emphasis tokens that were searched and not matching 
                // will be no longer considerred in tag processing
                // pop until matching delim is found
                while (!leftEmphasisToExplore.empty() && !isFound)
                {
                    auto leftToken = leftEmphasisToExplore.back();
                    //curr_left_delim = leftEmphasisToExplore.back();
                    // found left delim 
                    if ((*leftToken)->IsMatch(*currentEmphasis))
                    {
                        currentLeftEmphasis = leftToken;
                        isFound = true;
                    }
                    else
                    {
                        leftEmphasisToExplore.pop_back();
                        store.push_back(leftToken);
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
                        leftEmphasisToExplore.push_back(store.back());
                        store.pop_back();
                    }

                    // check for the reason why we had to backtrack
                    if ((*leftEmphasisToExplore.back())->IsSameType(*currentEmphasis))
                    {
                        //right emphasis becomes left emphasis
                        /// create new left empahsis html generator from right
                        (*currentEmphasis)->ReverseDirectionType();
                    }
                    else
                    {
                        // move to next token for right delim tokens
                        currentEmphasis++;
                    }
                    // no maching found begin from the start
                    continue;
                }
            }

            // check which one has leftover delims
            (*currentLeftEmphasis)->GenerateTags(*currentEmphasis);

            // all right delims used, move to next
            if ((*currentEmphasis)->IsDone())
            {
                currentEmphasis++;
            }

            // all left or right delims used, pop
            if ((*currentLeftEmphasis)->IsDone())
            { 
                leftEmphasisToExplore.pop_back();
            }
        }
        else
        { 
            currentEmphasis++;
        }
    }
}

std::string MarkDownParser::GenerateHtmlString() 
{ 
    // process tags 
    std::ostringstream html; 
    for (auto itr = m_tokenizedString.begin(); itr != m_tokenizedString.end(); itr++) 
    { 
        html << (*itr)->GenerateHtmlString();
    }

    return "<p>" + html.str() + "</p>";
}

void MarkDownParser::GetCh(char ch)
{
    // store chars unless it's escape
    if (ch != '\\'  ||
        (m_linkState.GetState() == LinkStateMachine::LinkTextStart))
    {
        m_currentToken += ch;
    }
}

void MarkDownParser::StartNewTokenCapture()
{
    m_currentToken.clear();
}

void MarkDownParser::CaptureLinkText()
{
    std::shared_ptr<MarkDownLinkTextHtmlGenerator> codeGen = 
        std::make_shared<MarkDownLinkTextHtmlGenerator>(m_tokenIterator);

    m_linkState.m_linkText = codeGen;
    m_linkLookUpTable.push_back(std::dynamic_pointer_cast<MarkDownLinkHtmlGenerator>(codeGen));
    m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
    if (m_tokenizedString.size() == 1)
        m_tokenIterator = m_tokenizedString.begin();
    else
        m_tokenIterator++;
}

void MarkDownParser::CaptureCurrentCollectedStringAsRegularToken()
{
    if(m_currentToken.empty())
        return;
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(m_currentToken);

    m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
    if (m_tokenizedString.size() == 1)
        m_tokenIterator = m_tokenizedString.begin();
    else
        m_tokenIterator++;
    if(m_linkState.GetState() == LinkStateMachine::LinkTextRun)
    { 
        CaptureLinkText();
    }

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
                    m_currentDelimiterType);

        m_emphasisLookUpTable.push_back(std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen));
        m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
        if (m_tokenizedString.size() == 1)
            m_tokenIterator = m_tokenizedString.begin();
        else
            m_tokenIterator++;

        m_currentToken.clear();
        return true;
    }
    return false;
}

bool MarkDownParser::IsRightEmphasisDelimiter()
{
    if (isspace(*m_curPos) && 
       (m_lookBehind != WhiteSpace) && 
       (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {        
        return true;
    }

    if (isalnum(*m_curPos) && 
        m_lookBehind != WhiteSpace && 
        m_tokenizedString.size() != 0)
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
    if (m_curPos + 1 == m_text.end())
    { 
        GetCh(*m_curPos);
    }

    if (IsRightEmphasisDelimiter())
    {
        std::shared_ptr<MarkDownRightEmphasisHtmlGenerator> codeGen = nullptr;
        if (IsLeftEmphasisDelimiter())
        {
            codeGen = 
                std::make_shared<MarkDownLeftAndRightEmphasisHtmlGenerator>(m_currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }
        else
        {
            codeGen = 
                // tokenizedStrings ->  to more meaningful reflect what it actually do
                std::make_shared<MarkDownRightEmphasisHtmlGenerator>(m_currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }

        // use staic cast
        m_emphasisLookUpTable.push_back(std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen));
        m_tokenizedString.push_back(std::dynamic_pointer_cast<MarkDownHtmlGenerator>(codeGen));
        if (m_tokenizedString.size() == 1)
            m_tokenIterator = m_tokenizedString.begin();
        else
            m_tokenIterator++;

        m_currentToken.clear();

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
        m_linkState.UpdateState(*m_curPos);
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
// add comments -> what it does: generating  n supported features + 1 tokens --> capture them in token class
void MarkDownParser::GenerateSymbolTable() // rename it to tokenize() // state machines
{

    while (m_curPos < m_text.end())
    {
        UpdateState();

        if ((m_emphasisState & InsideEmphasis) || 
            (m_linkState.GetState() == LinkStateMachine::LinkTextRun) || 
            (m_linkState.GetState() == LinkStateMachine::LinkDestinationStart))
        {
            // if new emphasis token found start capturing new token
            if ((m_emphasisState & EmphasisStart) || 
                (m_linkState.GetState() == LinkStateMachine::LinkTextRun ||
                (m_linkState.GetState() == LinkStateMachine::LinkDestinationStart)))
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

    if (m_emphasisState & OutsideEmphasis && !m_currentToken.empty())
    {
        CaptureCurrentCollectedStringAsRegularToken();
    }
}
