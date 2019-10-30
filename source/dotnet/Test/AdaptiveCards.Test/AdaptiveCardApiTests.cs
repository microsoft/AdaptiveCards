// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Collections;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Threading.Tasks;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardApiTests
    {
        [TestMethod]
        public void TestAssigningVersion()
        {
            AdaptiveCard card = new AdaptiveCard("1.0");

            Assert.AreEqual(1, card.Version.Major);
            Assert.AreEqual(0, card.Version.Minor);
            card.Version = new AdaptiveSchemaVersion(4, 5);

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);
        }

        [TestMethod]
        public void TestAssigningVersionAsString()
        {
            AdaptiveCard card = new AdaptiveCard("1.0");
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
            // By default we should be throwing an exception when no version present.
            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json),
                                                                   "Having no version tag should cause an exception to be thrown.");

            // Or we can supply a replacement version to use
            AdaptiveCard.OnDeserializingMissingVersion = () => new AdaptiveSchemaVersion(0, 5);
            var card = AdaptiveCard.FromJson(json);
            Assert.AreEqual(new AdaptiveSchemaVersion(0, 5), card.Card.Version);

            // But make sure that if the callback throws an exception that it is allowed through
            AdaptiveCard.OnDeserializingMissingVersion = () => throw new Exception();
            Assert.ThrowsException<Exception>(() => AdaptiveCard.FromJson(json),
                                              "An exception thrown from an OnDeserializingMissingVersion handler should be allowed to propagate out.");
            AdaptiveCard.OnDeserializingMissingVersion = null;
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
                    "image"
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    "image"
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/3.png",
                    "image"
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    "image"
                ),
                new RemoteResourceInformation(
                    "content/cats/4.png",
                    "image"
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/5.png",
                    "image"
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/6.png",
                    "image"
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
            AdaptiveContainer container = (AdaptiveContainer)card.Body[0];
            AdaptiveTextBlock textblock = (AdaptiveTextBlock)container.Items[0];
            AdaptiveImage image = (AdaptiveImage)container.Items[1];

            // Container property tests
            Assert.IsNull(container.Style);
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
            Assert.AreEqual(20U, imageBlock.PixelWidth);
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
            Assert.AreEqual(2, result.Warnings.Count);
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
            Assert.AreEqual(2, result.Warnings.Count);
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
                Assert.AreEqual(2, result.Warnings.Count);
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

            foreach (var column in columnSet.Columns)
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

        [TestMethod]
        public void BadImageWidthsAsAdditionalProperties()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""test-card-prop"" : ""giraffe"",
                    ""body"": [
                        {
                            ""type"": ""Image"",
                            ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                            ""width"": ""50px"",
                            ""height"": ""50px"",
                            ""test-image-prop"" : ""elephant""
                        },
                        {
                            ""type"": ""Image"",
                            ""url"": ""http://adaptivecards.io/content/cats/2.png"",
                            ""width"": ""50boguspx"",
                            ""height"": ""50boguspx"",
                            ""test-image-prop"" : ""cheetah""
                        }
                    ]
                }";

            var result = AdaptiveCard.FromJson(payload);

            // Expect one warning for each unknown property (3)
            // and one for each bad pixel size (2)
            Assert.AreEqual(5, result.Warnings.Count);

            // Check the card properties
            var card = result.Card;
            Assert.AreEqual("AdaptiveCard", card.Type);
            Assert.AreEqual(1, card.Version.Major);
            Assert.AreEqual(0, card.Version.Minor);

            // One AdditionalProp
            Assert.AreEqual(1, card.AdditionalProperties.Count);
            Assert.AreEqual("giraffe", card.AdditionalProperties["test-card-prop"]);

            // Check the properties on the first image
            var body = result.Card.Body;
            Assert.AreEqual(2, body.Count);

            var firstElement = body[0];
            Assert.AreEqual("Image", firstElement.Type);

            var image = firstElement as AdaptiveImage;
            Assert.AreEqual("http://adaptivecards.io/content/cats/1.png", image.UrlString);
            Assert.AreEqual((UInt32)50, image.PixelWidth);
            Assert.AreEqual((UInt32)50, image.PixelHeight);

            // One AdditionalProp
            Assert.AreEqual(1, image.AdditionalProperties.Count);
            Assert.AreEqual("elephant", image.AdditionalProperties["test-image-prop"]);

            // Check the properties on the second image
            var secondElement = body[1];
            Assert.AreEqual("Image", secondElement.Type);

            image = secondElement as AdaptiveImage;
            Assert.AreEqual("http://adaptivecards.io/content/cats/2.png", image.UrlString);

            // One AdditionalProp
            Assert.AreEqual(1, image.AdditionalProperties.Count);
            Assert.AreEqual("cheetah", image.AdditionalProperties["test-image-prop"]);
        }

        [TestMethod]
        public void BackgroundImageBackCompatWithLegacyUriType()
        {
            var testUrl = new Uri("https://bing.com");

            var card = new AdaptiveCard("1.0");
            card.BackgroundImage = testUrl;

            Assert.AreEqual(card.BackgroundImage.UrlString, testUrl.ToString());
            Assert.AreEqual(card.BackgroundImage.Url, testUrl);
        }

        [TestMethod]
        public void TestParseActionSetElement()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.2"",
                    ""body"": [
                      {
                        ""type"": ""ActionSet"",
                        ""actions"": [
                          {
                            ""type"": ""Action.Submit"",
                            ""title"": ""Action.Submit"",
                            ""data"": {
                              ""x"": 13
                            }
                          },
                          {
                            ""type"": ""Action.OpenUrl"",
                            ""title"": ""OpenUrl"",
                            ""url"": ""http://adaptivecards.io""
                          },
                          {
                            ""type"": ""Action.ShowCard"",
                            ""title"": ""ShowCard"",
                            ""card"": {
                              ""type"": ""AdaptiveCard"",
                              ""body"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""This is a show card""
                                }
                              ]
                            }
                          },
                          {
                            ""type"": ""Action.ToggleVisibility"",
                            ""title"": ""Toggle"",
                            ""targetElements"": [ ""test"" ]
                          }
                        ]
                      }
                    ],
                  ""actions"": []
                }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            var containers = card.Body;
            Assert.AreEqual(containers.Count, 1);

            var actionSet = (AdaptiveActionSet)card.Body[0];
            Assert.AreEqual(4, actionSet.Actions.Count);

            Assert.IsTrue(actionSet.Actions[0] is AdaptiveSubmitAction);
            var actionSubmit = (AdaptiveSubmitAction)actionSet.Actions[0];
            Assert.IsTrue(actionSubmit.Title == "Action.Submit");
            Assert.IsNotNull(actionSubmit.Data);

            Assert.IsTrue(actionSet.Actions[1] is AdaptiveOpenUrlAction);
            var actionOpenUrl = (AdaptiveOpenUrlAction)actionSet.Actions[1];
            Assert.IsTrue(actionOpenUrl.Title == "OpenUrl");
            Assert.IsFalse(String.IsNullOrWhiteSpace(actionOpenUrl.UrlString));

            Assert.IsTrue(actionSet.Actions[2] is AdaptiveShowCardAction);
            var actionShowCard = (AdaptiveShowCardAction)actionSet.Actions[2];
            Assert.IsTrue(actionShowCard.Title == "ShowCard");
            Assert.IsNotNull(actionShowCard.Card);

            Assert.IsTrue(actionSet.Actions[3] is AdaptiveToggleVisibilityAction);
            var actionToggleVisibility = (AdaptiveToggleVisibilityAction)actionSet.Actions[3];
            Assert.IsTrue(actionToggleVisibility.Title == "Toggle");
            Assert.IsTrue(actionToggleVisibility.TargetElements.Count != 0);
        }

        [TestMethod]
        public void TestObjectModelActionSetElement()
        {
            AdaptiveCard card = new AdaptiveCard(new AdaptiveSchemaVersion("1.2"));
            AdaptiveActionSet actionSet = new AdaptiveActionSet();
            card.Body.Add(actionSet);

            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Title = "Action.Submit",
                DataJson = "{\"x\": 13}"
            };
            actionSet.Actions.Add(submitAction);

            AdaptiveOpenUrlAction openUrlAction = new AdaptiveOpenUrlAction
            {
                Title = "OpenUrl",
                UrlString = "http://adaptivecards.io"
            };
            actionSet.Actions.Add(openUrlAction);

