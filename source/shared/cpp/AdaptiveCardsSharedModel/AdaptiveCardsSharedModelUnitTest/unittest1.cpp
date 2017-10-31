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
		TEST_METHOD(ISO8601TransformTest)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Short)}}";
            bool isDate = false;
            string::const_iterator begin = testString.begin(), end = testString.end();
			Assert::AreEqual<string>("02/13/2017", blck->parseISO8601(begin, end));
			delete blck;
		}
		TEST_METHOD(ISO8601TransformTestLong)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            bool isDate = false;
            string::const_iterator begin = testString.begin(), end = testString.end();
			Assert::AreEqual<string>("Monday, February 13, 2017", blck->parseISO8601(begin, end));
			delete blck;
		}
		TEST_METHOD(ISO8601TransformTestDefault)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
            bool isDate = false;
            string::const_iterator begin = testString.begin(), end = testString.end();
			Assert::AreEqual<string>("02/13/2017", blck->parseISO8601(begin, end));
			delete blck;
		}
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
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_hour = 12;
				expected.tm_min = 46;
				expected.tm_sec = 30;
				expected.tm_year = 117;
				expected.tm_mon = 1;
				expected.tm_mday = 13;
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

		TEST_METHOD(TransformToDateTest2)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-10-27T18:19:09Z, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 9;
				expected.tm_hour = 11;
				expected.tm_min = 19;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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
		TEST_METHOD(TransformToDateTest3)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-10-28T01:47:00Z, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 0;
				expected.tm_min = 47;
				expected.tm_hour = 18;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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
		TEST_METHOD(TransformToDateTest4)
		{
			TextBlock* blck = new TextBlock();
			string testString = "2017-10-28T02:17:00Z, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 0;
				expected.tm_min = 17;
				expected.tm_hour = 19;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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
		TEST_METHOD(TransformToDateTest5)
		{
			TextBlock* blck = new TextBlock();
			// paris
			string testString = "2017-10-28T04:20:00+02:00, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 0;
				expected.tm_min = 20;
				expected.tm_hour = 19;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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

		TEST_METHOD(TransformToDateTest6)
		{
			TextBlock* blck = new TextBlock();
			// seoul 
			string testString = "2017-10-28T11:25:00+09:00, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 0;
				expected.tm_min = 25;
				expected.tm_hour = 19;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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

		TEST_METHOD(TransformToDateTest7)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "2017-10-27T22:27:00-04:00, Short";
            struct tm result = {0};
			if(blck->ISO8601ToTm(testString.begin(), testString.end(), &result))
            {
				struct tm expected;
				expected.tm_sec = 0;
				expected.tm_min = 27;
				expected.tm_hour = 19;
				expected.tm_year = 117;
				expected.tm_mon = 9;
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
		TEST_METHOD(mallformedinputTest1)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "2017-10-27T22:7:00-04:00, Short";
            struct tm result = {0};
			try
			{
				blck->ISO8601ToTm(testString.begin(), testString.end(), &result);
			}
            catch(...)
            {
				Assert::Fail();
            }
			delete blck;
		}
		TEST_METHOD(mallformedinputTest2)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "2017-10-27T2:7:00Q04:00, Short";
            struct tm result = {0};
			try
			{
				blck->ISO8601ToTm(testString.begin(), testString.end(), &result);
			}
            catch(...)
            {
				Assert::Fail();
            }
			delete blck;
		}
	};
}
