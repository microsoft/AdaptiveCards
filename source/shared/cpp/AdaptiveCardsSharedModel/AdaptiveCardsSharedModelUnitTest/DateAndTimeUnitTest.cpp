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
            Assert::AreEqual<string>("{{TIME(2017-10-28T02:17:00Z)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{TIME(2017-10-28T02:17:00Z)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "19:17:0");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::Time);
        }
        TEST_METHOD(TransformToTimeTest2)
        {
            TextBlock blck;
            string testString = "{{TIME(2017-10-27T18:19:09Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T18:19:09Z)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{TIME(2017-10-27T18:19:09Z)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "11:19:9");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::Time);
        }
        TEST_METHOD(TransformToTimeWithSmallPositiveOffsetTest)
        {
            TextBlock blck;
            // paris
            string testString = "{{TIME(2017-10-28T04:20:00+02:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-28T04:20:00+02:00)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{TIME(2017-10-28T04:20:00+02:00)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "19:20:0");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::Time);
        }
        TEST_METHOD(TransformToTimeWithLargePositiveOffsetTest)
        {
            TextBlock blck;
            // seoul
            string testString = "{{TIME(2017-10-28T11:25:00+09:00)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-28T11:25:00+09:00)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{TIME(2017-10-28T11:25:00+09:00)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "19:25:0");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::Time);
        }
        TEST_METHOD(TransformToTimeWithMinusOffsetTest)
        {
            TextBlock blck;
            // New York
            string testString = "{{TIME(2017-10-27T22:27:00-04:00)}}"; 
            blck.SetText(testString);
            Assert::AreEqual<string>("{{TIME(2017-10-27T22:27:00-04:00)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{TIME(2017-10-27T22:27:00-04:00)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "19:27:0");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::Time);
        }
    };
    TEST_CLASS(DateTest)
    {
    public:
        TEST_METHOD(TransformDateTest)
        {
            TextBlock blck;
            blck.SetText("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, COMPACT)}}",  blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(2017-02-13T20:46:30Z, COMPACT)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/13/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateWithSmallPositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(2017-10-28T04:20:00+02:00, COMPACT)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "9/27/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateWithLargePositiveOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}";
            // New York
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(2017-10-28T11:25:00+09:00, COMPACT)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "9/27/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateNegativeOffset)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(2017-10-27T22:27:00-04:00, COMPACT)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "9/27/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateRespectsOptionalSpace)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(2017-10-27T22:27:00-04:00,COMPACT)}}");
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "9/27/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }

        TEST_METHOD(TransformToDateOnlyAllowsUpToOneSpaceBeforeModifier)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-10-27T22:27:00-04:00,  COMPACT)}}", blck.GetText());
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
            Assert::AreEqual<string>("You have arrived in New York on {{DATE(2017-10-27T22:23:00Z, SHORT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().back()->GetOriginalText(), "{{DATE(2017-10-27T22:23:00Z, SHORT)}}");
            Assert::AreEqual<string>(block.GetString().back()->GetText(), "9/27/2017");
            Assert::IsTrue(block.GetString().back()->GetFormat() == TextSectionFormat::DateShort);
        }

        TEST_METHOD(TwoISO8601WithText)
        {
            TextBlock blck;
            // New York
            string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<string>("You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, SHORT)}} at {{TIME(2017-10-27T22:27:00-04:00)}}.\r have a good trip", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            const auto& sections = block.GetString();

            Assert::AreEqual<string>(sections[0]->GetText(), "You have arrived in New York on ");
            Assert::IsTrue(sections[0]->GetFormat() == TextSectionFormat::RegularString);

            Assert::AreEqual<string>(sections[1]->GetOriginalText(), "{{DATE(2017-10-27T22:27:00-04:00, SHORT)}}");
            Assert::AreEqual<string>(sections[1]->GetText(), "9/27/2017");
            Assert::IsTrue(sections[1]->GetFormat() == TextSectionFormat::DateShort);

            Assert::AreEqual<string>(sections[2]->GetText(), " at ");
            Assert::IsTrue(sections[2]->GetFormat() == TextSectionFormat::RegularString);

            Assert::AreEqual<string>(sections[3]->GetOriginalText(), "{{TIME(2017-10-27T22:27:00-04:00)}}");
            Assert::AreEqual<string>(sections[3]->GetText(), "19:27:0");
            Assert::IsTrue(sections[3]->GetFormat() == TextSectionFormat::Time);

            Assert::AreEqual<string>(sections[4]->GetText(), ".\r have a good trip");
            Assert::IsTrue(sections[4]->GetFormat() == TextSectionFormat::RegularString);
        }

        TEST_METHOD(prefixStringISO8650sufixStringTest)
        {
            TextBlock blck;
            // New York
            string testString = "You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip";
            blck.SetText(testString);
            Assert::AreEqual<string>("You will arrived in Seattle on {{DATE(2017-10-27T22:23:00Z, SHORT)}}; have a good trip", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            const auto& sections = block.GetString();

            Assert::AreEqual<string>(sections[0]->GetText(), "You will arrived in Seattle on ");
            Assert::IsTrue(sections[0]->GetFormat() == TextSectionFormat::RegularString);

            Assert::AreEqual<string>(sections[1]->GetOriginalText(), "{{DATE(2017-10-27T22:23:00Z, SHORT)}}");
            Assert::AreEqual<string>(sections[1]->GetText(), "9/27/2017");
            Assert::IsTrue(sections[1]->GetFormat() == TextSectionFormat::DateShort);

            Assert::AreEqual<string>(sections[2]->GetText(), "; have a good trip");
            Assert::IsTrue(sections[2]->GetFormat() == TextSectionFormat::RegularString);
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
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/13/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }
        TEST_METHOD(DateLONGStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, LONG)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, LONG)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/13/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateLong);
        }
        TEST_METHOD(DateSHORTStyleInputTest)
        {
            TextBlock blck;
            string testString = "{{DATE(2017-02-13T20:46:30Z, SHORT)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, SHORT)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/13/2017");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateShort);
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
            Assert::AreEqual<string>("{{DATE(1992-02-29T18:08:00Z)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/29/1992");
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(1992-02-29T18:08:00Z)}}");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
        }
        TEST_METHOD(LeapYearValidDayOnlyAtUTCTest)
        {
            TextBlock blck;
            // UTC and PST at Leap Year
            string testString = "{{DATE(1992-02-29T07:59:00Z)}}";
            blck.SetText(testString);
            Assert::AreEqual<string>("{{DATE(1992-02-29T07:59:00Z)}}", blck.GetText());

            TextBlockText block = blck.GetTextForDateParsing();
            Assert::AreEqual<string>(block.GetString().front()->GetText(), "1/28/1992");
            Assert::AreEqual<string>(block.GetString().front()->GetOriginalText(), "{{DATE(1992-02-29T07:59:00Z)}}");
            Assert::IsTrue(block.GetString().front()->GetFormat() == TextSectionFormat::DateCompact);
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
