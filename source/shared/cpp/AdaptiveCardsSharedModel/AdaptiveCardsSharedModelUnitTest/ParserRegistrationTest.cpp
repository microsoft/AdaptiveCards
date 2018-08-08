#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>
#include <Windows.h>
#include <StrSafe.h>
#include "SharedAdaptiveCard.h"
#include "BaseCardElement.h"
#include "ActionParserRegistration.h"

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
				TestCustomElement(
					const Json::Value& value) :
					BaseCardElement(AdaptiveCards::CardElementType::Custom),
					BaseActionElement(AdaptiveCards::ActionType::Custom)
				{
					m_customImage = value.get("customImageProperty", Json::Value()).asString();
				}

				virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceUris) override
				{
					RemoteResourceInformation resourceInfo;
					resourceInfo.url = m_customImage;
					resourceInfo.resourceType = CardElementType::Image;
					resourceUris.push_back(resourceInfo);
				}

			private:
				std::string m_customImage;
			};

			// Define custom element parser
			class TestCustomParser : public BaseCardElementParser
			{
			public:
				virtual std::shared_ptr<BaseCardElement> Deserialize(
					std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
					std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
					std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& warnings,
					const Json::Value& value) override
				{
					return std::make_shared<TestCustomElement>(value);
				}
			};

			// Define custom action parser
			class TestCustomActionParser : public ActionElementParser
			{
			public:
				virtual std::shared_ptr<BaseActionElement> Deserialize(
					std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
					std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
					std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& warnings,
					const Json::Value& value) override
				{
					return std::make_shared<TestCustomElement>(value);
				}
			};

			ActionParserRegistration parser;

			std::string elemType("notRegisteredYet");
			// make sure we don't already have this parser
			Assert::IsTrue(!parser.GetParser(elemType));
			auto customParser = std::make_shared<TestCustomActionParser>();

			// make sure we can't override a known parser
			Assert::ExpectException<AdaptiveCardParseException>([&]() { parser.AddParser(ActionTypeToString(ActionType::OpenUrl), customParser); });

			// add our new parser
			parser.AddParser(elemType, customParser);
			Assert::IsTrue(customParser == parser.GetParser(elemType));
			
			// overwrite our new parser
			auto customParser2 = std::make_shared<TestCustomActionParser>();
			parser.AddParser(elemType, customParser2);
			Assert::IsTrue(customParser2 == parser.GetParser(elemType));

			// remove custom parser twice. shouldn't throw
			parser.RemoveParser(elemType);
			Assert::IsTrue(!parser.GetParser(elemType));
			parser.RemoveParser(elemType);
			Assert::IsTrue(!parser.GetParser(elemType));

			// attempt to remove known parser. shouldn't throw, but shouldn't remove
			Assert::IsTrue((bool)parser.GetParser(ActionTypeToString(ActionType::OpenUrl)));
			parser.RemoveParser(ActionTypeToString(ActionType::OpenUrl));
			Assert::IsTrue((bool)parser.GetParser(ActionTypeToString(ActionType::OpenUrl)));
		}
	};
}
