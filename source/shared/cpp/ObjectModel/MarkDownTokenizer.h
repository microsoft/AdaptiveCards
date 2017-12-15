#pragma once
#include "MarkDownHtmlGenerator.h"
#include <iomanip>
#include "BaseCardElement.h"
#include <list>

namespace AdaptiveCards
{
    class MarkDownTokenizer
    {
        public:
        MarkDownTokenizer(){};
        //virtual bool UpdateState(int ch, std::string& currentToken) = 0;
        virtual void Match(std::stringstream &) = 0;
        virtual void Flush(std::string& currentToken) = 0;
        typedef unsigned int state;
        void AppendCodeGenTokens(std::list<std::shared_ptr<MarkDownHtmlGenerator>> &); 
        void AppendEmphasisTokens(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &); 
        void AppendEmphasisTokens(MarkDownTokenizer &); 
        void PushFrontToCodeGenList(std::shared_ptr<MarkDownHtmlGenerator> &token);
        void PushBackToCodeGenList(std::shared_ptr<MarkDownHtmlGenerator> &token);
        void PopFrontFromCodeGenList();
        void PopBackFromCodeGenList();
        void Block(std::stringstream &);
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> &GetEmphasisTokens() {return m_emphasisLookUpTable;};

        protected:
        std::list<std::shared_ptr<MarkDownHtmlGenerator>> m_codeGenTokens;
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> m_emphasisLookUpTable;
    };

    class EmphasisParser: public MarkDownTokenizer
    {
        public:
        enum EmphasisState
        {   
            // init state for emphasis detection 
            Text = 0x0,
            // state for a emphasis delimiter run 
            Emphasis = 0x1,   
            // Emphasis statement is captured
            Captured = 0x2,
        };

        virtual void Match(std::stringstream &);
        //bool UpdateState(int ch, std::string& currentToken);
        void Flush(std::string& currentToken);
        void Clear();
        void MatchLeftAndRightEmphasises();
        std::string GenerateHtmlString();
        bool IsMarkDownDelimiter(char ch);
        void CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken); 
        void CaptureCurrentCollectedStringAsRegularToken();
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

        typedef unsigned int (* MatchWithChar)(EmphasisParser&, std::stringstream &, std::string &);
        static unsigned int MatchText(EmphasisParser &, std::stringstream &, std::string &);
        static unsigned int MatchEmphasis(EmphasisParser &, std::stringstream &, std::string &);

        protected:
        bool m_checkLookAhead = false;
        bool m_checkIntraWord = false;
        int m_lookBehind = Init;
        int m_delimiterCnts = 0;
        DelimiterType m_currentDelimiterType = Init;
        unsigned int m_current_state = 0;

        std::vector<MatchWithChar> m_stateMachine = 
            {
                MatchText, 
                MatchEmphasis,
            };

        std::string m_current_token;
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
        void Match(std::stringstream &);
        void Flush(std::string& currentToken);
        state GetState() const { return m_current_state; }
        void Clear();
        void AddLinkDelimiterToFrontOfCodeGenList(int ch);
        void AddLinkDelimiterToBackOfCodeGenList(int ch);
        EmphasisParser &GetLinkTextEmphasisTokenizer() { return m_linkTextEmphasisTokenizer; };

    private:
        void CaptureLinkToken(int ch, std::string &currentToken);
        typedef unsigned int (* UpdateStateWithChar)(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkInit(MarkDownLinkTokenizer &, int , std::string &);
        static unsigned int StateTransitionCheckAtLinkTextRun(MarkDownLinkTokenizer &, int, std::string &);
        static unsigned int StateTransitionCheckAtLinkTextEnd(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkDestinationStart(MarkDownLinkTokenizer &, int, std::string &); 
        static unsigned int StateTransitionCheckAtLinkDestinationRun(MarkDownLinkTokenizer &linkTokenizer, int ch, std::string &currentToken);

        bool MatchAtLinkInit(std::stringstream &);
        bool MatchAtLinkTextRun(std::stringstream &);
        bool MatchAtLinkTextEnd(std::stringstream &); 
        bool MatchAtLinkDestinationStart(std::stringstream &); 
        bool MatchAtLinkDestinationRun(std::stringstream &);

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
        EmphasisParser m_linkTextEmphasisTokenizer;
    };
}
