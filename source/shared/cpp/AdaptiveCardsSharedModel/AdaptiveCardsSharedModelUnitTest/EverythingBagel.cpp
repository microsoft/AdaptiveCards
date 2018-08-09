#include "stdafx.h"
#include "SharedAdaptiveCard.h"

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
		}
	};
}