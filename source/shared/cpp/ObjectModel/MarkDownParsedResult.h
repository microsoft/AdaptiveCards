// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BaseCardElement.h"
#include "MarkDownHtmlGenerator.h"
#include <list>

namespace AdaptiveSharedNamespace
{
    // Holds Parsing Result of MarkDown String
    class MarkDownParsedResult
    {
    public:
        MarkDownParsedResult() : m_isHTMLTagsAdded(false), m_isCaptured(false) {};

        // Translate Intermediate Parsing Result to a form that can be written to html string
        void Translate();
        void AddBlockTags();

        // Write to html string
        std::string GenerateHtmlString();

        // Append contents of the given parsing result object
        void AppendParseResult(MarkDownParsedResult&);

        // Append html code gen object to parse result
        void AppendToTokens(const std::shared_ptr<MarkDownHtmlGenerator>&);

        // Append emphasis html code gen object to parse result
        void AppendToLookUpTable(const std::shared_ptr<MarkDownEmphasisHtmlGenerator>&);

        // Take a char and convert it html code gen and append it to the result. used to store MarkDown keywords such as
        // '[', ']', '(', ')'
        void AddNewTokenToParsedResult(char ch);

        // Take string and convert it html code gen and append it to the result
        void AddNewTokenToParsedResult(std::string& word);

        // Take a new line char and convert it html code gen and append it to the result It is used to store MarkDown
        // keywords such as '\r', '\n'
        void AddNewLineTokenToParsedResult(char ch);
        void PopFront();
        void PopBack();
        void Clear();
        bool HasHtmlTags();
        void FoundHtmlTags();
        bool GetIsCaptured() const { return m_isCaptured; }
        void SetIsCaptured(const bool val) { m_isCaptured = val; }

    private:
        void MarkTags(MarkDownHtmlGenerator&);
        std::list<std::shared_ptr<MarkDownHtmlGenerator>> m_codeGenTokens;
        std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>> m_emphasisLookUpTable;
        bool m_isHTMLTagsAdded;
        bool m_isCaptured;

        // take m_emphasisLookUpTable and matches left and right emphasises
        void MatchLeftAndRightEmphasises();
    };
}
