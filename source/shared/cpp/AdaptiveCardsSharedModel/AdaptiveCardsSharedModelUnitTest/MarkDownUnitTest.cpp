// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "MarkDownParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(MarkdownTests)
    {
        TEST_METHOD(MarkDownBasicSanityTest_CanHandleEmptyStringTest)
        {
            MarkDownParser parser("");
            Assert::AreEqual<std::string>("<p></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(MarkDownBasicSanityTest_CanHandleEmphasisTest)
        {
            MarkDownParser parser("*");
            Assert::AreEqual<std::string>("<p>*</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(MarkDownBasicSanityTest_CanHandleStrongEmphasisTest)
        {
            MarkDownParser parser("**");
            Assert::AreEqual<std::string>("<p>**</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(EmphasisLeftDelimiterTest_LeftDelimiterTest)
        {
            MarkDownParser parser("*foo bar*");
            Assert::AreEqual<std::string>("<p><em>foo bar</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterTest)
        {
            MarkDownParser parser("_foo bar_");
            Assert::AreEqual<std::string>("<p><em>foo bar</em></p>", parser.TransformToHtml());
        }

        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser parser("_ foo bar_");
            Assert::AreEqual<std::string>("<p>_ foo bar_</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_LeftDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser parser("a*\"foo\"*");
            Assert::AreEqual<std::string>("<p>a*&quot;foo&quot;*</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterFalseCaseWithAlphaNumericInfrontAndPuntuationBehind)
        {
            MarkDownParser parser("a_\"foo\"_");
            Assert::AreEqual<std::string>("<p>a_&quot;foo&quot;_</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_LeftDelimiterIntraWordEmphasis)
        {
            MarkDownParser parser("foo*bar*");
            Assert::AreEqual<std::string>("<p>foo<em>bar</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterIntraWordEmphasis)
        {
            MarkDownParser parser("foo_bar_");
            Assert::AreEqual<std::string>("<p>foo_bar_</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_LeftDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser parser("5*6*78");
            Assert::AreEqual<std::string>("<p>5<em>6</em>78</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterNumericIntraWordEmphasis)
        {
            MarkDownParser parser("5_6_78");
            Assert::AreEqual<std::string>("<p>5_6_78</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisLeftDelimiterTest_UnderscoreLeftDelimiterCanBeProceededAndFollowedByPunct)
        {
            MarkDownParser parser("foo-_(bar)_");
            Assert::AreEqual<std::string>("<p>foo-<em>(bar)</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_MatchingRightDelimiterTest)
        {
            MarkDownParser parser("_foo_");
            Assert::AreEqual<std::string>("<p><em>foo</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_NonMatchingDelimiterTest)
        {
            MarkDownParser parser("_foo*");
            Assert::AreEqual<std::string>("<p>_foo*</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_MatchingRightDelimiterWithSpaceTest)
        {
            MarkDownParser parser("*foo *");
            Assert::AreEqual<std::string>("<p>*foo *</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_ValidDelimitersSurroundedByPunctuationTest)
        {
            MarkDownParser parser("*(*foo*)*");
            Assert::AreEqual<std::string>("<p><em>(<em>foo</em>)</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_PunctuationSurroundedByDelimiterValidTest)
        {
            MarkDownParser parser("*(foo)*");
            Assert::AreEqual<std::string>("<p><em>(foo)</em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_ValidIntraWordEmphasisTest)
        {
            MarkDownParser parser("*foo*bar");
            Assert::AreEqual<std::string>("<p><em>foo</em>bar</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_WhiteSpaceClosingEmphasisInvalidTest)
        {
            MarkDownParser parser("_foo bar _");
            Assert::AreEqual<std::string>("<p>_foo bar _</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_InvalidIntraWordEmphasisTest)
        {
            MarkDownParser parser("_foo_bar");
            Assert::AreEqual<std::string>("<p>_foo_bar</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EmphasisDelimiterTest_RightDelimiterFollowedByPunctuationValidTest)
        {
            MarkDownParser parser("_(bar)_.");
            Assert::AreEqual<std::string>("<p><em>(bar)</em>.</p>", parser.TransformToHtml());
        }
        TEST_METHOD(StrongDelimiterTest_SimpleValidCaseTest)
        {
            MarkDownParser parser("**foo bar**");
            Assert::AreEqual<std::string>("<p><strong>foo bar</strong></p>", parser.TransformToHtml());
            MarkDownParser parser1("__foo bar__");
            Assert::AreEqual<std::string>("<p><strong>foo bar</strong></p>", parser1.TransformToHtml());
        }
        TEST_METHOD(StrongDelimiterTest_DelimiterWithSpaceInvalidCaseTest)
        {
            MarkDownParser parser("** foo bar**");
            Assert::AreEqual<std::string>("<p>** foo bar**</p>", parser.TransformToHtml());
            MarkDownParser parser1("__ foo bar__");
            Assert::AreEqual<std::string>("<p>__ foo bar__</p>", parser1.TransformToHtml());
            MarkDownParser parser2("**foo bar **");
            Assert::AreEqual<std::string>("<p>**foo bar **</p>", parser2.TransformToHtml());
            MarkDownParser parser3("__foo bar __");
            Assert::AreEqual<std::string>("<p>__foo bar __</p>", parser3.TransformToHtml());
        }
        TEST_METHOD(StrongDelimiterTest_DelimiterSurroundingPuntuationInvalidCaseTest)
        {
            MarkDownParser parser("a**\"foo bar\"**");
            Assert::AreEqual<std::string>("<p>a**&quot;foo bar&quot;**</p>", parser.TransformToHtml());
            MarkDownParser parser2("a__\"foo bar\"__");
            Assert::AreEqual<std::string>("<p>a__&quot;foo bar&quot;__</p>", parser2.TransformToHtml());
        }
        TEST_METHOD(StrongDelimiterTest_IntraWordTest)
        {
            MarkDownParser parser("**foo**bar");
            Assert::AreEqual<std::string>("<p><strong>foo</strong>bar</p>", parser.TransformToHtml());
            MarkDownParser parser2("__foo__bar");
            Assert::AreEqual<std::string>("<p>__foo__bar</p>", parser2.TransformToHtml());
        }
        TEST_METHOD(StrongDelimiterTest_PunctuationDelimitersTest)
        {
            MarkDownParser parser("**(**foo)");
            Assert::AreEqual<std::string>("<p>**(**foo)</p>", parser.TransformToHtml());

            MarkDownParser parser2("__(__foo");
            Assert::AreEqual<std::string>("<p>__(__foo</p>", parser2.TransformToHtml());

            MarkDownParser parser3("foo-__(bar)__");
            Assert::AreEqual<std::string>("<p>foo-<strong>(bar)</strong></p>", parser3.TransformToHtml());

            MarkDownParser parser4("(**foo**)");
            Assert::AreEqual<std::string>("<p>(<strong>foo</strong>)</p>", parser4.TransformToHtml());

            MarkDownParser parser5("(__foo__)");
            Assert::AreEqual<std::string>("<p>(<strong>foo</strong>)</p>", parser5.TransformToHtml());

            MarkDownParser parser6("__(foo)__.");
            Assert::AreEqual<std::string>("<p><strong>(foo)</strong>.</p>", parser6.TransformToHtml());
        }
        TEST_METHOD(DelimiterNestingTest_PunctuationDelimitersTest)
        {
            MarkDownParser parser("_foo __bar__ baz_");
            Assert::AreEqual<std::string>("<p><em>foo <strong>bar</strong> baz</em></p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo *bar**");
            Assert::AreEqual<std::string>("<p><em>foo <em>bar</em></em></p>", parser2.TransformToHtml());

            MarkDownParser parser3("_foo _bar_ baz_");
            Assert::AreEqual<std::string>("<p><em>foo <em>bar</em> baz</em></p>", parser3.TransformToHtml());

            MarkDownParser parser4("*foo **bar** baz*");
            Assert::AreEqual<std::string>("<p><em>foo <strong>bar</strong> baz</em></p>", parser4.TransformToHtml());

            MarkDownParser parser5("*foo **bar *baz* bim** bop*");
            Assert::AreEqual<std::string>("<p><em>foo <strong>bar <em>baz</em> bim</strong> bop</em></p>", parser5.TransformToHtml());

            MarkDownParser parser6("***foo** bar*");
            Assert::AreEqual<std::string>("<p><em><strong>foo</strong> bar</em></p>", parser6.TransformToHtml());

            MarkDownParser parser7("*foo **bar***");
            Assert::AreEqual<std::string>("<p><em>foo <strong>bar</strong></em></p>", parser7.TransformToHtml());

            MarkDownParser parser8("** is not an empty emphasis");
            Assert::AreEqual<std::string>("<p>** is not an empty emphasis</p>", parser8.TransformToHtml());

            MarkDownParser parser9("**** is not an empty emphasis");
            Assert::AreEqual<std::string>("<p>**** is not an empty emphasis</p>", parser9.TransformToHtml());

            MarkDownParser parser10("**foo\nbar**");
            Assert::AreEqual<std::string>("<p><strong>foo\nbar</strong></p>", parser10.TransformToHtml());

            MarkDownParser parser11("__foo __bar__ baz__");
            Assert::AreEqual<std::string>("<p><strong>foo <strong>bar</strong> baz</strong></p>", parser11.TransformToHtml());

            MarkDownParser parser12("**foo **bar****");
            Assert::AreEqual<std::string>("<p><strong>foo <strong>bar</strong></strong></p>", parser12.TransformToHtml());

            MarkDownParser parser13("**foo *bar **baz**\n bim* bop**");
            Assert::AreEqual<std::string>("<p><strong>foo <em>bar <strong>baz</strong>\n bim</em> bop</strong></p>", parser13.TransformToHtml());

        }
        TEST_METHOD(Rule11_12Test_EscapeTest)
        {
            MarkDownParser parser("foo *\\**");
            Assert::AreEqual<std::string>("<p>foo <em>*</em></p>", parser.TransformToHtml());

            MarkDownParser parser2("foo **\\***");
            Assert::AreEqual<std::string>("<p>foo <strong>*</strong></p>", parser2.TransformToHtml());

            MarkDownParser parser3("foo __\\___");
            Assert::AreEqual<std::string>("<p>foo <strong>_</strong></p>", parser3.TransformToHtml());
        }
        TEST_METHOD(Rule11_12Test_UnevenMatchingDelimiter)
        {
            MarkDownParser parser("**foo*");
            Assert::AreEqual<std::string>("<p>*<em>foo</em></p>", parser.TransformToHtml());

            MarkDownParser parser1("*foo**");
            Assert::AreEqual<std::string>("<p><em>foo</em>*</p>", parser1.TransformToHtml());

            MarkDownParser parser2("***foo**");
            Assert::AreEqual<std::string>("<p>*<strong>foo</strong></p>", parser2.TransformToHtml());

            MarkDownParser parser3("*foo****");
            Assert::AreEqual<std::string>("<p><em>foo</em>***</p>", parser3.TransformToHtml());

            MarkDownParser parser4("**Gomphocarpus (*Gomphocarpus physocarpus*, syn.\n*Asclepias physocarpa*)**");
            Assert::AreEqual<std::string>("<p><strong>Gomphocarpus (<em>Gomphocarpus physocarpus</em>, syn.\n<em>Asclepias physocarpa</em>)</strong></p>",
                parser4.TransformToHtml());

            MarkDownParser parser5("*Hello* abc ***Hello* def *world***");
            Assert::AreEqual<std::string>("<p><em>Hello</em> abc <strong><em>Hello</em> def <em>world</em></strong></p>", parser5.TransformToHtml());

            MarkDownParser parser6("*foo**bar**baz*");
            Assert::AreEqual<std::string>("<p><em>foo<strong>bar</strong>baz</em></p>", parser6.TransformToHtml());
        }

        TEST_METHOD(Rule13Test_strongEmphasisNesting)
        {
            MarkDownParser parser("****foo****");
            Assert::AreEqual<std::string>("<p><strong><strong>foo</strong></strong></p>", parser.TransformToHtml());
            MarkDownParser parser2("******foo******");
            Assert::AreEqual<std::string>("<p><strong><strong><strong>foo</strong></strong></strong></p>", parser2.TransformToHtml());
        }
        TEST_METHOD(Rule14Test_strongAndEmpEmphasisNesting)
        {
            MarkDownParser parser("***foo***");
            Assert::AreEqual<std::string>("<p><strong><em>foo</em></strong></p>", parser.TransformToHtml());

            MarkDownParser parser2("_____foo_____");
            Assert::AreEqual<std::string>("<p><strong><strong><em>foo</em></strong></strong></p>", parser2.TransformToHtml());
        }
        TEST_METHOD(Rule15Test_OverrapingTest)
        {
            MarkDownParser parser("*foo _bar* baz_");
            Assert::AreEqual<std::string>("<p><em>foo _bar</em> baz_</p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo __bar *baz bim__ bam*");
            Assert::AreEqual<std::string>("<p><em>foo <strong>bar *baz bim</strong> bam</em></p>", parser2.TransformToHtml());
        }
        TEST_METHOD(Rule16Test_strongEmphasis)
        {
            MarkDownParser parser("**foo **bar baz**");
            Assert::AreEqual<std::string>("<p>**foo <strong>bar baz</strong></p>", parser.TransformToHtml());

            MarkDownParser parser2("*foo *bar baz*");
            Assert::AreEqual<std::string>("<p>*foo <em>bar baz</em></p>", parser2.TransformToHtml());

            MarkDownParser parser3("**K *J *foo**bar* *cool*");
            Assert::AreEqual<std::string>("<p><strong>K *J *foo</strong>bar* <em>cool</em></p>", parser3.TransformToHtml());

            MarkDownParser parser4("**m *J *foo**bar *cool**");
            Assert::AreEqual<std::string>("<p><strong>m *J *foo</strong>bar <em>cool</em>*</p>", parser4.TransformToHtml());

            MarkDownParser parser5("**H *foo**bar***");
            Assert::AreEqual<std::string>("<p><strong>H *foo</strong>bar***</p>", parser5.TransformToHtml());

            MarkDownParser parser6("*hello *hi **H foo** bar**");
            Assert::AreEqual<std::string>("<p><em>hello <em>hi <strong>H foo</strong> bar</em></em></p>", parser6.TransformToHtml());

            MarkDownParser parser7("hello **how are** *you **i** am **great** *thank* **you***");
            Assert::AreEqual<std::string>("<p>hello <strong>how are</strong> <em>you <strong>i</strong> am <strong>great</strong> <em>thank</em> <strong>you</strong></em></p>", parser7.TransformToHtml());

            MarkDownParser parser8("hello, **how are__ you**");
            Assert::AreEqual<std::string>("<p>hello, <strong>how are__ you</strong></p>", parser8.TransformToHtml());

            MarkDownParser parser9("hello, __how **are__ you?**");
            Assert::AreEqual<std::string>("<p>hello, <strong>how **are</strong> you?**</p>", parser9.TransformToHtml());

            MarkDownParser parser10("hello, **how are__ you**");
            Assert::AreEqual<std::string>("<p>hello, <strong>how are__ you</strong></p>", parser10.TransformToHtml());
        }
        TEST_METHOD(Rule16Test_TempTest)
        {
            MarkDownParser parser11("*hello *hello**h*");
            Assert::AreEqual<std::string>("<p>*hello <em>hello**h</em></p>", parser11.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_CanGenerateValidHtmlTagForLinkTest)
        {
            MarkDownParser parser("[hello](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithUnMatchingBrackets)
        {
            MarkDownParser parser("[[[[hello](www.naver.com)");
            Assert::AreEqual<std::string>("<p>[[[<a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets)
        {
            MarkDownParser parser("[[hello]](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\">[hello]</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets2)
        {
            MarkDownParser parser("[*[hello]*](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\"><em>[hello]</em></a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets3)
        {
            MarkDownParser parser("[*[hello[hello]hello]*](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\"><em>[hello[hello]hello]</em></a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets4)
        {
            MarkDownParser parser("[*hello[hello]hello](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\">*hello[hello]hello</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets5)
        {
            MarkDownParser parser("[*hellohello]hello](www.naver.com)");
            Assert::AreEqual<std::string>("<p>[*hellohello]hello](www.naver.com)</p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithMatchingInnerBrackets6)
        {
            MarkDownParser parser("[Bug [021356]](https://msn.com): Markdown link parsing");
            Assert::AreEqual<std::string>("<p><a href=\"https://msn.com\">Bug [021356]</a>: Markdown link parsing</p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_InvalidLinkTest)
        {
            MarkDownParser parser("[hello(www.naver.com)");
            Assert::AreEqual<std::string>("<p>[hello(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), false);
        }

        TEST_METHOD(LinkBasicValidationTest_InvalidLinkTestWithInvalidEmphasis)
        {
            MarkDownParser parser("*[*hello(www.naver.com)");
            Assert::AreEqual<std::string>("<p>*[*hello(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), false);
        }

        TEST_METHOD(LinkBasicValidationTest_InvalidLinkTestWithValidEmphasis)
        {
            MarkDownParser parser("*[*hello(www.naver.com)*");
            Assert::AreEqual<std::string>("<p>*[<em>hello(www.naver.com)</em></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(parser.HasHtmlTags(), true);
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithUnMatchingBracketsWithChars)
        {
            MarkDownParser parser("[a[b[hello](www.naver.com)");
            Assert::AreEqual<std::string>("<p>[a[b<a href=\"www.naver.com\">hello</a></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(LinkBasicValidationTest_ValidLinkTestWithUnMatchingBracketsWithCharsAndParenthesis)
        {
            MarkDownParser parser("[[a[b[h(ello](www.naver.com)");
            Assert::AreEqual<std::string>("<p>[[a[b<a href=\"www.naver.com\">h(ello</a></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(LinkBasicValidationTest_LinkTextWithNumberAndPunchuations)
        {
            MarkDownParser parser("[1234.5](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\">1234.5</a></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(LinkBasicValidationTest_InvalidCharsBetweenLinkTextAndDestination)
        {
            MarkDownParser parser("[hello]a(www.naver.com)");
            Assert::AreEqual<std::string>("<p>[hello]a(www.naver.com)</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(LinkBasicValidationTest_OutSideEmphasisAndLinkTest)
        {
            MarkDownParser parser("*[hello](www.naver.com)*");
            Assert::AreEqual<std::string>("<p><em><a href=\"www.naver.com\">hello</a></em></p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(LinkBasicValidationTest_EmphasisAndLinkTextTest)
        {
            MarkDownParser parser("[*hello*](www.naver.com)");
            Assert::AreEqual<std::string>("<p><a href=\"www.naver.com\"><em>hello</em></a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(LinkBasicValidationTest_UmatchingEmphasisAndLinkTextTest)
        {
            MarkDownParser parser("*[*hello*](www.naver.com)");
            Assert::AreEqual<std::string>("<p>*<a href=\"www.naver.com\"><em>hello</em></a></p>", parser.TransformToHtml());
        }
        TEST_METHOD(LinkBasicValidationTest_EmphasisAndLinkDestinationTest)
        {
            MarkDownParser parser("*[*hello*](*www.naver.com*)");
            Assert::AreEqual<std::string>("<p>*<a href=\"*www.naver.com*\"><em>hello</em></a></p>", parser.TransformToHtml());
        }
        TEST_METHOD(LinkBasicValidationTest_LinkWithComplexEmphasisString)
        {
            MarkDownParser parser("**Hello** *[*hello*](*www.naver.com*)*");
            Assert::AreEqual<std::string>("<p><strong>Hello</strong> <em><a href=\"*www.naver.com*\"><em>hello</em></a></em></p>", parser.TransformToHtml());
        }
        TEST_METHOD(LinkBasicValidationTest_TwoLinksTest)
        {
            MarkDownParser parser("*Hello* *[*hello*](*www.naver.com*)** Hello, [second](www.microsoft.com)");
            Assert::AreEqual<std::string>("<p><em>Hello</em> <em><a href=\"*www.naver.com*\"><em>hello</em></a></em>* Hello, <a href=\"www.microsoft.com\">second</a></p>", parser.TransformToHtml());
        }

        TEST_METHOD(ListTest_SimpleValidListTest)
        {
            MarkDownParser parser("- hello");
            Assert::AreEqual<std::string>("<ul><li>hello</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello");
            Assert::AreEqual<std::string>("<ul><li>hello</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("+ hello");
            Assert::AreEqual<std::string>("<ul><li>hello</li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_MultipleSimpleValidListTest)
        {
            MarkDownParser parser("- hello\n- world\n- hi");
            Assert::AreEqual<std::string>("<ul><li>hello</li><li>world</li><li>hi</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello\n* world\n* hi");
            Assert::AreEqual<std::string>("<ul><li>hello</li><li>world</li><li>hi</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("* hello\n- Hi");
            Assert::AreEqual<std::string>("<ul><li>hello</li><li>Hi</li></ul>", parser3.TransformToHtml());
            MarkDownParser parser4("+ hello\n+ world\n+ hi");
            Assert::AreEqual<std::string>("<ul><li>hello</li><li>world</li><li>hi</li></ul>", parser4.TransformToHtml());
        }

        TEST_METHOD(ListTest_ListTestsWithInterHyphen)
        {
            MarkDownParser parser("- hello world - hello hello");
            Assert::AreEqual<std::string>("<ul><li>hello world - hello hello</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello world - hello hello");
            Assert::AreEqual<std::string>("<ul><li>hello world - hello hello</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("- hello world + hello hello");
            Assert::AreEqual<std::string>("<ul><li>hello world + hello hello</li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_MultipleListWithHyphenTests)
        {
            MarkDownParser parser("- hello world - hello hello\r- winner winner chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world - hello hello</li><li>winner winner chicken dinner</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello world * hello hello\r* winner winner chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world * hello hello</li><li>winner winner chicken dinner</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("+ hello world * hello hello\r+ winner winner chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world * hello hello</li><li>winner winner chicken dinner</li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_MultipleListWithHyphenAndEmphasisTests)
        {
            MarkDownParser parser("- hello world - hello hello\r- ***winner* winner** chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world - hello hello</li><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello world * hello hello\r* ***winner* winner** chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world * hello hello</li><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("+ hello world * hello hello\r+ ***winner* winner** chicken dinner");
            Assert::AreEqual<std::string>("<ul><li>hello world * hello hello</li><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_MultipleListWithLinkTest)
        {
            MarkDownParser parser("- hello world\r- hello hello\r- new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<std::string>("<ul><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* hello world\r* hello hello\r* new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<std::string>("<ul><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("+ hello world\r+ hello hello\r+ new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<std::string>("<ul><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_PtagedBlockElementFollowedByListTest)
        {
            MarkDownParser parser("Hello\r- my list");
            Assert::AreEqual<std::string>("<p>Hello</p><ul><li>my list</li></ul>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
            MarkDownParser parser2("Hello\r* my list");
            Assert::AreEqual<std::string>("<p>Hello</p><ul><li>my list</li></ul>", parser2.TransformToHtml());
            Assert::AreEqual<bool>(true, parser2.HasHtmlTags());
            MarkDownParser parser3("Hello\r+ my list");
            Assert::AreEqual<std::string>("<p>Hello</p><ul><li>my list</li></ul>", parser3.TransformToHtml());
            Assert::AreEqual<bool>(true, parser3.HasHtmlTags());
        }

        TEST_METHOD(ListTest_ListFollowedByPtagedBlockElementTest)
        {
            MarkDownParser parser("- my list\r\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list</li></ul><p>Hello</p>", parser.TransformToHtml());
            MarkDownParser parser2("* my list\r\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list</li></ul><p>Hello</p>", parser2.TransformToHtml());
            MarkDownParser parser3("+ my list\r\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list</li></ul><p>Hello</p>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_ListFollowedWithNewLineCharTest)
        {
            MarkDownParser parser("- my list\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list\rHello</li></ul>", parser.TransformToHtml());
            MarkDownParser parser2("* my list\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list\rHello</li></ul>", parser2.TransformToHtml());
            MarkDownParser parser3("+ my list\rHello");
            Assert::AreEqual<std::string>("<ul><li>my list\rHello</li></ul>", parser3.TransformToHtml());
        }

        TEST_METHOD(ListTest_InvalidListStringReturnedUnchangedTest)
        {
            MarkDownParser parser("023-34-567");
            Assert::AreEqual<std::string>("<p>023-34-567</p>", parser.TransformToHtml());
            Assert::AreEqual<bool>(false, parser.HasHtmlTags());
        }

        TEST_METHOD(ListTest_LeftDelimiterFalseCaseWithSpaceTest)
        {
            MarkDownParser parser("* foo bar*");
            Assert::AreEqual<std::string>("<ul><li>foo bar*</li></ul>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }

        TEST_METHOD(OrderedListTest_SimpleValidListTest)
        {
            MarkDownParser parser("1. hello");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_MultipleSimpleValidListTest)
        {
            MarkDownParser parser("1. hello\n2. Hi");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello</li><li>Hi</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_ListTestsWithInterHyphen)
        {
            MarkDownParser parser("1. hello world - hello hello");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello world - hello hello</li></ol>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }
        TEST_METHOD(OrderedListTest_MultipleListWithHyphenTests)
        {
            MarkDownParser parser("1. hello world - hello hello\r2. winner winner chicken dinner");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello world - hello hello</li><li>winner winner chicken dinner</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_MultipleListWithHyphenAndEmphasisTests)
        {
            MarkDownParser parser("1. hello world - hello hello\r- ***winner* winner** chicken dinner");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello world - hello hello</li></ol><ul><li><strong><em>winner</em> winner</strong> chicken dinner</li></ul>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_MultipleListWithLinkTest)
        {
            MarkDownParser parser("1. hello world\r2. hello hello\r3. new site = [adaptive card](www.adaptivecards.io)");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>hello world</li><li>hello hello</li><li>new site = <a href=\"www.adaptivecards.io\">adaptive card</a></li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_PtagedBlockElementFollowedByListTest)
        {
            MarkDownParser parser("Hello\r1. my list");
            Assert::AreEqual<std::string>("<p>Hello</p><ol start=\"1\"><li>my list</li></ol>", parser.TransformToHtml());
            Assert::AreEqual<bool>(true, parser.HasHtmlTags());
        }
        TEST_METHOD(OrderedListTest_ListFollowedByPtagedBlockElementTest)
        {
            MarkDownParser parser("1. my list\r\rHello");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>my list</li></ol><p>Hello</p>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_ListFollowedWithNewLineCharTest)
        {
            MarkDownParser parser("1. my list\rHello");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>my list\rHello</li></ol>", parser.TransformToHtml());
        }
        TEST_METHOD(OrderedListTest_ListStartsWithRandomNumberTest)
        {
            MarkDownParser parser("777. my list\rHello");
            Assert::AreEqual<std::string>("<ol start=\"777\"><li>my list\rHello</li></ol>", parser.TransformToHtml());
        }

        TEST_METHOD(EscapeHtmlCharactersTest_GreaterThanTest)
        {
            MarkDownParser parser("5>3");
            Assert::AreEqual<std::string>("<p>5&gt;3</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EscapeHtmlCharactersTest_LessThanTest)
        {
            MarkDownParser parser("3<5");
            Assert::AreEqual<std::string>("<p>3&lt;5</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EscapeHtmlCharactersTest_QuotationTest)
        {
            MarkDownParser parser("\"Hello World!\"");
            Assert::AreEqual<std::string>("<p>&quot;Hello World!&quot;</p>", parser.TransformToHtml());
        }
        TEST_METHOD(EscapeHtmlCharactersTest_AmpersandTest)
        {
            MarkDownParser parser("Green Eggs & Ham");
            Assert::AreEqual<std::string>("<p>Green Eggs &amp; Ham</p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_NoMarkdown)
        {
            MarkDownParser parser("以前の製品のリンクで検索");
            Assert::AreEqual<std::string>("<p>以前の製品のリンクで検索</p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_Bold)
        {
            MarkDownParser parser("**以前の製品のリンクで検索**");
            Assert::AreEqual<std::string>("<p><strong>以前の製品のリンクで検索</strong></p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_BoldSentence)
        {
            MarkDownParser parser("How about **以前の製品のリンクで検索**");
            Assert::AreEqual<std::string>("<p>How about <strong>以前の製品のリンクで検索</strong></p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_BoldSentenceLeadingNonLatin)
        {
            MarkDownParser parser("以前の製品のリンクで検索 **以前の製品のリンクで検索**");
            Assert::AreEqual<std::string>("<p>以前の製品のリンクで検索 <strong>以前の製品のリンクで検索</strong></p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_BoldSentenceLeadingNonLatinNoSpace)
        {
            MarkDownParser parser("以前の製品のリンクで検索**以前の製品のリンクで検索**");
            Assert::AreEqual<std::string>("<p>以前の製品のリンクで検索<strong>以前の製品のリンクで検索</strong></p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_BoldSentenceNoWhitespace)
        {
            MarkDownParser parser("How about**以前の製品のリンクで検索**");
            Assert::AreEqual<std::string>("<p>How about<strong>以前の製品のリンクで検索</strong></p>", parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_NewlineWithLink)
        {
            MarkDownParser parser("It's OK!\rClick [以前の製品のリンクで検索](https://www.microsoft.com)\rClick [以前の製品のリンクで検索](https://www.microsoft.com)");
            Assert::AreEqual<std::string>("<p>It's OK!\rClick <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a>\rClick <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a></p>",
                parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_NumberedListWithLink)
        {
            MarkDownParser parser("1. Click [以前の製品のリンクで検索](https://www.microsoft.com)\r2. Click [以前の製品のリンクで検索](https://www.microsoft.com)");
            Assert::AreEqual<std::string>("<ol start=\"1\"><li>Click <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a></li><li>Click <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a></li></ol>",
                parser.TransformToHtml());
        }

        TEST_METHOD(NonLatinCharacters_NumberedListWithLinkLeadingText)
        {
            MarkDownParser parser("It's not OK!\r1. Click [以前の製品のリンクで検索](https://www.microsoft.com)\r2. Click [以前の製品のリンクで検索](https://www.microsoft.com)");
            Assert::AreEqual<std::string>("<p>It's not OK!</p><ol start=\"1\"><li>Click <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a></li><li>Click <a href=\"https://www.microsoft.com\">以前の製品のリンクで検索</a></li></ol>",
                parser.TransformToHtml());
        }

        TEST_METHOD(EscapeHtmlCharactersTest_CanDetectEscapeTest)
        {
            MarkDownParser parser("");
            Assert::AreEqual<bool>(false, parser.IsEscaped());

            (void) parser.TransformToHtml();
            Assert::AreEqual<bool>(false, parser.IsEscaped());

            MarkDownParser parser1("&");
            (void) parser1.TransformToHtml();
            Assert::AreEqual<bool>(true, parser1.IsEscaped());

            MarkDownParser parser2("Hello World&");
            (void) parser2.TransformToHtml();
            Assert::AreEqual<bool>(true, parser2.IsEscaped());

            MarkDownParser parser3(" & ");
            (void) parser3.TransformToHtml();
            Assert::AreEqual<bool>(true, parser3.IsEscaped());
        }
    };
}
