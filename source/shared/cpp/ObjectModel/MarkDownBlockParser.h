// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "MarkDownHtmlGenerator.h"
#include <iomanip>
#include "BaseCardElement.h"
#include "MarkDownParsedResult.h"

namespace AdaptiveSharedNamespace
{
    class MarkDownBlockParser
    {
    public:
        MarkDownBlockParser(){};
        // Matches each MarkDown's Syntax Form
        // For each match, stream moves to the next char
        virtual void Match(std::stringstream&) = 0;
        // Parses Block
        void ParseBlock(std::stringstream&);
        // Returns Parse result
        MarkDownParsedResult& GetParsedResult() { return m_parsedResult; }

    protected:
        // Holds parsed results
        MarkDownParsedResult m_parsedResult;
    };

    class EmphasisParser : public MarkDownBlockParser
    {
    public:
        EmphasisParser() = default;
        EmphasisParser(const EmphasisParser&) = default;
        EmphasisParser(EmphasisParser&&) = default;
        EmphasisParser& operator=(const EmphasisParser&) = default;
        EmphasisParser& operator=(EmphasisParser&&) = default;
        virtual ~EmphasisParser() = default;

        enum EmphasisState
        {
            // Text is being handled
            Text = 0x0,
            // Emphasis is being handled
            Emphasis = 0x1,
            // Empahais Parsing is done
            Captured = 0x2,
        };

        void Match(std::stringstream&) override;
        // Captures remaining charaters in given token
        // and causes the emphasis parsing to terminate
        void Flush(int ch, std::string& currentToken);
        // check if given character is * or _
        bool IsMarkDownDelimiter(int ch);
        void CaptureCurrentCollectedStringAsRegularToken(std::string& currentToken);
        void CaptureCurrentCollectedStringAsRegularToken();
        void UpdateCurrentEmphasisRunState(DelimiterType emphasisType);
        // Check if current delimiter will be considererd as a delimiter run
        bool IsEmphasisDelimiterRun(DelimiterType emphasisType) { return m_currentDelimiterType == emphasisType; }
        void ResetCurrentEmphasisState() { m_delimiterCnts = 0; }
        bool IsRightEmphasisDelimiter(int ch);
        // Attempt to capture current emphasis as right emphasis
        bool TryCapturingRightEmphasisToken(int ch, std::string& currentToken);
        bool IsLeftEmphasisDelimiter(int ch)
        {
            return (m_delimiterCnts && ch != EOF && !isspace(ch) && !(m_lookBehind == Alphanumeric && ispunct(ch)) &&
                    !(m_lookBehind == Alphanumeric && m_currentDelimiterType == Underscore));
        };
        // Attempt to capture current emphasis as right emphasis
        bool TryCapturingLeftEmphasisToken(int ch, std::string& currentToken);
        void CaptureEmphasisToken(int ch, std::string& currentToken);
        void UpdateLookBehind(int ch);
        static constexpr DelimiterType GetDelimiterTypeForCharAtCurrentPosition(int ch)
        {
            return (ch == '*') ? Asterisk : Underscore;
        };

        typedef EmphasisState (*MatchWithChar)(EmphasisParser&, std::stringstream&, std::string&);
        // Callback function that handles the Text State
        static EmphasisState MatchText(EmphasisParser&, std::stringstream&, std::string&);
        // Callback function that handles the Emphasis State
        static EmphasisState MatchEmphasis(EmphasisParser&, std::stringstream&, std::string&);

    protected:
        bool m_checkLookAhead = false;
        bool m_checkIntraWord = false;
        int m_lookBehind = Init;
        int m_delimiterCnts = 0;
        DelimiterType m_currentDelimiterType = Init;
        unsigned int m_current_state = 0;

        // vector of callback functions that handles state transistions
        std::vector<MatchWithChar> m_stateMachine = {
            MatchText,
            MatchEmphasis,
        };

        // holds currently collected token
        std::string m_current_token;
    };

    class LinkParser : public MarkDownBlockParser
    {
    public:
        LinkParser() = default;
        LinkParser(const LinkParser&) = default;
        LinkParser(LinkParser&&) = default;
        LinkParser& operator=(const LinkParser&) = default;
        LinkParser& operator=(LinkParser&&) = default;
        virtual ~LinkParser() = default;

        void Match(std::stringstream&) override;

    private:
        void CaptureLinkToken();

        // Matches Initial sytax of link
        bool MatchAtLinkInit(std::stringstream&);
        // Matches LinkText Run sytax of link
        bool MatchAtLinkTextRun(std::stringstream&);
        // Matches LinkText End sytax of link
        bool MatchAtLinkTextEnd(std::stringstream&);
        // Matches LinkDestination Start sytax of link
        bool MatchAtLinkDestinationStart(std::stringstream&);
        // Matches LinkDestination Run sytax of link
        bool MatchAtLinkDestinationRun(std::stringstream&);

        // holds intermidiate result of LinkText
        MarkDownParsedResult m_linkTextParsedResult;
    };

    class ListParser : public MarkDownBlockParser
    {
    public:
        ListParser() = default;
        ListParser(const ListParser&) = default;
        ListParser(ListParser&&) = default;
        ListParser& operator=(const ListParser&) = default;
        ListParser& operator=(ListParser&&) = default;
        virtual ~ListParser() = default;

        void Match(std::stringstream&) override;
        bool MatchNewListItem(std::stringstream&);
        bool MatchNewBlock(std::stringstream&);
        bool MatchNewOrderedListItem(std::stringstream&, std::string&);
        static constexpr bool IsHyphen(int ch) { return ch == '-'; };
        static constexpr bool IsDot(int ch) { return ch == '.'; };
        static constexpr bool IsNewLine(int ch) { return (ch == '\r') || (ch == '\n'); };

    protected:
        void ParseSubBlocks(std::stringstream&);
        bool CompleteListParsing(std::stringstream& stream);

    private:
        void CaptureListToken();
    };

    class OrderedListParser : public ListParser
    {
    public:
        OrderedListParser() = default;
        OrderedListParser(const OrderedListParser&) = default;
        OrderedListParser(OrderedListParser&&) = default;
        OrderedListParser& operator=(const OrderedListParser&) = default;
        OrderedListParser& operator=(OrderedListParser&&) = default;
        ~OrderedListParser() = default;

        void Match(std::stringstream&) override;

    private:
        void CaptureOrderedListToken(std::string&);
    };
}
