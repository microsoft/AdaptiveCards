#pragma once
#include "MarkDownHtmlGenerator.h"
#include "BaseCardElement.h"
#include <list>

namespace AdaptiveCards
{
    class LinkStateMachine
    {
    public:
        enum LinkStateEnum
        {
            LinkInit = 0,
            LinkTextStart,
            LinkTextRun,
            LinkTextEnd,
            LinkDestinationStart,
            LinkInsideDestination,
            LinkDestinationEnd,
        };
        typedef unsigned int state;

        bool IsItLink(); 
        void UpdateState(int ch);
        state GetState() const { return m_current_state; }
        std::shared_ptr<MarkDownLinkTextHtmlGenerator> m_linkText = nullptr;

    private:
        typedef unsigned int (* UpdateStateWithChar)(int ch);
        static unsigned int StateTransitionCheckAtLinkInit(int ch);
        static unsigned int StateTransitionCheckAtLinkTextStart(int ch);
        static unsigned int StateTransitionCheckAtLinkTextRun(int ch);
        static unsigned int StateTransitionCheckAtLinkTextEnd(int ch);
        static unsigned int StateTransitionCheckAtLinkDestinationStart(int ch);
        static unsigned int StateTransitionCheckAtLinkInsideDestination(int ch);
        std::vector<UpdateStateWithChar> m_stateMachine = 
            {
                StateTransitionCheckAtLinkInit, 
                StateTransitionCheckAtLinkTextStart,
                StateTransitionCheckAtLinkTextRun,
                StateTransitionCheckAtLinkTextEnd, 
                StateTransitionCheckAtLinkDestinationStart,
                StateTransitionCheckAtLinkInsideDestination,
            };

        state m_current_state = 0;
    };
}
