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
        static constexpr bool IsSpace(const int ch)
        {
            return (ch > 0) && isspace(ch);
        }

        static constexpr bool IsPunct(const int ch)
        {
            return (ch > 0) && ispunct(ch);
        }

        static constexpr bool IsAlnum(const int ch)
        {
            return (ch < 0 || isalnum(ch));
        }

        static constexpr bool IsCntrl(const int ch)
        {
            return (ch > 0) && iscntrl(ch);
        }

        static constexpr bool IsDigit(const int ch)
        {
            return (ch > 0) && isdigit(ch);
        }

        void ParseTextAndEmphasis(std::stringstream& stream);

        // Holds parsed results
        MarkDownParsedResult m_parsedResult;
    };

    class EmphasisParser : public MarkDownBlockParser
    {
    public:
        EmphasisParser() = default;
        EmphasisParser(const EmphasisParser&) = delete;
        EmphasisParser(EmphasisParser&&) = delete;
        EmphasisParser& operator=(const EmphasisParser&) = delete;
        EmphasisParser& operator=(EmphasisParser&&) = delete;
        virtual ~EmphasisParser() = default;

        enum class EmphasisState
        {
            Text,     // Text is being handled
            Emphasis, // Emphasis is being handled
            Captured  // Emphasis parsing is complete
        };

        void Match(std::stringstream&) override;

        // Captures remaining charaters in given token and causes the emphasis parsing to terminate
        void Flush(const int ch, std::string& currentToken);

        // check if given character is * or _
        bool IsMarkDownDelimiter(const int ch) const;

        void CaptureCurrentCollectedStringAsRegularToken(std::string& currentToken);
        void CaptureCurrentCollectedStringAsRegularToken();
        void UpdateCurrentEmphasisRunState(DelimiterType emphasisType);
        // Check if current delimiter will be considererd as a delimiter run
        bool IsEmphasisDelimiterRun(const DelimiterType emphasisType) const
        {
            return m_currentDelimiterType == emphasisType;
        }
        void ResetCurrentEmphasisState() { m_delimiterCnts = 0; }
        bool IsLeftEmphasisDelimiter(const int ch) const;
        bool IsRightEmphasisDelimiter(const int ch) const;
        // Attempt to capture current emphasis as left emphasis
        bool TryCapturingLeftEmphasisToken(const int ch, std::string& currentToken);
        // Attempt to capture current emphasis as right emphasis
        bool TryCapturingRightEmphasisToken(const int ch, std::string& currentToken);
        void CaptureEmphasisToken(const int ch, std::string& currentToken);
        void UpdateLookBehind(const int ch);
        static constexpr DelimiterType GetDelimiterTypeForChar(const int ch)
        {
            return (ch == '*') ? DelimiterType::Asterisk : DelimiterType::Underscore;
        };

        typedef EmphasisState (*MatchWithChar)(EmphasisParser&, std::stringstream&, std::string&);

        // Callback function that handles the Text State
        static EmphasisState MatchText(EmphasisParser&, std::stringstream&, std::string&);

        // Callback function that handles the Emphasis State
        static EmphasisState MatchEmphasis(EmphasisParser&, std::stringstream&, std::string&);

    protected:
        bool m_checkLookAhead = false;
        bool m_checkIntraWord = false;
        DelimiterType m_lookBehind = DelimiterType::Init;
        int m_delimiterCnts = 0;
        DelimiterType m_currentDelimiterType = DelimiterType::Init;
        EmphasisState m_current_state = EmphasisState::Text;

        // vector of callback functions that handles state transistions
        const std::unordered_map<EmphasisState, MatchWithChar> m_stateMachine = {{EmphasisState::Text, MatchText},
                                                                                 {EmphasisState::Emphasis, MatchEmphasis}};

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

        // Matches Initial syntax of link
        bool MatchAtLinkInit(std::stringstream&);
        // Matches LinkText Run syntax of link
        bool MatchAtLinkTextRun(std::stringstream&);
        // Matches LinkText End syntax of link
        bool MatchAtLinkTextEnd(std::stringstream&);
        // Matches LinkDestination Start syntax of link
        bool MatchAtLinkDestinationStart(std::stringstream&);
        // Matches LinkDestination Run syntax of link
        bool MatchAtLinkDestinationRun(std::stringstream&);

        // holds intermediate result of LinkText
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
        static constexpr bool IsHyphen(const int ch) { return ch == '-'; };
        static constexpr bool IsPlus(const int ch) { return ch == '+'; };
        static constexpr bool IsAsterisk(const int ch) { return ch == '*'; };
        static constexpr bool IsDot(const int ch) { return ch == '.'; };
        static constexpr bool IsNewLine(const int ch) { return (ch == '\r') || (ch == '\n'); };

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
