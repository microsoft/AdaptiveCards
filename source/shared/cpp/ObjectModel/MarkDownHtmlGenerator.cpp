#include "MarkDownHtmlGenerator.h"

using namespace AdaptiveCards;

std::string MarkDownStringHtmlGenerator::generateHtmlString()
{
    return m_token;
}

//     left and right emphasis tokens are match if
//     1. they are same types
//     2. neither of the emphasis tokens are both left and right emphasis tokens, and 
//        if either or both of them are, then their sum is not multipe of 3 
bool MarkDownEmphasisHtmlGenerator::IsMatch(std::shared_ptr<MarkDownHtmlGenerator> &token)
{
    std::shared_ptr<MarkDownEmphasisHtmlGenerator> emphasisToken = 
        std::dynamic_pointer_cast<MarkDownEmphasisHtmlGenerator>(token);
    if(emphasisToken)
    {
        if (this->type == emphasisToken->type)
        {
            // rule #9 & #10, sum of delim cnts can't be multipe of 3 
            return !((this->isLeftAndRightEmphasis || emphasisToken->isLeftAndRightEmphasis) &&
                (((this->m_numberOfUnusedDelimiters+ emphasisToken->m_numberOfUnusedDelimiters) % 3) == 0));
        }
    }

    return false;
}

void MarkDownEmphasisHtmlGenerator::PushItalicTag() 
{
    m_tags.push_back("<em>");
}

void MarkDownEmphasisHtmlGenerator::PushBoldTag() 
{
    m_tags.push_back("<strong>");
}

std::string MarkDownLeftEmphasisHtmlGenerator::generateHtmlString() 
{
    if (m_numberOfUnusedDelimiters)
    {
        int startIdx = m_token.size() - m_numberOfUnusedDelimiters;
        html << m_token.substr(startIdx, std::string::npos);
    }

    // append tags; since left delims, append it in the reverse order
    for (auto itr = m_tags.rbegin(); itr != m_tags.rend(); itr++)
    { 
        html << *itr;
    }
    return html.str();
}

void MarkDownRightEmphasisHtmlGenerator::PushItalicTag() 
{
    m_tags.push_back("</em>");
}

void MarkDownRightEmphasisHtmlGenerator::PushBoldTag() 
{
    m_tags.push_back("</strong>");
}

std::string MarkDownRightEmphasisHtmlGenerator::generateHtmlString() 
{
    // append tags; 
    for (auto itr = m_tags.begin(); itr != m_tags.end(); itr++)
    { 
        html << *itr;
    }

    // if there are unused emphasis, append them 
    if (m_numberOfUnusedDelimiters)
    {
        int startIdx = m_token.size() - m_numberOfUnusedDelimiters;
        html << m_token.substr(startIdx, std::string::npos);
    }

    return html.str();
}
