#include "MarkDownParsedResult.h"

using namespace AdaptiveCards;

void MarkDownParsedResult::Translate()
{
    MatchLeftAndRightEmphasises();
}

void MarkDownParsedResult::AddBlockTags()
{
    std::string tags = (m_codeGenTokens.front()->IsList())? "<ul>" : "<p>";
    std::shared_ptr<MarkDownStringHtmlGenerator> htmlToken =
        std::make_shared<MarkDownStringHtmlGenerator>(tags);
    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(htmlToken);
    m_codeGenTokens.push_front(token);

    std::string tags2 = (m_codeGenTokens.back()->IsList())? "\n</ul>" : "</p>";
    std::shared_ptr<MarkDownStringHtmlGenerator> htmlToken2 =
        std::make_shared<MarkDownStringHtmlGenerator>(tags2);
    std::shared_ptr<MarkDownHtmlGenerator> token2 = std::static_pointer_cast<MarkDownHtmlGenerator>(htmlToken2);
    m_codeGenTokens.push_back(token2);
}

void MarkDownParsedResult::Append(MarkDownParsedResult &x)
{
    m_codeGenTokens.splice(m_codeGenTokens.end(), x.m_codeGenTokens);
    m_emphasisLookUpTable.splice(m_emphasisLookUpTable.end(), x.m_emphasisLookUpTable);
}

void MarkDownParsedResult::Append(std::shared_ptr<MarkDownHtmlGenerator> &x) 
{
    if (!m_codeGenTokens.empty() && 
        m_codeGenTokens.back()->IsList() != x->IsList())
    {
        std::string tags = (x->IsList())? "</p>\n<ul>" : "</ul>\n<p>";

        std::shared_ptr<MarkDownStringHtmlGenerator> htmlToken =
            std::make_shared<MarkDownStringHtmlGenerator>(tags);
        std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(htmlToken);
        m_codeGenTokens.push_back(token);
    }

    m_codeGenTokens.push_back(x);
}

void MarkDownParsedResult::Append(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &x) 
{
    m_emphasisLookUpTable.push_back(x);
}

void MarkDownParsedResult::PopFront()
{ 
    m_codeGenTokens.pop_front();
}

void MarkDownParsedResult::PopBack()
{
    m_codeGenTokens.pop_back();
}

void MarkDownParsedResult::Clear()
{
    m_codeGenTokens.clear();
    m_emphasisLookUpTable.clear();
}

void MarkDownParsedResult::AddNewTokenToParsedResult(int ch)
{
    std::string string_token = std::string(1, ch);
    std::shared_ptr<MarkDownStringHtmlGenerator> htmlToken =
        std::make_shared<MarkDownStringHtmlGenerator>(string_token);
    std::shared_ptr<MarkDownHtmlGenerator> token = std::static_pointer_cast<MarkDownHtmlGenerator>(htmlToken);
    Append(token);
}

std::string MarkDownParsedResult::GenerateHtmlString() 
{ 
    // process tags 
    std::ostringstream html; 

    for (auto itr = m_codeGenTokens.begin(); itr != m_codeGenTokens.end(); itr++) 
    { 
        html << (*itr)->GenerateHtmlString();
    }

    return html.str();
}

// Following the rules speicified in CommonMark (http://spec.commonmark.org/0.27/)
// It generally supports more stricker version of the rules
// push left delims to stack, until matching right delim is found,
// update emphasis counts and type to build string after search is complete

