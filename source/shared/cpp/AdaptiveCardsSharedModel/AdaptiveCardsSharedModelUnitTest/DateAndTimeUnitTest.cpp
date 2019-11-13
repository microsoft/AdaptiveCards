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

// Use this macro to effectively skip a test when run outside of the Pacific timezone
#define SKIP_TEST_IF_NEEDED()                                           \
    {                                                                   \
    TIME_ZONE_INFORMATION tz{};                                         \
    GetTimeZoneInformation(&tz);                                        \
    if (tz.Bias == 480l)                                        \
    {                                                                   \
        Logger::WriteMessage(L"In Pacific timezone. Running test.");    \
    }                                                                   \
    else                                                                \
    {                                                                   \
        Logger::WriteMessage(L"Skipping test for non-Pacific timezone"); \
        return;                                                         \
    }                                                                   \
    }

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(TimeTest)
    {
    public:
        TEST_METHOD(TransformToTimeTest)
        {
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T22:07:00Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:07:00Z, SHORT)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormat)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            // New York
            // New York
            std::string testString = "{{TIME(2017-10-27T22:27:00-04:00, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:27:00-04:00, LONG)}}", blck.GetText());
        }
        TEST_METHOD(TimeWithLongFormatInText)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            // New York
            std::string testString = "Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("Hello {{TIME(2017-10-27T26:27:00Z, LONG)}} World!", blck.GetText());
        }
        TEST_METHOD(MissingLeadingDigitOfMinutesInputTest)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T22:7:00-04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T22:7:00-04:00)}}", blck.GetText());
        }
        TEST_METHOD(MissingColumnDelimiterTest)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            // New York
            std::string testString = "{{TIME(2017-10-27T2:7:00Q04:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-10-27T2:7:00Q04:00)}}", blck.GetText());
        }
        TEST_METHOD(ISO8601WithTextTest)
        {
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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

        TEST_METHOD(prefixStringISO8650suffixStringTest)
        {
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            std::string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-02-13T20:46:30Z, Long)}}", blck.GetText());
        }
        TEST_METHOD(InvalidDateTest)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            std::string testString = "{{DATE(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{DATE(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(InvalidTimeTest)
        {
            SKIP_TEST_IF_NEEDED();
            TextBlock blck;
            std::string testString = "{{TIME(2017-99-14T06:08:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<std::string>("{{TIME(2017-99-14T06:08:00Z)}}", blck.GetText());
        }
        TEST_METHOD(LeapYearValidDayTest)
        {
            SKIP_TEST_IF_NEEDED();
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
            SKIP_TEST_IF_NEEDED();
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
