#include "stdafx.h"
#include "CppUnitTest.h"
#include "Fact.h"
#include <Windows.h>
#include <StrSafe.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest {
	TEST_CLASS(FactTest) {
	public:
		TEST_METHOD(DefineFromEmptyConstructor) {
			Fact emptyFact;
			Assert::IsTrue(emptyFact.GetTitle().empty());

			//Define & test title
			string testTitle = "1 Example Title!";
			emptyFact.SetTitle(testTitle);
			Assert::AreEqual(testTitle, emptyFact.GetTitle());

			//Define & test value
			string testValue = "1 Example Value!";
			emptyFact.SetValue(testValue);
			Assert::AreEqual(testValue, emptyFact.GetValue());
		}

		TEST_METHOD() {	
		}
	};
}