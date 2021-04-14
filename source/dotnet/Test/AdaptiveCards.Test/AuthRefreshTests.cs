using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using System.IO;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AuthRefreshTests
    {
        [TestMethod]
        public void ParseRefreshTest()
        {
            string json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.4"",
              ""refresh"" : {
                ""action"":{
                  ""type"": ""Action.Execute"",
                  ""data"": {
                    ""HereIs"": ""Some Data""
                  },
                  ""verb"" : ""doStuff""
                },
                ""userIds"" : [
                  ""user1"",
                  ""user2"",
                  ""user3"",
                ]
              },
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""This is a text block"",
                }
              ]
            }";

            AdaptiveCard card = AdaptiveCard.FromJson(json).Card;

            // Check that the refresh values are populated
            Assert.IsNotNull(card.Refresh);

            // Check UserIds
            Assert.IsNotNull(card.Refresh.UserIds);
            Assert.AreEqual(card.Refresh.UserIds[0], "user1");
            Assert.AreEqual(card.Refresh.UserIds[1], "user2");
            Assert.AreEqual(card.Refresh.UserIds[2], "user3");

            // Check Execute Action
            Assert.IsNotNull(card.Refresh.Action);
            Assert.AreEqual(card.Refresh.Action.Verb, "doStuff");

            // Check Action data json
            JsonTextReader reader = new JsonTextReader(new StringReader(card.Refresh.Action.DataJson));
            reader.Read();
            Assert.AreEqual(reader.TokenType.ToString(), "StartObject");
            reader.Read();
            Assert.AreEqual(reader.TokenType.ToString(), "PropertyName");
            Assert.AreEqual(reader.Value, "HereIs");
            reader.Read();
            Assert.AreEqual(reader.TokenType.ToString(), "String");
            Assert.AreEqual(reader.Value, "Some Data");
            reader.Read();
            Assert.AreEqual(reader.TokenType.ToString(), "EndObject");
        }


        [TestMethod]
        public void ParseAuthTest()
        {
            string json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.4"",
              ""authentication"" : {
                ""text"" : ""Please Authenticate"",
                ""connectionName"" : ""myConnection"",
                ""tokenExchangeResource"" : {
                  ""id"" : ""tokenExchangeId"",
                  ""uri"" : ""http:\\token.exchange.resource"",
                  ""providerId"" : ""myProvider""
                },
                ""buttons"" : [
                  {
                    ""type"" : ""signIn"",
                    ""title"" : ""Click here to sign in"",
                    ""image"" : ""http:\\image.uri"",
                    ""value"" : ""buttonValue""
                  }
                ]
              },
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""This is a text block"",
                }
              ]
            }";

            AdaptiveCard card = AdaptiveCard.FromJson(json).Card;

            // Check that the authentication values are populated
            Assert.IsNotNull(card.Authentication);
            Assert.AreEqual(card.Authentication.Text, "Please Authenticate");
            Assert.AreEqual(card.Authentication.ConnectionName, "myConnection");

            // Check the TokenExchangeResource
            Assert.IsNotNull(card.Authentication.TokenExchangeResource);
            Assert.AreEqual(card.Authentication.TokenExchangeResource.Id, "tokenExchangeId");
            Assert.AreEqual(card.Authentication.TokenExchangeResource.Uri, "http:\\token.exchange.resource");
            Assert.AreEqual(card.Authentication.TokenExchangeResource.ProviderId, "myProvider");

            // Check the button array
            Assert.IsNotNull(card.Authentication.Buttons);
            Assert.AreEqual(card.Authentication.Buttons[0].Type, "signIn");
            Assert.AreEqual(card.Authentication.Buttons[0].Title, "Click here to sign in");
            Assert.AreEqual(card.Authentication.Buttons[0].Image, "http:\\image.uri");
            Assert.AreEqual(card.Authentication.Buttons[0].Value, "buttonValue");
        }
    }
}
