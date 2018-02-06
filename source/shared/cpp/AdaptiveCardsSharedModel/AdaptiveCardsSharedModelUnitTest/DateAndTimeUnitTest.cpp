#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(TimeTest)
    {
    public:
        TEST_METHOD(TransformToTimeTest)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-28T02:17:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:17 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeTest2)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-27T18:19:09Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("11:19 AM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithSmallPositiveOffsetTest)
        {
            TextBlock blck;
            // paris
            string testString = "{{TIME(2017-10-28T04:20:00+02:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:20 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithLargePositiveOffsetTest)
        {
            TextBlock blck;
            // seoul
            string testString = "{{TIME(2017-10-28T11:25:00+09:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("07:25 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithMinusOffsetTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:27:00-04:00)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<string>("07:27 PM", blck.GetText());
        }
    };
    TEST_CLASS(DateTest)
    {
    public:
        TEST_METHOD(TransformDateTest)
        {
            TextBlock blck;
            blck.SetText("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::AreEqual<string>("02/13/17",  blck.GetText());
        }

        TEST_METHOD(TransformToDateWithSmallPositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateWithLargePositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}";
            // New York
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateNegativeOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateRespectsOptionalSpace)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateOnlyAllowsUpToOneSpaceBeforeModifier)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>(testString, blck.GetText());
        }
    };
    TEST_CLASS(TimeAndDateInputTest)
    {
    public:
        TEST_METHOD(TimeWithShortFormat)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:07:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T22:07:00Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormat)
        {
            TextBlock blck;
            // New York
            // New York 
            string testString = "{{TIME(2017-10-27T22:27:00-04:00, LONG)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T22:27:00-04:00, LONG)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormatInText)
        {
            TextBlock blck;
            // New York
            string testString = "Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!";
            blck.SetText(testString);
            Assert::AreEqual<string>("Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!", blck.GetText());
        }
        TEST_METHOD(MissingLeadingDigitOfMinutesInputTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:7:00-04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T22:7:00-04:00)}}", blck.GetText());
        }
        TEST_METHOD(MissingColumnDelimiterTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T2:7:00Q04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T2:7:00Q04:00)}}", blck.GetText());
        }
        TEST_METHOD(ISO8601WithTextTest)
        {
            TextBlock blck;
            // New York
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:23:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("You have arrived in New York on Fri, Oct 27, 2017", blck.GetText());
        }

        TEST_METHOD(TwoISO8601WithText)
        {
            TextBlock blck;
            // New York
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<string>("You have arrived in New York on Fri, Oct 27, 2017 at 07:27 PM.\r have a good trip", blck.GetText());
        }

        TEST_METHOD(prefixStringISO8650sufixStringTest)
        {
            TextBlock blck;
            // New York
            string testString = "You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<string>("You will arrived in Seattle on Fri, Oct 27, 2017; have a good trip", blck.GetText());
        }

        TEST_METHOD(MalformedCurlybracketsTest)
        {
            TextBlock blck;
            string testString = "{a{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{a{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(MissingClosingCurlyBracketTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, SHORT)}", blck.GetText());
        }
        TEST_METHOD(YearInBadFormatInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017a02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017a02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(DateDefaultStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("02/13/17", blck.GetText());
        }
        TEST_METHOD(DateLONGStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("Monday, February 13, 2017", blck.GetText());
        }
        TEST_METHOD(DateSHORTStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("Mon, Feb 13, 2017", blck.GetText());
        }
        TEST_METHOD(DateSmallCaseLONGStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, Long)}}", blck.GetText());
        }
        TEST_METHOD(InvalidDateTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(InvalidTimeTest)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            string testString = "{{DATE(1992-02-29T18:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("02/29/92", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayOnlyAtUTCTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            string testString = "{{DATE(1992-02-29T07:59:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("02/28/92", blck.GetText());
        }
        TEST_METHOD(NoneLeapYearInvalidDayTest)
        {
            TextBlock blck;
            string testString = "{{DATE(1994-02-29T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(1994-02-29T06:08:00Z)}}", blck.GetText());
        }
    };

}
