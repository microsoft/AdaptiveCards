#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>

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
            struct tm result = {0};
			if(blck->stringToLocalTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_hour = 12;
				expected.tm_min = 46;
				expected.tm_sec = 30;
				expected.tm_year = 117;
				expected.tm_mon = 2;
				expected.tm_mday = 13;
				expected.tm_wday = 1;
				expected.tm_yday = 71;
				expected.tm_isdst = 1;

				Assert::AreEqual(0, memcmp(&expected, &result, sizeof(struct tm)));
            }
            else
            {
				Assert::Fail();
            }
			delete blck;
		}

		TEST_METHOD(TransformToDateTest2)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-10-27T18:19:09Z, Short";
            struct tm result = {0};
			if(blck->stringToLocalTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 9;
				expected.tm_hour = 11;
				expected.tm_min = 19;
				expected.tm_year = 117;
				expected.tm_mon = 10;
				expected.tm_mday = 27;
				expected.tm_wday = 0;
				expected.tm_yday = 0;
				expected.tm_isdst = 0;

				result.tm_wday = 0;
				result.tm_yday = 0;
				result.tm_isdst = 0;

				Assert::AreEqual(0, memcmp(&expected, &result, sizeof(struct tm)));
            }
            else
            {
				Assert::Fail();
            }
			delete blck;
		}
	};
}
