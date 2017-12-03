#pragma once

#include "BaseCardElement.h"
#include <vector>

namespace AdaptiveCards
{
    class LinkState
    {
    public:
        enum LinkStateEnum
        {
            LinkInit = 0,
            LinkTextStart = 1,
            LinkTextEnd,
            LinkDestinationStart,
            LinkInsideDestination,
            LinkDestinationEnd,
        };
        typedef unsigned int state;

        bool IsItLink(); 
        void UpdateState(int ch);
        state GetState() const { return m_current_state; }

    private:
        typedef unsigned int (* UpdateStateWithChar)(int ch);
        static unsigned int StateTransitionCheckAtLinkInit(int ch);
        static unsigned int StateTransitionCheckAtLinkTextStart(int ch);
        static unsigned int StateTransitionCheckAtLinkTextEnd(int ch);
        static unsigned int StateTransitionCheckAtLinkDestinationStart(int ch);
        static unsigned int StateTransitionCheckAtLinkInsideDestination(int ch);
        std::vector<UpdateStateWithChar> m_stateMachine = 
            {
                StateTransitionCheckAtLinkInit, 
                StateTransitionCheckAtLinkTextStart,
                StateTransitionCheckAtLinkTextEnd, 
                StateTransitionCheckAtLinkDestinationStart,
                StateTransitionCheckAtLinkInsideDestination,
            };
        state m_current_state = 0;
    };
}
