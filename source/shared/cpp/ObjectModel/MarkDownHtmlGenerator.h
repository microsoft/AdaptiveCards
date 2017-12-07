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
        virtual std::string generateHtmlString() = 0;
        bool IsMatch(std::shared_ptr<MarkDownHtmlGenerator> &token){return false;};
    protected:
        std::string m_token;
        std::ostringstream html;
};

class MarkDownStringHtmlGenerator : MarkDownHtmlGenerator
{ 
    public:
        MarkDownStringHtmlGenerator(std::string &token) : MarkDownHtmlGenerator(token){};
        std::string generateHtmlString();
};

class MarkDownEmphasisHtmlGenerator : protected MarkDownHtmlGenerator
{
    public:

        MarkDownEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                bool isLeftAndRightEmphasis,
                DelimiterType type
                ) : MarkDownHtmlGenerator(token), 
        m_numberOfUnusedDelimiters(sizeOfEmphasisDelimiterRun), type(type), m_tags(){};

        std::string generateHtmlString();
        bool IsMatch(std::shared_ptr<MarkDownHtmlGenerator> &token);
        void PushItalicTag(); 
        void PushBoldTag(); 

    protected:
        int m_numberOfUnusedDelimiters;
        bool isLeftAndRightEmphasis;
        DelimiterType type;
        std::vector<std::string> m_tags;

};

class MarkDownLeftEmphasisHtmlGenerator : MarkDownEmphasisHtmlGenerator 
{
    public:
        MarkDownLeftEmphasisHtmlGenerator (std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                bool isLeftAndRightEmphasis,
                DelimiterType type) : MarkDownEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, isLeftAndRightEmphasis, type){};
        std::string generateHtmlString();
};
class MarkDownRightEmphasisHtmlGenerator : MarkDownEmphasisHtmlGenerator 
{
    public:
        MarkDownRightEmphasisHtmlGenerator(std::string &token, 
                int sizeOfEmphasisDelimiterRun,
                bool isLeftAndRightEmphasis,
                DelimiterType type) : MarkDownEmphasisHtmlGenerator(token, 
                    sizeOfEmphasisDelimiterRun, isLeftAndRightEmphasis, type){};

        std::string generateHtmlString();
        void PushItalicTag(); 
        void PushBoldTag(); 
};
}
