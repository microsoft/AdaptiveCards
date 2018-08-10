#include "stdafx.h"
#include "SharedAdaptiveCard.h"
#include "SubmitAction.h"
#include "ShowCardAction.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
	TEST_CLASS(EverythingBagel)
	{
	public:
		TEST_METHOD(EverythingBagelTests)
		{
			auto parseResult = AdaptiveCard::DeserializeFromFile("EverythingBagel.json", 1.0);

			// ensure we're warning free
			{
				auto parseWarnings = parseResult->GetWarnings();
				Assert::AreEqual(0U, parseWarnings.size());
			}

			// get the card and start validating the structure
			auto everythingBagel = parseResult->GetAdaptiveCard();
			
			// validate actions
			{
				auto actions = everythingBagel->GetActions();
				Assert::AreEqual(2U, actions.size());

				// validate submit action
				{
					auto submitAction = std::static_pointer_cast<SubmitAction>(actions.at(0));
					Assert::IsTrue(submitAction->GetElementType() == ActionType::Submit);
					Assert::AreEqual(ActionTypeToString(ActionType::Submit), submitAction->GetElementTypeString());
					Assert::AreEqual(""s, submitAction->GetIconUrl());
					Assert::AreEqual("Action.Submit_id"s, submitAction->GetId());
					Assert::AreEqual("Action.Submit"s, submitAction->GetTitle());
					//Logger::WriteMessage("Submit Data: '"s.append(submitAction->GetDataJson()).append("'").c_str());
					Assert::AreEqual("{\n   \"submitValue\" : true\n}\n"s, submitAction->GetDataJson());

					auto additionalProps = submitAction->GetAdditionalProperties();
					Assert::IsTrue(additionalProps.empty());

					std::vector<RemoteResourceInformation> resourceUris;
					submitAction->GetResourceInformation(resourceUris);
					Assert::AreEqual(0U, resourceUris.size());
				}

				// validate showcard action
				{
					auto showCardAction = std::static_pointer_cast<ShowCardAction>(actions.at(1));
					Assert::IsTrue(showCardAction->GetElementType() == ActionType::ShowCard);
					Assert::AreEqual(ActionTypeToString(ActionType::ShowCard), showCardAction->GetElementTypeString());
					Assert::AreEqual(""s, showCardAction->GetIconUrl());
					Assert::AreEqual("Action.ShowCard_id"s, showCardAction->GetId());
					Assert::AreEqual("Action.ShowCard"s, showCardAction->GetTitle());

					auto additionalProps = showCardAction->GetAdditionalProperties();
					Assert::IsTrue(additionalProps.empty());

					std::vector<RemoteResourceInformation> resourceUris;
					showCardAction->GetResourceInformation(resourceUris);
					Assert::AreEqual(0U, resourceUris.size());

					// validate the subcard
					{
						auto subCard = std::static_pointer_cast<AdaptiveCard>(showCardAction->GetCard());
						Assert::AreEqual(0U, subCard->GetActions().size());
						Assert::AreEqual(""s, subCard->GetBackgroundImage());
						Assert::IsTrue(CardElementType::AdaptiveCard == subCard->GetElementType());
						Assert::AreEqual(""s, subCard->GetFallbackText());
						Assert::IsTrue(HeightType::Auto == subCard->GetHeight());
						Assert::AreEqual("en"s, subCard->GetLanguage());
						Assert::AreEqual(""s, subCard->GetSpeak());
						Assert::IsTrue(ContainerStyle::None == subCard->GetStyle());
						Assert::AreEqual(""s, subCard->GetVersion());
						Assert::IsTrue(VerticalContentAlignment::Top == subCard->GetVerticalContentAlignment());

						auto selectAction = subCard->GetSelectAction();
						Assert::IsTrue(!selectAction);

						//Logger::WriteMessage("Submit Data: '"s.append(subCard->Serialize()).append("'").c_str());
						Assert::AreEqual("{\"actions\":[],\"body\":[{\"isSubtle\":true,\"text\":\"Action.ShowCard text\",\"type\":\"TextBlock\"}],\"lang\":\"en\",\"type\":\"AdaptiveCard\",\"version\":\"\"}\n"s,
							subCard->Serialize());
					}
				}
			}
		}
	};
}