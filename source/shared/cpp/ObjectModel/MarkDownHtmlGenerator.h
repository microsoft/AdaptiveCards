// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include "BaseCardElement.h"

namespace AdaptiveSharedNamespace
{
    enum class DelimiterType
    {
        Init,
        Alphanumeric,
        Puntuation,
        Escape,
        WhiteSpace,
        Underscore,
        Asterisk
    };

    // this class knows how to generate html string of their types
    // - MarkDownStringHtmlGenerator
    //   it is the most basic form,
    //   it simply retains and return text as string
    // - MarkDownEmphasisHtmlGenerator
    //   it knows how to handle bold and italic html
    //   tags and apply those to its text when asked to generate html string
    // - MarkDownListHtmlGenerator
    //   it functions similarly as MarkDownStringHtmlGenerator, but its GetBlockType() returns
    //   MarkDownBlockType, this is used in generating html block tags
    //   list uses block tag of <ul> all others use <p>
    class MarkDownHtmlGenerator
    {
    public:
        MarkDownHtmlGenerator(const MarkDownHtmlGenerator&) = default;
        MarkDownHtmlGenerator(MarkDownHtmlGenerator&&) = default;
        MarkDownHtmlGenerator& operator=(const MarkDownHtmlGenerator&) = default;
        MarkDownHtmlGenerator& operator=(MarkDownHtmlGenerator&&) = default;
        virtual ~MarkDownHtmlGenerator() = default;

        enum MarkDownBlockType
        {
            ContainerBlock,
            UnorderedList,
            OrderedList
        };

        MarkDownHtmlGenerator() : m_token(""){};
        MarkDownHtmlGenerator(std::string& token) : m_token(token){};
        void MakeItHead() { m_isHead = true; }
        void MakeItTail() { m_isTail = true; }
        virtual bool IsNewLine() { return false; }
        virtual std::string GenerateHtmlString() = 0;
        virtual MarkDownBlockType GetBlockType() const { return ContainerBlock; };

    protected:
        std::string m_token;
        std::ostringstream html;
        bool m_isHead = false;
        bool m_isTail = false;
    };

    // - MarkDownStringHtmlGenerator
    //   it is the most basic form,
    //   it simply retains and return text as string
    class MarkDownStringHtmlGenerator : public MarkDownHtmlGenerator
    {
    public:
        MarkDownStringHtmlGenerator() = delete;
        MarkDownStringHtmlGenerator(const MarkDownStringHtmlGenerator&) = default;
        MarkDownStringHtmlGenerator(MarkDownStringHtmlGenerator&&) = default;
        MarkDownStringHtmlGenerator& operator=(const MarkDownStringHtmlGenerator&) = default;
        MarkDownStringHtmlGenerator& operator=(MarkDownStringHtmlGenerator&&) = default;
        ~MarkDownStringHtmlGenerator() = default;

        MarkDownStringHtmlGenerator(std::string& token) : MarkDownHtmlGenerator(token){};
        std::string GenerateHtmlString() override;
    };

    // - MarkDownNewLineHtmlGenerator
    //   it contains new line chars
    class MarkDownNewLineHtmlGenerator : public MarkDownStringHtmlGenerator
    {
    public:
        MarkDownNewLineHtmlGenerator() = delete;
        MarkDownNewLineHtmlGenerator(const MarkDownNewLineHtmlGenerator&) = default;
        MarkDownNewLineHtmlGenerator(MarkDownNewLineHtmlGenerator&&) = default;
        MarkDownNewLineHtmlGenerator& operator=(const MarkDownNewLineHtmlGenerator&) = default;
        MarkDownNewLineHtmlGenerator& operator=(MarkDownNewLineHtmlGenerator&&) = default;
        ~MarkDownNewLineHtmlGenerator() = default;

        MarkDownNewLineHtmlGenerator(std::string& token) : MarkDownStringHtmlGenerator(token){};
        bool IsNewLine() override { return true; }
    };

    // - MarkDownEmphasisHtmlGenerator
    //   it knows how to handle bold and italic html
    //   tags and apply those to its text when asked to generate html string
    class MarkDownEmphasisHtmlGenerator : public MarkDownHtmlGenerator
    {
    public:
        MarkDownEmphasisHtmlGenerator() = delete;
        MarkDownEmphasisHtmlGenerator(const MarkDownEmphasisHtmlGenerator&) = default;
        MarkDownEmphasisHtmlGenerator(MarkDownEmphasisHtmlGenerator&&) = default;
        MarkDownEmphasisHtmlGenerator& operator=(const MarkDownEmphasisHtmlGenerator&) = default;
        MarkDownEmphasisHtmlGenerator& operator=(MarkDownEmphasisHtmlGenerator&&) = default;
        ~MarkDownEmphasisHtmlGenerator() = default;

