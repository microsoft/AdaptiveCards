#pragma once

#include "BaseCardElement.h"
#include "MarkDownHtmlGenerator.h"
#include <list>

namespace AdaptiveCards
{
    // Holds Parsing Result of MarkDown String
    class MarkDownParsedResult
    {
        public:
        // Translate Intermediate Parsing Result to a form that can be
        // written to html string
        void Translate();
        void AddBlockTags();
        // Write to html string
        std::string GenerateHtmlString(); 
        // Append contents of the given parsing result object
        void Append(MarkDownParsedResult &);
        // Append html code gen object to parse result
        void Append(std::shared_ptr<MarkDownHtmlGenerator> &); 
        // Append emphasis html code gen object to parse result
        void Append(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &); 
        // Take a char and convert it html code gen and append it to the result
        // It is used to store MarkDown keywords such as '[', ']', '(', ')'
        void AddNewTokenToParsedResult(int ch);
        void PopFront();
        void PopBack();
        void Clear();
        private:
        std::list<std::shared_ptr<MarkDownHtmlGenerator>> m_codeGenTokens;
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> m_emphasisLookUpTable;
        // take m_emphasisLookUpTable and matches left and right emphasises
        void MatchLeftAndRightEmphasises();
    };
}
