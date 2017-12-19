#include <iostream>
#include "MarkDownBlockParser.h"

using namespace AdaptiveCards;

// Parses according to each key words
void MarkDownBlockParser::ParseBlock(std::stringstream &stream) 
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
        case ']': case ')':
        {
            // add these char as token to code gen list
            m_parsedResult.AddNewTokenToParsedResult(stream.get());
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
void EmphasisParser::Match(std::stringstream &stream)
{ 
    while (m_current_state != EmphasisState::Captured)
    {
        m_current_state = m_stateMachine[m_current_state](*this, stream, m_current_token);
    }
}

/// captures text untill it see emphasis character. When it does, switch to Emphasis state
EmphasisParser::EmphasisState EmphasisParser::MatchText(EmphasisParser &parser, std::stringstream &stream, std::string& token)
{
    /// MarkDown keywords
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.peek() == '-' || stream.eof())
    {
        parser.Flush(token);

        return EmphasisState::Captured;
    }

    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        // encounterred first emphasis delimiter
        parser.CaptureCurrentCollectedStringAsRegularToken();
        DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition(stream.peek()); 
        parser.UpdateCurrentEmphasisRunState(emphasisType);
        token += stream.get();
        return EmphasisState::Emphasis;
    }
    else
    {    
        parser.UpdateLookBehind(stream.peek());
        token += stream.get();
        return EmphasisState::Text;
    }
}

/// captures text untill it see none-emphasis character. When it does, switch to text state
EmphasisParser::EmphasisState EmphasisParser::MatchEmphasis(EmphasisParser &parser, std::stringstream &stream, std::string& token)
{
    // key word is encountered, flush what is being processed, and have those keyword
    // handled by ParseBlock()
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.peek() == '-' || stream.eof())
    {
        parser.Flush(token);
        return EmphasisState::Captured;
    }

    /// if another emphasis delimiter is encounterred, it is delimiter run
    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition(stream.peek());
        if (parser.IsEmphasisDelimiterRun(emphasisType))
        {
            parser.UpdateCurrentEmphasisRunState(emphasisType);
        }
        token += stream.get();
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
        token += stream.get();

        return EmphasisState::Text;
    }
    return EmphasisState::Emphasis;
}

// Captures remaining charaters in given token
// and causes the emphasis parsing to terminate
void EmphasisParser::Flush(std::string& currentToken)
{
    if (m_current_state != EmphasisState::Text)
    {
        CaptureEmphasisToken(currentToken[0], currentToken);
        m_delimiterCnts = 0;
    }
    else
    {
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
    currentToken.clear();
}

bool EmphasisParser::IsMarkDownDelimiter(char ch)
{
    return ((ch == '*' || ch == '_') && (m_lookBehind != Escape));
}

void EmphasisParser::CaptureCurrentCollectedStringAsRegularToken(std::string& currentToken) 
{
    if (currentToken.empty())
        return;
    std::shared_ptr<MarkDownHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(currentToken);

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

bool EmphasisParser::IsRightEmphasisDelimiter(char ch)
{
    if (isspace(ch) && 
       (m_lookBehind != WhiteSpace) && 
       (m_checkLookAhead || m_checkIntraWord || m_currentDelimiterType == Asterisk))
    {        
        return true;
    }

    if (isalnum(ch) && 
        m_lookBehind != WhiteSpace && 
        m_lookBehind != Init)
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

    return false;;
}

bool EmphasisParser::TryCapturingRightEmphasisToken(char ch, std::string &currentToken)
{
    if (IsRightEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownEmphasisHtmlGenerator> codeGen = nullptr;
        // right emphasis can be also left emphasis
        if (IsLeftEmphasisDelimiter(ch))
        {
            // since it is both left and right emphasis, create one accordingly
            codeGen = 
                std::make_shared<MarkDownLeftAndRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }
        else
        {
            codeGen = 
                std::make_shared<MarkDownRightEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                        m_currentDelimiterType);
        }

        m_parsedResult.AppendToLookUpTable(codeGen);

        m_parsedResult.AppendToTokens(codeGen);

        currentToken.clear();

        return true;
    }
    return false;
}

bool EmphasisParser::TryCapturingLeftEmphasisToken(char ch, std::string &currentToken)
{
    // left emphasis detected, save emphasis for later reference
    if (IsLeftEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownEmphasisHtmlGenerator> codeGen = 
            std::make_shared<MarkDownLeftEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                    m_currentDelimiterType);

        m_parsedResult.AppendToLookUpTable(codeGen);

        m_parsedResult.AppendToTokens(codeGen);

        currentToken.clear();
        return true;
    }
    return false;
}