// detects valid emphasis delimiters, when valid delimiters are found, they are added into
// a new space. each new delimiters that are part of the run is appended, in that way,
// it builds tokens of vectors
// each time emphasis tokens are found, they are also added into a lookup table.
// the look up table stores index of the corresponding token in the token vectors, and
// emphasis count and its types that are used in html generation 
// add comments -> what it does: generating  n supported features + 1 tokens --> capture them in token class
void MarkDownParsedResult::MatchLeftAndRightEmphasises()
{
    std::vector<std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator> leftEmphasisToExplore;
    auto currentEmphasis = m_emphasisLookUpTable.begin();

    while (!(currentEmphasis == m_emphasisLookUpTable.end()))
    {
        // keep exploring left until right token is found
        if ((*currentEmphasis)->IsLeftEmphasis() || 
            ((*currentEmphasis)->IsLeftAndRightEmphasis() && leftEmphasisToExplore.empty()))
        {
            if ((*currentEmphasis)->IsLeftAndRightEmphasis() && (*currentEmphasis)->IsRightEmphasis())
            {
                // Reverse Direction Type; right empahsis to left emphasis
                (*currentEmphasis)->ReverseDirectionType();
            }

            leftEmphasisToExplore.push_back(currentEmphasis);
            ++currentEmphasis;
        }
        else if (!leftEmphasisToExplore.empty())
        {
            auto currentLeftEmphasis = leftEmphasisToExplore.back();
            // because of rule #9 & #10 and multiple of 3 rule, left delim can jump ahead of right delim,
            // so need to check this condition.

            // check if matches are found
            //     mataches are found with left and right emphasis tokens if
            //     1. they are same types
            //     2. neigher of the emphasis tokens are both left and right emphasis tokens, and 
            //        if either or both of them are, then their sum is not multipe of 3 
            //        
            //     if matches are not found
            //     1. search left emphasis tokens first for match because of rule 14 matches on the left side is preferred 
            //        if match is found set left emphasis as the new left emphasis token and proceed to token processing
            //        any non-matching left emphasis will be poped, in this way it always move forward
            //        if still no match is found, 
            //     2. search right
            //        if the right emphasis can be left empahs search matching right emphasis tokens using the right emphasis
            //        as left emphasis
            //        else
            //        use current left emphasis to search, and pop current right emphasis
            if (!(*currentLeftEmphasis)->IsMatch(*currentEmphasis))
            {
                std::vector<std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator> store;
                bool isFound = false;
                // search first if matching left emphasis can be found with the right delim
                // if match found, set the new left emphasis token as current token, and
                // process tokens and as of the result, any left emphasis tokens that were searched and not matching 
                // will be no longer considerred in tag processing
                // pop until matching delim is found
                while (!leftEmphasisToExplore.empty() && !isFound)
                {
                    auto leftToken = leftEmphasisToExplore.back();
                    if ((*leftToken)->IsMatch(*currentEmphasis))
                    {
                        currentLeftEmphasis = leftToken;
                        isFound = true;
                    }
                    else
                    {
                        leftEmphasisToExplore.pop_back();
                        store.push_back(leftToken);
                    }
                }

                // if no match found from the left and the right emphasis is both left and right, 
                // and the sum of their emphasises counts is divisible by 3,
                // use current right emphasis as 
                // left emphasis, make the right emphasis, as current left
                // emphasis and start searching from there.
                // during the search if no match found, 
                // this emphasis tokens will be dropped
                if (!isFound)
                {
                    // restore state
                    while (!isFound && !store.empty())
                    {
                        leftEmphasisToExplore.push_back(store.back());
                        store.pop_back();
                    }

                    // check for the reason why we had to backtrack
                    if ((*leftEmphasisToExplore.back())->IsSameType(*currentEmphasis))
                    {
                        //right emphasis becomes left emphasis
                        /// create new left empahsis html generator from right
                        (*currentEmphasis)->ReverseDirectionType();
                    }
                    else
                    {
                        // move to next token for right delim tokens
                        currentEmphasis++;
                    }
                    // no maching found begin from the start
                    continue;
                }
            }
            // check which one has leftover delims
            (*currentLeftEmphasis)->GenerateTags(*currentEmphasis);

            // all right delims used, move to next
            if ((*currentEmphasis)->IsDone())
            {
                currentEmphasis++;
            }

            // all left or right delims used, pop
            if ((*currentLeftEmphasis)->IsDone())
            { 
                leftEmphasisToExplore.pop_back();
            }
        }
        else
        { 
            currentEmphasis++;
        }
    }
}
