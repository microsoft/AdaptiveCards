#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Short)}}";
			Assert::AreEqual<string>("DATE(2017-02-13T20:46:30Z, Short)", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod2)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "fjdkslj{ {DATE(2017-02-13T20:46:30Z, Short)}}fjdkslj";
			Assert::AreEqual<string>("", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod3)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "fjdkslj{fjdk{DATE(2017-02-13T20:46:30Z, Short)}}fjdkslj";
			Assert::AreEqual<string>("", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod4)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "fjdkslj{{DATE(2017-02-13T20:46:30Z, Short)}}fjdkslj";
			Assert::AreEqual<string>("DATE(2017-02-13T20:46:30Z, Short)", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod5)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "fjdkslj{{DATE(2017-02-13T20:46:30Z, Short)}lkjlk}";
			Assert::AreEqual<string>("DATE(2017-02-13T20:46:30Z, Short)", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod6)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Short)";
			Assert::AreEqual<string>("DATE(2017-02-13T20:46:30Z, Short)", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod7)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "fjdkslj{ {DATE(2017-02-13T20:46:30Z, Short";
			Assert::AreEqual<string>("", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}
		TEST_METHOD(TestMethod8)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "";
			Assert::AreEqual<string>("", blck->scanForDateAndTime(testString), nullptr, nullptr);
			delete blck;
		}

		TEST_METHOD(TransformToDateTest1)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-02-13T20:46:30Z, Short";
			string date = blck->localizeDate(testString.begin(), testString.end());
			Assert::AreEqual<string>("2/13/2017", date);
			delete blck;
		}

		TEST_METHOD(TransformToDateTestLong)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-02-13T20:46:30Z, Long";
			string date = blck->localizeDate(testString.begin(), testString.end());
			Assert::AreEqual<string>("Monday, Feburary 13, 2017", date);
			delete blck;
		}
	};
}
