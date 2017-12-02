#include <iomanip>
#include "LinkState.h"
using namespace AdaptiveCards;

void LinkState::UpdateState(int ch)
{ 
    m_look_behind = ch;
    switch(ch)
    {
        case '[':
            UpdateWithOpeningSqureBracket(ch);
            return;
        case ']':
            UpdateWithClosingSqureBracket(ch);
            return;
        case '(':
            UpdateWithOpeningParenthesis(ch);
            return;
        case ')':
            UpdateWithClosingParenthesis(ch);
            return;
        default:
            if(isspace(ch))
            {
                UpdateWithWhiteSpace(ch);
                break;
            }
            UpdateWithEverythingElse(ch);
    }
}

void LinkState::UpdateWithOpeningSqureBracket(int ch)
{
    m_state = LinkTextOpening;
    m_current_delimiter_type = Bracket;
}

void LinkState::UpdateWithClosingSqureBracket(int ch)
{
    m_state = (m_state == LinkTextDetecting && 
            m_current_delimiter_type == Bracket)? LinkTextClosing : LinkInit;
}

void LinkState::UpdateWithOpeningParenthesis(int ch)
{
    m_state = (m_state == LinkTextClosing)? LinkDestinationOpening : LinkInit; 
    if(m_state != LinkInit)
    { 
        m_current_delimiter_type = Parenthesis;
    }
}

void LinkState::UpdateWithClosingParenthesis(int ch)
{
    m_state = (m_state == LinkTextDetecting && 
            m_current_delimiter_type == Parenthesis)? LinkDetected: LinkInit;
}

void LinkState::UpdateWithEverythingElse(int ch)
{
    if (m_state != LinkInit && m_state != LinkTextClosing)
    {
        m_state = LinkTextDetecting;
        return;
    }
    m_state = LinkInit;
}

void LinkState::UpdateWithWhiteSpace(int ch)
{
    if (ch == '\n' || ch == '\r')
    {
        m_state = LinkInit;
        m_IsWhiteSpaceDetected = false;
        return;
    }

    if(m_state == LinkInit || m_state == LinkTextClosing)
    {
        m_IsWhiteSpaceDetected = false;
        m_state = LinkInit;
        return;
    }

    if(isspace(m_look_behind))
    {
        return;
    }
    
    if(m_IsWhiteSpaceDetected)
    {
        m_state = LinkInit;
        m_IsWhiteSpaceDetected = false;
    }
}
