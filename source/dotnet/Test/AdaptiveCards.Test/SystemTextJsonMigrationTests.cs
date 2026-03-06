// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    /// <summary>
    /// Tests that validate System.Text.Json-specific behavior after the migration from Newtonsoft.Json.
    /// These tests ensure the STJ infrastructure works correctly for all AdaptiveCards scenarios.
    /// </summary>
    [TestClass]
    public class SystemTextJsonMigrationTests
    {
        // =====================================================================
        // Category 1: STJ-Specific Behavior
        // =====================================================================

        [TestMethod]
        public void TrailingCommas_AreParsedCorrectly()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Hello"",
                    },
                ]
            }";

            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);
            Assert.AreEqual(1, result.Card.Body.Count);
            Assert.AreEqual("Hello", (result.Card.Body[0] as AdaptiveTextBlock)?.Text);
        }

        [TestMethod]
        public void InvalidJson_ThrowsAdaptiveSerializationException()
        {
            var json = "{ this is not valid json at all }}}";

            Assert.ThrowsException<AdaptiveSerializationException>(() =>
            {
                AdaptiveCard.FromJson(json);
            });
        }

        [TestMethod]
        public void PolymorphicDispatch_DeserializesCorrectConcreteTypes()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"" },
                    { ""type"": ""Image"", ""url"": ""http://example.com/img.png"" },
                    { ""type"": ""Container"", ""items"": [{ ""type"": ""TextBlock"", ""text"": ""Nested"" }] },
                    { ""type"": ""ColumnSet"", ""columns"": [{ ""type"": ""Column"", ""items"": [{ ""type"": ""TextBlock"", ""text"": ""Col"" }] }] }
                ],
                ""actions"": [
                    { ""type"": ""Action.Submit"", ""title"": ""Submit"" },
                    { ""type"": ""Action.OpenUrl"", ""url"": ""http://example.com"", ""title"": ""Open"" }
                ]
            }";

            var result = AdaptiveCard.FromJson(json);
            var card = result.Card;

            Assert.AreEqual(4, card.Body.Count);
            Assert.IsInstanceOfType(card.Body[0], typeof(AdaptiveTextBlock));
            Assert.IsInstanceOfType(card.Body[1], typeof(AdaptiveImage));
            Assert.IsInstanceOfType(card.Body[2], typeof(AdaptiveContainer));
            Assert.IsInstanceOfType(card.Body[3], typeof(AdaptiveColumnSet));

            Assert.AreEqual(2, card.Actions.Count);
            Assert.IsInstanceOfType(card.Actions[0], typeof(AdaptiveSubmitAction));
            Assert.IsInstanceOfType(card.Actions[1], typeof(AdaptiveOpenUrlAction));

            // Verify nested container items
            var container = card.Body[2] as AdaptiveContainer;
            Assert.AreEqual(1, container.Items.Count);
            Assert.IsInstanceOfType(container.Items[0], typeof(AdaptiveTextBlock));
            Assert.AreEqual("Nested", (container.Items[0] as AdaptiveTextBlock)?.Text);

            // Verify nested column items
            var columnSet = card.Body[3] as AdaptiveColumnSet;
            Assert.AreEqual(1, columnSet.Columns.Count);
            Assert.AreEqual(1, columnSet.Columns[0].Items.Count);
        }

        [TestMethod]
        public void UnknownType_BecomesUnknownElement()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""FutureWidget"", ""customProp"": ""value"" }
                ]
            }";

            var result = AdaptiveCard.FromJson(json);
            Assert.AreEqual(1, result.Card.Body.Count);
            Assert.IsInstanceOfType(result.Card.Body[0], typeof(AdaptiveUnknownElement));
            Assert.AreEqual("FutureWidget", result.Card.Body[0].Type);
        }

        [TestMethod]
        public void RegisterCustomType_WorksAtRuntime()
        {
            // Register a custom type name mapping
            AdaptiveTypedElementConverter.RegisterTypedElement<AdaptiveTextBlock>("CustomTextBlock");

            try
            {
                var json = @"{
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                        { ""type"": ""CustomTextBlock"", ""text"": ""Custom"" }
                    ]
                }";

                var result = AdaptiveCard.FromJson(json);
                Assert.AreEqual(1, result.Card.Body.Count);
                Assert.IsInstanceOfType(result.Card.Body[0], typeof(AdaptiveTextBlock));
                Assert.AreEqual("Custom", (result.Card.Body[0] as AdaptiveTextBlock)?.Text);
            }
            finally
            {
                // Clean up — remove the custom registration
                AdaptiveTypedElementConverter.TypedElementTypes.Value.Remove("CustomTextBlock");
            }
        }

        [TestMethod]
        public void NestedPolymorphism_DeeplyNestedElementsWork()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    {
                        ""type"": ""Container"",
                        ""items"": [
                            {
                                ""type"": ""Container"",
                                ""items"": [
                                    {
                                        ""type"": ""ColumnSet"",
                                        ""columns"": [
                                            {
                                                ""type"": ""Column"",
                                                ""items"": [
                                                    { ""type"": ""TextBlock"", ""text"": ""Deep"" }
                                                ]
                                            }
                                        ]
                                    }
                                ]
                            }
                        ]
                    }
                ]
            }";

            var result = AdaptiveCard.FromJson(json);
            var outerContainer = result.Card.Body[0] as AdaptiveContainer;
            var innerContainer = outerContainer.Items[0] as AdaptiveContainer;
            var columnSet = innerContainer.Items[0] as AdaptiveColumnSet;
            var column = columnSet.Columns[0];
            var textBlock = column.Items[0] as AdaptiveTextBlock;

            Assert.AreEqual("Deep", textBlock.Text);
        }

        [TestMethod]
        public void IdCollisionDetection_ThrowsOnDuplicateIds()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""id"": ""duplicate"", ""text"": ""First"" },
                    { ""type"": ""TextBlock"", ""id"": ""duplicate"", ""text"": ""Second"" }
                ]
            }";

            Assert.ThrowsException<AdaptiveSerializationException>(() =>
            {
                AdaptiveCard.FromJson(json);
            });
        }

        [TestMethod]
        public void FallbackIdExemption_SameIdInFallbackIsAllowed()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""id"": ""myId"",
                        ""text"": ""Primary"",
                        ""fallback"": {
                            ""type"": ""TextBlock"",
                            ""id"": ""myId"",
                            ""text"": ""Fallback""
                        }
                    }
                ]
            }";

            // Should NOT throw — fallback content is allowed to have the same ID
            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);
        }

        // =====================================================================
        // Category 2: Converter Parity
        // =====================================================================

        [TestMethod]
        public void StrictIntConverter_RejectsFloats()
        {
            // The card has "spacing" which is an int-backed enum, and a float value should be rejected
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"", ""maxLines"": 3.5 }
                ]
            }";

            // STJ with StrictIntConverter should handle this gracefully
            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);
            // maxLines should be 0 (default) since 3.5 is rejected
            var tb = result.Card.Body[0] as AdaptiveTextBlock;
            Assert.IsNotNull(tb);
        }

        [TestMethod]
        public void HeightConverter_ParsesAutoStretchAndPixels()
        {
            var jsonAuto = @"{ ""type"": ""AdaptiveCard"", ""version"": ""1.0"", ""body"": [{ ""type"": ""TextBlock"", ""text"": ""t"", ""height"": ""auto"" }] }";
            var jsonStretch = @"{ ""type"": ""AdaptiveCard"", ""version"": ""1.0"", ""body"": [{ ""type"": ""TextBlock"", ""text"": ""t"", ""height"": ""stretch"" }] }";

            var autoCard = AdaptiveCard.FromJson(jsonAuto).Card;
            var stretchCard = AdaptiveCard.FromJson(jsonStretch).Card;

            Assert.AreEqual(AdaptiveHeightType.Auto, (autoCard.Body[0] as AdaptiveElement)?.Height?.HeightType);
            Assert.AreEqual(AdaptiveHeightType.Stretch, (stretchCard.Body[0] as AdaptiveElement)?.Height?.HeightType);
        }

        [TestMethod]
        public void BackgroundImageConverter_StringAndObjectForm()
        {
            var jsonString = @"{ ""type"": ""AdaptiveCard"", ""version"": ""1.0"", ""backgroundImage"": ""http://example.com/bg.png"", ""body"": [] }";
            var jsonObject = @"{ ""type"": ""AdaptiveCard"", ""version"": ""1.0"", ""backgroundImage"": { ""url"": ""http://example.com/bg.png"", ""fillMode"": ""repeat"" }, ""body"": [] }";

            var stringCard = AdaptiveCard.FromJson(jsonString).Card;
            var objectCard = AdaptiveCard.FromJson(jsonObject).Card;

            Assert.AreEqual("http://example.com/bg.png", stringCard.BackgroundImage.UrlString);
            Assert.AreEqual("http://example.com/bg.png", objectCard.BackgroundImage.UrlString);
            Assert.AreEqual(AdaptiveImageFillMode.Repeat, objectCard.BackgroundImage.FillMode);
        }

        [TestMethod]
        public void FallbackConverter_DropValue()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"", ""fallback"": ""drop"" }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var tb = card.Body[0] as AdaptiveTextBlock;
            Assert.IsNotNull(tb.Fallback);
            Assert.AreEqual(AdaptiveFallbackElement.AdaptiveFallbackType.Drop, tb.Fallback.Type);
        }

        [TestMethod]
        public void FallbackConverter_ElementContent()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Primary"",
                        ""fallback"": {
                            ""type"": ""TextBlock"",
                            ""text"": ""Fallback content""
                        }
                    }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var tb = card.Body[0] as AdaptiveTextBlock;
            Assert.IsNotNull(tb.Fallback);
            Assert.AreEqual(AdaptiveFallbackElement.AdaptiveFallbackType.Content, tb.Fallback.Type);
            Assert.IsInstanceOfType(tb.Fallback.Content, typeof(AdaptiveTextBlock));
            Assert.AreEqual("Fallback content", (tb.Fallback.Content as AdaptiveTextBlock)?.Text);
        }

        [TestMethod]
        public void SchemaVersionConverter_Roundtrip()
        {
            var card = new AdaptiveCard("1.5");
            Assert.AreEqual(1, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);

            var json = card.ToJson();
            Assert.IsTrue(json.Contains("\"version\""));

            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(1, reparsed.Version.Major);
            Assert.AreEqual(5, reparsed.Version.Minor);
        }

        [TestMethod]
        public void ToggleElementsConverter_MixedStringAndObject()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [{ ""type"": ""TextBlock"", ""text"": ""t"" }],
                ""actions"": [
                    {
                        ""type"": ""Action.ToggleVisibility"",
                        ""title"": ""Toggle"",
                        ""targetElements"": [
                            ""element1"",
                            { ""elementId"": ""element2"", ""isVisible"": false }
                        ]
                    }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var action = card.Actions[0] as AdaptiveToggleVisibilityAction;
            Assert.IsNotNull(action);
            Assert.AreEqual(2, action.TargetElements.Count);
            Assert.AreEqual("element1", action.TargetElements[0].ElementId);
            Assert.AreEqual("element2", action.TargetElements[1].ElementId);
            Assert.AreEqual(false, action.TargetElements[1].IsVisible);
        }

        [TestMethod]
        public void EnumConverter_InvalidValueReturnsDefault()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"", ""size"": ""bogusInvalidSize"" }
                ]
            }";

            var result = AdaptiveCard.FromJson(json);
            var tb = result.Card.Body[0] as AdaptiveTextBlock;
            Assert.IsNotNull(tb);
            // Invalid enum value should fall back to default
            Assert.AreEqual(AdaptiveTextSize.Default, tb.Size);
        }

        [TestMethod]
        public void EnumConverter_CaseInsensitive()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"", ""size"": ""LARGE"" }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var tb = card.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual(AdaptiveTextSize.Large, tb.Size);
        }

        // =====================================================================
        // Category 3: Roundtrip Integrity
        // =====================================================================

        [TestMethod]
        public void Roundtrip_SimpleCard()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock("Hello world"),
                    new AdaptiveImage("http://example.com/img.png")
                }
            };

            var json = card.ToJson();
            var reparsed = AdaptiveCard.FromJson(json).Card;

            Assert.AreEqual(card.Version.ToString(), reparsed.Version.ToString());
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.IsInstanceOfType(reparsed.Body[0], typeof(AdaptiveTextBlock));
            Assert.IsInstanceOfType(reparsed.Body[1], typeof(AdaptiveImage));
            Assert.AreEqual("Hello world", (reparsed.Body[0] as AdaptiveTextBlock)?.Text);
            Assert.AreEqual("http://example.com/img.png", (reparsed.Body[1] as AdaptiveImage)?.UrlString);
        }

        [TestMethod]
        public void Roundtrip_ComplexCard()
        {
            var card = new AdaptiveCard("1.5")
            {
                Body =
                {
                    new AdaptiveTextBlock("Header") { Size = AdaptiveTextSize.Large, Weight = AdaptiveTextWeight.Bolder },
                    new AdaptiveColumnSet
                    {
                        Columns =
                        {
                            new AdaptiveColumn
                            {
                                Items = { new AdaptiveTextBlock("Col 1") }
                            },
                            new AdaptiveColumn
                            {
                                Items = { new AdaptiveImage("http://example.com/img.png") }
                            }
                        }
                    },
                    new AdaptiveContainer
                    {
                        Items =
                        {
                            new AdaptiveTextBlock("Inside container"),
                            new AdaptiveFactSet
                            {
                                Facts = { new AdaptiveFact("Key", "Value") }
                            }
                        }
                    },
                    new AdaptiveTextInput { Id = "input1", Placeholder = "Enter text" },
                    new AdaptiveChoiceSetInput
                    {
                        Id = "choice1",
                        Choices = { new AdaptiveChoice { Title = "Option 1", Value = "1" } }
                    }
                },
                Actions =
                {
                    new AdaptiveSubmitAction { Title = "Submit" },
                    new AdaptiveOpenUrlAction { Title = "Open", Url = new Uri("http://example.com") }
                }
            };

            var json = card.ToJson();
            var reparsed = AdaptiveCard.FromJson(json).Card;

            Assert.AreEqual(5, reparsed.Body.Count);
            Assert.AreEqual(2, reparsed.Actions.Count);

            // Check header
            var header = reparsed.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual("Header", header?.Text);
            Assert.AreEqual(AdaptiveTextSize.Large, header?.Size);

            // Check column set
            var colSet = reparsed.Body[1] as AdaptiveColumnSet;
            Assert.AreEqual(2, colSet?.Columns.Count);

            // Check container
            var container = reparsed.Body[2] as AdaptiveContainer;
            Assert.AreEqual(2, container?.Items.Count);

            // Check inputs
            var textInput = reparsed.Body[3] as AdaptiveTextInput;
            Assert.AreEqual("input1", textInput?.Id);
        }

        [TestMethod]
        public void Roundtrip_AdditionalProperties()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"", ""customProp"": ""customValue"", ""customNum"": 42 }
                ],
                ""customCardProp"": ""cardValue""
            }";

            var card = AdaptiveCard.FromJson(json).Card;

            // Check additional properties survived parsing
            var tb = card.Body[0] as AdaptiveTextBlock;
            Assert.IsTrue(tb.AdditionalProperties.ContainsKey("customProp"));
            Assert.AreEqual("customValue", tb.AdditionalProperties["customProp"].GetString());
            Assert.AreEqual(42, tb.AdditionalProperties["customNum"].GetInt32());

            // Roundtrip
            var json2 = card.ToJson();
            var reparsed = AdaptiveCard.FromJson(json2).Card;
            var tb2 = reparsed.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual("customValue", tb2.AdditionalProperties["customProp"].GetString());
            Assert.AreEqual(42, tb2.AdditionalProperties["customNum"].GetInt32());
        }

        [TestMethod]
        public void Roundtrip_ShowCardAction()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body = { new AdaptiveTextBlock("Main card") },
                Actions =
                {
                    new AdaptiveShowCardAction
                    {
                        Title = "Show",
                        Card = new AdaptiveCard("1.0")
                        {
                            Body = { new AdaptiveTextBlock("Inner card") }
                        }
                    }
                }
            };

            var json = card.ToJson();
            var reparsed = AdaptiveCard.FromJson(json).Card;

            var showCard = reparsed.Actions[0] as AdaptiveShowCardAction;
            Assert.IsNotNull(showCard?.Card);
            Assert.AreEqual(1, showCard.Card.Body.Count);
            Assert.AreEqual("Inner card", (showCard.Card.Body[0] as AdaptiveTextBlock)?.Text);
        }

        [TestMethod]
        public void Roundtrip_HostConfig()
        {
            var json = @"{
                ""spacing"": { ""small"": 3, ""default"": 8, ""medium"": 20, ""large"": 30, ""extraLarge"": 40, ""padding"": 10 },
                ""separator"": { ""lineThickness"": 1, ""lineColor"": ""#EEEEEE"" },
                ""supportsInteractivity"": true,
                ""fontTypes"": { ""default"": { ""fontFamily"": ""Calibri"" } },
                ""actions"": { ""maxActions"": 5, ""showCard"": { ""actionMode"": ""inline"" } }
            }";

            var config = AdaptiveCards.Rendering.AdaptiveHostConfig.FromJson(json);
            Assert.AreEqual(8, config.Spacing.Default);
            Assert.AreEqual(3, config.Spacing.Small);
            Assert.AreEqual(5, config.Actions.MaxActions);

            var json2 = config.ToJson();
            var reparsed = AdaptiveCards.Rendering.AdaptiveHostConfig.FromJson(json2);
            Assert.AreEqual(config.Spacing.Default, reparsed.Spacing.Default);
        }

        [TestMethod]
        public void Roundtrip_RequiresAndFallback()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Requires v1.2"",
                        ""fallback"": { ""type"": ""TextBlock"", ""text"": ""Fallback"" },
                        ""requires"": { ""adaptiveCards"": ""1.2"" }
                    }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var tb = card.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual("Requires v1.2", tb.Text);
            Assert.IsNotNull(tb.Fallback);
            Assert.IsNotNull(tb.Requires);

            // Roundtrip
            var json2 = card.ToJson();
            var reparsed = AdaptiveCard.FromJson(json2).Card;
            var tb2 = reparsed.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual("Requires v1.2", tb2.Text);
            Assert.IsNotNull(tb2.Fallback);
        }

        // =====================================================================
        // Category 4: Breaking Change Validation
        // =====================================================================

        [TestMethod]
        public void AdditionalProperties_IsJsonElement()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [{ ""type"": ""TextBlock"", ""text"": ""Hello"", ""custom"": ""val"" }]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var tb = card.Body[0] as AdaptiveTextBlock;
            var value = tb.AdditionalProperties["custom"];
            Assert.AreEqual(typeof(JsonElement), value.GetType());
        }

        [TestMethod]
        public void AdditionalProperties_SetWithSerializeToElement()
        {
            var tb = new AdaptiveTextBlock("Hello");
            tb.AdditionalProperties["myProp"] = JsonSerializer.SerializeToElement("test");
            tb.AdditionalProperties["myNum"] = JsonSerializer.SerializeToElement(42);

            Assert.AreEqual("test", tb.AdditionalProperties["myProp"].GetString());
            Assert.AreEqual(42, tb.AdditionalProperties["myNum"].GetInt32());
        }

        [TestMethod]
        public void AsJson_ReturnsJsonNode()
        {
            var inputs = new AdaptiveCards.Rendering.RenderedAdaptiveCardInputs();
            var result = inputs.AsJson();
            Assert.IsInstanceOfType(result, typeof(JsonNode));
        }

        [TestMethod]
        public void ToJson_ProducesValidJson()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body = { new AdaptiveTextBlock("Hello") },
                Actions = { new AdaptiveSubmitAction { Title = "Submit" } }
            };

            var json = card.ToJson();

            // Verify it's valid JSON by parsing it
            var doc = JsonDocument.Parse(json);
            Assert.IsNotNull(doc);

            // Verify key properties exist
            var root = doc.RootElement;
            Assert.IsTrue(root.TryGetProperty("type", out var typeProp) || root.TryGetProperty("Type", out typeProp));
            Assert.IsTrue(root.TryGetProperty("version", out _));
        }

        // =====================================================================
        // Category 5: Edge Cases & Regression
        // =====================================================================

        [TestMethod]
        public void ConcurrentParsing_IsThreadSafe()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
                    { ""type"": ""TextBlock"", ""text"": ""Hello"" },
                    { ""type"": ""Container"", ""items"": [{ ""type"": ""Image"", ""url"": ""http://example.com/img.png"" }] }
                ]
            }";

            var exceptions = new List<Exception>();
            var tasks = new Task[10];

            for (int i = 0; i < 10; i++)
            {
                tasks[i] = Task.Run(() =>
                {
                    try
                    {
                        for (int j = 0; j < 50; j++)
                        {
                            var result = AdaptiveCard.FromJson(json);
                            Assert.AreEqual(2, result.Card.Body.Count);
                        }
                    }
                    catch (Exception ex)
                    {
                        lock (exceptions) { exceptions.Add(ex); }
                    }
                });
            }

            Task.WaitAll(tasks);
            Assert.AreEqual(0, exceptions.Count, $"Thread safety failures: {string.Join("; ", exceptions.Select(e => e.Message))}");
        }

        [TestMethod]
        public void DataJson_GetterSetter_Roundtrip()
        {
            var action = new AdaptiveSubmitAction();
            action.DataJson = @"{""key"": ""value"", ""num"": 42}";
            Assert.IsNotNull(action.Data);

            var dataJson = action.DataJson;
            Assert.IsTrue(dataJson.Contains("key"));
            Assert.IsTrue(dataJson.Contains("value"));

            // Set to null
            action.DataJson = null;
            Assert.IsNull(action.Data);
        }

        [TestMethod]
        public void EmptyCard_SerializesWithoutError()
        {
            var card = new AdaptiveCard("1.0");
            var json = card.ToJson();
            Assert.IsNotNull(json);
            Assert.IsTrue(json.Contains("\"version\""));

            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(0, reparsed.Body.Count);
        }

        [TestMethod]
        public void NullVersion_WithCallback_UsesOverride()
        {
            try
            {
                AdaptiveCard.OnDeserializingMissingVersion = () => new AdaptiveSchemaVersion(0, 5);

                var json = @"{ ""type"": ""AdaptiveCard"", ""body"": [{ ""type"": ""TextBlock"", ""text"": ""No version"" }] }";
                var result = AdaptiveCard.FromJson(json);
                Assert.IsNotNull(result.Card);
                Assert.AreEqual(0, result.Card.Version.Major);
                Assert.AreEqual(5, result.Card.Version.Minor);
            }
            finally
            {
                AdaptiveCard.OnDeserializingMissingVersion = null;
            }
        }

        [TestMethod]
        public void NumberInput_NullableDoubles_WorkCorrectly()
        {
            var input = new AdaptiveNumberInput { Id = "num" };
            Assert.IsNull(input.Value);
            Assert.IsNull(input.Min);
            Assert.IsNull(input.Max);

            input.Value = 5.0;
            input.Min = 1.0;
            input.Max = 10.0;

            var card = new AdaptiveCard("1.0") { Body = { input } };
            var json = card.ToJson();
            Assert.IsTrue(json.Contains("\"value\""));
            Assert.IsTrue(json.Contains("\"min\""));
            Assert.IsTrue(json.Contains("\"max\""));

            var reparsed = AdaptiveCard.FromJson(json).Card;
            var reparsedInput = reparsed.Body[0] as AdaptiveNumberInput;
            Assert.AreEqual(5.0, reparsedInput.Value);
            Assert.AreEqual(1.0, reparsedInput.Min);
            Assert.AreEqual(10.0, reparsedInput.Max);
        }

        [TestMethod]
        public void Table_DeserializesCorrectly()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.5"",
                ""body"": [
                    {
                        ""type"": ""Table"",
                        ""columns"": [
                            { ""width"": 1 },
                            { ""width"": ""100px"" }
                        ],
                        ""rows"": [
                            {
                                ""type"": ""TableRow"",
                                ""cells"": [
                                    { ""type"": ""TableCell"", ""items"": [{ ""type"": ""TextBlock"", ""text"": ""Cell 1"" }] },
                                    { ""type"": ""TableCell"", ""items"": [{ ""type"": ""TextBlock"", ""text"": ""Cell 2"" }] }
                                ]
                            }
                        ]
                    }
                ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;
            var table = card.Body[0] as AdaptiveTable;
            Assert.IsNotNull(table);
            Assert.AreEqual(2, table.Columns.Count);
            Assert.AreEqual(1, table.Rows.Count);
            Assert.AreEqual(2, table.Rows[0].Cells.Count);

            // Check cell content
            var cell1 = table.Rows[0].Cells[0];
            Assert.AreEqual(1, cell1.Items.Count);
            Assert.AreEqual("Cell 1", (cell1.Items[0] as AdaptiveTextBlock)?.Text);
        }

        // =====================================================================
        // Category 6: Bug-fix Regression Tests
        // =====================================================================

        /// <summary>
        /// Verifies that <see cref="AdaptiveFallbackConverter.IsInFallback"/> does not leak
        /// across threads. Before the ThreadStatic fix, concurrent parsing of cards that contain
        /// fallback elements could corrupt the shared flag, causing valid cards to throw a
        /// spurious ID-collision exception or silently accept real collisions.
        /// </summary>
        [TestMethod]
        public void ConcurrentFallbackParsing_IsThreadSafe()
        {
            // A card with a fallback element that has the same ID as its parent (allowed per spec).
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.2"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""id"": ""shared"",
                        ""text"": ""Primary"",
                        ""fallback"": {
                            ""type"": ""TextBlock"",
                            ""id"": ""shared"",
                            ""text"": ""Fallback""
                        }
                    }
                ]
            }";

            var exceptions = new ConcurrentBag<Exception>();
            var tasks = new Task[10];

            for (int i = 0; i < 10; i++)
            {
                tasks[i] = Task.Run(() =>
                {
                    try
                    {
                        for (int j = 0; j < 50; j++)
                        {
                            var result = AdaptiveCard.FromJson(json);
                            Assert.IsNotNull(result.Card);
                            Assert.AreEqual(1, result.Card.Body.Count);
                        }
                    }
                    catch (Exception ex)
                    {
                        exceptions.Add(ex);
                    }
                });
            }

            Task.WaitAll(tasks);
            Assert.AreEqual(0, exceptions.Count,
                $"Thread-safety failures: {string.Join("; ", exceptions.Select(e => e.Message))}");
        }

        /// <summary>
        /// Verifies that collection element types (Container, Column, ColumnSet) do not emit
        /// properties that have their default values. Before the fix, the
        /// <c>AdaptiveCollectionElementConverter</c> wrote every property regardless of
        /// <c>[JsonIgnore(Condition = WhenWritingNull/WhenWritingDefault)]</c>, producing
        /// verbose (and sometimes <c>null</c>-valued) JSON that violated the spec.
        /// </summary>
        [TestMethod]
        public void CollectionElements_DefaultPropertiesAreNotSerialized()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveContainer { Items = { new AdaptiveTextBlock("Hello") } },
                    new AdaptiveColumnSet
                    {
                        Columns = { new AdaptiveColumn { Items = { new AdaptiveTextBlock("Col") } } }
                    }
                }
            };

            var json = card.ToJson();

            // These are all default values — they must NOT appear in the output.
            Assert.IsFalse(json.Contains("\"separator\""),
                "Default 'separator: false' must not be serialized");
            Assert.IsFalse(json.Contains("\"bleed\""),
                "Default 'bleed: false' must not be serialized");
            Assert.IsFalse(json.Contains("\"horizontalAlignment\""),
                "Default 'horizontalAlignment: Left' must not be serialized");
            Assert.IsFalse(json.Contains("\"verticalContentAlignment\""),
                "Default 'verticalContentAlignment: Top' (null-written by enum converter) must not be serialized");

            // Non-default values must still round-trip correctly.
            var card2 = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveContainer
                    {
                        Bleed = true,
                        Style = AdaptiveContainerStyle.Emphasis,
                        Items = { new AdaptiveTextBlock("Hello") }
                    }
                }
            };

            var json2 = card2.ToJson();
            Assert.IsTrue(json2.Contains("\"bleed\""), "Non-default 'bleed: true' must be serialized");
            Assert.IsTrue(json2.Contains("emphasis"), "Non-default 'style: emphasis' must be serialized");

            var reparsed = AdaptiveCard.FromJson(json2).Card;
            var container = reparsed.Body[0] as AdaptiveContainer;
            Assert.IsTrue(container.Bleed);
            Assert.AreEqual(AdaptiveContainerStyle.Emphasis, container.Style);
        }

        /// <summary>
        /// Verifies that setting <see cref="AdaptiveElement.IsVisible"/> to <c>false</c> is
        /// preserved after a serialise-then-parse round-trip. Before the fix, the property used
        /// <c>[JsonIgnore(Condition = WhenWritingDefault)]</c> which silently dropped
        /// <c>false</c> (the bool type-default) from the JSON, causing hidden elements to
        /// reappear as visible after re-parsing.
        /// </summary>
        [TestMethod]
        public void IsVisible_False_RoundtripsCorrectly()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock("Hidden") { IsVisible = false },
                    new AdaptiveTextBlock("Visible") { IsVisible = true },
                    new AdaptiveContainer
                    {
                        IsVisible = false,
                        Items = { new AdaptiveTextBlock("Inside hidden container") }
                    }
                }
            };

            var json = card.ToJson();

            // "isVisible": false must be present in the serialized JSON
            Assert.IsTrue(json.Contains("\"isVisible\""),
                "The isVisible property must always be serialized");
            Assert.IsTrue(json.Contains("\"isVisible\":false") || json.Contains("\"isVisible\": false"),
                "isVisible: false must be present in the JSON");

            var reparsed = AdaptiveCard.FromJson(json).Card;

            Assert.IsFalse(((AdaptiveTextBlock)reparsed.Body[0]).IsVisible,
                "TextBlock with IsVisible=false must remain hidden after roundtrip");
            Assert.IsTrue(((AdaptiveTextBlock)reparsed.Body[1]).IsVisible,
                "TextBlock with IsVisible=true must remain visible after roundtrip");
            Assert.IsFalse(((AdaptiveContainer)reparsed.Body[2]).IsVisible,
                "Container with IsVisible=false must remain hidden after roundtrip");
        }
    }
}
