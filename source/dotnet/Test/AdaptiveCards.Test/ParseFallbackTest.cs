using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class ParseFallbackTest
    {
        [TestMethod]
        public void DuplicateFallbackIdNestedOk()
        {
            string json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.2"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""First textblock"",
                  ""id"": ""duplicate"",
                  ""fallback"": {
                    ""type"": ""TextBlock"",
                    ""id"": ""duplicate"",
                    ""text"": ""First fallback textblock"",
                    ""fallback"": {
                      ""type"": ""TextBlock"",
                      ""id"": ""duplicate"",
                      ""text"": ""Second fallback textblock""
                    }
                  }
                }
              ]
            }";

            AdaptiveCard.FromJson(json);
        }

        [TestMethod]
        public void FallbackParsingJsonTest()
        {
            string json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
  	  ""type"": ""Container"",
  	  ""id"": ""A"",
  	  ""requires"": {
  	  	""adaptiveCards"": ""1.2""
  	  },
  	  ""items"": [
  	    {
  	      ""type"": ""Container"",
  	      ""id"": ""B"",
  	      ""fallback"": {
  	        ""type"": ""Container"",
  	        ""id"": ""B"",
  	        ""items"": [
  	          {
  	            ""type"": ""TextBlock"",
  	            ""id"": ""C"",
  	            ""text"": ""B Container fallback textblock""
  	          },
  	          {
  	            ""type"": ""Image"",
  	            ""id"": ""Z"",
  	            ""url"": ""http://adaptivecards.io/content/cats/1.png""
  	          }
  	        ]
  	      },
  	      ""items"": [
  	        {
  	          ""type"": ""ColumnSet"",
  	          ""id"": ""C"",
  	          ""columns"": [
  	            {
  	              ""type"": ""Column"",
  	              ""id"": ""D"",
  	              ""width"": ""auto"",
  	              ""items"": [
  	                {
  	                  ""type"": ""Graph"",
  	                  ""id"": ""E"",
  	                  ""someProperty"": ""blah"",
  	                  ""requires"": {
  	                    ""adaptiveCards"": ""1.2""
  	                  },
  	                  ""fallback"": {
  	                    ""type"": ""Container"",
  	                    ""id"": ""E"",
  	                    ""items"": [
  	                      {
  	                        ""type"": ""Image"",
  	                        ""id"": ""I"",
  	                        ""url"": ""http://adaptivecards.io/content/cats/2.png""
  	                      },
  	                      {
  	                        ""type"": ""TextBlock"",
  	                        ""id"": ""J"",
  	                        ""text"": ""C ColumnSet fallback textblock""
  	                      }
  	                    ]
  	                  }
  	                }
  	              ]
  	            }
  	          ]
  	        }
  	      ]
  	    }
  	  ]
  	},
  	{
  	  ""type"": ""TextBlock"",
  	  ""id"": ""F"",
  	  ""text"": ""F TextBlock""
  	},
  	{
  	  ""type"": ""Input.Text"",
  	  ""id"": ""G"",
  	  ""placeholder"": ""G Input.Text""
  	},
  	{
  	  ""type"": ""Graph"",
  	  ""id"": ""H"",
  	  ""someProperty"": ""foo"",
  	  ""fallback"": {
  	    ""type"": ""Container"",
  	    ""id"": ""L"",
  	    ""requires"": {
  	      ""adaptiveCards"": ""1.2""
  	    },
  	    ""items"": [
  	      {
  	        ""type"": ""TextBlock"",
  	        ""id"": ""K"",
  	        ""text"": ""H Graph fallback TextBlock""
  	      }
  	    ]
  	  }
  	}
  ]
}";

            AdaptiveCard.FromJson(json);
        }

        [TestMethod]
        public void RequiresAndFallbackSerialization()
        {
            string json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""This element requires version 1.2"",
      ""fallback"": {
        ""type"": ""TextBlock"",
        ""text"": ""This element has no version requirement""
      },
      ""requires"": {
        ""adaptiveCards"": ""1.2"",
        ""foobar"": ""2.0""
      }
    }
  ]
}";

            var parseResult = AdaptiveCard.FromJson(json);
            var card = parseResult.Card;
            var serializedCard = card.ToJson();

            Assert.AreEqual(json, serializedCard);
        }

        [TestMethod]
        public void RequiresValidation()
        {
            string json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""This element requires version 1.2"",
      ""requires"": {
        ""adaptiveCards"": ""1.2"",
        ""foobar"": ""2""
      }
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""This element has no explicit requirements""
    }
  ]
}";

            var parseResult = AdaptiveCard.FromJson(json);
            var card = parseResult.Card;

            var textBlock = (AdaptiveTextBlock)card.Body[0];
            var textBlockNoRequires = (AdaptiveTextBlock)card.Body[1];
            AdaptiveFeatureRegistration featureRegistration = new AdaptiveFeatureRegistration();
            featureRegistration.Set("foobar", "2");

            Assert.IsTrue(textBlock.MeetsRequirements(featureRegistration));
            Assert.IsTrue(textBlockNoRequires.MeetsRequirements(featureRegistration));

            featureRegistration.Remove("foobar");
            Assert.IsFalse(textBlock.MeetsRequirements(featureRegistration));
            Assert.IsTrue(textBlockNoRequires.MeetsRequirements(featureRegistration));

            featureRegistration.Set("foobar", "1.9.9.9");
            Assert.IsFalse(textBlock.MeetsRequirements(featureRegistration));
            Assert.IsTrue(textBlockNoRequires.MeetsRequirements(featureRegistration));

            featureRegistration.Set("foobar", "99");
            Assert.IsTrue(textBlock.MeetsRequirements(featureRegistration));
            Assert.IsTrue(textBlockNoRequires.MeetsRequirements(featureRegistration));
        }

        [TestMethod]
        public void NestedFallbacksSerialization()
        {
            string json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""GraphV2"",
      ""fallback"": {
        ""type"": ""Graph"",
        ""fallback"": {
          ""type"": ""TextBlock"",
          ""text"": ""No `Graph` support?""
        }
      }
    }
  ]
}";

            var parseResult = AdaptiveCard.FromJson(json);
            var card = parseResult.Card;
            var serializedCard = card.ToJson();

            Assert.AreEqual(json, serializedCard);
        }

        [TestMethod]
        public void DropFallbacksSerialization()
        {
            string expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""text here"",
      ""fallback"": ""drop""
    }
  ]
}";

            var parseResult = AdaptiveCard.FromJson(expected);
            Assert.AreEqual(expected, parseResult.Card.ToJson());

            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveTextBlock("text here")
                    {
                        Fallback = new AdaptiveFallbackElement(AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                    }
                }
            };
            var serializedCard = card.ToJson();
            Assert.AreEqual(expected, serializedCard);
        }

        [TestMethod]
        public void InvalidFallbackStringBody()
        {
            string json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.2"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""textblock"",
                  ""fallback"": ""steve""
                }
              ]
            }";

            try
            {
                AdaptiveCard.FromJson(json);
                Assert.IsTrue(false, "Deserializing should throw an exception");
            }
            catch (AdaptiveSerializationException e)
            {
                Assert.AreEqual("The only valid string value for the fallback property is 'drop'.", e.Message, "GetReason incorrect");
            }
        }

        [TestMethod]
        public void InvalidFallbackArray()
        {
            string json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.2"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""textblock"",
                  ""fallback"": [ { ""blah"": ""2"" } ]
                }
              ]
            }";

            try
            {
                AdaptiveCard.FromJson(json);
                Assert.IsTrue(false, "Deserializing should throw an exception");
            }
            catch (AdaptiveSerializationException e)
            {
                Assert.AreEqual("Invalid value for fallback", e.Message, "GetReason incorrect");
            }
        }
    }
}
