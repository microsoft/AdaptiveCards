// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "Column.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ElementTest)
    {
    public:
        TEST_METHOD(ColumnPixelWidthTest)
        {
            auto columnTest = std::make_shared<AdaptiveCards::Column>();
            Assert::AreEqual(0, columnTest->GetPixelWidth());
            Assert::AreEqual("Auto"s, columnTest->GetWidth());
<<<<<<< HEAD
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"Auto\"}\n"s, columnTest->Serialize());

            columnTest->SetWidth("20px"s);
            Assert::AreEqual(20, columnTest->GetPixelWidth());
            Assert::AreEqual("20px"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"20px\"}\n"s, columnTest->Serialize());

            columnTest->SetPixelWidth(40);
            Assert::AreEqual(40, columnTest->GetPixelWidth());
            Assert::AreEqual("40px"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"40px\"}\n"s, columnTest->Serialize());

            columnTest->SetWidth("Stretch");
            Assert::AreEqual(0, columnTest->GetPixelWidth());
            Assert::AreEqual("stretch"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"stretch\"}\n"s, columnTest->Serialize());
=======
            columnTest->SetWidth("20px"s);
            Assert::AreEqual(20, columnTest->GetPixelWidth());
            Assert::AreEqual("20px"s, columnTest->GetWidth());
            columnTest->SetPixelWidth(40);
            Assert::AreEqual(40, columnTest->GetPixelWidth());
            Assert::AreEqual("40px"s, columnTest->GetWidth());
>>>>>>> fee0c0319... [Shared] Reflect changes between width and pixel width (#3317)
        }
    };
}
