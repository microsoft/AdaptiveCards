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
        static void CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken, 
                std::list<std::shared_ptr<MarkDownHtmlGenerator>> &tokensOfString);
        virtual void UpdateState(int ch, std::string& currentToken) = 0;
        virtual void Flush(std::string& currentToken) = 0;
        typedef unsigned int state;
        void AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &); 
        void AppendEmphasisTokens(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &);
        void AppendTokens(MarkDownTokenizer& tokenizer);

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

        void UpdateState(int ch, std::string& currentToken);
        void Flush(std::string& currentToken);
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
            //LinkTextStart,
            LinkTextRun,
            LinkTextEnd,
            LinkDestinationStart,
            LinkInsideDestination,
            LinkDestinationEnd,
            LinkRestart,
        };
        typedef unsigned int state;

        bool IsItLink(); 
        void UpdateState(int ch, std::string& currentToken);
        state GetState() const { return m_current_state; }
        MarkDownEmphasisTokenizer &GetLinkTextEmphasisTokenizer() { return m_linkTextEmphasisTokenizer; };
        MarkDownEmphasisTokenizer &GetLinkDestinationEmphasisTokenizer() { return m_linkDestinationEmphasisTokenizer; };
        MarkDownEmphasisTokenizer &GetTextBlockEmphasisTokenizer() { return m_textBlockEmphasisTokenizer; };
        std::shared_ptr<MarkDownLinkTextHtmlGenerator> m_linkText = nullptr;

    private:
        typedef unsigned int (* UpdateStateWithChar)(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkInit(MarkDownLinkTokenizer &, int , std::string &);
        //static unsigned int StateTransitionCheckAtLinkTextStart(int ch);
        static unsigned int StateTransitionCheckAtLinkTextRun(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkTextEnd(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkDestinationStart(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkInsideDestination(MarkDownLinkTokenizer &, int, std::string &); 
        std::vector<UpdateStateWithChar> m_stateMachine = 
            {
                StateTransitionCheckAtLinkInit, 
                //StateTransitionCheckAtLinkTextStart,
                StateTransitionCheckAtLinkTextRun,
                StateTransitionCheckAtLinkTextEnd, 
                StateTransitionCheckAtLinkDestinationStart,
                StateTransitionCheckAtLinkInsideDestination,
            };

        state m_current_state = 0;
        MarkDownEmphasisTokenizer m_linkTextEmphasisTokenizer;
        MarkDownEmphasisTokenizer m_linkDestinationEmphasisTokenizer;
        MarkDownEmphasisTokenizer m_textBlockEmphasisTokenizer;
    };
}
