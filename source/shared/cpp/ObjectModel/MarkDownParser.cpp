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
    // begin parsing html blocks
    ParseBlock();

    // process further what is parsed before outputting 
    // html string
    m_parsedResult.Translate();

    //add block tags such as <p> <ul>
    m_parsedResult.AddBlockTags();

    return m_parsedResult.GenerateHtmlString();
}

// MarkDown is consisted of Blocks, this methods parses blocks
void MarkDownParser::ParseBlock() 
{
    std::stringstream stream(m_text);
    EmphasisParser parser;
    while (!stream.eof())
    {
        parser.ParseBlock(stream);
    }
    m_parsedResult.AppendParseResult(parser.GetParsedResult());
}
