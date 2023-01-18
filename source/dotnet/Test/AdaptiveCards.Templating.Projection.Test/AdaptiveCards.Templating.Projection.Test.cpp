#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdaptiveCardsTemplatingProjectionTest
{
    TEST_CLASS(AdaptiveCardsTemplatingProjectionTest)
    {
    public:

        TEST_METHOD(Instantiate)
        {
            winrt::AdaptiveCards::Templating::Projection::Template theTemplate(LR"(
            {
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "TextBlock",
                        "text": "${greeting} from ${$host.name}"
                    }
                ]
            })");

            auto boundTemplate = theTemplate.Expand(LR"({ "greeting": "Hello" })", LR"({ "name": ")" __FUNCTION__ L"\"}");
            Assert::AreEqual("",  winrt::to_string(boundTemplate).c_str());
        }

        TEST_METHOD(EmptyTemplate)
        {
            winrt::AdaptiveCards::Templating::Projection::Template testObject(L"{}");
            auto boundTestObject = testObject.Expand(L"{}");
            Assert::AreEqual(winrt::to_string(boundTestObject).c_str(), "{}");
        }
    };
}