        MarkDownEmphasisHtmlGenerator(std::string& token, int sizeOfEmphasisDelimiterRun, DelimiterType type) :
            MarkDownHtmlGenerator(token), m_numberOfUnusedDelimiters(sizeOfEmphasisDelimiterRun), type(type){};

        MarkDownEmphasisHtmlGenerator(std::string& token, int sizeOfEmphasisDelimiterRun, DelimiterType type, std::vector<std::string>& tags) :
            MarkDownHtmlGenerator(token), m_numberOfUnusedDelimiters(sizeOfEmphasisDelimiterRun), type(type), m_tags(tags){};

        virtual bool IsRightEmphasis() const { return false; }
        virtual bool IsLeftEmphasis() const { return false; }
        virtual bool IsLeftAndRightEmphasis() const { return false; }
        virtual void PushItalicTag();
        virtual void PushBoldTag();

        bool IsMatch(const MarkDownEmphasisHtmlGenerator& token);
        bool IsSameType(const MarkDownEmphasisHtmlGenerator& token);
        bool IsDone() const { return m_numberOfUnusedDelimiters == 0; }
        int GetNumberOfUnusedDelimiters() const { return m_numberOfUnusedDelimiters; };
        bool GenerateTags(MarkDownEmphasisHtmlGenerator& token);
        void ReverseDirectionType() { m_directionType = !m_directionType; };

    protected:
        enum
        {
            Left = 0,
            Right = 1,
        };

        int AdjustEmphasisCounts(int leftOver, MarkDownEmphasisHtmlGenerator& rightToken);
        int m_numberOfUnusedDelimiters;
        int m_directionType = Right;
        DelimiterType type;
        std::vector<std::string> m_tags;
    };

    // - MarkDownLeftEmphasisHtmlGenerator
    //   it knows how to generates opening italic and bold html tags
    class MarkDownLeftEmphasisHtmlGenerator : public MarkDownEmphasisHtmlGenerator
    {
    public:
        MarkDownLeftEmphasisHtmlGenerator() = delete;
        MarkDownLeftEmphasisHtmlGenerator(const MarkDownLeftEmphasisHtmlGenerator&) = default;
        MarkDownLeftEmphasisHtmlGenerator(MarkDownLeftEmphasisHtmlGenerator&&) = default;
        MarkDownLeftEmphasisHtmlGenerator& operator=(const MarkDownLeftEmphasisHtmlGenerator&) = default;
        MarkDownLeftEmphasisHtmlGenerator& operator=(MarkDownLeftEmphasisHtmlGenerator&&) = default;
        ~MarkDownLeftEmphasisHtmlGenerator() = default;

        MarkDownLeftEmphasisHtmlGenerator(std::string& token, int sizeOfEmphasisDelimiterRun, DelimiterType type) :
            MarkDownEmphasisHtmlGenerator(token, sizeOfEmphasisDelimiterRun, type){};

        MarkDownLeftEmphasisHtmlGenerator(std::string& token,
                                          int sizeOfEmphasisDelimiterRun,
                                          DelimiterType type,
                                          std::vector<std::string>& tags) :
            MarkDownEmphasisHtmlGenerator(token, sizeOfEmphasisDelimiterRun, type, tags){};

        bool IsLeftEmphasis() const override { return true; }
        std::string GenerateHtmlString() override;
    };

    // - MarkDownRightEmphasisHtmlGenerator
    //   it knows how to generates closing italic and bold html tags
    class MarkDownRightEmphasisHtmlGenerator : public MarkDownEmphasisHtmlGenerator
    {
    public:
        MarkDownRightEmphasisHtmlGenerator() = delete;
        MarkDownRightEmphasisHtmlGenerator(const MarkDownRightEmphasisHtmlGenerator&) = default;
        MarkDownRightEmphasisHtmlGenerator(MarkDownRightEmphasisHtmlGenerator&&) = default;
        MarkDownRightEmphasisHtmlGenerator& operator=(const MarkDownRightEmphasisHtmlGenerator&) = default;
        MarkDownRightEmphasisHtmlGenerator& operator=(MarkDownRightEmphasisHtmlGenerator&&) = default;
        ~MarkDownRightEmphasisHtmlGenerator() = default;

