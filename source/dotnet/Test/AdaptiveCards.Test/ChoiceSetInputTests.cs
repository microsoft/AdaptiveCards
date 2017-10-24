using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class ChoiceSetInputTests
    {

        [TestMethod]
        public void TestChoiceSetExpanded()
        {
            var card = new AdaptiveCard
            {
                Body = new List<AdaptiveElement>()
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Hello",
                        Weight = AdaptiveTextWeight.Bolder
                    },
                    new AdaptiveChoiceSetInput()
                    {
                        Id = "choiceTest",
                        Style = AdaptiveChoiceInputStyle.Expanded
                    }
                }
            };


            var expected = @"""style"": ""expanded""";

            StringAssert.Contains(card.ToJson(), expected);
        }
    }
}
