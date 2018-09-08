using System;
using System.Collections.Generic;
using System.Collections;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardApiTests
    {
        [TestMethod]
        public void TestAssigningVersion()
        {
            AdaptiveCard card = new AdaptiveCard();
            card.Version = new AdaptiveSchemaVersion(4, 5);

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);
        }

        [TestMethod]
        public void TestAssigningVersionAsString()
        {
            AdaptiveCard card = new AdaptiveCard();
            card.Version = "4.5";

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);

            card.Version = "3";

            Assert.AreEqual(3, card.Version.Major);
            Assert.AreEqual(0, card.Version.Minor);

            card.Version = "4.1.3";

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(1, card.Version.Minor);

            try
            {
                card.Version = "tacos";
                Assert.Fail("Assigning tacos to version should fail");
            }
            catch (AssertFailedException) { throw; }
            catch { }

            try
            {
                card.Version = "1.tacos";
                Assert.Fail("Assigning 1.tacos to version should fail");
            }
            catch (AssertFailedException) { throw; }
            catch { }
        }

        [TestMethod]
        public void TestParsingCard()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);
            Assert.AreEqual(1, result.Card.Body.Count);
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingVersion()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            // TODO: No longer throwing on this exception to work around bot framework integration issues. Revisit later
            //Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingType()
        {
            var json = @"{
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        // Make sure resource information for all Images and Medias in a card are returned
        // TODO: Add test for Media information when Media type is added
        public void TestResourceInformation()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""fallbackText"": ""Fallback Text"",
  ""speak"": ""Speak"",
  ""backgroundImage"": ""http://adaptivecards.io/content/cats/1.png"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello""
    },
    {
      ""type"": ""Image"",
      ""url"": ""http://adaptivecards.io/content/cats/2.png""
    },
    {
      ""type"": ""Container"",
      ""items"": [
        {
          ""type"": ""Image"",
          ""url"": ""http://adaptivecards.io/content/cats/3.png""
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                    ""type"": ""Image"",
                    ""url"": ""http://adaptivecards.io/content/cats/2.png""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ImageSet"",
          ""images"": [
            {
              ""type"": ""Image"",
              ""url"": ""content/cats/4.png""
            }
          ]
        }
      ]
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.ShowCard"",
      ""iconUrl"": ""http://adaptivecards.io/content/cats/5.png"",
      ""card"": {
          ""type"": ""AdaptiveCard"",
          ""version"": ""1.0"",
          ""body"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Hello""
            },
            {
              ""type"": ""Image"",
              ""url"": ""http://adaptivecards.io/content/cats/6.png""
            }
          ]
      }
    }
  ]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var expected = new RemoteResourceInformation[]
            {
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/1.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/3.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "content/cats/4.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/5.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/6.png",
                    typeof(AdaptiveImage),
                    null
                )
            };
            var actual = card.GetResourceInformation();
            CollectionAssert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void TestDefaultValueHandling()
        {
            var json = @"{
	            ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
	            ""type"": ""AdaptiveCard"",
	            ""version"": ""1.0"",
	            ""body"": [
		            {
			            ""type"": ""Container"",
			            ""style"": ""asdf"",
			            ""spacing"": ""asdf"",
			            ""items"": [
				            {
					            ""type"": ""TextBlock"",
					            ""text"": ""Sample text"",
					            ""color"": ""asdf"",
					            ""size"": ""asdf"",
					            ""weight"": ""asdf""
				            },
				            {
					            ""type"": ""Image"",
					            ""url"": ""http://adaptivecards.io/content/cats/1.png"",
					            ""style"": ""asdf"",
					            ""size"": ""asdf""
				            }
			            ]
		            }
	            ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;

            // Contents of card for easier access
            AdaptiveContainer container = (AdaptiveContainer) card.Body[0];
            AdaptiveTextBlock textblock = (AdaptiveTextBlock) container.Items[0];
            AdaptiveImage image = (AdaptiveImage) container.Items[1];

            // Container property tests
            Assert.AreEqual(AdaptiveContainerStyle.Default, container.Style);
            Assert.AreEqual(AdaptiveSpacing.Default, container.Spacing);

            // TextBlock property tests
            Assert.AreEqual(AdaptiveTextColor.Default, textblock.Color);
            Assert.AreEqual(AdaptiveTextSize.Default, textblock.Size);
            Assert.AreEqual(AdaptiveTextWeight.Default, textblock.Weight);

            // Image property tests
            Assert.AreEqual(AdaptiveImageStyle.Default, image.Style);
            Assert.AreEqual(AdaptiveImageSize.Auto, image.Size);
        }

        [TestMethod]
        public void TestExplicitImagePositiveTest()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20px"",
                              ""height"": ""50px""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result.Card;
            Assert.AreEqual(card.Body.Count, 1);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(0, result.Warnings.Count);
            Assert.AreEqual(20U,imageBlock.PixelWidth);
            Assert.AreEqual(50U, imageBlock.PixelHeight);
        }

        [TestMethod]
        public void TestExplicitImageWarningMessagesWithMalformedUnits()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20"",
                              ""height"": ""50 p x""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(0U, imageBlock.PixelWidth);
            Assert.AreEqual(0U, imageBlock.PixelHeight);
            Assert.AreEqual(3, result.Warnings.Count);
            Assert.AreEqual(
                result.Warnings[0].Message,
                @"The Value ""20"" for field ""width"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.");
            Assert.AreEqual(
                result.Warnings[1].Message,
                @"The Value "" x"" was not specified as a proper unit(px), it will be ignored.");
        }

        [TestMethod]
        public void TestExplicitImageWarningMessagesWithMalformedDimensions()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": "".20px"",
                              ""height"": ""50.1234.12px""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(1, card.Body.Count);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(0U, imageBlock.PixelWidth);
            Assert.AreEqual(0U, imageBlock.PixelHeight);
            Assert.AreEqual(3, result.Warnings.Count);
            Assert.AreEqual(
                @"The Value "".20px"" for field ""width"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.",
                result.Warnings[0].Message);
            Assert.AreEqual(
                @"The Value ""50.1234.12px"" for field ""height"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.",
                result.Warnings[1].Message);
        }

        [TestMethod]
        public void TestExplicitImageTestWithMalformedDimensionsInputs()
        {
            ArrayList payloads = new ArrayList
            {
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"", 
                      ""type"": ""AdaptiveCard"", 
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": "".20px"",
                              ""height"": ""50.1234.12px""
                          }
                      ]
                  }",
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"", 
                      ""type"": ""AdaptiveCard"", 
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20,00px"",
                              ""height"": ""200.00   px""
                          }
                      ]
                  }",
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""2000 px"",
                              ""height"": ""20a0px""
                          }
                      ]
                  }",
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20.a00px"",
                              ""height"": ""20.00""
                          }
                      ]
                  }",
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": "" 20.00px"",
                              ""height"": ""2 0.00px""
                          }
                      ]
                  }",
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""200px .00px"",
                              ""height"": ""2 0px00px""
                          }
                      ]
                  }"
            };

            foreach (string payload in payloads)
            {
                var result = AdaptiveCard.FromJson(payload);
                var card = result?.Card;
                Assert.AreEqual(1, card.Body.Count);
                var imageBlock = card.Body[0] as AdaptiveImage;
                Assert.AreEqual(0U, imageBlock.PixelWidth);
                Assert.AreEqual(0U, imageBlock.PixelHeight);
                Assert.AreEqual(3, result.Warnings.Count);
            }
        }

        [TestMethod]
        public void DefaultHeightIsAuto()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                        {
                            ""type"": ""ColumnSet"",
                            ""columns"": [
                                {
                                    ""type"": ""Column"",
                                    ""items"": [
                                        {
                                            ""type"": ""TextBlock"",
                                            ""text"": ""Tell us about yourself"",
                                            ""weight"": ""bolder"",
                                            ""size"": ""medium""
                                        }
                                    ]
                                },
                                {
                                     ""type"": ""Column"",
                                     ""items"": [
                                        {
                                            ""type"": ""Image"",
                                            ""url"": ""https://upload.wikimedia.org/wikipedia/commons/b/b2/Diver_Silhouette%2C_Great_Barrier_Reef.jpg"",
                                            ""size"": ""auto"",
                                        }
                                    ]
                                }
                            ]
                        }
                    ],
                    ""actions"": [
                        {
                            ""type"": ""Action.Submit"",
                            ""title"": ""Submit""
                        }
                    ]
                }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Height, AdaptiveHeight.Auto);
            Assert.AreEqual(card.Body.Count, 1);
            var columnSet = (AdaptiveColumnSet)card.Body[0];
            Assert.AreEqual(columnSet.Height, AdaptiveHeight.Auto);
            Assert.AreEqual(columnSet.Columns.Count, 2);

            foreach(var column in columnSet.Columns)
            {
                Assert.AreEqual(column.Items.Count, 1);
                var columnContent = column.Items[0];
                Assert.AreEqual(columnContent.Height, AdaptiveHeight.Auto);
            }

        }

        [TestMethod]
        public void TestCardStretch()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""height"": ""stretch"",
                      ""body"": [
                          {
                              ""type"": ""TextBlock"",
                              ""text"": ""This is a textblock""        
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);
            Assert.AreEqual(card.Height, AdaptiveHeight.Stretch);
        }

        [TestMethod]
        public void TestElementStretch()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""TextBlock"",
                              ""text"": ""This is a textblock"",
                              ""height"": ""stretch""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);
            Assert.AreEqual(card.Body[0].Height, AdaptiveHeight.Stretch);
        }

        [TestMethod]
        public void TestImageStretch()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""height"": ""stretch"",
                              ""size"": ""small""  
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);
            Assert.AreEqual(card.Body[0].Height, AdaptiveHeight.Stretch);
        }

        [TestMethod]
        public void TestVerticalContentAlignmentColumn()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""height"": ""stretch"",
                    ""verticalContentAlignment"": ""center"",
                    ""body"": [
                        {
                            ""type"": ""ColumnSet"",
                            ""height"": ""stretch"",
                            ""columns"": [
                                {
                                    ""type"": ""Column"",
                                    ""items"": [
                                        {
                                            ""type"": ""TextBlock"",
                                            ""text"": ""This text should be at the top""
                                        }
                                    ]
                                },
                                {
                                    ""type"": ""Column"",
                                    ""verticalContentAlignment"": ""top"",
                                    ""items"": [
                                        {
                                            ""type"": ""TextBlock"",
                                            ""text"": ""This text should be at the top""
                                        }
                                    ]
                                },
                                {
                                    ""type"": ""Column"",
                                    ""verticalContentAlignment"": ""center"",
                                    ""items"": [
                                        {
                                            ""type"": ""TextBlock"",
                                            ""text"": ""This text should be at the vertical center""
                                        }
                                    ]
                                },
                                {
                                    ""type"": ""Column"",
                                    ""verticalContentAlignment"": ""bottom"",
                                    ""items"": [
                                        {
                                            ""type"": ""TextBlock"",
                                            ""text"": ""This text should be at the bottom""
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);

            var columnSet = (AdaptiveColumnSet)card.Body[0];
            Assert.AreEqual(columnSet.Height, AdaptiveHeight.Stretch);

            var columns = columnSet.Columns;
            Assert.AreEqual(4, columns.Count);

            Assert.AreEqual(columns[0].VerticalContentAlignment, AdaptiveVerticalContentAlignment.Top);
            Assert.AreEqual(columns[1].VerticalContentAlignment, AdaptiveVerticalContentAlignment.Top);
            Assert.AreEqual(columns[2].VerticalContentAlignment, AdaptiveVerticalContentAlignment.Center);
            Assert.AreEqual(columns[3].VerticalContentAlignment, AdaptiveVerticalContentAlignment.Bottom);
        }

        [TestMethod]
        public void TestVerticalContentAlignmentContainer()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                        {
                            ""type"": ""Container"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""This text should be at the top""
                                }
                            ]
                        },
                        {
                            ""type"": ""Container"",
                            ""verticalContentAlignment"": ""top"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""This text should be at the top""
                                }
                            ]
                        },
                        {
                            ""type"": ""Container"",
                            ""verticalContentAlignment"": ""center"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""This text should be at the vertical center""
                                }
                            ]
                        },
                        {
                            ""type"": ""Container"",
                            ""verticalContentAlignment"": ""bottom"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""This text should be at the bottom""
                                }
                            ]
                        }
                    ]
                }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            var containers = card.Body;
            Assert.AreEqual(containers.Count, 4);

            Assert.AreEqual(((AdaptiveContainer)containers[0]).VerticalContentAlignment, AdaptiveVerticalContentAlignment.Top);
            Assert.AreEqual(((AdaptiveContainer)containers[1]).VerticalContentAlignment, AdaptiveVerticalContentAlignment.Top);
            Assert.AreEqual(((AdaptiveContainer)containers[2]).VerticalContentAlignment, AdaptiveVerticalContentAlignment.Center);
            Assert.AreEqual(((AdaptiveContainer)containers[3]).VerticalContentAlignment, AdaptiveVerticalContentAlignment.Bottom);
        }
    }
}
