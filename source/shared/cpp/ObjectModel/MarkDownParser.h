// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "md4c/md4c-html.h"

namespace AdaptiveCards
{
    class MarkDownParser
    {
    public:
        MarkDownParser(const std::string& txt);

        std::string TransformToHtml();
        std::string GetRawText() const;
        bool HasHtmlTags() const;

    private:
        static void md_output(const MD_CHAR* processedChunk, MD_SIZE chunkSize, void* pvData);
        std::string m_text;
        bool m_hasHTMLTag{false};
    };
}
