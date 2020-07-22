package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

public class FactSetPropertiesTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        final String factSetNoDefaultValues =
            "{\"facts\":[{\"title\":\"Title\",\"value\":\"Value\"}]," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"Sample id\"," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"FactSet\"}\n";

        FactSet factSet = TestUtil.createMockFactSet(TestUtil.createMockFact("Title", "Value"));
        factSet.SetFallbackType(FallbackType.Content);
        factSet.SetFallbackContent(TestUtil.createMockImage());
        factSet.SetHeight(HeightType.Stretch);
        factSet.SetId("Sample id");
        factSet.SetIsVisible(false);
        factSet.SetSeparator(true);
        factSet.SetSpacing(Spacing.Medium);

        Assert.assertEquals(factSetNoDefaultValues, factSet.Serialize());
    }

    @Test
    public void FactsTestjsdfhjisdc() throws Exception
    {
        {
            final String factSetEmptyFacts = "{\"facts\":[],\"type\":\"FactSet\"}\n";
            FactSet factSet = TestUtil.createMockFactSet();
            Assert.assertEquals(factSetEmptyFacts, factSet.Serialize());

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(factSetEmptyFacts), "1.0");
                Assert.fail();
            }
            catch (Exception e)
            {
                Assert.fail();
            }

        }

        {
            final String factSetWithFact = "{\"facts\":[{\"title\":\"Title\",\"value\":\"Value\"}],\"type\":\"FactSet\"}\n";
            FactSet factSet = TestUtil.createMockFactSet(TestUtil.createMockFact("Title", "Value"));
            Assert.assertEquals(factSetWithFact, factSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(factSetWithFact), "1.0");
            FactSet parsedFactSet = TestUtil.castToFactSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(1, parsedFactSet.GetFacts().size());

            final String factJson = "{\"title\":\"Title\",\"value\":\"Value\"}\n";
            Fact parsedFact = parsedFactSet.GetFacts().get(0);
            Assert.assertEquals(factJson, parsedFact.Serialize());
        }
    }
}
