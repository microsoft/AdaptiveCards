// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdaptiveCards.ObjectModel.Uwp;
using Windows.Data.Json;


namespace UWPObjectModelTest
{
    [TestClass]
    public class ObjectModelTest
    {
        [TestMethod]
        public void Card()
        {
            AdaptiveCard card = new AdaptiveCard
            {
                BackgroundImage = new AdaptiveBackgroundImage
                {
                    Url = "https://www.stuff.com/background.jpg"
                },
                FallbackText = "Fallback Text",
                Height = HeightType.Stretch,
                Language = "en",
                Speak = "This is a card",
                Style = ContainerStyle.Emphasis,
                Version = "1.3",
                VerticalContentAlignment = VerticalContentAlignment.Center,
                Refresh = new AdaptiveRefresh
                {
                    Action = new AdaptiveExecuteAction()
                },
                Authentication = new AdaptiveAuthentication
                {
                    Text = "Please Authenticate your account",
                    ConnectionName = "myConnection",
                    TokenExchangeResource = new AdaptiveTokenExchangeResource
                    {
                        Id = "myTokenId",
                        ProviderId = "myProviderId",
                        Uri = "https://mytoken.exchange/resource"
                    },
                }
            };

            card.Refresh.UserIds.Add("user1");
            card.Refresh.UserIds.Add("user2");

            AdaptiveAuthCardButton button = new AdaptiveAuthCardButton
            {
                Type = "signIn",
                Value = "value",
                Title = "Click here to sign in",
                Image = "https://myauthbutton/image.jpg"
            };

            card.Authentication.Buttons.Add(button);

            Assert.AreEqual("https://www.stuff.com/background.jpg", card.BackgroundImage.Url);
            Assert.AreEqual("Fallback Text", card.FallbackText);
            Assert.AreEqual(HeightType.Stretch, card.Height);
            Assert.AreEqual("en", card.Language);
            Assert.AreEqual("This is a card", card.Speak);
            Assert.AreEqual(ContainerStyle.Emphasis, card.Style);
            Assert.AreEqual("1.3", card.Version);
            Assert.AreEqual(VerticalContentAlignment.Center, card.VerticalContentAlignment);

            Assert.IsNotNull(card.Refresh);
            Assert.IsNotNull(card.Refresh.Action);
            Assert.AreEqual(ActionType.Execute, card.Refresh.Action.ActionType);
            Assert.IsNotNull(card.Refresh.UserIds);
            Assert.AreEqual(2, card.Refresh.UserIds.Count);
            Assert.AreEqual("user1", card.Refresh.UserIds[0]);
            Assert.AreEqual("user2", card.Refresh.UserIds[1]);

            Assert.IsNotNull(card.Authentication);
            Assert.AreEqual("Please Authenticate your account", card.Authentication.Text);
            Assert.AreEqual("myConnection", card.Authentication.ConnectionName);

            Assert.IsNotNull(card.Authentication.TokenExchangeResource);
            Assert.AreEqual("myTokenId", card.Authentication.TokenExchangeResource.Id);
            Assert.AreEqual("myProviderId", card.Authentication.TokenExchangeResource.ProviderId);
            Assert.AreEqual("https://mytoken.exchange/resource", card.Authentication.TokenExchangeResource.Uri);

            Assert.IsNotNull(card.Authentication.Buttons);
            Assert.AreEqual(1, card.Authentication.Buttons.Count);
            Assert.AreEqual("signIn", card.Authentication.Buttons[0].Type);
            Assert.AreEqual("value", card.Authentication.Buttons[0].Value);
            Assert.AreEqual("Click here to sign in", card.Authentication.Buttons[0].Title);
            Assert.AreEqual("https://myauthbutton/image.jpg", card.Authentication.Buttons[0].Image);

            card.SelectAction = new AdaptiveSubmitAction
            {
                Title = "Select Action"
            };
            Assert.IsNotNull(card.SelectAction);
            Assert.AreEqual("Select Action", card.SelectAction.Title);

            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Text = "This is a text block"
            };
            card.Body.Add(textBlock);

            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock
            {
                Text = "This is another text block"
            };
            card.Body.Add(textBlock2);

            Assert.AreEqual("This is a text block", (card.Body[0] as AdaptiveTextBlock).Text);
            Assert.AreEqual("This is another text block", (card.Body[1] as AdaptiveTextBlock).Text);

            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Title = "Submit One"
            };
            card.Actions.Add(submitAction);

            AdaptiveSubmitAction submitAction2 = new AdaptiveSubmitAction
            {
                Title = "Submit Two"
            };
            card.Actions.Add(submitAction2);

            Assert.AreEqual("Submit One", card.Actions[0].Title);
            Assert.AreEqual("Submit Two", card.Actions[1].Title);

            string expectedSerialization = "{\"actions\":[{\"title\":\"Submit One\",\"type\":\"Action.Submit\"},{\"title\":\"Submit Two\",\"type\":\"Action.Submit\"}],\"authentication\":{\"buttons\":[{\"image\":\"https://myauthbutton/image.jpg\",\"title\":\"Click here to sign in\",\"type\":\"signIn\",\"value\":\"value\"}],\"connectionName\":\"myConnection\",\"text\":\"Please Authenticate your account\",\"tokenExchangeResource\":{\"id\":\"myTokenId\",\"providerId\":\"myProviderId\",\"uri\":\"https://mytoken.exchange/resource\"}},\"backgroundImage\":\"https://www.stuff.com/background.jpg\",\"body\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"fallbackText\":\"Fallback Text\",\"height\":\"Stretch\",\"lang\":\"en\",\"refresh\":{\"action\":{\"type\":\"Action.Execute\"},\"userIds\":[\"user1\",\"user2\"]},\"speak\":\"This is a card\",\"style\":\"Emphasis\",\"type\":\"AdaptiveCard\",\"version\":\"1.3\",\"verticalContentAlignment\":\"Center\"}";