#pragma warning disable 0618
            AdaptiveShowCardAction showCardAction = new AdaptiveShowCardAction
            {
                Title = "ShowCard",
                Card = new AdaptiveCard
                {
                    Body = new List<AdaptiveElement>
                    {
                        new AdaptiveTextBlock
                        {
                            Text = "This is a show card"
                        }
                    }
                }
            };
#pragma warning restore 0618

            actionSet.Actions.Add(showCardAction);

            AdaptiveToggleVisibilityAction toggleVisibilityAction = new AdaptiveToggleVisibilityAction
            {
                Title = "Toggle",
                TargetElements = new List<AdaptiveTargetElement> { "test" }
            };
            actionSet.Actions.Add(toggleVisibilityAction);

            // This lines are not indented so the comparisson doesn't fail due to extra spaces
            var expectedJson =
@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""ActionSet"",
      ""actions"": [
        {
          ""type"": ""Action.Submit"",
          ""data"": {
            ""x"": 13
          },
          ""title"": ""Action.Submit""
        },
        {
          ""type"": ""Action.OpenUrl"",
          ""url"": ""http://adaptivecards.io"",
          ""title"": ""OpenUrl""
        },
        {
          ""type"": ""Action.ShowCard"",
          ""card"": {
            ""type"": ""AdaptiveCard"",
            ""version"": ""1.0"",
            ""body"": [
              {
                ""type"": ""TextBlock"",
                ""text"": ""This is a show card""
              }
            ]
          },
          ""title"": ""ShowCard""
        },
        {
          ""type"": ""Action.ToggleVisibility"",
          ""targetElements"": [
            ""test""
          ],
          ""title"": ""Toggle""
        }
      ]
    }
  ]
}";

            var outputJson = card.ToJson();
            Assert.AreEqual(outputJson, expectedJson);
        }

        [TestMethod]
        public void TestParseMinHeight()
        {
            var payload =
                @"{
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.2"",
                    ""minHeight"": ""500px"",
                    ""body"": [
                      {
                        ""type"": ""ColumnSet"",
                        ""minHeight"": ""100px"",
                        ""columns"": [
                          {
                            ""type"": ""Column"",
                            ""minHeight"": ""200px"",
                            ""items"": [
                              {
                                ""type"": ""TextBlock"",
                                ""text"": ""TextBlock""
                              }
                            ]
                          },
                          {
                            ""type"": ""Column"",
                            ""items"": [
                              {
                                ""type"": ""Container"",
                                ""minHeight"": ""300px"",
                                ""items"": [
                                  {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""TextBlock""
                                  }
                                ]
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(500u, card.PixelMinHeight);

            var containers = card.Body;
            Assert.AreEqual(containers.Count, 1);

            var columnSet = (AdaptiveColumnSet)card.Body[0];
            Assert.AreEqual(100u, columnSet.PixelMinHeight);

            var columns = columnSet.Columns;
            Assert.AreEqual(200u, columns[0].PixelMinHeight);
            Assert.AreEqual(0u, columns[1].PixelMinHeight);

            var container = (AdaptiveContainer)columns[1].Items[0];
            Assert.AreEqual(300u, container.PixelMinHeight);
        }

        [TestMethod]
        public void TestObjectModelMinHeight()
        {
            AdaptiveCard card = new AdaptiveCard(new AdaptiveSchemaVersion("1.2"))
            {
                PixelMinHeight = 500,
                Body = new List<AdaptiveElement>
                {
                    new AdaptiveColumnSet()
                    {
                        PixelMinHeight = 100,
                        Columns = new List<AdaptiveColumn>
                        {
                            new AdaptiveColumn
                            {
                                PixelMinHeight = 200,
                                Items = new List<AdaptiveElement>
                                {
                                    new AdaptiveTextBlock
                                    {
                                        Text = "TextBlock"
                                    }
                                }
                            },
                            new AdaptiveColumn
                            {
                               Items = new List<AdaptiveElement>
                               {
                                   new AdaptiveContainer
                                   {
                                       PixelMinHeight = 300,
                                       Items = new List<AdaptiveElement>
                                       {
                                            new AdaptiveTextBlock
                                            {
                                                Text = "TextBlock"
                                            }
                                       }
                                   }
                               }
                            }
                        }
                    }
                }
            };

            // This lines are not indented so the comparisson doesn't fail due to extra spaces
            var expectedJson =
@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""ColumnSet"",
      ""columns"": [
        {
          ""type"": ""Column"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""TextBlock""
            }
          ],
          ""minHeight"": ""200px""
        },
        {
          ""type"": ""Column"",
          ""items"": [
            {
              ""type"": ""Container"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""TextBlock""
                }
              ],
              ""minHeight"": ""300px""
            }
          ]
        }
      ],
      ""minHeight"": ""100px""
    }
  ],
  ""minHeight"": ""500px""
}";
            var outputJson = card.ToJson();
            Assert.AreEqual(outputJson, expectedJson);
        }

        [TestMethod]
        public void TestImplicitImageType()
        {
            // Images set to type "Image" or with type unset should parse correctly within an image set
            var imageTypeSetOrEmpty =
            @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""ImageSet"",
                        ""images"": [
                            {
                                ""type"": ""Image"",
                                ""url"": ""http://adaptivecards.io/content/cats/1.png""
                            },
                            {
                                ""url"": ""http://adaptivecards.io/content/cats/1.png""
                            }
                        ]
                    }
                ]
            }";

            // Images set to a bogus type should not parse correctly
            var imageTypeInvalid =
            @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""ImageSet"",
                        ""images"": [
                            {
                                ""type"": ""Elephant"",
                                ""url"": ""http://adaptivecards.io/content/cats/1.png""
                            }
                        ]
                    }
                ]
            }";

            var result = AdaptiveCard.FromJson(imageTypeSetOrEmpty);
            Assert.IsNotNull(result.Card);
            Assert.AreEqual(2, (result.Card.Body[0] as AdaptiveImageSet).Images.Count);

            var ex = Assert.ThrowsException<ArgumentException>(() =>
            {
                AdaptiveCard.FromJson(imageTypeInvalid);
            });

            StringAssert.Contains(ex.Message, "The value \"AdaptiveCards.AdaptiveUnknownElement\" is not of type \"AdaptiveCards.AdaptiveImage\" and cannot be used in this generic collection.");
        }

        [TestMethod]
        public void TestParsingRichTextBlockWithInvalidInlineType()
        {
            // card with invalid inline type
            var invalidCard =
            @"{
                  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                            ""type"": ""AdaptiveCard"",
                  ""version"": ""1.2"",
                  ""body"": [
                    {
                      ""type"": ""RichTextBlock"",
                      ""inlines"": [
                        {
                          ""type"": ""TextRun"",
                          ""text"": ""You did exactly what you had to do. You considered all your options, you tried every alternative and then you made the hard choice. The Enterprise computer system is controlled by three primary main processor cores, cross-linked with a redundant melacortz ramistat, fourteen kiloquad interface modules. I think you've let your personal feelings cloud your judgement. Flair is what marks the difference between artistry and mere competence. They were just sucked into space. We have a saboteur aboard. When has justice ever been as simple as a rule book? Your shields were failing, sir. Travel time to the nearest starbase? Sorry, Data. I'm afraid I still don't understand, sir. How long can two people talk about nothing? Wait a minute - you've been declared dead. You can't give orders around here. You're going to be an interesting companion, Mr. Data. Our neural pathways have become accustomed to your sensory input patterns. Fear is the true enemy, the only enemy. The Federation's gone; the Borg is everywhere! Computer, lights up!""
                        },
                        {
                          ""type"": ""who cares???"",
                          ""text"": ""You did exactly what you had to do. You considered all your options, you tried every alternative and then you made the hard choice. The Enterprise computer system is controlled by three primary main processor cores, cross-linked with a redundant melacortz ramistat, fourteen kiloquad interface modules. I think you've let your personal feelings cloud your judgement. Flair is what marks the difference between artistry and mere competence. They were just sucked into space. We have a saboteur aboard. When has justice ever been as simple as a rule book? Your shields were failing, sir. Travel time to the nearest starbase? Sorry, Data. I'm afraid I still don't understand, sir. How long can two people talk about nothing? Wait a minute - you've been declared dead. You can't give orders around here. You're going to be an interesting companion, Mr. Data. Our neural pathways have become accustomed to your sensory input patterns. Fear is the true enemy, the only enemy. The Federation's gone; the Borg is everywhere! Computer, lights up!""
                        }
                      ]
                    }
                  ]
            }";

            var ex = Assert.ThrowsException<AdaptiveSerializationException>(() =>
            {
                AdaptiveCard.FromJson(invalidCard);
            });


            StringAssert.Contains(ex.Message, "Property 'type' must be 'TextRun'");
        }
                void RenderCardTask(string payload)
        {
            AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(payload);
        }

        [TestMethod]
        public void TestConcurrentParsing()
        {
            // card with invalid inline type
            var adaptiveCard =
@"{
    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Publish Adaptive Card schema"",
            ""weight"": ""bolder"",
            ""size"": ""medium""
        },
        {
            ""type"": ""ColumnSet"",
            ""columns"": [
                {
                    ""type"": ""Column"",
                    ""width"": ""auto"",
                    ""items"": [
                        {
                            ""type"": ""Image"",
                            ""url"": ""https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"",
                            ""size"": ""small"",
                            ""style"": ""person""
                        }
                    ]
                },
                {
                    ""type"": ""Column"",
                    ""width"": ""stretch"",
                    ""items"": [
                        {
                            ""type"": ""TextBlock"",
                            ""text"": ""Matt Hidinger"",
                            ""weight"": ""bolder"",
                            ""wrap"": true
                        },
                        {
                            ""type"": ""TextBlock"",
                            ""spacing"": ""none"",
                            ""text"": ""Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}"",
                            ""isSubtle"": true,
                            ""wrap"": true
                        }
                    ]
                }
            ]
        },
        {
            ""type"": ""TextBlock"",
            ""text"": ""Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation."",
            ""wrap"": true
        },
        {
            ""type"": ""FactSet"",
            ""facts"": [
                {
                    ""title"": ""Board:"",
                    ""value"": ""Adaptive Card""
                },
                {
                    ""title"": ""List:"",
                    ""value"": ""Backlog""
                },
                {
                    ""title"": ""Assigned to:"",
                    ""value"": ""Matt Hidinger""
                },
                {
                    ""title"": ""Due date:"",
                    ""value"": ""Not set""
                }
            ]
        }
    ],
    ""actions"": [
        {
            ""type"": ""Action.ShowCard"",
            ""title"": ""Set due date"",
            ""card"": {
                ""type"": ""AdaptiveCard"",
                ""body"": [
                    {
                        ""type"": ""Input.Date"",
                        ""id"": ""dueDate""
                    }
                ],
                ""actions"": [
                    {
                        ""type"": ""Action.Submit"",
                        ""title"": ""OK""
                    }
                ]
            }
        },
        {
            ""type"": ""Action.ShowCard"",
            ""title"": ""Comment"",
            ""card"": {
                ""type"": ""AdaptiveCard"",
                ""body"": [
                    {
                        ""type"": ""Input.Text"",
                        ""id"": ""comment"",
                        ""isMultiline"": true,
                        ""placeholder"": ""Enter your comment""
                    }
                ],
                ""actions"": [
                    {
                        ""type"": ""Action.Submit"",
                        ""title"": ""OK""
                    }
                ]
            }
        }
    ]
}";
            List<Task> tasks = new List<Task>();
            for (var i = 0; i < 10; i++)
            {
                var payload = adaptiveCard;
                var task = Task.Run(() => { RenderCardTask(payload); });
                tasks.Add(task);
            }

            try
            {
                Task.WaitAll(tasks.ToArray());
            }
            catch
            {
                // it's perfectly fine card. if there is exception, it is due to concurreny
                // as it's the only variable.
                Assert.Fail();
            }
        }
    }
}
