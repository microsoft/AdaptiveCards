// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include <iostream>
#include "MarkDownBlockParser.h"

using namespace AdaptiveSharedNamespace;

// Parses according to each key words
void MarkDownBlockParser::ParseBlock(std::stringstream& stream)
{
    switch (stream.peek())
    {
        // parses link
    case '[':
    {
        LinkParser linkParser;
        // do syntax check of link
        linkParser.Match(stream);
        // append link result to the rest
        m_parsedResult.AppendParseResult(linkParser.GetParsedResult());
        break;
    }
    // handles special cases where these tokens are not encountered
    // as not part of link
    case ']':
    case ')':
    {
        // add these char as token to code gen list
        char streamChar;
        stream.get(streamChar);
        m_parsedResult.AddNewTokenToParsedResult(streamChar);
        break;
    }
    case '\n':
    case '\r':
    {
        // add new line char as token to code gen list
        char streamChar;
        stream.get(streamChar);
        m_parsedResult.AddNewLineTokenToParsedResult(streamChar);
        break;
    }
    // handles list block
    case '-':
    {
        ListParser listParser;
        // do syntax check of list
        listParser.Match(stream);
        // append list result to the rest
        m_parsedResult.AppendParseResult(listParser.GetParsedResult());
        break;
    }
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        OrderedListParser orderedListParser;
        // do syntax check of list
        orderedListParser.Match(stream);
        // append list result to the rest
        m_parsedResult.AppendParseResult(orderedListParser.GetParsedResult());
        break;
    }
    // everything else is treated as normal text + emphasis
    default:
        EmphasisParser emphasisParser;
        // do syntax check of normal text + emphasis
        emphasisParser.Match(stream);
        // append result to the rest
        m_parsedResult.AppendParseResult(emphasisParser.GetParsedResult());
    }
}

// Emphasis Match's syntax is complete when it's Captured
// Its syntax is always correct, therefore it attemps to
// capture until it can't capture anymore.
// it moves two states, emphasis state and text state,
// at each transition of state, one token is captured
void EmphasisParser::Match(std::stringstream& stream)
{
    while (m_current_state != EmphasisState::Captured)
    {
        m_current_state = m_stateMachine.at(m_current_state)(*this, stream, m_current_token);
    }
}

/// captures text until it see emphasis character. When it does, switch to Emphasis state
EmphasisParser::EmphasisState EmphasisParser::MatchText(EmphasisParser& parser, std::stringstream& stream, std::string& token)
{
    /// MarkDown keywords
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.peek() == '\n' ||
        stream.peek() == '\r' || stream.eof())
    {
        parser.Flush(stream.peek(), token);
        return EmphasisState::Captured;
    }

    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        // encounterred first emphasis delimiter
        parser.CaptureCurrentCollectedStringAsRegularToken();
        const DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition(stream.peek());
        // get previous character and update the look behind if it was captured before
        if (stream.tellg())
        {
            stream.unget();
            parser.UpdateLookBehind(stream.get());
        }

        parser.UpdateCurrentEmphasisRunState(emphasisType);
        char streamChar;
        stream.get(streamChar);
        token += streamChar;
        return EmphasisState::Emphasis;
    }
    else
    {
        parser.UpdateLookBehind(stream.peek());
        char streamChar;
        stream.get(streamChar);
        token += streamChar;
        return EmphasisState::Text;
    }
}

/// captures text untill it see none-emphasis character. When it does, switch to text state
EmphasisParser::EmphasisState EmphasisParser::MatchEmphasis(EmphasisParser& parser, std::stringstream& stream, std::string& token)
{
    // key word is encountered, flush what is being processed, and have those keyword
    // handled by ParseBlock()
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.peek() == '\n' ||
        stream.peek() == '\r' || stream.eof())
    {
        parser.Flush(stream.peek(), token);
        return EmphasisState::Captured;
    }

    /// if another emphasis delimiter is encounterred, it is delimiter run
    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        const DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition((stream.peek()));
        if (parser.IsEmphasisDelimiterRun(emphasisType))
        {
            parser.UpdateCurrentEmphasisRunState(emphasisType);
        }

        char streamChar;
        stream.get(streamChar);
        token += streamChar;
    }
    /// delimiter run is ended, capture the current accumulated token as emphasis
    else
    {
        parser.CaptureEmphasisToken(stream.peek(), token);

        if (stream.peek() == '\\')
        {
            // skips escape char
            stream.get();
        }

        parser.ResetCurrentEmphasisState();
        parser.UpdateLookBehind(stream.peek());
        char streamChar;
        stream.get(streamChar);
        token += streamChar;
        return EmphasisState::Text;
    }
    return EmphasisState::Emphasis;
}

