#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include "BaseCardElement.h"

AdaptiveSharedNamespaceStart

enum DelimiterType
{
    Init,
    Alphanumeric,
    Puntuation,
    Escape,
    WhiteSpace,
    Underscore,
    Asterisk,
};

// this class knows how to generate html string of their types 
// - MarkDownStringHtmlGenerator 
//   it is the most basic form,
//   it simply retains and return text as string
// - MarkDownEmphasisHtmlGenerator 
//   it knows how to handle bold and italic html
//   tags and apply those to its text when asked to generate html string
// - MarkDownListHtmlGenerator
//   it functions simmilary as MarkDownStringHtmlGenerator, but its GetBlockType() returns
//   MarkDownBlockType, this is used in generating html block tags
//   list uses block tag of <ul> all others use <p>
class MarkDownHtmlGenerator
{
    public:
        enum MarkDownBlockType
        {
            ContainerBlock,
            UnorderedList,
            OrderedList
        };

        MarkDownHtmlGenerator() : m_token(""){};
        MarkDownHtmlGenerator(std::string &token) : m_token(token){};
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
        MarkDownStringHtmlGenerator(std::string &token) : MarkDownHtmlGenerator(token){};
        std::string GenerateHtmlString();
};

// - MarkDownNewLineHtmlGenerator 
//   it contains new line chars
class MarkDownNewLineHtmlGenerator : public MarkDownStringHtmlGenerator 
{ 
    public:
        MarkDownNewLineHtmlGenerator(std::string &token) : MarkDownStringHtmlGenerator(token){};
        bool IsNewLine() { return true; }
};

// - MarkDownEmphasisHtmlGenerator 
//   it knows how to handle bold and italic html
//   tags and apply those to its text when asked to generate html string
class MarkDownEmphasisHtmlGenerator : public MarkDownHtmlGenerator
{
    public:
        MarkDownEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type
                ) : MarkDownHtmlGenerator(token), 
        m_numberOfUnusedDelimiters(sizeOfEmphasisDelimiterRun), type(type){};

        MarkDownEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type,
                std::vector<std::string> &tags
                ) : MarkDownHtmlGenerator(token), 
        m_numberOfUnusedDelimiters(sizeOfEmphasisDelimiterRun), type(type), m_tags(tags){};

        virtual bool IsRightEmphasis() const { return false; }
        virtual bool IsLeftEmphasis() const  { return false; }
        virtual bool IsLeftAndRightEmphasis() const { return false; }
        virtual void PushItalicTag(); 
        virtual void PushBoldTag(); 

        bool IsMatch(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token);
        bool IsSameType(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token);
        bool IsDone() const { return m_numberOfUnusedDelimiters == 0; }
        int GetNumberOfUnusedDelimiters() const { return m_numberOfUnusedDelimiters; };
        void GenerateTags(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token);
        void ReverseDirectionType() { m_directionType = !m_directionType; };
    protected:
        enum 
        {
            Left = 0,
            Right = 1,
        };

        int AdjustEmphasisCounts(int leftOver, std::shared_ptr<MarkDownEmphasisHtmlGenerator> rightToken);
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
        MarkDownLeftEmphasisHtmlGenerator (std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type) : MarkDownEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, type){};
        
        MarkDownLeftEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type, std::vector<std::string> &tags) : MarkDownEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, type, tags){};

        bool IsLeftEmphasis() const  { return true; }
        std::string GenerateHtmlString();
};

// - MarkDownRightEmphasisHtmlGenerator 
//   it knows how to generates closing italic and bold html tags
class MarkDownRightEmphasisHtmlGenerator : public MarkDownEmphasisHtmlGenerator 
{
    public:
        MarkDownRightEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type) : MarkDownEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, type){};

        void GenerateTags(std::shared_ptr<MarkDownEmphasisHtmlGenerator> &token);
        bool IsRightEmphasis() const { return true; }
        std::string GenerateHtmlString();
        void PushItalicTag(); 
        void PushBoldTag(); 
};

// - MarkDownLeftAndRightEmphasisHtmlGenerator 
//   it can have both directions, and its final direction is determined at the later stage
class MarkDownLeftAndRightEmphasisHtmlGenerator : public MarkDownRightEmphasisHtmlGenerator 
{
    public:
        MarkDownLeftAndRightEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                DelimiterType type) : MarkDownRightEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, type) {};
        bool IsRightEmphasis() const { return m_directionType == Right; }
        bool IsLeftEmphasis() const  { return m_directionType == Left; }
        bool IsLeftAndRightEmphasis() const { return true; };
        void PushItalicTag(); 
        void PushBoldTag(); 
};

// - MarkDownListHtmlGenerator
//   it functions simmilary as MarkDownStringHtmlGenerator, but its GetBlockType() returns
//   UnorderedList type, this is used in generating html block tags <ul>
class MarkDownListHtmlGenerator : public MarkDownStringHtmlGenerator 
{
    public:
        MarkDownListHtmlGenerator(std::string &token) : MarkDownStringHtmlGenerator(token) {};
        std::string GenerateHtmlString();
        MarkDownBlockType GetBlockType() const { return UnorderedList; }; 
};

// - MarkDownUnorderedListHtmlGenerator
//   it functions simmilary as MarkDownStringHtmlGenerator, but its GetBlockType() returns
//   OrderedList type, this is used in generating html block tags <ol>
class MarkDownOrderedListHtmlGenerator : public MarkDownStringHtmlGenerator 
{
    public:
        MarkDownOrderedListHtmlGenerator(std::string &token, std::string &number_string) : 
            MarkDownStringHtmlGenerator(token), m_numberString(number_string) {};
        std::string GenerateHtmlString();
        MarkDownBlockType GetBlockType() const { return OrderedList; }; 
    private:
        std::string m_numberString;
};

AdaptiveSharedNamespaceEnd