void EmphasisParser::UpdateLookBehind(char ch)
{
    //store ch and move itr
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
        m_lookBehind = (ch == '\\')? Escape : Puntuation;
    }
}

void EmphasisParser::CaptureEmphasisToken(char ch, std::string &currentToken)
{
    if (!TryCapturingRightEmphasisToken(ch, currentToken) && 
        !TryCapturingLeftEmphasisToken(ch, currentToken) &&
        !currentToken.empty())
    {
        // no valid emphasis delimiter runs found during current emphasis delimiter run
        // treat them as regular string tokens
        CaptureCurrentCollectedStringAsRegularToken(currentToken);
    }
}

void LinkParser::Match(std::stringstream &stream) 
{ 
    // link syntax check, match keyword at each stage
    if (MatchAtLinkInit(stream) && 
       MatchAtLinkTextRun(stream) && 
       MatchAtLinkTextEnd(stream) && 
       MatchAtLinkDestinationStart(stream) && 
       MatchAtLinkDestinationRun(stream))
    {
        /// Link is in correct syntax, capture it as link
        CaptureLinkToken();
    }
}

// link is in form of [txt](url), this method matches '['
bool LinkParser::MatchAtLinkInit(std::stringstream &lookahead)
{
    if (lookahead.peek() == '[')
    {    
        m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
        return true;
    }

    // this won't ever happend if this method is used intentionally,
    // this is added as safeguard, however.
    return false;
}

// link is in form of [txt](url), this method matches txt
bool LinkParser::MatchAtLinkTextRun(std::stringstream &lookahead)
{ 
    if (lookahead.peek() == ']')
    {
        m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
        return true;
    }
    else
    {
        if (lookahead.peek() =='[')
        {
            m_parsedResult.AppendParseResult(m_linkTextParsedResult);
            return false;
        }
        else
        {
            // Block() will process the inline items within Link Text block 
            ParseBlock(lookahead);
            m_linkTextParsedResult.AppendParseResult(m_parsedResult);

            if (lookahead.peek() == ']')
            {
                // move code gen objects to link text list to further process it 
                m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
                return true;
            }

            m_parsedResult.AppendParseResult(m_linkTextParsedResult);
            return false;
        }
    }
}

// link is in form of [txt](url), this method matches ']'
bool LinkParser::MatchAtLinkTextEnd(std::stringstream &lookahead)
{
    if (lookahead.peek() == '(')
    { 
        m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
        return true;
    } 
    
    m_parsedResult.AppendParseResult(m_linkTextParsedResult);
    return false;
}

// link is in form of [txt](url), this method matches '('
bool LinkParser::MatchAtLinkDestinationStart(std::stringstream &lookahead)
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
bool LinkParser::MatchAtLinkDestinationRun(std::stringstream &lookahead)
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
    std::shared_ptr<MarkDownHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    m_parsedResult.AppendToTokens(codeGen);
}

// list has form of -\s+ markdown block and a line break
// this method checks such syntax
void ListParser::Match(std::stringstream &stream) 
{ 
    if (stream.peek() == '-')
    {
        stream.get();
        // check for the mendatory space
        if (stream.peek() == ' ')
        {
            // at this point, syntax check is complete, 
            // thus any other spaces are ignored
            while (stream.peek() == ' ')
            {
                stream.get();
            }
            // parse block that follows
            ParseBlock(stream);
            // capture list token
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
    std::string htmlString = m_parsedResult.GenerateHtmlString();
    // list item has form of <li>block</li>
    // New line character at the end of block is dropped
    if (htmlString.back() == '\r' || htmlString.back() == '\n')
    {
        htmlString.pop_back();
    }

    html << "<li>";
    html << htmlString;
    html << "</li>";

    std::string html_string = html.str();
    std::shared_ptr<MarkDownListHtmlGenerator> codeGen = 
        std::make_shared<MarkDownListHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    m_parsedResult.AppendToTokens(codeGen);
}
