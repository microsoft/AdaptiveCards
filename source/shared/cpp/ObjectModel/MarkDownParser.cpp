#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveCards;

MarkDownParser::MarkDownParser(const std::string &txt) : m_text(txt)
{
}

// transforms string to html
std::string MarkDownParser::TransformToHtml()
{
    ParseBlock();

    m_parsedResult.Translate();

    return "<p>" + m_parsedResult.GenerateHtmlString() + "</p>";
}

// MarkDown is consisted of Blocks, this methods parses blocks
void MarkDownParser::ParseBlock() // rename it to tokenize() // state machines
{
    std::stringstream stream(m_text);
    EmphasisParser parser;
    while (!stream.eof())
    {
        parser.ParseBlock(stream);
    }
    m_parsedResult.Append(parser.GetParsedResult());
}

