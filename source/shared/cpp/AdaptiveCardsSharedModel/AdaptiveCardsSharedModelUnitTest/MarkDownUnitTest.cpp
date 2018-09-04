#include "stdafx.h"
#include "CppUnitTest.h"
#include "MarkDownParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(MarkDownBasicSanityTest)
    {
        TEST_METHOD(CanHandleEmptyStringTest)
        {
            MarkDownParser parser("");
            Assert::AreEqual<string>("<p></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }
    };

    TEST_CLASS(EmphasisLeftDelimterTest)
    {
        TEST_METHOD(LeftDelimiterTest)
        {
            MarkDownParser parser("*foo bar*");
            Assert::AreEqual<string>("<p><em>foo bar</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLeftDelimiterTest)
        {
            MarkDownParser parser("_foo bar_");
            Assert::AreEqual<string>("<p><em>foo bar</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(LeftDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser parser("* foo bar*");
            Assert::AreEqual<string>("<p>* foo bar*</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }
        TEST_METHOD(UnderscoreLeftDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser parser("_ foo bar_");
            Assert::AreEqual<string>("<p>_ foo bar_</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }
        TEST_METHOD(LeftDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser parser("a*\"foo\"*");
            Assert::AreEqual<string>("<p>a*&quot;foo&quot;*</p>", parser.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLeftDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser parser("a_\"foo\"_");
            Assert::AreEqual<string>("<p>a_&quot;foo&quot;_</p>", parser.TransformToHtml());
        }
        TEST_METHOD(LeftDelimiterIntraWordEmphasis)
        {
            MarkDownParser parser("foo*bar*");
            Assert::AreEqual<string>("<p>foo<em>bar</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLeftDelimiterIntraWordEmphasis)
        {
            MarkDownParser parser("foo_bar_");
            Assert::AreEqual<string>("<p>foo_bar_</p>", parser.TransformToHtml());
        }
        TEST_METHOD(LeftDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser parser("5*6*78");
            Assert::AreEqual<string>("<p>5<em>6</em>78</p>", parser.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLeftDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser parser("5_6_78");
            Assert::AreEqual<string>("<p>5_6_78</p>", parser.TransformToHtml());
        }
        TEST_METHOD(UnderscoreLeftDelimiterCanBeProceededAndFollowedByPunct)
        {
            MarkDownParser parser("foo-_(bar)_");
            Assert::AreEqual<string>("<p>foo-<em>(bar)</em></p>", parser.TransformToHtml());
        }
    };
    TEST_CLASS(EmphasisDelimterTest)
    {
        TEST_METHOD(MatchingRightDelimiterTest)
        {
            MarkDownParser parser("_foo_");
            Assert::AreEqual<string>("<p><em>foo</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(NonMatchingDelimiterTest)
        {
            MarkDownParser parser("_foo*");
            Assert::AreEqual<string>("<p>_foo*</p>", parser.TransformToHtml());
        }
        TEST_METHOD(MatchingRightDelimiterWithSpaceTest)
        {
            MarkDownParser parser("*foo *");
            Assert::AreEqual<string>("<p>*foo *</p>", parser.TransformToHtml());
        }
        TEST_METHOD(ValidDelimtersSurroundedByPunctuationTest)
        {
            MarkDownParser parser("*(*foo*)*");
            Assert::AreEqual<string>("<p><em>(<em>foo</em>)</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(PunctuationSurroundedByDelimiterValidTest)
        {
            MarkDownParser parser("*(foo)*");
            Assert::AreEqual<string>("<p><em>(foo)</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(ValidIntraWordEmphasisTest)
        {
            MarkDownParser parser("*foo*bar");
            Assert::AreEqual<string>("<p><em>foo</em>bar</p>", parser.TransformToHtml());
        }
        TEST_METHOD(WhiteSpaceClosingEmphasisInvalidTest)
        {
            MarkDownParser parser("_foo bar _");
            Assert::AreEqual<string>("<p>_foo bar _</p>", parser.TransformToHtml());
        }
        TEST_METHOD(InvalidIntraWordEmphasisTest)
        {
            MarkDownParser parser("_foo_bar");
            Assert::AreEqual<string>("<p>_foo_bar</p>", parser.TransformToHtml());
        }
        TEST_METHOD(RightDelimiterFollowedByPunctuationValidTest)
        {
            MarkDownParser parser("_(bar)_.");
            Assert::AreEqual<string>("<p><em>(bar)</em>.</p>", parser.TransformToHtml());
        }
    };

    TEST_CLASS(StrongDelimterTest)
    {
        TEST_METHOD(SimpleValidCaseTest)
        {
            MarkDownParser parser("**foo bar**");
            Assert::AreEqual<string>("<p><strong>foo bar</strong></p>", parser.TransformToHtml());
            MarkDownParser parser1("__foo bar__");
            Assert::AreEqual<string>("<p><strong>foo bar</strong></p>", parser1.TransformToHtml());
        }
        TEST_METHOD(DelimiterWithSpaceInvalidCaseTest)
        {
            MarkDownParser parser("** foo bar**");
            Assert::AreEqual<string>("<p>** foo bar**</p>", parser.TransformToHtml());
            MarkDownParser parser1("__ foo bar__");
            Assert::AreEqual<string>("<p>__ foo bar__</p>", parser1.TransformToHtml());
            MarkDownParser parser2("**foo bar **");
            Assert::AreEqual<string>("<p>**foo bar **</p>", parser2.TransformToHtml());
            MarkDownParser parser3("__foo bar __");
            Assert::AreEqual<string>("<p>__foo bar __</p>", parser3.TransformToHtml());
        }
        TEST_METHOD(DelimiterSurroundingPuntuationInvalidCaseTest)
        {
            MarkDownParser parser("a**\"foo bar\"**");
            Assert::AreEqual<string>("<p>a**&quot;foo bar&quot;**</p>", parser.TransformToHtml());
            MarkDownParser parser2("a__\"foo bar\"__");
            Assert::AreEqual<string>("<p>a__&quot;foo bar&quot;__</p>", parser2.TransformToHtml());
        }
        TEST_METHOD(IntraWordTest)
        {
            MarkDownParser parser("**foo**bar");
            Assert::AreEqual<string>("<p><strong>foo</strong>bar</p>", parser.TransformToHtml());
            MarkDownParser parser2("__foo__bar");
            Assert::AreEqual<string>("<p>__foo__bar</p>", parser2.TransformToHtml());
        }
        TEST_METHOD(PunctuationDelimitersTest)
        {
            MarkDownParser parser("**(**foo)");
            Assert::AreEqual<string>("<p>**(**foo)</p>", parser.TransformToHtml());

            MarkDownParser parser2("__(__foo");
            Assert::AreEqual<string>("<p>__(__foo</p>", parser2.TransformToHtml());

            MarkDownParser parser3("foo-__(bar)__");
            Assert::AreEqual<string>("<p>foo-<strong>(bar)</strong></p>", parser3.TransformToHtml());

            MarkDownParser parser4("(**foo**)");
            Assert::AreEqual<string>("<p>(<strong>foo</strong>)</p>", parser4.TransformToHtml());

            MarkDownParser parser5("(__foo__)");
            Assert::AreEqual<string>("<p>(<strong>foo</strong>)</p>", parser5.TransformToHtml());

            MarkDownParser parser6("__(foo)__.");
            Assert::AreEqual<string>("<p><strong>(foo)</strong>.</p>", parser6.TransformToHtml());
        }
    };
    

    TEST_CLASS(DelimiterNestingTest)
    {
        TEST_METHOD(PunctuationDelimitersTest)
        {
            MarkDownParser parser("_foo __bar__ baz_");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong> baz</em></p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo *bar**");
            Assert::AreEqual<string>("<p><em>foo <em>bar</em></em></p>", parser2.TransformToHtml());

            MarkDownParser parser3("_foo _bar_ baz_");
            Assert::AreEqual<string>("<p><em>foo <em>bar</em> baz</em></p>", parser3.TransformToHtml());

            MarkDownParser parser4("*foo **bar** baz*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong> baz</em></p>", parser4.TransformToHtml());

            MarkDownParser parser5("*foo **bar *baz* bim** bop*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar <em>baz</em> bim</strong> bop</em></p>", parser5.TransformToHtml());

            MarkDownParser parser6("***foo** bar*");
            Assert::AreEqual<string>("<p><em><strong>foo</strong> bar</em></p>", parser6.TransformToHtml());

            MarkDownParser parser7("*foo **bar***");
            Assert::AreEqual<string>("<p><em>foo <strong>bar</strong></em></p>", parser7.TransformToHtml());

            MarkDownParser parser8("** is not an empty emphasis");
            Assert::AreEqual<string>("<p>** is not an empty emphasis</p>", parser8.TransformToHtml());

            MarkDownParser parser9("**** is not an empty emphasis");
            Assert::AreEqual<string>("<p>**** is not an empty emphasis</p>", parser9.TransformToHtml());

            MarkDownParser parser10("**foo\nbar**");
            Assert::AreEqual<string>("<p><strong>foo\nbar</strong></p>", parser10.TransformToHtml());

            MarkDownParser parser11("__foo __bar__ baz__");
            Assert::AreEqual<string>("<p><strong>foo <strong>bar</strong> baz</strong></p>", parser11.TransformToHtml());

            MarkDownParser parser12("**foo **bar****");
            Assert::AreEqual<string>("<p><strong>foo <strong>bar</strong></strong></p>", parser12.TransformToHtml());

            MarkDownParser parser13("**foo *bar **baz**\n bim* bop**");
            Assert::AreEqual<string>("<p><strong>foo <em>bar <strong>baz</strong>\n bim</em> bop</strong></p>", parser13.TransformToHtml());

        }
    };
    TEST_CLASS(Rule11_12Test)
    {
        TEST_METHOD(EscapeTest)
        {
            MarkDownParser parser("foo *\\**");
            Assert::AreEqual<string>("<p>foo <em>*</em></p>", parser.TransformToHtml());

            MarkDownParser parser2("foo **\\***");
            Assert::AreEqual<string>("<p>foo <strong>*</strong></p>", parser2.TransformToHtml());

            MarkDownParser parser3("foo __\\___");
            Assert::AreEqual<string>("<p>foo <strong>_</strong></p>", parser3.TransformToHtml());
        }
        TEST_METHOD(UnevenMatchingDelimiter)
        {
            MarkDownParser parser("**foo*");
            Assert::AreEqual<string>("<p>*<em>foo</em></p>", parser.TransformToHtml());

            MarkDownParser parser1("*foo**");
            Assert::AreEqual<string>("<p><em>foo</em>*</p>", parser1.TransformToHtml());

            MarkDownParser parser2("***foo**");
            Assert::AreEqual<string>("<p>*<strong>foo</strong></p>", parser2.TransformToHtml());

            MarkDownParser parser3("*foo****");
            Assert::AreEqual<string>("<p><em>foo</em>***</p>", parser3.TransformToHtml());

            MarkDownParser parser4("**Gomphocarpus (*Gomphocarpus physocarpus*, syn.\n*Asclepias physocarpa*)**");
            Assert::AreEqual<string>("<p><strong>Gomphocarpus (<em>Gomphocarpus physocarpus</em>, syn.\n<em>Asclepias physocarpa</em>)</strong></p>", 
                parser4.TransformToHtml());

            MarkDownParser parser5("*Hello* abc ***Hello* def *world***");
            Assert::AreEqual<string>("<p><em>Hello</em> abc <strong><em>Hello</em> def <em>world</em></strong></p>", parser5.TransformToHtml());

            MarkDownParser parser6("*foo**bar**baz*");
            Assert::AreEqual<string>("<p><em>foo<strong>bar</strong>baz</em></p>", parser6.TransformToHtml());
        }
    };
    TEST_CLASS(Rule13Test)
    {
        TEST_METHOD(strongEmphasisNesting)
        {
            MarkDownParser parser("****foo****");
            Assert::AreEqual<string>("<p><strong><strong>foo</strong></strong></p>", parser.TransformToHtml());
            MarkDownParser parser2("******foo******");
            Assert::AreEqual<string>("<p><strong><strong><strong>foo</strong></strong></strong></p>", parser2.TransformToHtml());
        }
    };
    TEST_CLASS(Rule14Test)
    {
        TEST_METHOD(strongAndEmpEmphasisNesting)
        {
            MarkDownParser parser("***foo***");
            Assert::AreEqual<string>("<p><strong><em>foo</em></strong></p>", parser.TransformToHtml());

            MarkDownParser parser2("_____foo_____");
            Assert::AreEqual<string>("<p><strong><strong><em>foo</em></strong></strong></p>", parser2.TransformToHtml());
        }
    };
    TEST_CLASS(Rule15Test)
    {
        TEST_METHOD(OverrapingTest)
        {
            MarkDownParser parser("*foo _bar* baz_");
            Assert::AreEqual<string>("<p><em>foo _bar</em> baz_</p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo __bar *baz bim__ bam*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar *baz bim</strong> bam</em></p>", parser2.TransformToHtml());
        }
    };

    TEST_CLASS(Rule16Test)
    {
        TEST_METHOD(strongEmphasis)
        {
            MarkDownParser parser("**foo **bar baz**");
            Assert::AreEqual<string>("<p>**foo <strong>bar baz</strong></p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo *bar baz*");
            Assert::AreEqual<string>("<p>*foo <em>bar baz</em></p>", parser2.TransformToHtml());

            MarkDownParser parser3("**K *J *foo**bar* *cool*");
            Assert::AreEqual<string>("<p><strong>K *J *foo</strong>bar* <em>cool</em></p>", parser3.TransformToHtml());

            MarkDownParser parser4("**m *J *foo**bar *cool**");
            Assert::AreEqual<string>("<p><strong>m *J *foo</strong>bar <em>cool</em>*</p>", parser4.TransformToHtml());

            MarkDownParser parser5("**H *foo**bar***");
            Assert::AreEqual<string>("<p><strong>H *foo</strong>bar***</p>", parser5.TransformToHtml());

            MarkDownParser parser6("*hello *hi **H foo** bar**");
            Assert::AreEqual<string>("<p><em>hello <em>hi <strong>H foo</strong> bar</em></em></p>", parser6.TransformToHtml());

            MarkDownParser parser7("hello **how are** *you **i** am **great** *thank* **you***");
            Assert::AreEqual<string>("<p>hello <strong>how are</strong> <em>you <strong>i</strong> am <strong>great</strong> <em>thank</em> <strong>you</strong></em></p>", parser7.TransformToHtml());

            MarkDownParser parser8("hello, **how are__ you**");
            Assert::AreEqual<string>("<p>hello, <strong>how are__ you</strong></p>", parser8.TransformToHtml());

            MarkDownParser parser9("hello, __how **are__ you?**");
            Assert::AreEqual<string>("<p>hello, <strong>how **are</strong> you?**</p>", parser9.TransformToHtml());

            MarkDownParser parser10("hello, **how are__ you**");
            Assert::AreEqual<string>("<p>hello, <strong>how are__ you</strong></p>", parser10.TransformToHtml());
        }
        TEST_METHOD(TempTest)
        {
            MarkDownParser parser11("*hello *hello**h*");
            Assert::AreEqual<string>("<p>*hello <em>hello**h</em></p>", parser11.TransformToHtml());
        }
    };
    TEST_CLASS(LinkBasicValidationTest)
    {
        TEST_METHOD(CanGenerateValidHtmlTagForLinkTest)
        {
            MarkDownParser parser("[hello](www.naver.com)"); 
            Assert::AreEqual<string>("<p><a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(ValidLinkTestWithUnMatchingBrackets)
        {
            MarkDownParser parser("[[[[hello](www.naver.com)"); 
            Assert::AreEqual<string>("<p>[[[<a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
        }
        TEST_METHOD(InvalidLinkTest)
        {
            MarkDownParser parser("[hello(www.naver.com)"); 
            Assert::AreEqual<string>("<p>[hello(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), false);
        }

        TEST_METHOD(InvalidLinkTestWithInvalidEmphasis)
        {
            MarkDownParser parser("*[*hello(www.naver.com)"); 
            Assert::AreEqual<string>("<p>*[*hello(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), false);
        }

        TEST_METHOD(InvalidLinkTestWithValidEmphasis)
        {
            MarkDownParser parser("*[*hello(www.naver.com)*"); 
            Assert::AreEqual<string>("<p>*[<em>hello(www.naver.com)</em></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), true);
        }

        TEST_METHOD(ValidLinkTestWithUnMatchingBracketsWithChars)
        {
            MarkDownParser parser("[a[b[hello](www.naver.com)"); 
            Assert::AreEqual<string>("<p>[a[b<a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(ValidLinkTestWithUnMatchingBracketsWithCharsAndParenthesis)
        {
            MarkDownParser parser("[[a[b[h(ello](www.naver.com)"); 
            Assert::AreEqual<string>("<p>[[a[b<a href=\"www.naver.com\">h(ello</a></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(InvalidCharsBetweenLinkTextAndDestination)
        {
            MarkDownParser parser("[hello]a(www.naver.com)");
            Assert::AreEqual<string>("<p>[hello]a(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(OutSideEmphasisAndLinkTest)
        {
            MarkDownParser parser("*[hello](www.naver.com)*"); 
            Assert::AreEqual<string>("<p><em><a href=\"www.naver.com\">hello</a></em></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(EmphasisAndLinkTextTest)
        {
            MarkDownParser parser("[*hello*](www.naver.com)"); 
            Assert::AreEqual<string>("<p><a href=\"www.naver.com\"><em>hello</em></a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(UmatchingEmphasisAndLinkTextTest)
        {
            MarkDownParser parser("*[*hello*](www.naver.com)"); 
            Assert::AreEqual<string>("<p>*<a href=\"www.naver.com\"><em>hello</em></a></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisAndLinkDestinationTest)
        {
            MarkDownParser parser("*[*hello*](*www.naver.com*)"); 
            Assert::AreEqual<string>("<p>*<a href=\"*www.naver.com*\"><em>hello</em></a></p>", parser.TransformToHtml());
        }
        TEST_METHOD(LinkWithComplexEmphasisString)
        {
            MarkDownParser parser("**Hello** *[*hello*](*www.naver.com*)*"); 
            Assert::AreEqual<string>("<p><strong>Hello</strong> <em><a href=\"*www.naver.com*\"><em>hello</em></a></em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(TwoLinksTest)
        {
            MarkDownParser parser("*Hello* *[*hello*](*www.naver.com*)** Hello, [second](www.microsoft.com)"); 
            Assert::AreEqual<string>("<p><em>Hello</em> <em><a href=\"*www.naver.com*\"><em>hello</em></a></em>* Hello, <a href=\"www.microsoft.com\">second</a></p>", parser.TransformToHtml());
        }
    };

    TEST_CLASS(ListTest)
    {
        TEST_METHOD(SimpleValidListTest)
        {
            MarkDownParser parser("- hello");
            Assert::AreEqual<string>("<ul><li>hello</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleSimpleValidListTest)
        {
            MarkDownParser parser("- hello\n- Hi");
            Assert::AreEqual<string>("<ul><li>hello</li><li>Hi</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(ListTestsWithInterHyphen)
        {
            MarkDownParser parser("- hello world - hello hello");
            Assert::AreEqual<string>("<ul><li>hello world - hello hello</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleListWithHyphenTests)
        {
            MarkDownParser parser("- hello world - hello hello\r- winner winner chicken dinner");
            Assert::AreEqual<string>("<ul><li>hello world - hello hello</li><li>winner winner chicken dinner</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleListWithHyphenAndEmphasisTests)
        {
            MarkDownParser parser("- hello world - hello hello\r- ***winner* winner** chicken dinner");
            Assert::AreEqual<string>("<ul><li>hello world - hello hello</li><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleListWithLinkTest)
        {
            MarkDownParser parser("- hello world\r- hello hello\r- new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<string>("<ul><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(PtagedBlockElementFollowedByListTest)
        {
            MarkDownParser parser("Hello\r- my list");
            Assert::AreEqual<string>("<p>Hello</p><ul><li>my list</li></ul>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }
        TEST_METHOD(ListFollowedByPtagedBlockElementTest)
        {
            MarkDownParser parser("- my list\r\rHello");
            Assert::AreEqual<string>("<ul><li>my list</li></ul><p>Hello</p>", parser.TransformToHtml());
        }
        TEST_METHOD(ListFollowedWithNewLineCharTest)
        {
            MarkDownParser parser("- my list\rHello");
            Assert::AreEqual<string>("<ul><li>my list\rHello</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(InvalidListStringReturnedUnchangedTest)
        {
            MarkDownParser parser("023-34-567");
            Assert::AreEqual<string>("<p>023-34-567</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }
    };
    TEST_CLASS(OrderedListTest)
    {
        TEST_METHOD(SimpleValidListTest)
        {
            MarkDownParser parser("1. hello");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleSimpleValidListTest)
        {
            MarkDownParser parser("1. hello\n2. Hi");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello</li><li>Hi</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(ListTestsWithInterHyphen)
        {
            MarkDownParser parser("1. hello world - hello hello");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello world - hello hello</li></ol>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }
        TEST_METHOD(MultipleListWithHyphenTests)
        {
            MarkDownParser parser("1. hello world - hello hello\r2. winner winner chicken dinner");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello world - hello hello</li><li>winner winner chicken dinner</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleListWithHyphenAndEmphasisTests)
        {
            MarkDownParser parser("1. hello world - hello hello\r- ***winner* winner** chicken dinner");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello world - hello hello</li></ol><ul><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(MultipleListWithLinkTest)
        {
            MarkDownParser parser("1. hello world\r2. hello hello\r3. new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<string>("<ol start=\"1\"><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(PtagedBlockElementFollowedByListTest)
        {
            MarkDownParser parser("Hello\r1. my list");
            Assert::AreEqual<string>("<p>Hello</p><ol start=\"1\"><li>my list</li></ol>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }
        TEST_METHOD(ListFollowedByPtagedBlockElementTest)
        {
            MarkDownParser parser("1. my list\r\rHello");
            Assert::AreEqual<string>("<ol start=\"1\"><li>my list</li></ol><p>Hello</p>", parser.TransformToHtml());
        }
        TEST_METHOD(ListFollowedWithNewLineCharTest)
        {
            MarkDownParser parser("1. my list\rHello");
            Assert::AreEqual<string>("<ol start=\"1\"><li>my list\rHello</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(ListStartsWithRandomNumberTest)
        {
            MarkDownParser parser("777. my list\rHello");
            Assert::AreEqual<string>("<ol start=\"777\"><li>my list\rHello</li></ol>", parser.TransformToHtml());
        }
    };

    TEST_CLASS(EscapeHtmlCharactersTest)
    {
        TEST_METHOD(GreaterThanTest)
        {
            MarkDownParser parser("5>3");
            Assert::AreEqual<string>("<p>5&gt;3</p>", parser.TransformToHtml());
        }
        TEST_METHOD(LessThanTest)
        {
            MarkDownParser parser("3<5");
            Assert::AreEqual<string>("<p>3&lt;5</p>", parser.TransformToHtml());
        }
        TEST_METHOD(QuotationTest)
        {
            MarkDownParser parser("\"Hello World!\"");
            Assert::AreEqual<string>("<p>&quot;Hello World!&quot;</p>", parser.TransformToHtml());
        }
        TEST_METHOD(AmpersandTest)
        {
            MarkDownParser parser("Green Eggs & Ham");
            Assert::AreEqual<string>("<p>Green Eggs &amp; Ham</p>", parser.TransformToHtml());
        }
    };
}
