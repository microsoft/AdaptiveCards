#pragma once
#include "MarkDownHtmlGenerator.h"
#include "BaseCardElement.h"
#include <list>

namespace AdaptiveCards
{
    class MarkDownTokenizer
    {
        public:
        MarkDownTokenizer(){};
        virtual bool UpdateState(int ch, std::string& currentToken) = 0;
        virtual void Flush(std::string& currentToken) = 0;
        typedef unsigned int state;
        void AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &); 
        void AppendEmphasisTokens(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &); 
        void AppendEmphasisTokens(MarkDownTokenizer &); 
        void PushFrontToCodeGenList(std::shared_ptr<MarkDownHtmlGenerator> &token);
        void PushBackToCodeGenList(std::shared_ptr<MarkDownHtmlGenerator> &token);
        void PopFrontFromCodeGenList();
        void PopBackFromCodeGenList();
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &GetEmphasisTokens() {return m_emphasisLookUpTable;};

        protected:
        std::list<std::shared_ptr<MarkDownHtmlGenerator>> m_codeGenTokens;
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> m_emphasisLookUpTable;
    };

    class MarkDownEmphasisTokenizer: public MarkDownTokenizer
    {
        public:
        enum EmphasisState
        {   
            // init state for emphasis detection 
            EmphasisNone = 0x0,
            // state for a emphasis delimiter run 
            EmphasisRun = 0x1,   
        };

        bool UpdateState(int ch, std::string& currentToken);
        void Flush(std::string& currentToken);
        void Clear();
        void MatchLeftAndRightEmphasises();
        std::string GenerateHtmlString();
        bool IsMarkDownDelimiter(char ch);
        void CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken); 
        void UpdateCurrentEmphasisRunState(DelimiterType emphasisType);
        bool IsEmphasisDelimiterRun(DelimiterType emphasisType) { return m_currentDelimiterType == emphasisType; }
        void ResetCurrentEmphasisState() { m_delimiterCnts = 0; }
        bool IsRightEmphasisDelimiter(int ch);
        bool TryCapturingRightEmphasisToken(int ch, std::string &currentToken);
        bool IsLeftEmphasisDelimiter(int ch) 
        {
            return (m_delimiterCnts && 
                    !isspace(ch) && 
                    !(m_lookBehind == Alphanumeric && ispunct(ch)) && 
                    !(m_lookBehind == Alphanumeric && m_currentDelimiterType == Underscore));
        };
        bool TryCapturingLeftEmphasisToken(int ch, std::string &currentToken);
        void CaptureEmphasisToken(int ch, std::string &currentToken);
        void UpdateLookBehind(int ch);
        static DelimiterType GetDelimiterTypeForCharAtCurrentPosition(int ch) { return (ch == '*')? Asterisk : Underscore; };

        typedef unsigned int (* UpdateStateWithChar)(MarkDownEmphasisTokenizer &emphasisStateMachine, 
                int ch, std::string &currentToken);
        static unsigned int MarkDownEmphasisStateNone(MarkDownEmphasisTokenizer &emphasisStateMachine, 
                int ch, std::string &currentToken);
        static unsigned int MarkDownEmphasisStateRun(MarkDownEmphasisTokenizer &emphasisStateMachine, 
                int ch, std::string &currentToken); 

        protected:
        bool m_checkLookAhead = false;
        bool m_checkIntraWord = false;
        int m_lookBehind = Init;
        int m_delimiterCnts = 0;
        DelimiterType m_currentDelimiterType = Init;
        unsigned int m_current_state = 0;

        std::vector<UpdateStateWithChar> m_stateMachine = 
            {
                MarkDownEmphasisStateNone, 
                MarkDownEmphasisStateRun,
            };
    };

    class MarkDownLinkTokenizer : public MarkDownTokenizer
    {
    public:
        enum LinkStateEnum
        {
            LinkInit = 0,
            LinkTextReinit,
            LinkTextRun,
            LinkTextEnd,
            LinkDestinationStart,
            LinkDestinationRun,
            LinkDestinationEnd,
        };
        typedef unsigned int state;

        bool IsItLink(); 
        bool UpdateState(int ch, std::string& currentToken);
        void Flush(std::string& currentToken);
        state GetState() const { return m_current_state; }
        void Clear();
        void AddLinkDelimiterToFrontOfCodeGenList(int ch);
        void AddLinkDelimiterToBackOfCodeGenList(int ch);
        MarkDownEmphasisTokenizer &GetLinkTextEmphasisTokenizer() { return m_linkTextEmphasisTokenizer; };

    private:
        void CaptureLinkToken(int ch, std::string &currentToken);
        typedef unsigned int (* UpdateStateWithChar)(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkInit(MarkDownLinkTokenizer &, int , std::string &);
        static unsigned int StateTransitionCheckAtLinkTextRun(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkTextEnd(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkDestinationStart(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkDestinationRun(MarkDownLinkTokenizer &linkTokenizer, int ch, std::string &currentToken);

        std::vector<UpdateStateWithChar> m_stateMachine = 
            {
                StateTransitionCheckAtLinkInit, 
                StateTransitionCheckAtLinkTextRun,
                StateTransitionCheckAtLinkTextRun,
                StateTransitionCheckAtLinkTextEnd, 
                StateTransitionCheckAtLinkDestinationStart,
                StateTransitionCheckAtLinkDestinationRun,
            };

        state m_current_state = 0;
        MarkDownEmphasisTokenizer m_linkTextEmphasisTokenizer;
    };
}
