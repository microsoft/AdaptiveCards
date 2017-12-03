#include <iomanip>
#include "LinkState.h"
using namespace AdaptiveCards;

void LinkState::UpdateState(int ch)
{ 
    state newState = m_stateMachine[m_current_state](ch);
    m_current_state = newState;
}

bool LinkState::IsItLink() 
{
    return m_current_state == LinkDestinationEnd;
}

unsigned int LinkState::StateTransitionCheckAtLinkInit(int ch)
{
    return (ch == '[')?  LinkTextStart : LinkInit;
}

unsigned int LinkState::StateTransitionCheckAtLinkTextStart(int ch)
{
    return (ch == ']')? LinkTextEnd : LinkTextStart;
}

unsigned int LinkState::StateTransitionCheckAtLinkTextEnd(int ch)
{
    return (ch == '(')? LinkDestinationStart : LinkInit;
}

unsigned int LinkState::StateTransitionCheckAtLinkDestinationStart(int ch)
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

unsigned int LinkState::StateTransitionCheckAtLinkInsideDestination(int ch)
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

