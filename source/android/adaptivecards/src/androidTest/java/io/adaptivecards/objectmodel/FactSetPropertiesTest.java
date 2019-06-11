package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class FactSetPropertiesTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {

    }

    @Test
    public void FactsTest() throws Exception
    {
        {
            final String factSetEmptyFacts = "{\"facts\":[],\"type\":\"FactSet\"}\n";
            FactSet factSet = TestUtil.createMockFactSet();
            Assert.assertEquals(factSetEmptyFacts, factSet.Serialize());

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseElementStringInCard(factSetEmptyFacts), "1.0");
                Assert.fail();
            }
            catch (IOException e)
            {
                Assert.assertEquals(true, e.getMessage().contains("Could not parse required key: facts. It was not found"));
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

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementStringInCard(factSetWithFact), "1.0");
            FactSet parsedFactSet = TestUtil.castToFactSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(1, parsedFactSet.GetFacts().size());

            final String factJson = "{\"title\":\"Title\",\"value\":\"Value\"}\n";
            Fact parsedFact = parsedFactSet.GetFacts().get(0);
            Assert.assertEquals(factJson, parsedFact.Serialize());
        }
    }
}
