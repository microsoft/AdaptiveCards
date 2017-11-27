#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include "MarkDownParser.h"
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
    TEST_CLASS(EmphasisLeftDelimterTest)
    {
        TEST_METHOD(LefDelimiterTest)
        {
            MarkDownParser blck("*foo bar*");
            Assert::AreEqual<string>("<p><em>foo bar</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterTest)
        {
            MarkDownParser blck("_foo bar_");
            Assert::AreEqual<string>("<p><em>foo bar</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(LefDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser blck("* foo bar*");
            Assert::AreEqual<string>("<p>* foo bar*</p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser blck("_ foo bar_");
            Assert::AreEqual<string>("<p>_ foo bar_</p>", blck.TransformToHtml());
        }
        TEST_METHOD(LefDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser blck("a*\"foo\"*");
            Assert::AreEqual<string>("<p>a*\"foo\"*</p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser blck("a_\"foo\"_");
            Assert::AreEqual<string>("<p>a_\"foo\"_</p>", blck.TransformToHtml());
        }
        TEST_METHOD(LefDelimiterIntraWordEmphasis)
        {
            MarkDownParser blck("foo*bar*");
            Assert::AreEqual<string>("<p>foo<em>bar</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterIntraWordEmphasis)
        {
            MarkDownParser blck("foo_bar_");
            Assert::AreEqual<string>("<p>foo_bar_</p>", blck.TransformToHtml());
        }
        TEST_METHOD(LefDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser blck("5*6*78");
            Assert::AreEqual<string>("<p>5<em>6</em>78</p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser blck("5_6_78");
            Assert::AreEqual<string>("<p>5_6_78</p>", blck.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLefDelimiterCanBeProceededAndFollowedByPunct)
        {
            MarkDownParser blck("foo-_(bar)_");
            Assert::AreEqual<string>("<p>foo-<em>(bar)</em></p>", blck.TransformToHtml());
        }
    };
    TEST_CLASS(EmphasisDelimterTest)
    {
        TEST_METHOD(MatchingRightDelimiterTest)
        {
            MarkDownParser blck("_foo_");
            Assert::AreEqual<string>("<p><em>foo</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(NonMatchingDelimiterTest)
        {
            MarkDownParser blck("_foo*");
            Assert::AreEqual<string>("<p>_foo*</p>", blck.TransformToHtml());
        }
        TEST_METHOD(MatchingRightDelimiterWithSpaceTest)
        {
            MarkDownParser blck("*foo *");
            Assert::AreEqual<string>("<p>*foo *</p>", blck.TransformToHtml());
        }
        TEST_METHOD(ValidDelimtersSurroundedByPunctuationTest)
        {
            MarkDownParser blck("*(*foo*)*");
            Assert::AreEqual<string>("<p><em>(<em>foo</em>)</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(PunctuationSurroundedByDelimiterValidTest)
        {
            MarkDownParser blck("*(foo)*");
            Assert::AreEqual<string>("<p><em>(foo)</em></p>", blck.TransformToHtml());
        }
        TEST_METHOD(ValidIntraWordEmphasisTest)
        {
            MarkDownParser blck("*foo*bar");
            Assert::AreEqual<string>("<p><em>foo</em>bar</p>", blck.TransformToHtml());
        }
        TEST_METHOD(WhiteSpaceClosingEmphasisInvalidTest)
        {
            MarkDownParser blck("_foo bar _");
            Assert::AreEqual<string>("<p>_foo bar _</p>", blck.TransformToHtml());
        }
        TEST_METHOD(InvalidIntraWordEmphasisTest)
        {
            MarkDownParser blck("_foo_bar");
            Assert::AreEqual<string>("<p>_foo_bar</p>", blck.TransformToHtml());
        }
        TEST_METHOD(RightDelimiterFollowedByPunctuationValidTest)
        {
            MarkDownParser blck("_(bar)_.");
            Assert::AreEqual<string>("<p><em>(bar)</em>.</p>", blck.TransformToHtml());
        }
    };

    TEST_CLASS(StrongDelimterTest)
    {
        TEST_METHOD(SimpleValidCaseTest)
        {
            MarkDownParser blck("**foo bar**");
            Assert::AreEqual<string>("<p><strong>foo bar</strong></p>", blck.TransformToHtml());
            MarkDownParser blck1("__foo bar__");
            Assert::AreEqual<string>("<p><strong>foo bar</strong></p>", blck1.TransformToHtml());
        }
        TEST_METHOD(DelimiterWithSpaceInvalidCaseTest)
        {
            MarkDownParser blck("** foo bar**");
            Assert::AreEqual<string>("<p>** foo bar**</p>", blck.TransformToHtml());
            MarkDownParser blck1("__ foo bar__");
            Assert::AreEqual<string>("<p>__ foo bar__</p>", blck1.TransformToHtml());
            MarkDownParser blck2("**foo bar **");
            Assert::AreEqual<string>("<p>**foo bar **</p>", blck2.TransformToHtml());
            MarkDownParser blck3("__foo bar __");
            Assert::AreEqual<string>("<p>__foo bar __</p>", blck3.TransformToHtml());
        }
        TEST_METHOD(DelimiterSurroundingPuntuationInvalidCaseTest)
        {
            MarkDownParser blck("a**\"foo bar\"**");
            Assert::AreEqual<string>("<p>a**\"foo bar\"**</p>", blck.TransformToHtml());
            MarkDownParser blck2("a__\"foo bar\"__");
            Assert::AreEqual<string>("<p>a__\"foo bar\"__</p>", blck2.TransformToHtml());
        }
        TEST_METHOD(IntraWordTest)
        {
            MarkDownParser blck("**foo**bar");
            Assert::AreEqual<string>("<p><strong>foo</strong>bar</p>", blck.TransformToHtml());
            MarkDownParser blck2("__foo__bar");
            Assert::AreEqual<string>("<p>__foo__bar</p>", blck2.TransformToHtml());
        }
        TEST_METHOD(PunctuationDelimitersTest)
        {
            MarkDownParser blck("**(**foo)");
            Assert::AreEqual<string>("<p>**(**foo)</p>", blck.TransformToHtml());

            MarkDownParser blck2("__(__foo");
            Assert::AreEqual<string>("<p>__(__foo</p>", blck2.TransformToHtml());

            MarkDownParser blck3("foo-__(bar)__");
            Assert::AreEqual<string>("<p>foo-<strong>(bar)</strong></p>", blck3.TransformToHtml());

            MarkDownParser blck4("(**foo**)");
            Assert::AreEqual<string>("<p>(<strong>foo</strong>)</p>", blck4.TransformToHtml());

            MarkDownParser blck5("(__foo__)");
            Assert::AreEqual<string>("<p>(<strong>foo</strong>)</p>", blck5.TransformToHtml());

            MarkDownParser blck6("__(foo)__.");
            Assert::AreEqual<string>("<p><strong>(foo)</strong>.</p>", blck6.TransformToHtml());
        }
    };

    TEST_CLASS(DelimiterNestingTest)
    {
        TEST_METHOD(PunctuationDelimitersTest)
        {
            MarkDownParser blck("_foo __bar__ baz_");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong> baz</em></p>", blck.TransformToHtml());

            MarkDownParser blck2("*foo *bar**");
            Assert::AreEqual<string>("<p><em>foo <em>bar</em></em></p>", blck2.TransformToHtml());

            MarkDownParser blck3("_foo _bar_ baz_");
            Assert::AreEqual<string>("<p><em>foo <em>bar</em> baz</em></p>", blck3.TransformToHtml());

            MarkDownParser blck4("*foo **bar** baz*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong> baz</em></p>", blck4.TransformToHtml());

            MarkDownParser blck5("*foo **bar *baz* bim** bop*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar <em>baz</em> bim</strong> bop</em></p>", blck5.TransformToHtml());

            MarkDownParser blck6("***foo** bar*");
            Assert::AreEqual<string>("<p><em><strong>foo</strong> bar</em></p>", blck6.TransformToHtml());

            MarkDownParser blck7("*foo **bar***");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong></em></p>", blck7.TransformToHtml());

            MarkDownParser blck8("** is not an empty emphasis");
            Assert::AreEqual<string>("<p>** is not an empty emphasis</p>", blck8.TransformToHtml());

            MarkDownParser blck9("**** is not an empty emphasis");
            Assert::AreEqual<string>("<p>**** is not an empty emphasis</p>", blck9.TransformToHtml());

            MarkDownParser blck10("**foo\nbar**");
            Assert::AreEqual<string>("<p><strong>foo\nbar</strong></p>", blck10.TransformToHtml());

            MarkDownParser blck11("__foo __bar__ baz__");
            Assert::AreEqual<string>("<p><strong>foo <strong>bar</strong> baz</strong></p>", blck11.TransformToHtml());

            MarkDownParser blck12("**foo **bar****");
            Assert::AreEqual<string>("<p><strong>foo <strong>bar</strong></strong></p>", blck12.TransformToHtml());

            MarkDownParser blck13("**foo *bar **baz**\n bim* bop**");
            Assert::AreEqual<string>("<p><strong>foo <em>bar <strong>baz</strong>\n bim</em> bop</strong></p>", blck13.TransformToHtml());

        }
    };
    TEST_CLASS(Rule11Test)
    {
        TEST_METHOD(EscapeTest)
        {
            MarkDownParser blck("foo *\\**");
            Assert::AreEqual<string>("<p>foo <em>*</em></p>", blck.TransformToHtml());

            MarkDownParser blck2("foo **\\***");
            Assert::AreEqual<string>("<p>foo <strong>*</strong></p>", blck2.TransformToHtml());
        }

    };
}
