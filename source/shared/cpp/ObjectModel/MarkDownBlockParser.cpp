#include <iostream>
#include "MarkDownBlockParser.h"

using namespace AdaptiveCards;

void MarkDownBlockParser::ParseBlock(std::stringstream &stream) 
{
    switch(stream.peek())
    {
        case '[':
        {
            LinkParser linkParser;
            linkParser.Match(stream);
            m_parsedResult.Append(linkParser.GetParsedResult());
            break;
        }
        case ']': case ')':
        {
            // add these char as token to code gen list
            m_parsedResult.AddNewTokenToParsedResult(stream.get());
            break;
        }
        case '-':
        {
            ListParser listParser;
            listParser.Match(stream);
            m_parsedResult.Append(listParser.GetParsedResult());
        }
        default:
            EmphasisParser emphasisParser;
            emphasisParser.Match(stream);
            m_parsedResult.Append(emphasisParser.GetParsedResult());
    }
}

// Emphasis Match's syntax is complete when it's Captured
// Its syntax is always correct, therefore it attemps to
// capture until it can't capture no more.
// it moves two states, emphasis state and text state,
// at each transition of state, one token is captured
void EmphasisParser::Match(std::stringstream &stream)
{ 
    while (m_current_state != Captured)
    {
        m_current_state = m_stateMachine[m_current_state](*this, stream, m_current_token);
    }
}
/// captures text untill it see emphasis character. When it does, switch to Emphasis state
unsigned int EmphasisParser::MatchText(EmphasisParser &parser, std::stringstream &stream, std::string& token)
{
    /// MarkDown keywords
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.eof())
    {
        parser.Flush(token);
        return Captured;
    }

    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        // encounterred first emphasis delimiter
        parser.CaptureCurrentCollectedStringAsRegularToken();
        DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition(stream.peek()); 
        parser.UpdateCurrentEmphasisRunState(emphasisType);
        token += stream.get();
        return Emphasis;
    }
    else
    {    
        parser.UpdateLookBehind(stream.peek());
        token += stream.get();
        return Text;
    }
}

/// captures text untill it see none-emphasis character. When it does, switch to text state
unsigned int EmphasisParser::MatchEmphasis(EmphasisParser &parser, std::stringstream &stream, std::string& token)
{
    if (stream.peek() == '[' || stream.peek() == ']' || stream.peek() == ')' || stream.eof())
    {
        parser.Flush(token);
        return Captured;
    }

    if (parser.IsMarkDownDelimiter(stream.peek()))
    {
        DelimiterType emphasisType = EmphasisParser::GetDelimiterTypeForCharAtCurrentPosition(stream.peek());
        if (parser.IsEmphasisDelimiterRun(emphasisType))
        {
            parser.UpdateCurrentEmphasisRunState(emphasisType);
        }
        token += stream.get();
    }
    else
    {
        if (stream.peek() != '\\')
        {
            parser.CaptureEmphasisToken(stream.peek(), token);
        }
        else
        {
            // skips escape char
            parser.CaptureEmphasisToken(stream.peek(), token);
            stream.get();
        }

        parser.ResetCurrentEmphasisState();
        parser.UpdateLookBehind(stream.peek());
        token += stream.get();

        return Text;
    }
    return Emphasis;
}

