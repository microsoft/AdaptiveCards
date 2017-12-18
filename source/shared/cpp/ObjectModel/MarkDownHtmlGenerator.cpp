#include "MarkDownHtmlGenerator.h"

using namespace AdaptiveCards;

std::string MarkDownStringHtmlGenerator::GenerateHtmlString()
{
    return m_token;
}

//     left and right emphasis tokens are match if
//     1. they are same types
//     2. neither of the emphasis tokens are both left and right emphasis tokens, and 
//        if either or both of them are, then their sum is not multipe of 3 
bool MarkDownEmphasisHtmlGenerator::IsMatch(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token)
{
    std::shared_ptr<MarkDownEmphasisHtmlGenerator> emphasisToken = 
        std::static_pointer_cast<MarkDownEmphasisHtmlGenerator>(token);
    if(emphasisToken)
    {
        if (this->type == emphasisToken->type)
        {
            // rule #9 & #10, sum of delim cnts can't be multipe of 3 
            return !((this->IsLeftAndRightEmphasis() || emphasisToken->IsLeftAndRightEmphasis()) &&
                (((this->m_numberOfUnusedDelimiters+ emphasisToken->m_numberOfUnusedDelimiters) % 3) == 0));
        }
    }
    return false;
}

bool MarkDownEmphasisHtmlGenerator::IsSameType(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token)
{
    return this->type == token->type;
}

// adjust number of emphasis counts after maching is done
int MarkDownEmphasisHtmlGenerator::AdjustEmphasisCounts(int leftOver, std::shared_ptr<MarkDownEmphasisHtmlGenerator> rightToken)
{
    int delimCnts = 0;
    if (leftOver >= 0)
    {
        delimCnts = this->m_numberOfUnusedDelimiters - leftOver;
        this->m_numberOfUnusedDelimiters = leftOver;
        rightToken->m_numberOfUnusedDelimiters = 0;
    }
    else
    {
        delimCnts = this->m_numberOfUnusedDelimiters;
        rightToken->m_numberOfUnusedDelimiters = leftOver * (-1);
        this->m_numberOfUnusedDelimiters = 0;
    }
    return delimCnts;
}

void MarkDownEmphasisHtmlGenerator::GenerateTags(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token)
{
    int delimCnts = 0, leftOver = 0;
    leftOver = this->m_numberOfUnusedDelimiters - token->m_numberOfUnusedDelimiters;
    delimCnts = this->AdjustEmphasisCounts(leftOver, token);

    // emphasis found
    if (delimCnts % 2)
    {
        this->PushItalicTag();
        token->PushItalicTag();
    }

    // strong emphasis found
    for (int i = 0; i < delimCnts / 2; i++)
    {
        this->PushBoldTag();
        token->PushBoldTag();
    }
}

void MarkDownEmphasisHtmlGenerator::PushItalicTag() 
{
    m_tags.push_back("<em>");
}

void MarkDownEmphasisHtmlGenerator::PushBoldTag() 
{
    m_tags.push_back("<strong>");
}

std::string MarkDownLeftEmphasisHtmlGenerator::GenerateHtmlString() 
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

std::string MarkDownRightEmphasisHtmlGenerator::GenerateHtmlString() 
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

void MarkDownLeftAndRightEmphasisHtmlGenerator::PushItalicTag() 
{
    if (m_directionType == Left)
    {
        m_tags.push_back("<em>");
    }
    else
    {
        m_tags.push_back("</em>");
    }
}

void MarkDownLeftAndRightEmphasisHtmlGenerator::PushBoldTag() 
{
    if (m_directionType == Left)
    {
        m_tags.push_back("<strong>");
    }
    else
    {
        m_tags.push_back("</strong>");
    }
}
