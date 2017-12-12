#include <iostream>
#include "MarkDownTokenizer.h"
using namespace AdaptiveCards;

void MarkDownLinkTokenizer::UpdateState(int ch, std::string &currentToken) 
{ 
    state newState = m_stateMachine[m_current_state](*this, ch, currentToken);
    if (newState == LinkRestart)
    {
    }
    m_current_state = newState;
}

bool MarkDownLinkTokenizer::IsItLink() 
{
    return m_current_state == LinkDestinationEnd;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkInit(MarkDownLinkTokenizer &linkTokenizer, 
        int ch, std::string &currentToken)
{
    if (ch == '[')
    {
        return LinkTextRun;
    }
    else
    {
        // link activity not detected
        // keep process regular and emphas text
        linkTokenizer.GetTextBlockEmphasisTokenizer().UpdateState(ch, currentToken);
        return LinkInit;
    }
}

//unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkTextStart(int ch)
//{
//    return (ch == ']')? LinkTextEnd : LinkTextRun;
//}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkTextRun(MarkDownLinkTokenizer &linkTokenizer, 
                int ch, std::string &currentToken)
{ 
    if (ch == ']')
    {
        return LinkTextEnd;
    }
    // invalid link detected, append everything that was detected to tokens 
    else if (ch == '[')
    {
        linkTokenizer.GetTextBlockEmphasisTokenizer().AppendTokens(
                linkTokenizer.GetLinkTextEmphasisTokenizer()
        linkTokenizer.GetTextBlockEmphasisTokenizer().AppendEmphasisTokens();
        return LinkTextRun;
    }
    else
    {
        linkTokenizer.GetLinkTextEmphasisTokenizer().UpdateState(ch, currentToken);
        return LinkTextRun;
    }

    linkTokenizer.GetLinkTextEmphasisTokenizer().UpdateState(ch, currentToken);
    return LinkTextRun;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkTextEnd(MarkDownLinkTokenizer &linkTokenizer, 
                int ch, std::string &currentToken)
{
    return (ch == '(')? LinkDestinationStart : LinkInit;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkDestinationStart(int ch)
{
    if (isspace(ch))
    {
        return LinkDestinationStart;
    }

    if (iscntrl(ch))
    {
        return LinkInit;
    }

    return LinkInsideDestination;
}

unsigned int MarkDownLinkTokenizer::StateTransitionCheckAtLinkInsideDestination(int ch)
{
    if(isspace(ch) || iscntrl(ch))
    {
        return LinkInit;
    }

    if(ch == ')')
    {
        return LinkDestinationEnd;
    }

    return LinkInsideDestination;
}

void MarkDownTokenizer::AppendTokens(MarkDownTokenizer& tokenizer)
{
    this->AppendEmphasisTokens(
    this->AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &a) 
}
void MarkDownTokenizer::AppendEmphasisTokens(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &a) 
{
    a.splice(a.end(), m_emphasisLookUpTable);
}

void MarkDownTokenizer::AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &a) 
{
    a.splice(a.end(), m_codeGenTokens);
}

void MarkDownEmphasisTokenizer::UpdateState(int ch, std::string& currentToken)
{ 
    state newState = m_stateMachine[m_current_state](*this, ch, currentToken);
    m_current_state = newState;
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
        emphasisStateMachine.CaptureCurrentCollectedStringAsRegularToken(currentToken);
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
        emphasisStateMachine.CaptureEmphasisToken(ch, currentToken);
        emphasisStateMachine.ResetCurrentEmphasisState();
        emphasisStateMachine.UpdateLookBehind(ch);
        return MarkDownEmphasisTokenizer::EmphasisNone;
    }
    return MarkDownEmphasisTokenizer::EmphasisRun;
}
