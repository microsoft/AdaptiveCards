#include <iomanip>
#include "LinkState.h"
using namespace AdaptiveCards;

void LinkStateMachine::UpdateState(int ch)
{ 
    state newState = m_stateMachine[m_current_state](ch);
    m_current_state = newState;
}

bool LinkStateMachine::IsItLink() 
{
    return m_current_state == LinkDestinationEnd;
}

unsigned int LinkStateMachine::StateTransitionCheckAtLinkInit(int ch)
{
    return (ch == '[')?  LinkTextStart : LinkInit;
}

unsigned int LinkStateMachine::StateTransitionCheckAtLinkTextStart(int ch)
{
    return (ch == ']')? LinkTextEnd : LinkTextRun;
}

unsigned int LinkStateMachine::StateTransitionCheckAtLinkTextRun(int ch)
{
    return (ch == ']')? LinkTextEnd : LinkTextStart;
}

unsigned int LinkStateMachine::StateTransitionCheckAtLinkTextEnd(int ch)
{
    return (ch == '(')? LinkDestinationStart : LinkInit;
}

unsigned int LinkStateMachine::StateTransitionCheckAtLinkDestinationStart(int ch)
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

unsigned int LinkStateMachine::StateTransitionCheckAtLinkInsideDestination(int ch)
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

