package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class ShowCardActionPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }


    @Test
    public void cardTest() throws Exception
    {

        {
            final String showCardActionWithNoCard = "{\"type\":\"Action.ShowCard\"}";

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(showCardActionWithNoCard), "1.0");
                Assert.fail();
            }
            catch (IOException e)
            {
                // Expecting failure due to card not existing
                Assert.assertEquals(true, e.getMessage().contains("Expected JSON Object"));
            }
            catch (Exception e){
                Assert.fail();
            }
        }

        {
            final String showCardActionWithEmptyCard = "{\"card\"{},\"type\":\"Action.ShowCard\"}";

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(showCardActionWithEmptyCard), "1.0");
                Assert.fail();
            }
            catch (IOException e)
            {
                // Expecting failure due to card not existing
                Assert.assertEquals(true, e.getMessage().contains("Expected JSON Object"));
            }
            catch (Exception e){
                Assert.fail();
            }
        }

        {
            final String showCardActionWithCard = "{\"card\":{" +
                "\"actions\":[{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}]," +
                "\"body\":[{\"text\":\"Test\",\"type\":\"TextBlock\"}]," +
                "\"type\":\"AdaptiveCard\",\"version\":\"1.0\"" +
                "},\"type\":\"Action.ShowCard\"}\n";

            ShowCardAction showCardAction = TestUtil.createMockShowCardAction(TestUtil.createSampleCard());
            Assert.assertEquals(showCardActionWithCard, showCardAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(showCardActionWithCard), "1.0");
            ShowCardAction parsedShowCardAction = TestUtil.castToShowCardAction(result.GetAdaptiveCard().GetActions().get(0));

            AdaptiveCard showCardActionCard = parsedShowCardAction.GetCard();

            Assert.assertEquals("1.0", showCardActionCard.GetVersion());

            Assert.assertEquals(1, showCardActionCard.GetBody().size());
            TextBlock textBlock = TestUtil.castToTextBlock(showCardActionCard.GetBody().get(0));
            Assert.assertEquals("Test", textBlock.GetText());

            Assert.assertEquals(1, showCardActionCard.GetActions().size());
            OpenUrlAction openUrlAction = TestUtil.castToOpenUrlAction(showCardActionCard.GetActions().get(0));
            Assert.assertEquals("http://", openUrlAction.GetUrl());
        }

    }

    public static final String s_defaultShowCardJson = "{\"type\":\"Action.ShowCard\"}\n";

}
