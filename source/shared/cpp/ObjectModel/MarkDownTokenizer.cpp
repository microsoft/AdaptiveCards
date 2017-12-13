#include <iostream>
#include "MarkDownTokenizer.h"

using namespace AdaptiveCards;

bool MarkDownLinkTokenizer::UpdateState(int ch, std::string &currentToken) 
{ 
    state newState = m_stateMachine[m_current_state](*this, ch, currentToken);
    m_current_state = newState;

    if (newState == LinkDestinationEnd)
    {
        m_current_state = LinkInit;
    }

    if (newState == LinkInit)
    { 
        m_linkTextEmphasisTokenizer.AppendEmphasisTokens(m_emphasisLookUpTable);
        m_linkTextEmphasisTokenizer.AppendCodeGenTokens(m_codeGenTokens);
    }

    return (newState == LinkDestinationEnd || newState == LinkInit);
}

bool MarkDownLinkTokenizer::IsItLink() 
{
    return m_current_state == LinkDestinationEnd;
}

void MarkDownLinkTokenizer::Clear()
{
    m_current_state = LinkInit;
    m_codeGenTokens.clear();
    m_emphasisLookUpTable.clear();
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkInit(MarkDownLinkTokenizer &linkTokenizer, 
        int ch, std::string &currentToken)
{
    if (ch == '[')
    {    
        return LinkTextRun;
    }

    return LinkInit;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkTextRun(MarkDownLinkTokenizer &linkTokenizer, 
                int ch, std::string &currentToken)
{ 
    if (ch == ']')
    {
        currentToken.pop_back();
        linkTokenizer.GetLinkTextEmphasisTokenizer().Flush(currentToken);
        return LinkTextEnd;
    }
    else
    {
        switch (ch)
        {
            case '[': case '(': case ')':
            {
                std::shared_ptr<MarkDownStringHtmlGenerator> htmlToken =
                    std::make_shared<MarkDownStringHtmlGenerator>(std::string("["));
                std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(htmlToken);
                linkTokenizer.PushFront(token);
                return (ch == '[') ? LinkTextRun : LinkInit;
            }
            default:
                linkTokenizer.GetLinkTextEmphasisTokenizer().UpdateState(ch, currentToken);
        }
        return LinkTextRun;
    }
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkTextEnd(MarkDownLinkTokenizer &linkTokenizer,
    int ch, std::string &currentToken)
{
    if (ch == '(')
    { 
        currentToken.pop_back();
        return LinkDestinationStart;
    } 
    
    return LinkInit;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkDestinationStart(MarkDownLinkTokenizer &linkTokenizer, 
                int ch, std::string &currentToken)
{
    if (isspace(ch))
    {
        return LinkDestinationStart;
    }

    if (iscntrl(ch))
    {
        return LinkInit;
    }

    if(ch == ')')
    { 
        currentToken.pop_back();
        linkTokenizer.CaptureLinkToken(ch, currentToken);
        return LinkDestinationEnd;
    }

    if (currentToken.back() == '(')
    { 
        currentToken.pop_back();
    }
    return LinkDestinationRun;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkDestinationRun(MarkDownLinkTokenizer &linkTokenizer, 
                int ch, std::string &currentToken)
{
    if (isspace(ch) || iscntrl(ch))
    { 
        return LinkInit;
    }

    if(ch == ')')
    { 
        currentToken.pop_back();
        linkTokenizer.CaptureLinkToken(ch, currentToken);
        return LinkDestinationEnd;
    }

    return LinkDestinationRun;
}

void MarkDownLinkTokenizer::CaptureLinkToken(int ch, std::string &currentToken)
{
    std::ostringstream html; 
    html << "<a href=\"";
    html << MarkDownStringHtmlGenerator(currentToken).GenerateHtmlString();
    currentToken.clear();
    html << "\">";
    m_linkTextEmphasisTokenizer.MatchLeftAndRightEmphasises();
    html << m_linkTextEmphasisTokenizer.GenerateHtmlString();
    html << "</a>";

    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(html.str());

    m_codeGenTokens.push_back(std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen));
}

void MarkDownTokenizer::AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &a) 
{
    a.splice(a.end(), m_codeGenTokens);
}

void MarkDownTokenizer::AppendEmphasisTokens(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &a) 
{
    a.splice(a.end(), m_emphasisLookUpTable);
}

void MarkDownTokenizer::AppendEmphasisTokens(MarkDownTokenizer &tokenizer) 
{
    tokenizer.GetEmphasisTokens().splice(tokenizer.GetEmphasisTokens().end(), m_emphasisLookUpTable);
}

void MarkDownTokenizer::PushFront(std::shared_ptr<MarkDownHtmlGenerator> &token) 
{
    m_codeGenTokens.push_front(token);
}

//// match and update emphasis  tokens
void MarkDownEmphasisTokenizer::MatchLeftAndRightEmphasises() 
{
    std::vector<std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator> leftEmphasisToExplore;
    auto currentEmphasis = m_emphasisLookUpTable.begin(); 

    while (!(currentEmphasis == m_emphasisLookUpTable.end()))
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

std::string MarkDownEmphasisTokenizer::GenerateHtmlString() 
{ 
    // process tags 
    std::ostringstream html; 
    for (auto itr = m_codeGenTokens.begin(); itr != m_codeGenTokens.end(); itr++) 
    { 
        html << (*itr)->GenerateHtmlString();
    }

    return html.str();
}

bool MarkDownEmphasisTokenizer::UpdateState(int ch, std::string& currentToken)
{ 
    state newState = m_stateMachine[m_current_state](*this, ch, currentToken);
    m_current_state = newState;
    return true;
}

void MarkDownEmphasisTokenizer::Flush(std::string& currentToken)
{
    if (m_current_state != EmphasisNone)
    {
        CaptureEmphasisToken(currentToken[0], currentToken);
        m_delimiterCnts = 0;
    }
    else
    {
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
    currentToken.clear();
}

bool MarkDownEmphasisTokenizer::IsMarkDownDelimiter(char ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

void MarkDownEmphasisTokenizer::CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken) 
{
    if (currentToken.size() == 0)
        return;
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(currentToken);

    m_codeGenTokens.push_back(std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen));

    currentToken.clear();
}

void MarkDownEmphasisTokenizer::UpdateCurrentEmphasisRunState(DelimiterType emphasisType)
{
    if (m_lookBehind != WhiteSpace)
    {
        m_checkLookAhead = (m_lookBehind == Puntuation);
        m_checkIntraWord = (m_lookBehind == Alphanumeric && emphasisType == Underscore);
    }
    ++m_delimiterCnts;
    m_currentDelimiterType = emphasisType;
}

bool MarkDownEmphasisTokenizer::IsRightEmphasisDelimiter(int ch)
{
    if (isspace(ch) && 
       (m_lookBehind != WhiteSpace) && 
       (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {        
        return true;
    }

    if (isalnum(ch) && 
        m_lookBehind != WhiteSpace && 
        m_codeGenTokens.size() != 0)
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

    if (ispunct(ch) && m_lookBehind != WhiteSpace)
    {
        return true;
    }

    return false;;
}

bool MarkDownEmphasisTokenizer::TryCapturingRightEmphasisToken(int ch, std::string &currentToken)
{
    if (IsRightEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownRightEmphasisHtmlGenerator> codeGen = nullptr;
        if (IsLeftEmphasisDelimiter(ch))
        {
            codeGen = 
                std::make_shared<MarkDownLeftAndRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }
        else
        {
            codeGen = 
                std::make_shared<MarkDownRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }

        m_emphasisLookUpTable.push_back(std::static_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen));
        m_codeGenTokens.push_back(std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen));
        // use staic cast
        currentToken.clear();

        return true;
    }
    return false;
}

// save left emphasis to look up table
// return true, if left emphasis was detected and added
bool MarkDownEmphasisTokenizer::TryCapturingLeftEmphasisToken(int ch, std::string &currentToken)
{
    // left emphasis detected, save emphasis for later reference
    if (IsLeftEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownLeftEmphasisHtmlGenerator> codeGen = 
            std::make_shared<MarkDownLeftEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                    m_currentDelimiterType);

        m_emphasisLookUpTable.push_back(std::static_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen));
        m_codeGenTokens.push_back(std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen));

        currentToken.clear();
        return true;
    }
    return false;
}

void MarkDownEmphasisTokenizer::UpdateLookBehind(int ch)
{
    //store ch and move itr
    if (isspace(ch))
    {
        m_lookBehind = WhiteSpace;
    }

    if (isalnum(ch))
    {
        m_lookBehind = Alphanumeric;
    }

    if (ispunct(ch))
    {
        m_lookBehind = (ch == '\\')? Escape : Puntuation;
    }
}

void MarkDownEmphasisTokenizer::CaptureEmphasisToken(int ch, std::string &currentToken)
{
    if (!TryCapturingRightEmphasisToken(ch, currentToken) && 
        !TryCapturingLeftEmphasisToken(ch, currentToken) &&
        !currentToken.empty())
    {
        // no valid emphasis delimiter runs found during current emphasis delimiter run
        // treat them as regular string tokens
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
}

unsigned int MarkDownEmphasisTokenizer::MarkDownEmphasisStateNone(MarkDownEmphasisTokenizer &emphasisStateMachine, 
        int ch, std::string &currentToken) 
{
    if(emphasisStateMachine.IsMarkDownDelimiter(ch))
    {
        // encounterred first emphasis delimiter
        currentToken.pop_back();
        emphasisStateMachine.CaptureCurrentCollectedStringAsRegularToken(currentToken);
        currentToken.push_back(ch);
        DelimiterType emphasisType = MarkDownEmphasisTokenizer::GetDelimiterTypeForCharAtCurrentPosition(ch); 
        emphasisStateMachine.UpdateCurrentEmphasisRunState(emphasisType);
        return MarkDownEmphasisTokenizer::EmphasisRun;
    }
    else
    {    
        emphasisStateMachine.UpdateLookBehind(ch);
        return MarkDownEmphasisTokenizer::EmphasisNone;
    }
}

unsigned int MarkDownEmphasisTokenizer::MarkDownEmphasisStateRun(MarkDownEmphasisTokenizer &emphasisStateMachine, 
        int ch, std::string &currentToken) 
{
    if (emphasisStateMachine.IsMarkDownDelimiter(ch))
    {
        DelimiterType emphasisType = MarkDownEmphasisTokenizer::GetDelimiterTypeForCharAtCurrentPosition(ch);
        if (emphasisStateMachine.IsEmphasisDelimiterRun(emphasisType))
        {
            emphasisStateMachine.UpdateCurrentEmphasisRunState(emphasisType);
        }
    }
    else
    {
        if (ch != '\\')
        {
            currentToken.pop_back();
            emphasisStateMachine.CaptureEmphasisToken(ch, currentToken);
            currentToken.push_back(ch);
        }
        else
        {
            emphasisStateMachine.CaptureEmphasisToken(ch, currentToken);
        }

        emphasisStateMachine.ResetCurrentEmphasisState();
        emphasisStateMachine.UpdateLookBehind(ch);
        return MarkDownEmphasisTokenizer::EmphasisNone;
    }
    return MarkDownEmphasisTokenizer::EmphasisRun;
}
