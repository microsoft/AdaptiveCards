// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "stdafx.h"
#include "ActionParserRegistration.h"
#include "ParseUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ParserRegistrationTest)
    {
    public:
        TEST_METHOD(ParserRegistrationTests)
        {
            // Define custom type. This implements both element and action for convenience
            class TestCustomElement : public BaseCardElement, public BaseActionElement
            {
            public:
                TestCustomElement(const Json::Value& value) : BaseCardElement(AdaptiveCards::CardElementType::Custom),
                                                              BaseActionElement(AdaptiveCards::ActionType::Custom)
                {
                    m_customImage = value.get("customProperty", Json::Value()).asString();
                }

                virtual ~TestCustomElement() {};

            private:
                std::string m_customImage;
            };

            // Define custom element parser
            class TestCustomElementParser : public BaseCardElementParser
            {
            public:
                virtual ~TestCustomElementParser() {};
                virtual std::shared_ptr<BaseCardElement> Deserialize(ParseContext &/*context*/, const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }
                virtual std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext &context, const std::string& value) override
                {
                    return Deserialize(context, ParseUtil::GetJsonValueFromString(value));
                }
            };

            // Define custom action parser
            class TestCustomActionParser : public ActionElementParser
            {
            public:
                virtual ~TestCustomActionParser() {};
                virtual std::shared_ptr<BaseActionElement> Deserialize(ParseContext &/*context*/, const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }
                virtual std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext &context, const std::string& value) override
                {
                    return Deserialize(context, ParseUtil::GetJsonValueFromString(value));
                }
            };

            ActionParserRegistration actionParser;
            ElementParserRegistration elementParser;

            std::string elemType("notRegisteredYet");
            // make sure we don't already have this parser
            Assert::IsTrue(!actionParser.GetParser(elemType));
            auto customActionParser = std::make_shared<TestCustomActionParser>();
            auto customElementParser = std::make_shared<TestCustomElementParser>();

            // make sure we can't override a known parser
            Assert::ExpectException<AdaptiveCardParseException>([&]() { actionParser.AddParser(ActionTypeToString(ActionType::OpenUrl), customActionParser); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { elementParser.AddParser(CardElementTypeToString(CardElementType::Container), customElementParser); });

            // add our new parser
            actionParser.AddParser(elemType, customActionParser);
            {
                auto actionParserWrapper = std::static_pointer_cast<ActionElementParserWrapper>(actionParser.GetParser(elemType));
                Assert::IsTrue(customActionParser == actionParserWrapper->GetActualParser());
            }

            elementParser.AddParser(elemType, customElementParser);
            {
                auto cardParserWrapper = std::static_pointer_cast<BaseCardElementParserWrapper>(elementParser.GetParser(elemType));
                Assert::IsTrue(customElementParser == cardParserWrapper->GetActualParser());
            }

            // overwrite our new parser
            auto customActionParser2 = std::make_shared<TestCustomActionParser>();
            actionParser.AddParser(elemType, customActionParser2);
            {
                auto actionParserWrapper = std::static_pointer_cast<ActionElementParserWrapper>(actionParser.GetParser(elemType));
                Assert::IsTrue(customActionParser2 == actionParserWrapper->GetActualParser());
            }

            auto customElementParser2 = std::make_shared<TestCustomElementParser>();
            elementParser.AddParser(elemType, customElementParser2);
            {
                auto cardParserWrapper = std::static_pointer_cast<BaseCardElementParserWrapper>(elementParser.GetParser(elemType));
                Assert::IsTrue(customElementParser2 == cardParserWrapper->GetActualParser());
            }

            // remove custom parser twice. shouldn't throw
            actionParser.RemoveParser(elemType);
            Assert::IsTrue(!actionParser.GetParser(elemType));
            actionParser.RemoveParser(elemType);
            Assert::IsTrue(!actionParser.GetParser(elemType));
            elementParser.RemoveParser(elemType);
            Assert::IsTrue(!elementParser.GetParser(elemType));
            elementParser.RemoveParser(elemType);
            Assert::IsTrue(!elementParser.GetParser(elemType));

            // make sure we can't remove known parser
            Assert::IsTrue((bool)actionParser.GetParser(ActionTypeToString(ActionType::OpenUrl)));
            Assert::ExpectException<AdaptiveCardParseException>([&]() { actionParser.RemoveParser(ActionTypeToString(ActionType::OpenUrl)); });
            Assert::IsTrue((bool)actionParser.GetParser(ActionTypeToString(ActionType::OpenUrl)));
            Assert::IsTrue((bool)elementParser.GetParser(CardElementTypeToString(CardElementType::Container)));
            Assert::ExpectException<AdaptiveCardParseException>([&]() { elementParser.RemoveParser(CardElementTypeToString(CardElementType::Container)); });
            Assert::IsTrue((bool)elementParser.GetParser(CardElementTypeToString(CardElementType::Container)));
        }
    };
}