// Captures remaining charaters in given token
// and causes the emphasis parsing to terminate
void EmphasisParser::Flush(int ch, std::string& currentToken)
{
    if (m_current_state == EmphasisState::Emphasis)
    {
        CaptureEmphasisToken(ch, currentToken);
        m_delimiterCnts = 0;
    }
    else
    {
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
    currentToken.clear();
}

bool EmphasisParser::IsMarkDownDelimiter(int ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

void EmphasisParser::CaptureCurrentCollectedStringAsRegularToken(std::string& currentToken)
{
    if (currentToken.empty())
        return;
    std::shared_ptr<MarkDownHtmlGenerator> codeGen = std::make_shared<MarkDownStringHtmlGenerator>(currentToken);

    m_parsedResult.AppendToTokens(codeGen);

    currentToken.clear();
}

void EmphasisParser::CaptureCurrentCollectedStringAsRegularToken()
{
    CaptureCurrentCollectedStringAsRegularToken(m_current_token);
}

void EmphasisParser::UpdateCurrentEmphasisRunState(DelimiterType emphasisType)
{
    if (m_lookBehind != WhiteSpace)
    {
        m_checkLookAhead = (m_lookBehind == Puntuation);
        m_checkIntraWord = (m_lookBehind == Alphanumeric && emphasisType == Underscore);
    }
    ++m_delimiterCnts;
    m_currentDelimiterType = emphasisType;
}

bool EmphasisParser::IsRightEmphasisDelimiter(int ch)
{
    if ((std::isspace(ch) || (ch == EOF)) && (m_lookBehind != WhiteSpace) &&
        (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {
        return true;
    }

    if (isalnum(ch) && m_lookBehind != WhiteSpace && m_lookBehind != Init)
    {
        if (!m_checkLookAhead && !m_checkIntraWord)
        {
            return true;
        }

        if (m_checkLookAhead || m_checkIntraWord)
        {
            return false;
        }
    }

    if (ispunct(ch) && m_lookBehind != WhiteSpace)
    {
        return true;
    }

    return false;
    ;
}

bool EmphasisParser::TryCapturingRightEmphasisToken(int ch, std::string& currentToken)
{
    if (IsRightEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownEmphasisHtmlGenerator> codeGen = nullptr;
        // right emphasis can be also left emphasis
        if (IsLeftEmphasisDelimiter(ch))
        {
            // since it is both left and right emphasis, create one accordingly
            codeGen = std::make_shared<MarkDownLeftAndRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, m_currentDelimiterType);
        }
        else
        {
            codeGen = std::make_shared<MarkDownRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, m_currentDelimiterType);
        }

        m_parsedResult.AppendToLookUpTable(codeGen);

        m_parsedResult.AppendToTokens(codeGen);

        currentToken.clear();

        return true;
    }
    return false;
}

bool EmphasisParser::TryCapturingLeftEmphasisToken(int ch, std::string& currentToken)
{
    // left emphasis detected, save emphasis for later reference
    if (IsLeftEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownEmphasisHtmlGenerator> codeGen =
            std::make_shared<MarkDownLeftEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, m_currentDelimiterType);

        m_parsedResult.AppendToLookUpTable(codeGen);

        m_parsedResult.AppendToTokens(codeGen);

        currentToken.clear();
        return true;
    }
    return false;
}

void EmphasisParser::UpdateLookBehind(int ch)
{
    // store ch and move itr
    if (isspace(ch))
    {
        m_lookBehind = WhiteSpace;
    }

    if (isalnum(ch))
    {
        m_lookBehind = Alphanumeric;
    }

    if (ispunct(ch))
    {
        m_lookBehind = (ch == '\\') ? Escape : Puntuation;
    }
}

void EmphasisParser::CaptureEmphasisToken(int ch, std::string& currentToken)
{
    if (!TryCapturingRightEmphasisToken(ch, currentToken) && !TryCapturingLeftEmphasisToken(ch, currentToken) &&
        !currentToken.empty())
    {
        // no valid emphasis delimiter runs found during current emphasis delimiter run
        // treat them as regular string tokens
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
}

void LinkParser::Match(std::stringstream& stream)
{
    // link syntax check, match keyword at each stage
    if (MatchAtLinkInit(stream) && MatchAtLinkTextRun(stream) && MatchAtLinkTextEnd(stream) &&
        MatchAtLinkDestinationStart(stream) && MatchAtLinkDestinationRun(stream))
    {
        /// Link is in correct syntax, capture it as link
        CaptureLinkToken();
    }
}

// link is in form of [txt](url), this method matches '['
bool LinkParser::MatchAtLinkInit(std::stringstream& lookahead)
{
    if (lookahead.peek() == '[')
    {
        char streamChar;
        lookahead.get(streamChar);
        m_linkTextParsedResult.AddNewTokenToParsedResult(streamChar);
        return true;
    }

    // this won't ever happend if this method is used intentionally,
    // this is added as safeguard, however.
    return false;
}

// link is in form of [txt](url), this method matches txt
bool LinkParser::MatchAtLinkTextRun(std::stringstream& lookahead)
{
    if (lookahead.peek() == ']')
    {
        char streamChar;
        lookahead.get(streamChar);
        m_linkTextParsedResult.AddNewTokenToParsedResult(streamChar);
        return true;
    }
    else
    {
        // parses recursively to the right
        while (lookahead.peek() != EOF && lookahead.peek() != ']')
        {
            MarkDownBlockParser::ParseBlock(lookahead);
            m_linkTextParsedResult.AppendParseResult(GetParsedResult());

            if (m_linkTextParsedResult.GetIsCaptured())
            {
                break;
            }
        }

        if (lookahead.peek() == ']')
        {
            // move code gen objects to link text list to further process it
            char streamChar;
            lookahead.get(streamChar);
            m_linkTextParsedResult.AddNewTokenToParsedResult(streamChar);
            return true;
        } 

        m_parsedResult.AppendParseResult(m_linkTextParsedResult);
        return false;
    }
}

// link is in form of [txt](url), this method matches ']'
bool LinkParser::MatchAtLinkTextEnd(std::stringstream& lookahead)
{
    if (lookahead.peek() == '(')
    {
        char streamChar;
        lookahead.get(streamChar);
        m_linkTextParsedResult.AddNewTokenToParsedResult(streamChar);
        return true;
    }

    m_parsedResult.AppendParseResult(m_linkTextParsedResult);
    return false;
}

// link is in form of [txt](url), this method matches '('
bool LinkParser::MatchAtLinkDestinationStart(std::stringstream& lookahead)
{
    // control key is detected, syntax check failed
    if (iscntrl(lookahead.peek()))
    {
        m_parsedResult.AppendParseResult(m_linkTextParsedResult);
        return false;
    }

    if (lookahead.peek() == ')')
    {
        lookahead.get();
        return true;
    }

    // parses destination
    ParseBlock(lookahead);

    if (lookahead.peek() == ')')
    {
        return true;
    }

    m_parsedResult.AppendParseResult(m_linkTextParsedResult);
    return false;
}

// link is in form of [txt](url), this method matches ')'
bool LinkParser::MatchAtLinkDestinationRun(std::stringstream& lookahead)
{
    if (isspace(lookahead.peek()) || iscntrl(lookahead.peek()))
    {
        m_parsedResult.AppendParseResult(m_linkTextParsedResult);
        return false;
    }

    if (lookahead.peek() == ')')
    {
        lookahead.get();
        return true;
    }

    // parses destination
    ParseBlock(lookahead);
    return true;
}

// this method is called when link syntax check is complete
// it processes the parsed result from link destination  and link text
// and build a MarkDownStringHtmlGenerator that will output
// string in link syntax (text)[destination) will converts to
// <a href=\destination\>text</a>
void LinkParser::CaptureLinkToken()
{
    std::ostringstream html;
    html << "<a href=\"";
    // process link destination
    html << m_parsedResult.GenerateHtmlString();
    html << "\">";

    // when syntax check is complete, we have seen
    // '[', ']', '(', these keywords are not
    // needed anymore, so pop them from the parse result
    // if syntax check failed for link, then they must be
    // retained as part of parse result
    m_linkTextParsedResult.PopFront();
    m_linkTextParsedResult.PopBack();
    m_linkTextParsedResult.PopBack();

    // translate what is captured in text of link
    // emphasis are processed here
    m_linkTextParsedResult.Translate();
    html << m_linkTextParsedResult.GenerateHtmlString();
    html << "</a>";

    std::string html_string = html.str();

    // Generate a MarkDownStringHtmlGenerator object
    std::shared_ptr<MarkDownHtmlGenerator> codeGen = std::make_shared<MarkDownStringHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    m_parsedResult.FoundHtmlTags();
    m_parsedResult.AppendToTokens(codeGen);
    m_parsedResult.SetIsCaptured(true);
}

// list marker have form of ^-\s+ or \r-\s+
// this method matches -\s
bool ListParser::MatchNewListItem(std::stringstream& stream)
{
    if (IsHyphen(stream.peek()))
    {
        stream.get();
        if (stream.peek() == ' ')
        {
            stream.unget();
            return true;
        }
        stream.unget();
    }
    return false;
}

// if lines are seperated by more than two new lines,
// they are new block items
// caller of this method is expected to have matched new line char
// before calling this method
// this method will return true, after it mataches new line char
// at least once.
bool ListParser::MatchNewBlock(std::stringstream& stream)
{
    if (IsNewLine(stream.peek()))
    {
        do
        {
            stream.get();
        } while (IsNewLine(stream.peek()));

        return true;
    }

    return false;
}

// ordered list marker has form of ^\d+\.\s* or [\r,\n]\d+\.\s*, and this method checks the syntax
// this method matches \d+\.
bool ListParser::MatchNewOrderedListItem(std::stringstream& stream, std::string& number_string)
{
    do
    {
        char streamChar;
        stream.get(streamChar);
        number_string += streamChar;
    } while (isdigit(stream.peek()));

    if (stream.peek() == '.')
    {
        // ordered list syntax check complete
        stream.unget();
        return true;
    }

    return false;
}

// parse blocks that wasn't captured
// if what we encounter is one of following items, start of new list, list item, or new block element,
// we do not include in the current block, we return, and have it handled by the caller
void ListParser::ParseSubBlocks(std::stringstream& stream)
{
    while (!stream.eof())
    {
        if (IsNewLine(stream.peek()))
        {
            char newLineChar;
            stream.get(newLineChar);
            // check if it is the start of new block items
            if (isdigit(stream.peek()))
            {
                std::string number_string = "";
                if (MatchNewOrderedListItem(stream, number_string))
                {
                    break;
                }
                else
                {
                    m_parsedResult.AddNewTokenToParsedResult(number_string);
                }
            }
            else if (MatchNewListItem(stream) || MatchNewBlock(stream))
            {
                break;
            }

            m_parsedResult.AddNewTokenToParsedResult(newLineChar);
        }
        ParseBlock(stream);
    }
}

bool ListParser::CompleteListParsing(std::stringstream& stream)
{
    // check for - of -\s+ list marker
    if (stream.peek() == ' ')
    {
        // at this point, syntax check is complete,
        // thus any other spaces are ignored
        // remove space
        do
        {
            stream.get();
        } while (stream.peek() == ' ');

        ParseBlock(stream);
        // parse blocks that follows
        ParseSubBlocks(stream);

        return true;
    }
    return false;
}

// list marker has a form of ^-\s+ or [\r, \n]-\s+, and this method checks the syntax
void ListParser::Match(std::stringstream& stream)
{
    // check for - of -\s+ list marker
    if (IsHyphen(stream.peek()))
    {
        stream.get();
        if (CompleteListParsing(stream))
        {
            CaptureListToken();
        }
        else
        {
            // if incorrect syntax, capture what was thrown as a new token.
            m_parsedResult.AddNewTokenToParsedResult('-');
        }
    }
}

void ListParser::CaptureListToken()
{
    std::ostringstream html;
    m_parsedResult.Translate();
    std::string htmlString = m_parsedResult.GenerateHtmlString();

    html << "<li>";
    html << htmlString;
    html << "</li>";

    std::string html_string = html.str();
    std::shared_ptr<MarkDownListHtmlGenerator> codeGen = std::make_shared<MarkDownListHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    m_parsedResult.FoundHtmlTags();
    m_parsedResult.AppendToTokens(codeGen);
}

// ordered list marker has form of ^\d+\.\s* or [\r,\n]\d+\.\s*, and this method checks the syntax
void OrderedListParser::Match(std::stringstream& stream)
{
    // used to capture digit char
    std::string number_string = "";
    if (isdigit(stream.peek()))
    {
        do
        {
            char streamChar;
            stream.get(streamChar);
            number_string += streamChar;
        } while (isdigit(stream.peek()));

        if (IsDot(stream.peek()))
        {
            // ordered list syntax check complete
            stream.get();
            if (CompleteListParsing(stream))
            {
                CaptureOrderedListToken(number_string);
            }
            else
            {
                number_string += '.';
                m_parsedResult.AddNewTokenToParsedResult(number_string);
            }
        }
        else
        {
            // if incorrect syntax, capture as a new token.
            m_parsedResult.AddNewTokenToParsedResult(number_string);
        }
    }
}

void OrderedListParser::CaptureOrderedListToken(std::string& number_string)
{
    std::ostringstream html;
    m_parsedResult.Translate();
    std::string htmlString = m_parsedResult.GenerateHtmlString();

    html << "<li>";
    html << htmlString;
    html << "</li>";

    std::string html_string = html.str();
    std::shared_ptr<MarkDownOrderedListHtmlGenerator> codeGen =
        std::make_shared<MarkDownOrderedListHtmlGenerator>(html_string, number_string);

    m_parsedResult.Clear();
    m_parsedResult.FoundHtmlTags();
    m_parsedResult.AppendToTokens(codeGen);
}
