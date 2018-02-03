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
            Assert::AreEqual<wstring>(L"07:17 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeTest2)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-27T18:19:09Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"11:19 AM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithSmallPositiveOffsetTest)
        {
            TextBlock blck;
            // paris
            string testString = "{{TIME(2017-10-28T04:20:00+02:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"07:20 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithLargePositiveOffsetTest)
        {
            TextBlock blck;
            // seoul
            string testString = "{{TIME(2017-10-28T11:25:00+09:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"07:25 PM", blck.GetText());
        }
        TEST_METHOD(TransformToTimeWithMinusOffsetTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:27:00-04:00)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"07:27 PM", blck.GetText());
        }
    };
    TEST_CLASS(DateTest)
    {
    public:
        TEST_METHOD(TransformDateTest)
        {
            TextBlock blck;
            blck.SetText("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::AreEqual<wstring>(L"02/13/17",  blck.GetText());
        }

        TEST_METHOD(TransformToDateWithSmallPositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateWithLargePositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}";
            // New York
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateNegativeOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateRespectsOptionalSpace)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"10/27/17", blck.GetText());
        }

        TEST_METHOD(TransformToDateOnlyAllowsUpToOneSpaceBeforeModifier)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}", blck.GetText());
        }

        TEST_METHOD(TransformDateToMultipleLanguagesShort)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-14T06:08:00Z, SHORT)}}";
            blck.SetText(testString);

            std::vector<std::string> languagesArray = {
                "zh-CN",  // Mandarin
                "en-US",  // English
                "es-MX",  // Spanish
                "hi-IN",  // Hindi
                "ar-EG",  // Arabic
                "id-ID",  // Indonesian
                "fr-FR",  // French
                "bn-BD", // Bengali
                "pt-BR", // Portuguese
                "ru-RU",  // Russian
                "de-DE",  // German
                "ja-JP",  // Japanese
                "pa-PK",  // Punjabi
                "te-IN",  // Telugu
                "ko-KR"   // Korean 
            };

            std::vector<std::wstring> expectedResultsArray =
            {
                L"周一, 2月 13, 2017",
                L"Mon, Feb 13, 2017",
                L"lun., feb. 13, 2017",
                L"सोम., फरवरी 13, 2017",
                L"الإثنين, فبراير 13, 2017",
                L"Sen, Feb 13, 2017",
                L"lun., févr. 13, 2017",
                L"সোম, ফেব্রুয়ারী 13, 2017",
                L"seg, fev 13, 2017",
                L"Пн, фев 13, 2017",
                L"Mo, Feb 13, 2017",
                L"月, 2 13, 2017",
                L"ਸੋਮ., ਫ਼ਰਵਰੀ 13, 2017",
                L"సోమ., ఫిబ్రవరి 13, 2017", // May be wrong, check
                L"월, 2 13, 2017"
            };

            for (size_t i{}; i < languagesArray.size(); ++i)
            {
                std::locale lang = std::locale(languagesArray[i]);
                blck.SetLanguage(lang);
                Assert::AreEqual<wstring>(expectedResultsArray[i], blck.GetText());
            }
        }

        TEST_METHOD(TransformDateToMultipleLanguagesLong)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00Z, LONG)}}";
            blck.SetText(testString);
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
            Assert::AreEqual<wstring>(L"{{TIME(2017-10-27T22:07:00Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormat)
        {
            TextBlock blck;
            // New York
            // New York 
            string testString = "{{TIME(2017-10-27T22:27:00-04:00, LONG)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{TIME(2017-10-27T22:27:00-04:00, LONG)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormatInText)
        {
            TextBlock blck;
            // New York
            string testString = "Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!", blck.GetText());
        }
        TEST_METHOD(MissingLeadingDigitOfMinutesInputTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:7:00-04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{TIME(2017-10-27T22:7:00-04:00)}}", blck.GetText());
        }
        TEST_METHOD(MissingColumnDelimiterTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T2:7:00Q04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{TIME(2017-10-27T2:7:00Q04:00)}}", blck.GetText());
        }
        TEST_METHOD(ISO8601WithTextTest)
        {
            TextBlock blck;
            // New York
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:23:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"You have arrived in New York on Fri, Oct 27, 2017", blck.GetText());
        }

        TEST_METHOD(TwoISO8601WithText)
        {
            TextBlock blck;
            // New York
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"You have arrived in New York on Fri, Oct 27, 2017 at 07:27 PM.\r have a good trip", blck.GetText());
        }

        TEST_METHOD(prefixStringISO8650sufixStringTest)
        {
            TextBlock blck;
            // New York
            string testString = "You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"You will arrived in Seattle on Fri, Oct 27, 2017; have a good trip", blck.GetText());
        }

        TEST_METHOD(MalformedCurlybracketsTest)
        {
            TextBlock blck;
            string testString = "{a{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{a{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(MissingClosingCurlyBracketTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(2017-02-13T20:46:30Z, SHORT)}", blck.GetText());
        }
        TEST_METHOD(YearInBadFormatInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017a02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(2017a02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(DateDefaultStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"02/13/17", blck.GetText());
        }
        TEST_METHOD(DateLONGStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"Monday, February 13, 2017", blck.GetText());
        }
        TEST_METHOD(DateSHORTStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"Mon, Feb 13, 2017", blck.GetText());
        }
        TEST_METHOD(DateSmallCaseLONGStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(2017-02-13T20:46:30Z, Long)}}", blck.GetText());
        }
        TEST_METHOD(InvalidDateTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(InvalidTimeTest)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{TIME(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            string testString = "{{DATE(1992-02-29T18:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"02/29/92", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayOnlyAtUTCTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            string testString = "{{DATE(1992-02-29T07:59:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"02/28/92", blck.GetText());
        }
        TEST_METHOD(NoneLeapYearInvalidDayTest)
        {
            TextBlock blck;
            string testString = "{{DATE(1994-02-29T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<wstring>(L"{{DATE(1994-02-29T06:08:00Z)}}", blck.GetText());
        }
    };

}
