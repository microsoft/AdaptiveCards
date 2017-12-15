#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

MarkDownParser::MarkDownParser(const std::string &txt) : m_text(txt), m_curPos(m_text.begin())
{
}

// Following the rules speicified in CommonMark (http://spec.commonmark.org/0.27/)
// It generally supports more stricker version of the rules
// push left delims to stack, until matching right delim is found,
// update emphasis counts and type to build string after search is complete
std::string MarkDownParser::TransformToHtml()
{
    //Tokenize();

    ParseBlock();

    return GenerateHtmlString();
}

std::string MarkDownParser::GenerateHtmlString() 
{ 
    // process tags 
    std::ostringstream html; 
    for (auto itr = m_tokenizedString.begin(); itr != m_tokenizedString.end(); itr++) 
    { 
        html << (*itr)->GenerateHtmlString();
    }

    return "<p>" + html.str() + "</p>";
}

void MarkDownParser::GetCh(char ch)
{
    // store chars unless it's escape
    if (ch != '\\')
    {
        m_currentToken += ch;
    }
}

// detects valid emphasis delimiters, when valid delimiters are found, they are added into
// a new space. each new delimiters that are part of the run is appended, in that way,
// it builds tokens of vectors
// each time emphasis tokens are found, they are also added into a lookup table.
// the look up table stores index of the corresponding token in the token vectors, and
// emphasis count and its types that are used in html generation 
// add comments -> what it does: generating  n supported features + 1 tokens --> capture them in token class
void MarkDownParser::Tokenize() // rename it to tokenize() // state machines
{
    EmphasisParser EmphasisParser;
    MarkDownLinkTokenizer linkTokenizer;
    bool IsLinkTokenizingDone = true;
    while (m_curPos < m_text.end())
    {
        GetCh(*m_curPos);
        if (*m_curPos == '[' || !IsLinkTokenizingDone)
        {
            // first detection of link, capture what has been processed
            if (*m_curPos == '[' && IsLinkTokenizingDone)
            { 
                m_currentToken.pop_back();
                EmphasisParser.Flush(m_currentToken);
                EmphasisParser.AppendCodeGenTokens(m_tokenizedString);
                EmphasisParser.UpdateLookBehind('a');
            }

            IsLinkTokenizingDone = linkTokenizer.UpdateState(*m_curPos, m_currentToken);

            if (IsLinkTokenizingDone || (!IsLinkTokenizingDone && m_curPos + 1 == m_text.end()))
            { 
                if (!linkTokenizer.IsItLink())
                {
                    if (!IsLinkTokenizingDone && m_curPos + 1 == m_text.end())
                    { 
                        linkTokenizer.Flush(m_currentToken);
                    }
                    linkTokenizer.AppendEmphasisTokens(EmphasisParser);
                }
                linkTokenizer.AppendCodeGenTokens(m_tokenizedString);
                if (*m_curPos == '[')
                {
                    IsLinkTokenizingDone = false;
                }
            }
        }
#if 0
        else
        {
            EmphasisParser.UpdateState(*m_curPos, m_currentToken);
        }
#endif
        ++m_curPos; 
    }
    EmphasisParser.Flush(m_currentToken);
    EmphasisParser.MatchLeftAndRightEmphasises();
    EmphasisParser.AppendCodeGenTokens(m_tokenizedString);
}

void MarkDownParser::ParseBlock() // rename it to tokenize() // state machines
{
    std::stringstream stream(m_text);
    EmphasisParser parser;
    parser.Block(stream);
    parser.AppendEmphasisTokens(m_emphasisLookUpTable);
    parser.MatchLeftAndRightEmphasises();
    parser.AppendCodeGenTokens(m_tokenizedString);
}

