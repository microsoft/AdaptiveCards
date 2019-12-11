// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "TextBlock.h"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <time.h>
#include <StrSafe.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    static TIME_ZONE_INFORMATION tzOriginal{};
    static bool changedTime = false;

    void EnableTimeZoneChange(bool set)
    {
        HANDLE hToken;
        TOKEN_PRIVILEGES tkp;

        OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
        LookupPrivilegeValue(NULL, SE_TIME_ZONE_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = set?SE_PRIVILEGE_ENABLED:0;
        if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0))
        {
            Logger::WriteMessage("Could not get the permissions to changes the timezone");
        }
    }

    // Time tests assume a Pacific Timezone. Make sure that we're
    // setting it up appropriately for the run of the tests.
    TEST_MODULE_INITIALIZE(InitializeTimeZone)
    {
        GetTimeZoneInformation(&tzOriginal);
        changedTime = false;
        // Don't do this if we're already on the right timezone
        if (tzOriginal.Bias != 480)
        {
            Logger::WriteMessage("Changing TimeZone to Seattle");
            TIME_ZONE_INFORMATION tzSeattle = { 0 };
            tzSeattle.Bias = 480;
            StringCchCopy(tzSeattle.StandardName, 32, L"Test Standard Zone");
            tzSeattle.StandardDate.wMonth = 11;
            tzSeattle.StandardDate.wDayOfWeek = 0;
            tzSeattle.StandardDate.wDay = 1;
            tzSeattle.StandardDate.wHour = 2;

            StringCchCopy(tzSeattle.DaylightName, 32, L"Test Daylight Zone");
            tzSeattle.DaylightDate.wMonth = 3;
            tzSeattle.DaylightDate.wDayOfWeek = 0;
            tzSeattle.DaylightDate.wDay = 2;
            tzSeattle.DaylightDate.wHour = 2;
            tzSeattle.DaylightBias = -60;

            EnableTimeZoneChange(true);
            bool timeZoneChanged = SetTimeZoneInformation(&tzSeattle);
            EnableTimeZoneChange(false);
            if (!timeZoneChanged)
            {
                Assert::Fail(L"Could not change the timezone");
            }
            changedTime = true;
        }
    }

    // Reset the timezone on the machine to the original one.
    TEST_MODULE_CLEANUP(CleanupTimeZone)
    {
        if (changedTime)
        {
            Logger::WriteMessage("Resetting TimeZone");

            EnableTimeZoneChange(true);
            SetTimeZoneInformation(&tzOriginal);
            EnableTimeZoneChange(false);
            changedTime = false;
        }
    }


    TEST_CLASS(TimeTest)
    {
    public:
        TEST_METHOD(TransformToTimeTest)
        {
            TextBlock blck;
            std::string testString = "{{TIME(2017-10-28T02:17:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-28T02:17:00Z)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().front()->GetText(), "07:17 PM");
            Assert::IsTrue(preparser.GetTextTokens().front()->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }
        TEST_METHOD(TransformToTimeTest2)
        {
            TextBlock blck;
            std::string testString = "{{TIME(2017-10-27T18:19:09Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T18:19:09Z)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().front()->GetText(), "11:19 AM");
            Assert::IsTrue(preparser.GetTextTokens().front()->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }
        TEST_METHOD(TransformToTimeWithSmallPositiveOffsetTest)
        {
            TextBlock blck;
            // paris
            std::string testString = "{{TIME(2017-10-28T04:20:00+02:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-28T04:20:00+02:00)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().front()->GetText(), "07:20 PM");
            Assert::IsTrue(preparser.GetTextTokens().front()->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }
        TEST_METHOD(TransformToTimeWithLargePositiveOffsetTest)
        {
            TextBlock blck;
            // seoul
            std::string testString = "{{TIME(2017-10-28T11:25:00+09:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-28T11:25:00+09:00)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().front()->GetText(), "07:25 PM");
            Assert::IsTrue(preparser.GetTextTokens().front()->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }
        TEST_METHOD(TransformToTimeWithMinusOffsetTest)
        {
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T22:27:00-04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:27:00-04:00)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().front()->GetText(), "07:27 PM");
            Assert::IsTrue(preparser.GetTextTokens().front()->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }
    };
    TEST_CLASS(DateTest)
    {
    public:
        TEST_METHOD(TransformDateTest)
        {
            TextBlock blck;
            blck.SetText("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}",  blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::IsTrue(token->GetDay() == 13 && token->GetMonth() == 1 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateWithSmallPositiveOffset)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}");
            Assert::IsTrue(token->GetDay() == 27 && token->GetMonth() == 9 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateWithLargePositiveOffset)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}";
            // New York
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}");
            Assert::IsTrue(token->GetDay() == 27 && token->GetMonth() == 9 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateNegativeOffset)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}");
            Assert::IsTrue(token->GetDay() == 27 && token->GetMonth() == 9 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateRespectsOptionalSpace)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}");
            Assert::IsTrue(token->GetDay() == 27 && token->GetMonth() == 9 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateOnlyAllowsUpToOneSpaceBeforeModifier)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}", blck.GetText());
        }

    };
    TEST_CLASS(TimeAndDateInputTest)
    {
    public:
        TEST_METHOD(TimeWithShortFormat)
        {
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T22:07:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:07:00Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormat)
        {
            TextBlock blck;
            // New York
            // New York
            std::string testString = "{{TIME(2017-10-27T22:27:00-04:00, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:27:00-04:00, LONG)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormatInText)
        {
            TextBlock blck;
            // New York
            std::string testString = "Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!", blck.GetText());
        }
        TEST_METHOD(MissingLeadingDigitOfMinutesInputTest)
        {
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T22:7:00-04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:7:00-04:00)}}", blck.GetText());
        }
        TEST_METHOD(MissingColumnDelimiterTest)
        {
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T2:7:00Q04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T2:7:00Q04:00)}}", blck.GetText());
        }
        TEST_METHOD(ISO8601WithTextTest)
        {
            TextBlock blck;
            // New York
            std::string testString = "You have arrived in New York on {{DATE(2017-10-27T22:23:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("You have arrived in New York on {{DATE(2017-10-27T22:23:00Z, SHORT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            Assert::AreEqual<std::string>(preparser.GetTextTokens().back()->GetText(), "{{DATE(2017-10-27T22:23:00Z, SHORT)}}");
            // Assert::AreEqual<std::string>(preparser.GetTextTokens().back()->GetText(), "9/27/2017");
            Assert::IsTrue(preparser.GetTextTokens().back()->GetFormat() == DateTimePreparsedTokenFormat::DateShort);
        }

        TEST_METHOD(TwoISO8601WithText)
        {
            TextBlock blck;
            // New York
            std::string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip", blck.GetText());

            DateTimePreparser block = blck.GetTextForDateParsing();
            const auto& tokens = block.GetTextTokens();

            Assert::AreEqual<std::string>(tokens[0]->GetText(), "You have arrived in New York on ");
            Assert::IsTrue(tokens[0]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);

            Assert::AreEqual<std::string>(tokens[1]->GetText(), "{{DATE(2017-10-27T22:27:00-04:00, SHORT)}}");
            Assert::IsTrue(tokens[1]->GetDay() == 27 && tokens[1]->GetMonth() == 9 && tokens[1]->GetYear() == 2017);
            Assert::IsTrue(tokens[1]->GetFormat() == DateTimePreparsedTokenFormat::DateShort);

            Assert::AreEqual<std::string>(tokens[2]->GetText(), " at ");
            Assert::IsTrue(tokens[2]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);

            Assert::AreEqual<std::string>(tokens[3]->GetText(), "07:27 PM");
            Assert::IsTrue(tokens[3]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);

            Assert::AreEqual<std::string>(tokens[4]->GetText(), ".\r have a good trip");
            Assert::IsTrue(tokens[4]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }

        TEST_METHOD(prefixStringISO8650sufixStringTest)
        {
            TextBlock blck;
            // New York
            std::string testString = "You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            const auto& tokens = preparser.GetTextTokens();

            Assert::AreEqual<std::string>(tokens[0]->GetText(), "You will arrived in Seattle on ");
            Assert::IsTrue(tokens[0]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);

            Assert::AreEqual<std::string>(tokens[1]->GetText(), "{{DATE(2017-10-27T22:23:00Z, SHORT)}}");
            Assert::IsTrue(tokens[1]->GetDay() == 27 && tokens[1]->GetMonth() == 9 && tokens[1]->GetYear() == 2017);
            Assert::IsTrue(tokens[1]->GetFormat() == DateTimePreparsedTokenFormat::DateShort);

            Assert::AreEqual<std::string>(tokens[2]->GetText(), "; have a good trip");
            Assert::IsTrue(tokens[2]->GetFormat() == DateTimePreparsedTokenFormat::RegularString);
        }

        TEST_METHOD(MalformedCurlybracketsTest)
        {
            TextBlock blck;
            std::string testString = "{a{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{a{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(MissingClosingCurlyBracketTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, SHORT)}", blck.GetText());
        }
        TEST_METHOD(YearInBadFormatInputTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017a02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017a02-13T20:46:30Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(DateDefaultStyleInputTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-02-13T20:46:30Z)}}");
            Assert::IsTrue(token->GetDay() == 13 && token->GetMonth() == 1 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }
        TEST_METHOD(DateLONGStyleInputTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, LONG)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-02-13T20:46:30Z, LONG)}}");
            Assert::IsTrue(token->GetDay() == 13 && token->GetMonth() == 1 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateLong);
        }
        TEST_METHOD(DateSHORTStyleInputTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(2017-02-13T20:46:30Z, SHORT)}}");
            Assert::IsTrue(token->GetDay() == 13 && token->GetMonth() == 1 && token->GetYear() == 2017);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateShort);
        }
        TEST_METHOD(DateSmallCaseLONGStyleInputTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, Long)}}", blck.GetText());
        }
        TEST_METHOD(InvalidDateTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(InvalidTimeTest)
        {
            TextBlock blck;
            std::string testString = "{{TIME(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            std::string testString = "{{DATE(1992-02-29T18:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(1992-02-29T18:08:00Z)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(1992-02-29T18:08:00Z)}}");
            Assert::IsTrue(token->GetDay() == 29 && token->GetMonth() == 1 && token->GetYear() == 1992);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }
        TEST_METHOD(LeapYearValidDayOnlyAtUTCTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            std::string testString = "{{DATE(1992-02-29T07:59:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(1992-02-29T07:59:00Z)}}", blck.GetText());

            DateTimePreparser preparser = blck.GetTextForDateParsing();
            std::shared_ptr<DateTimePreparsedToken> token(preparser.GetTextTokens().front());
            Assert::AreEqual<std::string>(token->GetText(), "{{DATE(1992-02-29T07:59:00Z)}}");
            Assert::IsTrue(token->GetDay() == 28 && token->GetMonth() == 1 && token->GetYear() == 1992);
            Assert::IsTrue(token->GetFormat() == DateTimePreparsedTokenFormat::DateCompact);
        }
        TEST_METHOD(NoneLeapYearInvalidDayTest)
        {
            TextBlock blck;
            std::string testString = "{{DATE(1994-02-29T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(1994-02-29T06:08:00Z)}}", blck.GetText());
        }
    };

}
