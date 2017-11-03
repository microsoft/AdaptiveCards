#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{        
    TEST_CLASS(DateAndTimeTest)
    {
    public:
        TEST_METHOD(ISO8601TransformTest)
        {
            TextBlock blck;
            blck.SetText("{{DATE(2017-02-13T20:46:30Z, SHORT)}}");
            Assert::AreEqual<string>("02/13/17",  blck.GetText());
        }
        TEST_METHOD(ISO8601TransformTestLONG)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("Monday, February 13, 2017", blck.GetText());
        }
        TEST_METHOD(ISO8601TransformTestSmallCaseLONG)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("Monday, February 13, 2017", blck.GetText());
        }
        TEST_METHOD(ISO8601TransformTestDefault)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("02/13/17", blck.GetText());
        }

        TEST_METHOD(ISO8601TransformBadInputTest)
        {
            TextBlock blck;
            string testString = "{a{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{a{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }

        TEST_METHOD(ISO8601TransformBadInputTestMissingClosingCurlyBracket)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, SHORT)}", blck.GetText());
        }

        TEST_METHOD(ISO8601TransformBadInputTestBadYear)
        {
            TextBlock blck;
            string testString = "{{DATE(2017a02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017a02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }

        TEST_METHOD(TransformToDateTest1)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("02/13/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateTest2)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-27T18:19:09Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("11:19:09 AM", blck.GetText());
        }
        TEST_METHOD(TransformToDateTest3)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T01:47:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }
        TEST_METHOD(TransformToTimeTest)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-28T02:17:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:17:00 PM", blck.GetText());
        }
        TEST_METHOD(TransformToDateTest4)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T02:17:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }
        TEST_METHOD(TransformToTimeTest1)
        {
            TextBlock blck;
            // paris
            string testString = "{{TIME(2017-10-28T04:20:00+02:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:20:00 PM", blck.GetText());
        }
        TEST_METHOD(TransformToDateTest5)
        {
            TextBlock blck;
            // paris
            string testString = "{{DATE(2017-10-28T04:20:00+02:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToTimeTest3)
        {
            TextBlock blck;
            // seoul 
            string testString = "{{TIME(2017-10-28T11:25:00+09:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:25:00 PM", blck.GetText());
        }

        TEST_METHOD(TransformToDateTest6)
        {
            TextBlock blck;
            // seoul 
            string testString = "{{DATE(2017-10-28T11:25:00+09:00, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("Friday, October 27, 2017", blck.GetText());
        }

        TEST_METHOD(TransformToTimeTest4)
        {
            TextBlock blck;
            // New York 
            string testString = "{{TIME(2017-10-27T22:27:00-04:00, SHORT)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<string>("07:27:00 PM", blck.GetText());
        }
        TEST_METHOD(TransformToDateTest7)
        {
            TextBlock blck;
            // New York 
            string testString = "{{DATE(2017-10-27T22:27:00-04:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }
        TEST_METHOD(mallformedinputTest1)
        {
            TextBlock blck;
            // New York 
            string testString = "{{TIME(2017-10-27T22:7:00-04:00, SHORT)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T22:7:00-04:00, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(mallformedinputTest2)
        {
            TextBlock blck;
            // New York 
            string testString = "{{TIME(2017-10-27T2:7:00Q04:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T2:7:00Q04:00, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(ISO8601WithText)
        {
            TextBlock blck;
            // New York 
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("You have arrived in New York on 10/27/17", blck.GetText());
        }

        TEST_METHOD(TwoISO8601WithText)
        {
            TextBlock blck;
            // New York 
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("You have arrived in New York on 10/27/17 at 07:27:00 PM", blck.GetText());
        }

        TEST_METHOD(prefixStringISO8650sufixStringTest)
        {
            TextBlock blck;
            // New York 
            string testString = "You will arrived in Seattle on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}}; have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<string>("You will arrived in Seattle on 10/27/17; have a good trip", blck.GetText());
        }
    };
}