            var jsonString = card.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(card.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        public void ValidateBaseElementProperties(
            IAdaptiveCardElement element,
            string id,
            bool isVisible,
            bool separator,
            Spacing spacing,
            HeightType height)
        {
            Assert.AreEqual(id, element.Id);
            Assert.AreEqual(isVisible, element.IsVisible);
            Assert.AreEqual(separator, element.Separator);
            Assert.AreEqual(spacing, element.Spacing);
            Assert.AreEqual(height, element.Height);
        }


        public void ValidateBaseInputProperties(
            IAdaptiveInputElement input,
            string errorMessage,
            bool isRequired,
            string label)
        {
            Assert.AreEqual(errorMessage, input.ErrorMessage);
            Assert.AreEqual(isRequired, input.IsRequired);
            Assert.AreEqual(label, input.Label);
        }

        [TestMethod]
        public void TextBlock()
        {
            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                // Text Block Properties
                Color = ForegroundColor.Accent,
                FontType = FontType.Monospace,
                HorizontalAlignment = HAlignment.Center,
                IsSubtle = true,
                Language = "en",
                MaxLines = 3,
                Size = TextSize.Large,
                Style = TextStyle.Heading,
                Text = "This is a text block",
                Weight = TextWeight.Bolder,
                Wrap = true,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "TextBlockId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Large,
            };

            ValidateBaseElementProperties(textBlock, "TextBlockId", false, true, Spacing.Large, HeightType.Stretch);

            Assert.IsTrue(textBlock.Color.HasValue);
            Assert.AreEqual(ForegroundColor.Accent, textBlock.Color.Value);
            Assert.IsTrue(textBlock.FontType.HasValue);
            Assert.AreEqual(FontType.Monospace, textBlock.FontType.Value);
            Assert.AreEqual(HAlignment.Center, textBlock.HorizontalAlignment);
            Assert.IsTrue(textBlock.IsSubtle.HasValue);
            Assert.IsTrue(textBlock.IsSubtle.Value);
            Assert.AreEqual("en", textBlock.Language);
            Assert.AreEqual<uint>(3, textBlock.MaxLines);
            Assert.IsTrue(textBlock.Size.HasValue);
            Assert.AreEqual(TextSize.Large, textBlock.Size.Value);
            Assert.IsTrue(textBlock.Style.HasValue);
            Assert.AreEqual(TextStyle.Heading, textBlock.Style.Value);
            Assert.AreEqual("This is a text block", textBlock.Text);
            Assert.IsTrue(textBlock.Weight.HasValue);
            Assert.AreEqual(TextWeight.Bolder, textBlock.Weight.Value);
            Assert.IsTrue(textBlock.Wrap);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Body.Add(textBlock);

            string expectedSerialization = "{\"actions\":[],\"body\":[{\"color\":\"Accent\",\"fontType\":\"Monospace\",\"height\":\"Stretch\",\"horizontalAlignment\":\"center\",\"id\":\"TextBlockId\",\"isSubtle\":true,\"isVisible\":false,\"maxLines\":3,\"separator\":true,\"size\":\"Large\",\"spacing\":\"large\",\"style\":\"heading\",\"text\":\"This is a text block\",\"type\":\"TextBlock\",\"weight\":\"Bolder\",\"wrap\":true}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());

            // Validate optional properties are unset
            textBlock = new AdaptiveTextBlock
            {
                // Text Block Properties
                Text = "This is a text block",
            };

            Assert.IsFalse(textBlock.Color.HasValue);
            Assert.IsFalse(textBlock.FontType.HasValue);
            Assert.IsFalse(textBlock.IsSubtle.HasValue);
            Assert.IsFalse(textBlock.Size.HasValue);
            Assert.IsFalse(textBlock.Style.HasValue);
            Assert.IsFalse(textBlock.Weight.HasValue);

            adaptiveCard = new AdaptiveCard();
            adaptiveCard.Body.Add(textBlock);

            expectedSerialization = "{\"actions\":[],\"body\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void Image()
        {
            AdaptiveImage image = new AdaptiveImage
            {
                // Image Properties
                AltText = "This is a picture",
                BackgroundColor = "0xffffffff",
                HorizontalAlignment = HAlignment.Center,
                PixelHeight = 50,
                PixelWidth = 40,
                Size = ImageSize.Medium,
                Style = ImageStyle.Person,
                Url = "https://www.stuff.com/picture.jpg",

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "ImageId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Large,
            };

            ValidateBaseElementProperties(image, "ImageId", false, true, Spacing.Large, HeightType.Stretch);

            Assert.AreEqual("This is a picture", image.AltText);
            Assert.AreEqual("0xffffffff", image.BackgroundColor);
            Assert.AreEqual(HAlignment.Center, image.HorizontalAlignment);
            Assert.AreEqual<uint>(50, image.PixelHeight);
            Assert.AreEqual<uint>(40, image.PixelWidth);
            Assert.AreEqual(ImageSize.Medium, image.Size);
            Assert.AreEqual(ImageStyle.Person, image.Style);
            Assert.AreEqual("https://www.stuff.com/picture.jpg", image.Url);

            var jsonString = image.ToJson().ToString();
            Assert.AreEqual("{\"altText\":\"This is a picture\",\"backgroundColor\":\"0xffffffff\",\"height\":\"50px\",\"horizontalAlignment\":\"center\",\"id\":\"ImageId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"large\",\"style\":\"person\",\"type\":\"Image\",\"url\":\"https://www.stuff.com/picture.jpg\",\"width\":\"40px\"}", jsonString);
        }

        [TestMethod]
        public void Media()
        {
            AdaptiveMediaSource mediaSource1 = new AdaptiveMediaSource
            {
                MimeType = "audio/mp4",
                Url = "https://www.stuff.com/media.mp4"
            };

            Assert.AreEqual("audio/mp4", mediaSource1.MimeType);
            Assert.AreEqual("https://www.stuff.com/media.mp4", mediaSource1.Url);

            AdaptiveMediaSource mediaSource2 = new AdaptiveMediaSource
            {
                MimeType = "audio/mpeg",
                Url = "https://www.stuff.com/media.mp3"
            };

            Assert.AreEqual("audio/mpeg", mediaSource2.MimeType);
            Assert.AreEqual("https://www.stuff.com/media.mp3", mediaSource2.Url);

            AdaptiveMedia media = new AdaptiveMedia
            {
                // Media Properties
                AltText = "This is some audio",
                Poster = "https://www.stuff.com/poster.jpg",

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "MediaId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Large,
            };

            ValidateBaseElementProperties(media, "MediaId", false, true, Spacing.Large, HeightType.Stretch);

            Assert.AreEqual("This is some audio", media.AltText);
            Assert.AreEqual("https://www.stuff.com/poster.jpg", media.Poster);

            media.Sources.Add(mediaSource1);
            media.Sources.Add(mediaSource2);

            Assert.AreEqual("https://www.stuff.com/media.mp4", media.Sources[0].Url);
            Assert.AreEqual("https://www.stuff.com/media.mp3", media.Sources[1].Url);

            var jsonString = media.ToJson().ToString();
            Assert.AreEqual("{\"altText\":\"This is some audio\",\"height\":\"Stretch\",\"id\":\"MediaId\",\"isVisible\":false,\"poster\":\"https://www.stuff.com/poster.jpg\",\"separator\":true,\"sources\":[{\"mimeType\":\"audio/mp4\",\"url\":\"https://www.stuff.com/media.mp4\"},{\"mimeType\":\"audio/mpeg\",\"url\":\"https://www.stuff.com/media.mp3\"}],\"spacing\":\"large\",\"type\":\"Media\"}", jsonString);
        }

        [TestMethod]
        public void Container()
        {
            AdaptiveContainer container = new AdaptiveContainer
            {
                // Container Properties
                Bleed = true,
                Style = ContainerStyle.Emphasis,
                VerticalContentAlignment = VerticalContentAlignment.Bottom,
                Rtl = true,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "ContainerId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge,
            };

            ValidateBaseElementProperties(container, "ContainerId", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            Assert.IsTrue(container.Bleed);
            Assert.AreEqual(ContainerStyle.Emphasis, container.Style);
            Assert.AreEqual(VerticalContentAlignment.Bottom, container.VerticalContentAlignment);
            Assert.IsTrue(container.Rtl.HasValue);
            Assert.IsTrue(container.Rtl.Value);

            container.SelectAction = new AdaptiveSubmitAction
            {
                Title = "Select Action"
            };
            Assert.IsNotNull(container.SelectAction);
            Assert.AreEqual("Select Action", container.SelectAction.Title);

            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Text = "This is a text block"
            };
            container.Items.Add(textBlock);

            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock
            {
                Text = "This is another text block"
            };
            container.Items.Add(textBlock2);

            Assert.AreEqual("This is a text block", (container.Items[0] as AdaptiveTextBlock).Text);
            Assert.AreEqual("This is another text block", (container.Items[1] as AdaptiveTextBlock).Text);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Body.Add(container);

            string expectedSerialization = "{\"actions\":[],\"body\":[{\"bleed\":true,\"height\":\"Stretch\",\"id\":\"ContainerId\",\"isVisible\":false,\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"rtl\":true,\"selectAction\":{\"title\":\"Select Action\",\"type\":\"Action.Submit\"},\"separator\":true,\"spacing\":\"extraLarge\",\"style\":\"Emphasis\",\"type\":\"Container\",\"verticalContentAlignment\":\"Bottom\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void ColumnSet()
        {
            AdaptiveColumn column1 = new AdaptiveColumn
            {
                // Column Properties
                Bleed = true,
                Style = ContainerStyle.Emphasis,
                VerticalContentAlignment = VerticalContentAlignment.Bottom,
                Width = "50px",
                Rtl = true,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "ColumnId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Small,
            };

            ValidateBaseElementProperties(column1, "ColumnId", false, true, Spacing.Small, HeightType.Stretch);

            Assert.IsTrue(column1.Bleed);
            Assert.AreEqual(ContainerStyle.Emphasis, column1.Style);
            Assert.AreEqual(VerticalContentAlignment.Bottom, column1.VerticalContentAlignment);
            Assert.AreEqual("50px", column1.Width);
            Assert.AreEqual<uint>(50, column1.PixelWidth);
            Assert.IsTrue(column1.Rtl.HasValue);
            Assert.IsTrue(column1.Rtl.Value);

            column1.SelectAction = new AdaptiveSubmitAction
            {
                Title = "Select Action"
            };
            Assert.IsNotNull(column1.SelectAction);
            Assert.AreEqual("Select Action", column1.SelectAction.Title);

            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Text = "This is a text block"
            };
            column1.Items.Add(textBlock);

            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock
            {
                Text = "This is another text block"
            };
            column1.Items.Add(textBlock2);

            Assert.AreEqual("This is a text block", (column1.Items[0] as AdaptiveTextBlock).Text);
            Assert.AreEqual("This is another text block", (column1.Items[1] as AdaptiveTextBlock).Text);

            column1.FallbackType = FallbackType.Content;
            column1.FallbackContent = new AdaptiveColumn();

            Assert.AreEqual(FallbackType.Content, column1.FallbackType);
            Assert.AreEqual(ElementType.Column, column1.FallbackContent.ElementType);

            AdaptiveColumn column2 = new AdaptiveColumn
            {
                Id = "Column2Id",
                Rtl = false
            };
            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock
            {
                Text = "This is a text block"
            };
            column2.Items.Add(textBlock3);

            Assert.IsTrue(column2.Rtl.HasValue);
            Assert.IsFalse(column2.Rtl.Value);

            AdaptiveColumn column3 = new AdaptiveColumn
            {
                Id = "Column3Id"
            };

            Assert.IsFalse(column3.Rtl.HasValue);

            AdaptiveColumnSet columnSet = new AdaptiveColumnSet
            {
                // ColumnSet Properties
                Bleed = true,
                Style = ContainerStyle.Emphasis,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "ColumnSetId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Small,
            };

            ValidateBaseElementProperties(columnSet, "ColumnSetId", false, true, Spacing.Small, HeightType.Stretch);

            Assert.IsTrue(columnSet.Bleed);
            Assert.AreEqual(ContainerStyle.Emphasis, columnSet.Style);

            columnSet.Columns.Add(column1);
            columnSet.Columns.Add(column2);
            columnSet.Columns.Add(column3);

            Assert.AreEqual("ColumnId", columnSet.Columns[0].Id);
            Assert.AreEqual("Column2Id", columnSet.Columns[1].Id);
            Assert.AreEqual("Column3Id", columnSet.Columns[2].Id);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Body.Add(columnSet);

            string expectedSerialization = "{\"actions\":[],\"body\":[{\"bleed\":true,\"columns\":[{\"bleed\":true,\"fallback\":{\"items\":[],\"type\":\"Column\",\"width\":\"auto\"},\"height\":\"Stretch\",\"id\":\"ColumnId\",\"isVisible\":false,\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"rtl\":true,\"selectAction\":{\"title\":\"Select Action\",\"type\":\"Action.Submit\"},\"separator\":true,\"spacing\":\"small\",\"style\":\"Emphasis\",\"type\":\"Column\",\"verticalContentAlignment\":\"Bottom\",\"width\":\"50px\"},{\"id\":\"Column2Id\",\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"}],\"rtl\":false,\"type\":\"Column\",\"width\":\"auto\"},{\"id\":\"Column3Id\",\"items\":[],\"type\":\"Column\",\"width\":\"auto\"}],\"height\":\"Stretch\",\"id\":\"ColumnSetId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"small\",\"style\":\"Emphasis\",\"type\":\"ColumnSet\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void FactSet()
        {
            AdaptiveFact fact1 = new AdaptiveFact
            {
                Title = "Title1",
                Value = "Value1",
                Language = "en"
            };

            Assert.AreEqual("Title1", fact1.Title);
            Assert.AreEqual("Value1", fact1.Value);
            Assert.AreEqual("en", fact1.Language);

            AdaptiveFact fact2 = new AdaptiveFact
            {
                Title = "Title2",
                Value = "Value2",
            };

            AdaptiveFactSet factSet = new AdaptiveFactSet
            {
                Height = HeightType.Stretch,
                Id = "FactSetId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(factSet, "FactSetId", false, true, Spacing.Medium, HeightType.Stretch);

            factSet.Facts.Add(fact1);
            factSet.Facts.Add(fact2);

            Assert.AreEqual("Value1", factSet.Facts[0].Value);
            Assert.AreEqual("Value2", factSet.Facts[1].Value);

            var jsonString = factSet.ToJson().ToString();
            Assert.AreEqual("{\"facts\":[{\"title\":\"Title1\",\"value\":\"Value1\"},{\"title\":\"Title2\",\"value\":\"Value2\"}],\"height\":\"Stretch\",\"id\":\"FactSetId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"medium\",\"type\":\"FactSet\"}", jsonString);
        }

        [TestMethod]
        public void ImageSet()
        {
            AdaptiveImage image1 = new AdaptiveImage
            {
                Id = "Image1Id",
                Url = "https://www.stuff.com/picture.jpg"
            };

            AdaptiveImage image2 = new AdaptiveImage
            {
                Id = "Image2Id",
                Url = "https://www.stuff.com/picture2.jpg"
            };

            AdaptiveImageSet imageSet = new AdaptiveImageSet
            {
                // ImageSet Property
                ImageSize = ImageSize.Small,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "ImageSetId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(imageSet, "ImageSetId", false, true, Spacing.Medium, HeightType.Stretch);
            Assert.AreEqual(ImageSize.Small, imageSet.ImageSize);

            imageSet.Images.Add(image1);
            imageSet.Images.Add(image2);

            Assert.AreEqual("Image1Id", imageSet.Images[0].Id);
            Assert.AreEqual("Image2Id", imageSet.Images[1].Id);

            var jsonString = imageSet.ToJson().ToString();
            Assert.AreEqual("{\"height\":\"Stretch\",\"id\":\"ImageSetId\",\"imageSize\":\"Small\",\"images\":[{\"id\":\"Image1Id\",\"type\":\"Image\",\"url\":\"https://www.stuff.com/picture.jpg\"},{\"id\":\"Image2Id\",\"type\":\"Image\",\"url\":\"https://www.stuff.com/picture2.jpg\"}],\"isVisible\":false,\"separator\":true,\"spacing\":\"medium\",\"type\":\"ImageSet\"}", jsonString);
        }

        [TestMethod]
        public void TextInput()
        {
            AdaptiveTextInput textInput = new AdaptiveTextInput
            {
                // Input.Text Properties
                IsMultiline = true,
                MaxLength = 5,
                Placeholder = "Placeholder",
                Regex = "([A-Z])\\w+",
                TextInputStyle = TextInputStyle.Email,
                Value = "Value",

                // Input Properties
                ErrorMessage = "Text Input Error Message",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "TextInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(textInput, "TextInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(textInput, "Text Input Error Message", true, "LabelText");

            Assert.IsTrue(textInput.IsMultiline);
            Assert.AreEqual<uint>(5, textInput.MaxLength);
            Assert.AreEqual("Placeholder", textInput.Placeholder);
            Assert.AreEqual("([A-Z])\\w+", textInput.Regex);
            Assert.AreEqual(TextInputStyle.Email, textInput.TextInputStyle);
            Assert.AreEqual("Value", textInput.Value);

            textInput.InlineAction = new AdaptiveSubmitAction
            {
                Title = "Inline Action"
            };
            Assert.IsNotNull(textInput.InlineAction);
            Assert.AreEqual("Inline Action", textInput.InlineAction.Title);

            var jsonString = textInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Text Input Error Message\",\"height\":\"Stretch\",\"id\":\"TextInputId\",\"inlineAction\":{\"title\":\"Inline Action\",\"type\":\"Action.Submit\"},\"isMultiline\":true,\"isRequired\":true,\"isVisible\":false,\"label\":\"LabelText\",\"maxLength\":5,\"placeholder\":\"Placeholder\",\"regex\":\"([A-Z])\\\\w+\",\"separator\":true,\"spacing\":\"medium\",\"style\":\"Email\",\"type\":\"Input.Text\",\"value\":\"Value\"}", jsonString);
        }

        [TestMethod]
        public void NumberInput()
        {
            AdaptiveNumberInput numberInput = new AdaptiveNumberInput
            {
                // Input.Number Properties
                Max = 50,
                Min = 40,
                Placeholder = "Placeholder",
                Value = 42,

                // Input Properties
                ErrorMessage = "Number Input Error Message",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "NumberInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(numberInput, "NumberInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(numberInput, "Number Input Error Message", true, "LabelText");

            Assert.AreEqual(50, numberInput.Max);
            Assert.AreEqual(40, numberInput.Min);
            Assert.AreEqual("Placeholder", numberInput.Placeholder);
            Assert.AreEqual(42, numberInput.Value);

            var jsonString = numberInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Number Input Error Message\",\"height\":\"Stretch\",\"id\":\"NumberInputId\",\"isRequired\":true,\"isVisible\":false,\"label\":\"LabelText\",\"max\":50,\"min\":40,\"placeholder\":\"Placeholder\",\"separator\":true,\"spacing\":\"medium\",\"type\":\"Input.Number\",\"value\":42}", jsonString);
        }

        [TestMethod]
        public void NumberInputEmptyProps()
        {
            AdaptiveNumberInput numberInput = new AdaptiveNumberInput
            {
                Max = null,
                Min = null,
                Value = null,
                Placeholder = "some text",
                IsRequired = false
            };

            Assert.IsNull(numberInput.Max);
            Assert.IsNull(numberInput.Min);
            Assert.IsNull(numberInput.Value);
            Assert.AreEqual("{\"placeholder\":\"some text\",\"type\":\"Input.Number\"}", numberInput.ToJson().ToString());

            numberInput.Min = -1;
            numberInput.Max = 1;
            numberInput.Value = 0;

            Assert.AreEqual(numberInput.Min, -1);
            Assert.AreEqual(numberInput.Max, 1);
            Assert.AreEqual(numberInput.Value, 0);
            Assert.AreEqual("{\"max\":1,\"min\":-1,\"placeholder\":\"some text\",\"type\":\"Input.Number\",\"value\":0}", numberInput.ToJson().ToString());
        }

        [TestMethod]
        public void DateInput()
        {
            AdaptiveDateInput dateInput = new AdaptiveDateInput
            {
                // Input.Date Properties
                Max = "2019-01-14",
                Min = "2017-01-14",
                Placeholder = "Placeholder",
                Value = "2018-01-14",

                // Input Properties
                ErrorMessage = "Date Input Error Message",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "DateInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(dateInput, "DateInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(dateInput, "Date Input Error Message", true, "LabelText");

            Assert.AreEqual("2019-01-14", dateInput.Max);
            Assert.AreEqual("2017-01-14", dateInput.Min);
            Assert.AreEqual("Placeholder", dateInput.Placeholder);
            Assert.AreEqual("2018-01-14", dateInput.Value);

            var jsonString = dateInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Date Input Error Message\",\"height\":\"Stretch\",\"id\":\"DateInputId\",\"isRequired\":true,\"isVisible\":false,\"label\":\"LabelText\",\"max\":\"2019-01-14\",\"min\":\"2017-01-14\",\"placeholder\":\"Placeholder\",\"separator\":true,\"spacing\":\"medium\",\"type\":\"Input.Date\",\"value\":\"2018-01-14\"}", jsonString);
        }

        [TestMethod]
        public void TimeInput()
        {
            AdaptiveTimeInput timeInput = new AdaptiveTimeInput
            {
                // Input.Time Properties
                Max = "05:00",
                Min = "01:00",
                Placeholder = "Placeholder",
                Value = "02:00",

                // Input Properties
                ErrorMessage = "ErrorMessage",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "TimeInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(timeInput, "TimeInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(timeInput, "ErrorMessage", true, "LabelText");

            Assert.AreEqual("05:00", timeInput.Max);
            Assert.AreEqual("01:00", timeInput.Min);
            Assert.AreEqual("Placeholder", timeInput.Placeholder);
            Assert.AreEqual("02:00", timeInput.Value);

            var jsonString = timeInput.ToJson().ToString();
        }

        [TestMethod]
        public void ToggleInput()
        {
            AdaptiveToggleInput toggleInput = new AdaptiveToggleInput
            {
                // Input.Toggle Properties
                Title = "Title",
                Value = "Value",
                ValueOff = "ValueOff",
                ValueOn = "ValueOn",
                Wrap = true,

                // Input Properties
                ErrorMessage = "ErrorMessage",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "ToggleInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(toggleInput, "ToggleInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(toggleInput, "ErrorMessage", true, "LabelText");

            Assert.AreEqual("Title", toggleInput.Title);
            Assert.AreEqual("Value", toggleInput.Value);
            Assert.AreEqual("ValueOff", toggleInput.ValueOff);
            Assert.AreEqual("ValueOn", toggleInput.ValueOn);
            Assert.AreEqual(true, toggleInput.Wrap);

            var jsonString = toggleInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"ErrorMessage\",\"height\":\"Stretch\",\"id\":\"ToggleInputId\",\"isRequired\":true,\"isVisible\":false,\"label\":\"LabelText\",\"separator\":true,\"spacing\":\"medium\",\"title\":\"Title\",\"type\":\"Input.Toggle\",\"value\":\"Value\",\"valueOff\":\"ValueOff\",\"valueOn\":\"ValueOn\",\"wrap\":true}", jsonString);
        }

        [TestMethod]
        public void ChoiceSetInput()
        {
            AdaptiveChoiceInput choice1 = new AdaptiveChoiceInput
            {
                Title = "Title1",
                Value = "Value1",
            };

            Assert.AreEqual("Title1", choice1.Title);
            Assert.AreEqual("Value1", choice1.Value);

            AdaptiveChoiceInput choice2 = new AdaptiveChoiceInput
            {
                Title = "Title2",
                Value = "Value2",
            };

            AdaptiveChoiceSetInput choiceSet = new AdaptiveChoiceSetInput
            {
                // Input.ChoiceSet Properties
                ChoiceSetStyle = ChoiceSetStyle.Expanded,
                IsMultiSelect = true,
                Value = "Value2",
                Wrap = true,

                // Input Properties
                ErrorMessage = "ErrorMessage",
                IsRequired = true,
                Label = "LabelText",

                // BaseElement Properties
                Height = HeightType.Stretch,
                Id = "ChoiceSetInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(choiceSet, "ChoiceSetInputId", false, true, Spacing.Medium, HeightType.Stretch);
            ValidateBaseInputProperties(choiceSet, "ErrorMessage", true, "LabelText");

            Assert.AreEqual(ChoiceSetStyle.Expanded, choiceSet.ChoiceSetStyle);
            Assert.AreEqual(true, choiceSet.IsMultiSelect);
            Assert.AreEqual("Value2", choiceSet.Value);
            Assert.AreEqual(true, choiceSet.Wrap);

            choiceSet.Choices.Add(choice1);
            choiceSet.Choices.Add(choice2);

            Assert.AreEqual("Value1", choiceSet.Choices[0].Value);
            Assert.AreEqual("Value2", choiceSet.Choices[1].Value);

            var jsonString = choiceSet.ToJson().ToString();
            Assert.AreEqual("{\"choices\":[{\"title\":\"Title1\",\"value\":\"Value1\"},{\"title\":\"Title2\",\"value\":\"Value2\"}],\"errorMessage\":\"ErrorMessage\",\"height\":\"Stretch\",\"id\":\"ChoiceSetInputId\",\"isMultiSelect\":true,\"isRequired\":true,\"isVisible\":false,\"label\":\"LabelText\",\"separator\":true,\"spacing\":\"medium\",\"style\":\"Expanded\",\"type\":\"Input.ChoiceSet\",\"value\":\"Value2\",\"wrap\":true}", jsonString);
        }

        public void ValidateBaseActionProperties(
            IAdaptiveActionElement element,
            string iconUrl,
            string id,
            bool isEnabled,
            string title,
            string style)
        {
            Assert.AreEqual(iconUrl, element.IconUrl);
            Assert.AreEqual(id, element.Id);
            Assert.AreEqual(style, element.Style);
            Assert.AreEqual(title, element.Title);
            Assert.AreEqual(isEnabled, element.IsEnabled);
        }

        [TestMethod]
        public void OpenUrlAction()
        {
            var url = new System.Uri("http://www.stuff.com");
            AdaptiveOpenUrlAction openUrlAction = new AdaptiveOpenUrlAction
            {
                Url = url,
                Tooltip = "I am a tooltip",
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                IsEnabled = false,
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(openUrlAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", false, "Title", "Destructive");
            Assert.AreEqual(url, openUrlAction.Url);
            Assert.AreEqual("I am a tooltip", openUrlAction.Tooltip);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Actions.Add(openUrlAction);

            string expectedSerialization = "{\"actions\":[{\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"isEnabled\":false,\"style\":\"Destructive\",\"title\":\"Title\",\"tooltip\":\"I am a tooltip\",\"type\":\"Action.OpenUrl\",\"url\":\"http://www.stuff.com/\"}],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void SubmitAction()
        {
            JsonValue dataJson = JsonValue.CreateStringValue("foo");
            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                DataJson = dataJson,
                Tooltip = "I am a tooltip",
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                IsEnabled = true,
                Style = "Destructive",
                Title = "Title",
                AssociatedInputs = AssociatedInputs.None
            };

            ValidateBaseActionProperties(submitAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", true, "Title", "Destructive");
            Assert.AreEqual(dataJson, submitAction.DataJson);
            Assert.AreEqual("I am a tooltip", submitAction.Tooltip);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Actions.Add(submitAction);

            string expectedSerialization = "{\"actions\":[{\"associatedInputs\":\"None\",\"data\":\"foo\",\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"style\":\"Destructive\",\"title\":\"Title\",\"tooltip\":\"I am a tooltip\",\"type\":\"Action.Submit\"}],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void ExecuteAction()
        {
            JsonValue dataJson = JsonValue.CreateStringValue("foo");
            AdaptiveExecuteAction executeAction = new AdaptiveExecuteAction
            {
                DataJson = dataJson,
                Verb = "doStuff",
                Tooltip = "I am a tooltip",
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                IsEnabled = false,
                Style = "Destructive",
                Title = "Title",
                AssociatedInputs = AssociatedInputs.None
            };

            ValidateBaseActionProperties(executeAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", false, "Title", "Destructive");
            Assert.AreEqual(dataJson, executeAction.DataJson);
            Assert.AreEqual("doStuff", executeAction.Verb);
            Assert.AreEqual("I am a tooltip", executeAction.Tooltip);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Actions.Add(executeAction);

            string expectedSerialization = "{\"actions\":[{\"associatedInputs\":\"None\",\"data\":\"foo\",\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"isEnabled\":false,\"style\":\"Destructive\",\"title\":\"Title\",\"tooltip\":\"I am a tooltip\",\"type\":\"Action.Execute\",\"verb\":\"doStuff\"}],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void ShowCardAction()
        {
            AdaptiveShowCardAction showCardAction = new AdaptiveShowCardAction
            {
                IconUrl = "http://www.stuff.com/icon.jpg",
                Tooltip = "I am a tooltip",
                Id = "OpenUrlId",
                IsEnabled = true,
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(showCardAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", true, "Title", "Destructive");

            Assert.AreEqual("I am a tooltip", showCardAction.Tooltip);

            AdaptiveCard card = new AdaptiveCard();
            showCardAction.Card = card;
            Assert.IsNotNull(showCardAction.Card);

            AdaptiveCard parentCard = new AdaptiveCard();
            parentCard.Actions.Add(showCardAction);

            string expectedSerialization = "{\"actions\":[{\"card\":{\"actions\":[],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"},\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"style\":\"Destructive\",\"title\":\"Title\",\"tooltip\":\"I am a tooltip\",\"type\":\"Action.ShowCard\"}],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = parentCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(parentCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());
        }

        [TestMethod]
        public void ToggleVisibilityAction()
        {
            AdaptiveToggleVisibilityTarget toggleTarget1 = new AdaptiveToggleVisibilityTarget
            {
                ElementId = "elementId",
                IsVisible = IsVisible.IsVisibleToggle
            };

            Assert.AreEqual("elementId", toggleTarget1.ElementId);
            Assert.AreEqual(IsVisible.IsVisibleToggle, toggleTarget1.IsVisible);

            AdaptiveToggleVisibilityTarget toggleTarget2 = new AdaptiveToggleVisibilityTarget
            {
                ElementId = "element2Id",
                IsVisible = IsVisible.IsVisibleTrue
            };

            AdaptiveToggleVisibilityAction toggleAction = new AdaptiveToggleVisibilityAction
            {
                Tooltip = "I am a tooltip",
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "ToggleVisibilityId",
                IsEnabled = false,
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(toggleAction, "http://www.stuff.com/icon.jpg", "ToggleVisibilityId", false, "Title", "Destructive");
            Assert.AreEqual("I am a tooltip", toggleAction.Tooltip);

            toggleAction.TargetElements.Add(toggleTarget1);
            toggleAction.TargetElements.Add(toggleTarget2);

            Assert.AreEqual("elementId", toggleAction.TargetElements[0].ElementId);
            Assert.AreEqual("element2Id", toggleAction.TargetElements[1].ElementId);

            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Actions.Add(toggleAction);

            string expectedSerialization = "{\"actions\":[{\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"ToggleVisibilityId\",\"isEnabled\":false,\"style\":\"Destructive\",\"targetElements\":[\"elementId\",{\"elementId\":\"element2Id\",\"isVisible\":true}],\"title\":\"Title\",\"tooltip\":\"I am a tooltip\",\"type\":\"Action.ToggleVisibility\"}],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());

        }

        [TestMethod]
        public void ActionSet()
        {
            AdaptiveActionSet actionSet = new AdaptiveActionSet
            {
                Height = HeightType.Stretch,
                Id = "ActionSetId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge
            };

            ValidateBaseElementProperties(actionSet, "ActionSetId", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Title = "Submit One"
            };
            actionSet.Actions.Add(submitAction);

            AdaptiveSubmitAction submitAction2 = new AdaptiveSubmitAction
            {
                Title = "Submit Two"
            };
            actionSet.Actions.Add(submitAction2);

            Assert.AreEqual("Submit One", actionSet.Actions[0].Title);
            Assert.AreEqual("Submit Two", actionSet.Actions[1].Title);

            var jsonString = actionSet.ToJson().ToString();
            Assert.AreEqual("{\"actions\":[{\"title\":\"Submit One\",\"type\":\"Action.Submit\"},{\"title\":\"Submit Two\",\"type\":\"Action.Submit\"}],\"height\":\"Stretch\",\"id\":\"ActionSetId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"extraLarge\",\"type\":\"ActionSet\"}", jsonString);
        }

        [TestMethod]
        public void RichTextBlock()
        {
            AdaptiveTextRun textRun1 = new AdaptiveTextRun
            {
                Color = ForegroundColor.Accent,
                FontType = FontType.Monospace,
                Highlight = true,
                IsSubtle = true,
                Italic = true,
                Language = "en",
                Size = TextSize.Large,
                Strikethrough = true,
                Text = "This is text run number 1",
                Weight = TextWeight.Bolder,
                Underline = true,
            };

            Assert.AreEqual(ForegroundColor.Accent, textRun1.Color);
            Assert.AreEqual(FontType.Monospace, textRun1.FontType);
            Assert.IsTrue(textRun1.Highlight);
            Assert.IsTrue(textRun1.IsSubtle.HasValue);
            Assert.IsTrue(textRun1.IsSubtle.Value);
            Assert.IsTrue(textRun1.Italic);
            Assert.IsTrue(textRun1.Strikethrough);
            Assert.AreEqual("en", textRun1.Language);
            Assert.AreEqual(TextSize.Large, textRun1.Size);
            Assert.AreEqual("This is text run number 1", textRun1.Text);
            Assert.AreEqual(TextWeight.Bolder, textRun1.Weight);
            Assert.IsTrue(textRun1.Underline);

            textRun1.SelectAction = new AdaptiveSubmitAction
            {
                Title = "Select Action"
            };
            Assert.IsNotNull(textRun1.SelectAction);
            Assert.AreEqual("Select Action", textRun1.SelectAction.Title);

            AdaptiveTextRun textRun2 = new AdaptiveTextRun { Text = "This is text run number 2" };
            AdaptiveTextRun textRun3 = new AdaptiveTextRun { Text = "This is text run number 3" };

            AdaptiveRichTextBlock richTextBlock = new AdaptiveRichTextBlock
            {
                Height = HeightType.Stretch,
                HorizontalAlignment = HAlignment.Center,
                Id = "RichTextBlockId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Large,
            };

            ValidateBaseElementProperties(richTextBlock, "RichTextBlockId", false, true, Spacing.Large, HeightType.Stretch);

            Assert.AreEqual(HAlignment.Center, richTextBlock.HorizontalAlignment);

            richTextBlock.Inlines.Add(textRun1);
            richTextBlock.Inlines.Add(textRun2);
            richTextBlock.Inlines.Add(textRun3);

            Assert.AreEqual("This is text run number 1", (richTextBlock.Inlines[0] as AdaptiveTextRun).Text);
            Assert.AreEqual("This is text run number 2", (richTextBlock.Inlines[1] as AdaptiveTextRun).Text);
            Assert.AreEqual("This is text run number 3", (richTextBlock.Inlines[2] as AdaptiveTextRun).Text);

            var jsonString = richTextBlock.ToJson().ToString();
            Assert.AreEqual("{\"height\":\"Stretch\",\"horizontalAlignment\":\"center\",\"id\":\"RichTextBlockId\",\"inlines\":[{\"color\":\"Accent\",\"fontType\":\"Monospace\",\"highlight\":true,\"isSubtle\":true,\"italic\":true,\"selectAction\":{\"title\":\"Select Action\",\"type\":\"Action.Submit\"},\"size\":\"Large\",\"strikethrough\":true,\"text\":\"This is text run number 1\",\"type\":\"TextRun\",\"underline\":true,\"weight\":\"Bolder\"},{\"text\":\"This is text run number 2\",\"type\":\"TextRun\"},{\"text\":\"This is text run number 3\",\"type\":\"TextRun\"}],\"isVisible\":false,\"separator\":true,\"spacing\":\"large\",\"type\":\"RichTextBlock\"}", jsonString);
        }

        [TestMethod]
        public void Fallback()
        {
            AdaptiveTextBlock textBlockDrop = new AdaptiveTextBlock
            {
                Text = "This text block has fallback type Drop",
                FallbackType = FallbackType.Drop
            };

            textBlockDrop.Requirements.Add(new AdaptiveRequirement("foo", "1.2.3.4"));

            Assert.AreEqual(FallbackType.Drop, textBlockDrop.FallbackType);

            var jsonString = textBlockDrop.ToJson().ToString();
            Assert.AreEqual("{\"fallback\":\"drop\",\"requires\":{\"foo\":\"1.2.3.4\"},\"text\":\"This text block has fallback type Drop\",\"type\":\"TextBlock\"}", jsonString);

            AdaptiveTextBlock textBlockNone = new AdaptiveTextBlock
            {
                Text = "This text block has fallback explicitly set to None",
                FallbackType = FallbackType.None
            };

            textBlockNone.Requirements.Add(new AdaptiveRequirement("foo", "*"));

            Assert.AreEqual(FallbackType.None, textBlockNone.FallbackType);

            jsonString = textBlockNone.ToJson().ToString();
            Assert.AreEqual("{\"requires\":{\"foo\":\"0.0.0.0\"},\"text\":\"This text block has fallback explicitly set to None\",\"type\":\"TextBlock\"}", jsonString);
        }

        [TestMethod]
        public void Table()
        {
            // Create a table
            AdaptiveTable table = new AdaptiveTable
            {
                // Table Properties
                ShowGridLines = false,
                FirstRowAsHeaders = true,
                HorizontalCellContentAlignment = HAlignment.Right,
                VerticalCellContentAlignment = VerticalContentAlignment.Bottom,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "TableId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge,
            };

            ValidateBaseElementProperties(table, "TableId", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            Assert.IsFalse(table.ShowGridLines);
            Assert.IsTrue(table.FirstRowAsHeaders);
            Assert.AreEqual(HAlignment.Right, table.HorizontalCellContentAlignment);
            Assert.AreEqual(VerticalContentAlignment.Bottom, table.VerticalCellContentAlignment);

            // Create a column defintion
            AdaptiveTableColumnDefinition columnDefinition1 = new AdaptiveTableColumnDefinition
            {
                HorizontalCellContentAlignment = HAlignment.Center,
                VerticalCellContentAlignment = VerticalContentAlignment.Center,
                Width = 2
            };

            // Validate column definition properties
            Assert.AreEqual(HAlignment.Center, columnDefinition1.HorizontalCellContentAlignment);
            Assert.AreEqual(VerticalContentAlignment.Center, columnDefinition1.VerticalCellContentAlignment);
            Assert.AreEqual(2U, columnDefinition1.Width);

            // Create another column definitoin
            AdaptiveTableColumnDefinition columnDefinition2 = new AdaptiveTableColumnDefinition
            {
                HorizontalCellContentAlignment = HAlignment.Right,
                VerticalCellContentAlignment = VerticalContentAlignment.Bottom
            };

            // Add the column definitions to the table
            table.Columns.Add(columnDefinition1);
            table.Columns.Add(columnDefinition2);

            // Create a row
            AdaptiveTableRow row = new AdaptiveTableRow
            {

                Style = ContainerStyle.Emphasis,
                HorizontalCellContentAlignment = HAlignment.Center,
                VerticalCellContentAlignment = VerticalContentAlignment.Center,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "RowId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge,
            };

            // Validate the row properties
            ValidateBaseElementProperties(row, "RowId", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            Assert.AreEqual(ContainerStyle.Emphasis, row.Style);
            Assert.AreEqual(HAlignment.Center, row.HorizontalCellContentAlignment);
            Assert.AreEqual(VerticalContentAlignment.Center, row.VerticalCellContentAlignment);

            // Add the row to the table;
            table.Rows.Add(row);

            // Create a cell 
            AdaptiveTableCell cell1 = new AdaptiveTableCell
            {
                Bleed = true,
                Style = ContainerStyle.Emphasis,
                VerticalContentAlignment = VerticalContentAlignment.Bottom,
                Rtl = true,

                // Base Element Properties
                Height = HeightType.Stretch,
                Id = "Cell1Id",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge,
            };

            // Validate the cell properties
            ValidateBaseElementProperties(cell1, "Cell1Id", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            Assert.IsTrue(cell1.Bleed);
            Assert.AreEqual(ContainerStyle.Emphasis, cell1.Style);
            Assert.AreEqual(VerticalContentAlignment.Bottom, cell1.VerticalContentAlignment);
            Assert.IsTrue(cell1.Rtl.HasValue);
            Assert.IsTrue(cell1.Rtl.Value);

            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Text = "Cell1 Text Block"
            };
            cell1.Items.Add(textBlock);
            Assert.AreEqual("Cell1 Text Block", (cell1.Items[0] as AdaptiveTextBlock).Text);

            // Create a second cell
            AdaptiveTableCell cell2 = new AdaptiveTableCell();

            // Add the cells to the row
            row.Cells.Add(cell1);
            row.Cells.Add(cell2);

            // Put the table in a card and validate serialization/deserialization
            AdaptiveCard adaptiveCard = new AdaptiveCard();
            adaptiveCard.Body.Add(table);

            string expectedSerialization = "{\"actions\":[],\"body\":[{\"columns\":[{\"horizontalCellContentAlignment\":\"center\",\"verticalCellContentAlignment\":\"Center\"},{\"horizontalCellContentAlignment\":\"right\",\"verticalCellContentAlignment\":\"Bottom\"}],\"height\":\"Stretch\",\"horizontalCellContentAlignment\":\"right\",\"id\":\"TableId\",\"isVisible\":false,\"rows\":[{\"cells\":[{\"bleed\":true,\"height\":\"Stretch\",\"id\":\"Cell1Id\",\"isVisible\":false,\"items\":[{\"text\":\"Cell1 Text Block\",\"type\":\"TextBlock\"}],\"rtl\":true,\"separator\":true,\"spacing\":\"extraLarge\",\"style\":\"Emphasis\",\"type\":\"TableCell\",\"verticalContentAlignment\":\"Bottom\"},{\"items\":[],\"type\":\"TableCell\"}],\"horizontalCellContentAlignment\":\"center\",\"style\":\"Emphasis\",\"type\":\"TableRow\",\"verticalCellContentAlignment\":\"Center\"}],\"separator\":true,\"showGridLines\":false,\"spacing\":\"extraLarge\",\"type\":\"Table\",\"verticalCellContentAlignment\":\"Bottom\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}";

            var jsonString = adaptiveCard.ToJson().ToString();
            Assert.AreEqual(expectedSerialization, jsonString);

            var parseResult = AdaptiveCard.FromJson(adaptiveCard.ToJson());
            Assert.AreEqual(expectedSerialization, parseResult.AdaptiveCard.ToJson().ToString());

        }
    }
}
