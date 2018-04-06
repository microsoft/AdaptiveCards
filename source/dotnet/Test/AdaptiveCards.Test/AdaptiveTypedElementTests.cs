using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveTypedElementTests
    {
        private void TestGetElementById<T>(AdaptiveTypedElement parent, string id) where T : AdaptiveTypedElement
        {
            var element = parent.GetElementById<T>(id);

            Assert.IsNotNull(element);
        }

        [TestMethod]
        public void TestGetAdaptiveCardById()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
	""type"": ""AdaptiveCard"",
	""id"": ""myCard""
}";
            var card = AdaptiveCard.FromJson(json).Card;
            TestGetElementById<AdaptiveCard>(card, "myCard");
        }

        [TestMethod]
        public void TestGetAdaptiveColumnById()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""ColumnSet"",
			""columns"": [
				{
					""type"": ""Column"",
                    ""id"": ""myColumn""

                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            TestGetElementById<AdaptiveColumn>(card, "myColumn");
        }

        [TestMethod]
        public void TestGetAdaptiveImageFromAdaptiveImageSetById()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""ImageSet"",
			""images"": [
				{
					""type"": ""Image"",
                    ""id"": ""myImage"",
                    ""url"": ""https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg""
                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            TestGetElementById<AdaptiveImage>(card, "myImage");
        }

        [TestMethod]
        public void TestGetElementFromAdaptiveContainerById()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""Container"",
			""items"": [
				{
					""type"": ""TextBlock"",
                    ""id"": ""myTextBlock"",
                    ""text"": """"
                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            TestGetElementById<AdaptiveTextBlock>(card, "myTextBlock");
        }

        [TestMethod]
        public void TestSetImage()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""Container"",
			""items"": [
				{
					""type"": ""Image"",
                    ""id"": ""myImage"",
                    ""url"": ""https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg""
                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var imageUrl = "http://messagecardplayground.azurewebsites.net/assets/airplane.png";
            card.SetImage("myImage", imageUrl);
            var image = card.GetElementById<AdaptiveImage>("myImage");
            Assert.AreEqual(imageUrl, image.Url.ToString());
        }

        [TestMethod]
        public void TestSetTextOnTextBlock()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""Container"",
			""items"": [
				{
					""type"": ""TextBlock"",
                    ""id"": ""myTextBlock"",
                    ""text"": """"
                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var text = "Text";
            card.SetText("myTextBlock", text);
            var textBlock = card.GetElementById<AdaptiveTextBlock>("myTextBlock");
            Assert.AreEqual(text, textBlock.Text);
        }

        [TestMethod]
        public void TestSetTextOnTextInput()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
	""body"": [
		{
			""type"": ""Container"",
			""items"": [
				{
					""type"": ""Input.Text"",
                    ""id"": ""myTextInput""
                }
			]
		}
	]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var text = "Text";
            card.SetText("myTextInput", text);
            var textInput = card.GetElementById<AdaptiveTextInput>("myTextInput");
            Assert.AreEqual(text, textInput.Value);
        }
    }
}