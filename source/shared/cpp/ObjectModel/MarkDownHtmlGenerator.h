#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include "BaseCardElement.h"

namespace AdaptiveCards
{

enum DelimiterType
{
    Init,
    Alphanumeric,
    Puntuation,
    Escape,
    WhiteSpace,
    Underscore = 0x8,
    Asterisk   = 0x10,
};

class MarkDownHtmlGenerator
{
    public:
        MarkDownHtmlGenerator(std::string &token) : m_token(token){};
        virtual std::string GenerateHtmlString() = 0;
    protected:
        std::string m_token;
        std::ostringstream html;
};

class MarkDownStringHtmlGenerator : public MarkDownHtmlGenerator
{ 
    public:
        MarkDownStringHtmlGenerator(std::string &token) : MarkDownHtmlGenerator(token){};
        std::string GenerateHtmlString();
};

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
        virtual int GetPositionAtTokenTable() { return 0; }

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

class MarkDownLinkHtmlGenerator : public MarkDownHtmlGenerator
{ 
    public:        
        typedef std::shared_ptr<MarkDownEmphasisHtmlGenerator> EmphasisCodeGeneratorPointerType;
        typedef std::list<EmphasisCodeGeneratorPointerType> EmphasisCodeGeneratorPointerTypeList;
        typedef std::shared_ptr<MarkDownHtmlGenerator> CodeGeneratorPointerType;
        typedef std::list<CodeGeneratorPointerType> CodeGeneratorPointerTypeList;

        MarkDownLinkHtmlGenerator(std::string token, 
                CodeGeneratorPointerTypeList::iterator tokenPositionAsIterator) : 
            MarkDownHtmlGenerator(token), m_tokenListBegin(tokenPositionAsIterator){};

        bool IsLink() { return m_isLink; }
        void ConfirmLink() { m_isLink = true; }
        void SetEmphasisListBegin(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator &begin)
        {
            m_emphasisListBegin = begin;
        }

        void SetEmphasisListEnd(std::list<std::shared_ptr<MarkDownEmphasisHtmlGenerator>>::iterator &end)
        {
            m_emphasisListEnd = end;
        }

        void SetTokenListEnd(std::list<std::shared_ptr<MarkDownHtmlGenerator>>::iterator &end)
        {
            m_tokenListEnd = end;
        }

        std::string GenerateHtmlString() { return m_token; };
    protected:
        bool m_isLink = false;
        EmphasisCodeGeneratorPointerTypeList m_emphasisList = EmphasisCodeGeneratorPointerTypeList();
        EmphasisCodeGeneratorPointerTypeList::iterator m_emphasisListBegin;
        EmphasisCodeGeneratorPointerTypeList::iterator m_emphasisListEnd;

        CodeGeneratorPointerTypeList::iterator m_tokenListBegin;
        CodeGeneratorPointerTypeList::iterator m_tokenListEnd;
};

class MarkDownLinkTextHtmlGenerator : public MarkDownLinkHtmlGenerator
{ 
    public:        
        MarkDownLinkTextHtmlGenerator(CodeGeneratorPointerTypeList::iterator tokenPositionAsIterator) : 
            MarkDownLinkHtmlGenerator("[", tokenPositionAsIterator){};

        std::string GenerateHtmlString() { return m_token; };
    protected:
};

}
