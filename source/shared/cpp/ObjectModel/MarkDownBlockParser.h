#pragma once
#include "MarkDownHtmlGenerator.h"
#include <iomanip>
#include "BaseCardElement.h"
#include "MarkDownParsedResult.h"

namespace AdaptiveCards
{
    class MarkDownBlockParser
    {
        public:
        MarkDownBlockParser(){};
        // Matches each MarkDown's Syntax Form
        // For each match, stream moves to the next char
        virtual void Match(std::stringstream &) = 0;
        // Parses Block
        void ParseBlock(std::stringstream &);
        // Returns Parse result
        MarkDownParsedResult &GetParsedResult() { return m_parsedResult; }

        protected:
        // Holds parsed results
        MarkDownParsedResult m_parsedResult;
    };

    class EmphasisParser: public MarkDownBlockParser
    {
        public:
        enum EmphasisState
        {   
            // Text is being handled
            Text = 0x0,
            // Emphasis is being handled
            Emphasis = 0x1,   
            // Empahais Parsing is done
            Captured = 0x2,
        };

        virtual void Match(std::stringstream &);
        // Captures remaining charaters in given token
        // and causes the emphasis parsing to terminate
        void Flush(std::string& currentToken);
        // check if given character is * or _
        bool IsMarkDownDelimiter(char ch);
        void CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken); 
        void CaptureCurrentCollectedStringAsRegularToken();
        void UpdateCurrentEmphasisRunState(DelimiterType emphasisType);
        // Check if current delimiter will be considererd as a delimiter run
        bool IsEmphasisDelimiterRun(DelimiterType emphasisType) { return m_currentDelimiterType == emphasisType; }
        void ResetCurrentEmphasisState() { m_delimiterCnts = 0; }
        bool IsRightEmphasisDelimiter(char ch);
        // Attempt to capture current emphasis as right emphasis
        bool TryCapturingRightEmphasisToken(char ch, std::string &currentToken);
        bool IsLeftEmphasisDelimiter(char ch) 
        {
            return (m_delimiterCnts && 
                    !isspace(ch) && 
                    !(m_lookBehind == Alphanumeric && ispunct(ch)) && 
                    !(m_lookBehind == Alphanumeric && m_currentDelimiterType == Underscore));
        };
        // Attempt to capture current emphasis as right emphasis
        bool TryCapturingLeftEmphasisToken(char ch, std::string &currentToken);
        void CaptureEmphasisToken(char ch, std::string &currentToken);
        void UpdateLookBehind(char ch);
        static DelimiterType GetDelimiterTypeForCharAtCurrentPosition(char ch) { return (ch == '*')? Asterisk : Underscore; };

        typedef EmphasisState (* MatchWithChar)(EmphasisParser&, std::stringstream &, std::string &);
        // Callback function that handles the Text State
        static EmphasisState MatchText(EmphasisParser &, std::stringstream &, std::string &);
        // Callback function that handles the Emphasis State
        static EmphasisState MatchEmphasis(EmphasisParser &, std::stringstream &, std::string &);

        protected:
        bool m_checkLookAhead = false;
        bool m_checkIntraWord = false;
        int m_lookBehind = Init;
        int m_delimiterCnts = 0;
        DelimiterType m_currentDelimiterType = Init;
        unsigned int m_current_state = 0;

        // vector of callback functions that handles state transistions
        std::vector<MatchWithChar> m_stateMachine = 
            {
                MatchText, 
                MatchEmphasis,
            };

        // holds currently collected token
        std::string m_current_token;
    };

    class LinkParser : public MarkDownBlockParser
    {
        public:
        void Match(std::stringstream &);

        private:
        void CaptureLinkToken();

        // Matches Initial sytax of link
        bool MatchAtLinkInit(std::stringstream &);
        // Matches LinkText Run sytax of link
        bool MatchAtLinkTextRun(std::stringstream &);
        // Matches LinkText End sytax of link
        bool MatchAtLinkTextEnd(std::stringstream &); 
        // Matches LinkDestination Start sytax of link
        bool MatchAtLinkDestinationStart(std::stringstream &); 
        // Matches LinkDestination Run sytax of link
        bool MatchAtLinkDestinationRun(std::stringstream &);

        // holds intermidiate result of LinkText
        MarkDownParsedResult m_linkTextParsedResult;
    };

    class ListParser : public MarkDownBlockParser
    {
        public:
        void Match(std::stringstream &);

        private:
        void CaptureListToken();
    };
}