        MarkDownRightEmphasisHtmlGenerator(std::string& token, int sizeOfEmphasisDelimiterRun, DelimiterType type) :
            MarkDownEmphasisHtmlGenerator(token, sizeOfEmphasisDelimiterRun, type){};

        void GenerateTags(std::shared_ptr<MarkDownEmphasisHtmlGenerator>& token);
        bool IsRightEmphasis() const override { return true; }
        std::string GenerateHtmlString() override;
        void PushItalicTag() override;
        void PushBoldTag() override;
    };

    // - MarkDownLeftAndRightEmphasisHtmlGenerator
    //   it can have both directions, and its final direction is determined at the later stage
    class MarkDownLeftAndRightEmphasisHtmlGenerator : public MarkDownRightEmphasisHtmlGenerator
    {
    public:
        MarkDownLeftAndRightEmphasisHtmlGenerator() = delete;
        MarkDownLeftAndRightEmphasisHtmlGenerator(const MarkDownLeftAndRightEmphasisHtmlGenerator&) = default;
        MarkDownLeftAndRightEmphasisHtmlGenerator(MarkDownLeftAndRightEmphasisHtmlGenerator&&) = default;
        MarkDownLeftAndRightEmphasisHtmlGenerator& operator=(const MarkDownLeftAndRightEmphasisHtmlGenerator&) = default;
        MarkDownLeftAndRightEmphasisHtmlGenerator& operator=(MarkDownLeftAndRightEmphasisHtmlGenerator&&) = default;
        ~MarkDownLeftAndRightEmphasisHtmlGenerator() = default;

        MarkDownLeftAndRightEmphasisHtmlGenerator(std::string& token, int sizeOfEmphasisDelimiterRun, DelimiterType type) :
            MarkDownRightEmphasisHtmlGenerator(token, sizeOfEmphasisDelimiterRun, type){};
        bool IsRightEmphasis() const override { return m_directionType == Right; }
        bool IsLeftEmphasis() const override { return m_directionType == Left; }
        bool IsLeftAndRightEmphasis() const override { return true; };
        void PushItalicTag() override;
        void PushBoldTag() override;
    };

    // - MarkDownListHtmlGenerator
    //   it functions similarly as MarkDownStringHtmlGenerator, but its GetBlockType() returns
    //   UnorderedList type, this is used in generating html block tags <ul>
    class MarkDownListHtmlGenerator : public MarkDownStringHtmlGenerator
    {
    public:
        MarkDownListHtmlGenerator() = delete;
        MarkDownListHtmlGenerator(const MarkDownListHtmlGenerator&) = default;
        MarkDownListHtmlGenerator(MarkDownListHtmlGenerator&&) = default;
        MarkDownListHtmlGenerator& operator=(const MarkDownListHtmlGenerator&) = default;
        MarkDownListHtmlGenerator& operator=(MarkDownListHtmlGenerator&&) = default;
        ~MarkDownListHtmlGenerator() = default;

        MarkDownListHtmlGenerator(std::string& token) : MarkDownStringHtmlGenerator(token){};
        std::string GenerateHtmlString() override;
        MarkDownBlockType GetBlockType() const override { return UnorderedList; };
    };

    // - MarkDownUnorderedListHtmlGenerator
    //   it functions similarly as MarkDownStringHtmlGenerator, but its GetBlockType() returns
    //   OrderedList type, this is used in generating html block tags <ol>
    class MarkDownOrderedListHtmlGenerator : public MarkDownStringHtmlGenerator
    {
    public:
        MarkDownOrderedListHtmlGenerator() = delete;
        MarkDownOrderedListHtmlGenerator(const MarkDownOrderedListHtmlGenerator&) = default;
        MarkDownOrderedListHtmlGenerator(MarkDownOrderedListHtmlGenerator&&) = default;
        MarkDownOrderedListHtmlGenerator& operator=(const MarkDownOrderedListHtmlGenerator&) = default;
        MarkDownOrderedListHtmlGenerator& operator=(MarkDownOrderedListHtmlGenerator&&) = default;
        ~MarkDownOrderedListHtmlGenerator() = default;

        MarkDownOrderedListHtmlGenerator(std::string& token, std::string& number_string) :
            MarkDownStringHtmlGenerator(token), m_numberString(number_string){};
        std::string GenerateHtmlString() override;
        MarkDownBlockType GetBlockType() const override { return OrderedList; };

    private:
        std::string m_numberString;
    };

}
