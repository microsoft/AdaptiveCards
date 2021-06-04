// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MarkDownParser.h"

namespace AdaptiveCards
{
    MarkDownParser::MarkDownParser(const std::string& txt) : m_text(txt) {}

    void MarkDownParser::md_output(const MD_CHAR* processedChunk, MD_SIZE chunkSize, void* pvData)
    {
        std::ostringstream* output = static_cast<std::ostringstream*>(pvData);
        output->write(processedChunk, static_cast<size_t>(chunkSize));
    }

    // transforms string to html
    std::string MarkDownParser::TransformToHtml()
    {
        std::ostringstream processedOutput;
        const auto result = md_html(m_text.c_str(),
                                    static_cast<unsigned>(m_text.length()),
                                    md_output,
                                    &processedOutput,
                                    MD_FLAG_NOINDENTEDCODEBLOCKS | MD_FLAG_NOHTMLBLOCKS | MD_FLAG_NOHTMLSPANS,
                                    0);
        if (result == 0)
        {
            auto outputStr = processedOutput.str();
            if (!outputStr.empty())
            {
                if (outputStr.back() == '\n')
                {
                    outputStr.pop_back();
                }

                // detect if we've got more tags than the standard <p></p> wrapper:
                //
                // look for the second '<' from the front of the string and the first '<' from the end of the string. if
                // they're different, there's another tag in there somewhere...
                m_hasHTMLTag = (outputStr.length() > 1 && outputStr.find('<', 1) != outputStr.rfind('<'));
            }

            return outputStr;
        }

        return m_text;
    }

    bool MarkDownParser::HasHtmlTags() const { return m_hasHTMLTag; }

    std::string MarkDownParser::GetRawText() const { return m_text; }
}
