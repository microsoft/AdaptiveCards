// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "AdaptiveCardParseException.h"
#include "AdaptiveCardParseWarning.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

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
