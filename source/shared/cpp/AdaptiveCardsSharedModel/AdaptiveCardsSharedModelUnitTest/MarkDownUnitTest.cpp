#include "stdafx.h"
#include "CppUnitTest.h"
#include "MarkDownParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
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
    TEST_CLASS(Rule11_12Test)
    {
        TEST_METHOD(EscapeTest)
        {
            MarkDownParser blck("foo *\\**");
            Assert::AreEqual<string>("<p>foo <em>*</em></p>", blck.TransformToHtml());

            MarkDownParser blck2("foo **\\***");
            Assert::AreEqual<string>("<p>foo <strong>*</strong></p>", blck2.TransformToHtml());

            MarkDownParser blck3("foo __\\___");
            Assert::AreEqual<string>("<p>foo <strong>_</strong></p>", blck3.TransformToHtml());
        }
        TEST_METHOD(UnevenMatchingDelimiter)
        {
            MarkDownParser blck("**foo*");
            Assert::AreEqual<string>("<p>*<em>foo</em></p>", blck.TransformToHtml());

            MarkDownParser blck1("*foo**");
            Assert::AreEqual<string>("<p><em>foo</em>*</p>", blck1.TransformToHtml());

            MarkDownParser blck2("***foo**");
            Assert::AreEqual<string>("<p>*<strong>foo</strong></p>", blck2.TransformToHtml());

            MarkDownParser blck3("*foo****");
            Assert::AreEqual<string>("<p><em>foo</em>***</p>", blck3.TransformToHtml());

            MarkDownParser blck4("**Gomphocarpus (*Gomphocarpus physocarpus*, syn.\n*Asclepias physocarpa*)**");
            Assert::AreEqual<string>("<p><strong>Gomphocarpus (<em>Gomphocarpus physocarpus</em>, syn.\n<em>Asclepias physocarpa</em>)</strong></p>", 
                blck4.TransformToHtml());

            MarkDownParser blck5("*Hello* abc ***Hello* def *world***");
            Assert::AreEqual<string>("<p><em>Hello</em> abc <strong><em>Hello</em> def <em>world</em></strong></p>", blck5.TransformToHtml());
        }
        TEST_METHOD(TmpTest)
        {
            MarkDownParser blck1("*foo**bar**baz*");
            Assert::AreEqual<string>("<p><em>foo<strong>bar</strong>baz</em></p>", blck1.TransformToHtml());
            
        }
    };
    TEST_CLASS(Rule13Test)
    {
        TEST_METHOD(strongEmphasisNesting)
        {
            MarkDownParser blck("****foo****");
            Assert::AreEqual<string>("<p><strong><strong>foo</strong></strong></p>", blck.TransformToHtml());
            MarkDownParser blck2("******foo******");
            Assert::AreEqual<string>("<p><strong><strong><strong>foo</strong></strong></strong></p>", blck2.TransformToHtml());
        }
    };
    TEST_CLASS(Rule14Test)
    {
        TEST_METHOD(strongAndEmpEmphasisNesting)
        {
            MarkDownParser blck("***foo***");
            Assert::AreEqual<string>("<p><strong><em>foo</em></strong></p>", blck.TransformToHtml());

            MarkDownParser blck2("_____foo_____");
            Assert::AreEqual<string>("<p><strong><strong><em>foo</em></strong></strong></p>", blck2.TransformToHtml());
        }
    };

    TEST_CLASS(Rule15Test)
    {
        TEST_METHOD(OverrapingTest)
        {
            MarkDownParser blck("*foo _bar* baz_");
            Assert::AreEqual<string>("<p><em>foo _bar</em> baz_</p>", blck.TransformToHtml());

            MarkDownParser blck2("*foo __bar *baz bim__ bam*");
            Assert::AreEqual<string>("<p><em>foo <strong>bar *baz bim</strong> bam</em></p>", blck2.TransformToHtml());
        }
    };

    TEST_CLASS(Rule16Test)
    {
        TEST_METHOD(strongEmphasis)
        {
            MarkDownParser blck("**foo **bar baz**");
            Assert::AreEqual<string>("<p>**foo <strong>bar baz</strong></p>", blck.TransformToHtml());

            MarkDownParser blck2("*foo *bar baz*");
            Assert::AreEqual<string>("<p>*foo <em>bar baz</em></p>", blck2.TransformToHtml());

            MarkDownParser blck3("**K *J *foo**bar* *cool*");
            Assert::AreEqual<string>("<p><strong>K *J *foo</strong>bar* <em>cool</em></p>", blck3.TransformToHtml());

            MarkDownParser blck4("**m *J *foo**bar *cool**");
            Assert::AreEqual<string>("<p><strong>m *J *foo</strong>bar <em>cool</em>*</p>", blck4.TransformToHtml());
        }
#if 1
        TEST_METHOD(tmpTest)
        {
            MarkDownParser blck5("**H *foo**bar***");
            Assert::AreEqual<string>("<p><strong>H *foo</strong>bar***</p>", blck5.TransformToHtml());
        }
#endif
    };
}
