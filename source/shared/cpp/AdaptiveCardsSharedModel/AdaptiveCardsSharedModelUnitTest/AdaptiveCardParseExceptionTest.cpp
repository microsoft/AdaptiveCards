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
	TEST_CLASS(AdaptiveCardParseExceptionTests)
	{
	public:
		TEST_METHOD(AdaptiveCardParseExceptionTest)
		{
			std::string errorMessage("error message");
			auto parseException = std::make_unique<AdaptiveCardParseException>(ErrorStatusCode::InvalidJson, errorMessage);
			Assert::AreEqual(parseException->what(), errorMessage.c_str());
			Assert::IsTrue(parseException->GetStatusCode() == ErrorStatusCode::InvalidJson);
			Assert::AreEqual(parseException->GetReason(), errorMessage);
		}

		TEST_METHOD(AdaptiveCardParseWarningTest)
		{
			std::string errorMessage("error message");
			auto parseWarning = std::make_unique<AdaptiveCardParseWarning>(WarningStatusCode::AssetLoadFailed, errorMessage);
			Assert::IsTrue(parseWarning->GetStatusCode() == WarningStatusCode::AssetLoadFailed);
			Assert::AreEqual(parseWarning->GetReason(), errorMessage);
		}
	};
}