// Captures remaining charaters in given token
// and causes the emphasis parsing to terminate
void EmphasisParser::Flush(std::string& currentToken)
{
    if (m_current_state != Text)
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

void EmphasisParser::CaptureCurrentCollectedStringAsRegularToken(std::string&currentToken) 
{
    if (currentToken.empty())
        return;
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(currentToken);
    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
    m_parsedResult.Append(token);

    currentToken.clear();
}

void EmphasisParser::CaptureCurrentCollectedStringAsRegularToken() 
{
    if (m_current_token.empty())
        return;
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(m_current_token);

    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
    m_parsedResult.Append(token);

    m_current_token.clear();
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

bool EmphasisParser::TryCapturingRightEmphasisToken(int ch, std::string &currentToken)
{
    if (IsRightEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownRightEmphasisHtmlGenerator> codeGen = nullptr;
        if (IsLeftEmphasisDelimiter(ch))
        {
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

        std::shared_ptr<MarkDownEmphasisHtmlGenerator> emphasisToken = std::static_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen);
        m_parsedResult.Append(emphasisToken);

        std::shared_ptr<MarkDownHtmlGenerator> htmlToken = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
        m_parsedResult.Append(htmlToken);
        // use staic cast
        currentToken.clear();

        return true;
    }
    return false;
}

// save left emphasis to look up table
// return true, if left emphasis was detected and added
bool EmphasisParser::TryCapturingLeftEmphasisToken(int ch, std::string &currentToken)
{
    // left emphasis detected, save emphasis for later reference
    if (IsLeftEmphasisDelimiter(ch))
    {
        std::shared_ptr<MarkDownLeftEmphasisHtmlGenerator> codeGen = 
            std::make_shared<MarkDownLeftEmphasisHtmlGenerator>(currentToken, m_delimiterCnts, 
                    m_currentDelimiterType);

        std::shared_ptr<MarkDownEmphasisHtmlGenerator> emphasisToken = std::static_pointer_cast<MarkDownEmphasisHtmlGenerator>(codeGen);
        m_parsedResult.Append(emphasisToken);

        std::shared_ptr<MarkDownHtmlGenerator> htmlToken = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
        m_parsedResult.Append(htmlToken);

        currentToken.clear();
        return true;
    }
    return false;
}

void EmphasisParser::UpdateLookBehind(int ch)
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

void EmphasisParser::CaptureEmphasisToken(int ch, std::string &currentToken)
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
    if(MatchAtLinkInit(stream) && 
       MatchAtLinkTextRun(stream) && 
       MatchAtLinkTextEnd(stream) && 
       MatchAtLinkDestinationStart(stream) && 
       MatchAtLinkDestinationRun(stream))
    {
        /// Link is in correct syntax, capture it as Link
        CaptureLinkToken();
    }
}

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
            m_parsedResult.Append(m_linkTextParsedResult);
            return false;
        }
        else
        {
            // Block() will process the inline items within Link Text block 
            ParseBlock(lookahead);
            m_linkTextParsedResult.Append(m_parsedResult);

            if(lookahead.peek() == ']')
            {
                // move code gen objects to link text list to further process it 
                m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
                return true;
            }

            m_parsedResult.Append(m_linkTextParsedResult);
            return false;
        }
    }
}

bool LinkParser::MatchAtLinkTextEnd(std::stringstream &lookahead)
{
    if (lookahead.peek() == '(')
    { 
        m_linkTextParsedResult.AddNewTokenToParsedResult(lookahead.get());
        return true;
    } 
    
    m_parsedResult.Append(m_linkTextParsedResult);
    return false;
}

bool LinkParser::MatchAtLinkDestinationStart(std::stringstream &lookahead)
{
    if (iscntrl(lookahead.peek()))
    {
        m_parsedResult.Append(m_linkTextParsedResult);
        return false;
    }

    if(lookahead.peek() == ')')
    { 
        lookahead.get();
        return true;
    }

    ParseBlock(lookahead);

    if(lookahead.peek() == ')')
    {
        return true;
    }

    m_parsedResult.Append(m_linkTextParsedResult);
    return false;
}

bool LinkParser::MatchAtLinkDestinationRun(std::stringstream &lookahead)
{
    if (isspace(lookahead.peek()) || iscntrl(lookahead.peek()))
    { 
        m_parsedResult.Append(m_linkTextParsedResult);
        return false;
    }

    if(lookahead.peek() == ')')
    { 
        lookahead.get();
        return true;
    }

    ParseBlock(lookahead);
    return true;
}

void LinkParser::CaptureLinkToken()
{
    std::ostringstream html; 
    html << "<a href=\"";
    html << m_parsedResult.GenerateHtmlString();
    html << "\">";
    m_linkTextParsedResult.PopFront();
    m_linkTextParsedResult.PopBack();
    m_linkTextParsedResult.PopBack();
    m_linkTextParsedResult.Translate();
    html << m_linkTextParsedResult.GenerateHtmlString();
    html << "</a>";

    std::string html_string = html.str();
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
    m_parsedResult.Append(token);
}

void ListParser::Match(std::stringstream &stream) 
{ 
    if (stream.peek() == '-')
    {
        stream.get();
        if (stream.peek() == ' ')
        {
            while(stream.peek() == ' ')
            {
                stream.get();
            }
            ParseBlock(stream);
            CaptureListToken();
        }
    }
}

void ListParser::CaptureListToken()
{
    std::ostringstream html;
    html << "<ul>\n";
    html << "<li>";
    html << m_parsedResult.GenerateHtmlString();
    html << "</li>\n";
    html << "</ul>";

    std::string html_string = html.str();
    std::shared_ptr<MarkDownStringHtmlGenerator> codeGen = 
        std::make_shared<MarkDownStringHtmlGenerator>(html_string);

    m_parsedResult.Clear();
    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(codeGen);
    m_parsedResult.Append(token);

}
