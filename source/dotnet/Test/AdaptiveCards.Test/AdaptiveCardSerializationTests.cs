using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardSerializationTests
    {
        [TestMethod]
        public void TestSerializingTextBlock()
        {
            var card = new AdaptiveCard()
            {
                Body =
                {
                    new TextBlock()
                    {
                        Text = "Hello world"
                    }
                }
            };

            string json = card.ToJson();

            // Re-parse the card
            card = AdaptiveCard.FromJson(json).Card;

            // Ensure there's a text element
            Assert.AreEqual(1, card.Body.Count);
            Assert.IsInstanceOfType(card.Body[0], typeof(TextBlock));
            Assert.AreEqual("Hello world", (card.Body[0] as TextBlock).Text);
        }
    }
}
