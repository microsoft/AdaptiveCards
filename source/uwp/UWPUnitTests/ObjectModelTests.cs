// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;


namespace UWPUnitTests
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
                InputNecessityIndicators = InputNecessityIndicators.RequiredInputs,
                Language = "en",
                Speak = "This is a card",
                Style = ContainerStyle.Emphasis,
                Version = "1.3",
                VerticalContentAlignment = VerticalContentAlignment.Center,
            };

            Assert.AreEqual("https://www.stuff.com/background.jpg", card.BackgroundImage.Url);
            Assert.AreEqual("Fallback Text", card.FallbackText);
            Assert.AreEqual(HeightType.Stretch, card.Height);
            Assert.AreEqual(InputNecessityIndicators.RequiredInputs, card.InputNecessityIndicators);
            Assert.AreEqual("en", card.Language);
            Assert.AreEqual("This is a card", card.Speak);
            Assert.AreEqual(ContainerStyle.Emphasis, card.Style);
            Assert.AreEqual("1.3", card.Version);
            Assert.AreEqual(VerticalContentAlignment.Center, card.VerticalContentAlignment);

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

            var jsonString = card.ToJson().ToString();
            Assert.AreEqual("{\"actions\":[{\"title\":\"Submit One\",\"type\":\"Action.Submit\"},{\"title\":\"Submit Two\",\"type\":\"Action.Submit\"}],\"backgroundImage\":\"https://www.stuff.com/background.jpg\",\"body\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"fallbackText\":\"Fallback Text\",\"height\":\"Stretch\",\"inputNecessityIndicators\":\"RequiredInputs\",\"lang\":\"en\",\"speak\":\"This is a card\",\"style\":\"Emphasis\",\"type\":\"AdaptiveCard\",\"version\":\"1.3\",\"verticalContentAlignment\":\"Center\"}", jsonString);
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

        [TestMethod]
        public void TextBlock()
        {
            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Color = ForegroundColor.Accent,
                FontType = FontType.Monospace,
                Height = HeightType.Stretch,
                HorizontalAlignment = HAlignment.Center,
                Id = "TextBlockId",
                IsSubtle = true,
                IsVisible = false,
                Language = "en",
                MaxLines = 3,
                Separator = true,
                Size = TextSize.Large,
                Spacing = Spacing.Large,
                Text = "This is a text block",
                Weight = TextWeight.Bolder,
                Wrap = true
            };

            ValidateBaseElementProperties(textBlock, "TextBlockId", false, true, Spacing.Large, HeightType.Stretch);

            Assert.AreEqual(ForegroundColor.Accent, textBlock.Color);
            Assert.AreEqual(FontType.Monospace, textBlock.FontType);
            Assert.AreEqual(HAlignment.Center, textBlock.HorizontalAlignment);
            Assert.IsTrue(textBlock.IsSubtle);
            Assert.AreEqual("en", textBlock.Language);
            Assert.AreEqual<uint>(3, textBlock.MaxLines);
            Assert.AreEqual(TextSize.Large, textBlock.Size);
            Assert.AreEqual("This is a text block", textBlock.Text);
            Assert.AreEqual(TextWeight.Bolder, textBlock.Weight);
            Assert.IsTrue(textBlock.Wrap);

            var jsonString = textBlock.ToJson().ToString();
            Assert.AreEqual("{\"color\":\"Accent\",\"fontType\":\"Monospace\",\"height\":\"Stretch\",\"horizontalAlignment\":\"center\",\"id\":\"TextBlockId\",\"isSubtle\":true,\"isVisible\":false,\"maxLines\":3,\"separator\":true,\"size\":\"Large\",\"spacing\":\"large\",\"text\":\"This is a text block\",\"type\":\"TextBlock\",\"weight\":\"Bolder\",\"wrap\":true}", jsonString);
        }

        [TestMethod]
        public void Image()
        {
            AdaptiveImage image = new AdaptiveImage
            {
                AltText = "This is a picture",
                BackgroundColor = "0xffffffff",
                Height = HeightType.Stretch,
                HorizontalAlignment = HAlignment.Center,
                Id = "ImageId",
                IsVisible = false,
                PixelHeight = 50,
                PixelWidth = 40,
                Separator = true,
                Size = ImageSize.Medium,
                Spacing = Spacing.Large,
                Style = ImageStyle.Person,
                Url = "https://www.stuff.com/picture.jpg"
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
                AltText = "This is some audio",
                Height = HeightType.Stretch,
                Id = "MediaId",
                IsVisible = false,
                Poster = "https://www.stuff.com/poster.jpg",
                Separator = true,
                Spacing = Spacing.Large
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
                Bleed = true,
                Height = HeightType.Stretch,
                Id = "ContainerId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.ExtraLarge,
                Style = ContainerStyle.Emphasis,
                VerticalContentAlignment = VerticalContentAlignment.Bottom
            };

            ValidateBaseElementProperties(container, "ContainerId", false, true, Spacing.ExtraLarge, HeightType.Stretch);

            Assert.AreEqual(ContainerStyle.Emphasis, container.Style);
            Assert.AreEqual(VerticalContentAlignment.Bottom, container.VerticalContentAlignment);
            Assert.IsTrue(container.Bleed);

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

            var jsonString = container.ToJson().ToString();
            Assert.AreEqual("{\"bleed\":true,\"height\":\"Stretch\",\"id\":\"ContainerId\",\"isVisible\":false,\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"selectAction\":{\"title\":\"Select Action\",\"type\":\"Action.Submit\"},\"separator\":true,\"spacing\":\"extraLarge\",\"style\":\"Emphasis\",\"type\":\"Container\",\"verticalContentAlignment\":\"Bottom\"}", jsonString);
        }

        [TestMethod]
        public void ColumnSet()
        {
            AdaptiveColumn column1 = new AdaptiveColumn
            {
                Bleed = true,
                Height = HeightType.Stretch,
                Id = "ColumnId",
                IsVisible = false,
                Width = "50px",
                Separator = true,
                Spacing = Spacing.Small,
                Style = ContainerStyle.Emphasis,
                VerticalContentAlignment = VerticalContentAlignment.Bottom,
            };

            ValidateBaseElementProperties(column1, "ColumnId", false, true, Spacing.Small, HeightType.Stretch);

            Assert.IsTrue(column1.Bleed);
            Assert.AreEqual("50px", column1.Width);
            Assert.AreEqual<uint>(50, column1.PixelWidth);
            Assert.AreEqual(ContainerStyle.Emphasis, column1.Style);
            Assert.AreEqual(VerticalContentAlignment.Bottom, column1.VerticalContentAlignment);

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
                Id = "Column2Id"
            };
            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock
            {
                Text = "This is a text block"
            };
            column2.Items.Add(textBlock3);

            AdaptiveColumnSet columnSet = new AdaptiveColumnSet
            {
                Bleed = true,
                Height = HeightType.Stretch,
                Id = "ColumnSetId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Small,
                Style = ContainerStyle.Emphasis,
            };

            Assert.IsTrue(columnSet.Bleed);
            ValidateBaseElementProperties(columnSet, "ColumnSetId", false, true, Spacing.Small, HeightType.Stretch);

            columnSet.Columns.Add(column1);
            columnSet.Columns.Add(column2);

            Assert.AreEqual("ColumnId", columnSet.Columns[0].Id);
            Assert.AreEqual("Column2Id", columnSet.Columns[1].Id);

            var jsonString = columnSet.ToJson().ToString();
            Assert.AreEqual("{\"bleed\":true,\"columns\":[{\"bleed\":true,\"fallback\":{\"items\":[],\"type\":\"Column\",\"width\":\"auto\"},\"height\":\"Stretch\",\"id\":\"ColumnId\",\"isVisible\":false,\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"},{\"text\":\"This is another text block\",\"type\":\"TextBlock\"}],\"selectAction\":{\"title\":\"Select Action\",\"type\":\"Action.Submit\"},\"separator\":true,\"spacing\":\"small\",\"style\":\"Emphasis\",\"type\":\"Column\",\"verticalContentAlignment\":\"Bottom\",\"width\":\"50px\"},{\"id\":\"Column2Id\",\"items\":[{\"text\":\"This is a text block\",\"type\":\"TextBlock\"}],\"type\":\"Column\",\"width\":\"auto\"}],\"height\":\"Stretch\",\"id\":\"ColumnSetId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"small\",\"style\":\"Emphasis\",\"type\":\"ColumnSet\"}", jsonString);
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
                ImageSize = ImageSize.Small,
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
                IsMultiline = true,
                MaxLength = 5,
                Placeholder = "Placeholder",
                Value = "Value",
                ErrorMessage = "Text Input Error Message",
                Regex = "([A-Z])\\w+",
                TextInputStyle = TextInputStyle.Email,
                Height = HeightType.Stretch,
                Id = "TextInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(textInput, "TextInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.IsFalse(textInput.IsRequired);
            Assert.AreEqual("Text Input Error Message", textInput.ErrorMessage);
            Assert.AreEqual("([A-Z])\\w+", textInput.Regex);
            Assert.AreEqual(true, textInput.IsMultiline);
            Assert.AreEqual<uint>(5, textInput.MaxLength);
            Assert.AreEqual("Placeholder", textInput.Placeholder);
            Assert.AreEqual("Value", textInput.Value);
            Assert.AreEqual(TextInputStyle.Email, textInput.TextInputStyle);

            textInput.InlineAction = new AdaptiveSubmitAction
            {
                Title = "Inline Action"
            };
            Assert.IsNotNull(textInput.InlineAction);
            Assert.AreEqual("Inline Action", textInput.InlineAction.Title);

            var jsonString = textInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Text Input Error Message\",\"height\":\"Stretch\",\"id\":\"TextInputId\",\"inlineAction\":{\"title\":\"Inline Action\",\"type\":\"Action.Submit\"},\"isMultiline\":true,\"isVisible\":false,\"maxLength\":5,\"placeholder\":\"Placeholder\",\"regex\":\"([A-Z])\\\\w+\",\"separator\":true,\"spacing\":\"medium\",\"style\":\"Email\",\"type\":\"Input.Text\",\"value\":\"Value\"}", jsonString);
        }

        [TestMethod]
        public void NumberInput()
        {
            AdaptiveNumberInput numberInput = new AdaptiveNumberInput
            {
                Max = 50,
                Min = 40,
                Placeholder = "Placeholder",
                Value = 42,
                IsRequired = false,
                ErrorMessage = "Number Input Error Message",
                Height = HeightType.Stretch,
                Id = "NumberInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(numberInput, "NumberInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.IsFalse(numberInput.IsRequired);
            Assert.AreEqual("Number Input Error Message", numberInput.ErrorMessage);
            Assert.AreEqual(50, numberInput.Max);
            Assert.AreEqual(40, numberInput.Min);
            Assert.AreEqual("Placeholder", numberInput.Placeholder);
            Assert.AreEqual(42, numberInput.Value);

            var jsonString = numberInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Number Input Error Message\",\"height\":\"Stretch\",\"id\":\"NumberInputId\",\"isVisible\":false,\"max\":50,\"min\":40,\"placeholder\":\"Placeholder\",\"separator\":true,\"spacing\":\"medium\",\"type\":\"Input.Number\",\"value\":42}", jsonString);
        }

        [TestMethod]
        public void DateInput()
        {
            AdaptiveDateInput dateInput = new AdaptiveDateInput
            {
                ErrorMessage = "Date Input Error Message",
                Max = "2019-01-14",
                Min = "2017-01-14",
                Placeholder = "Placeholder",
                Height = HeightType.Stretch,
                Id = "DateInputId",
                IsRequired = true,
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
                Value = "2018-01-14",
            };

            ValidateBaseElementProperties(dateInput, "DateInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.IsTrue(dateInput.IsRequired);
            Assert.AreEqual("Date Input Error Message", dateInput.ErrorMessage);
            Assert.AreEqual("2019-01-14", dateInput.Max);
            Assert.AreEqual("2017-01-14", dateInput.Min);
            Assert.AreEqual("Placeholder", dateInput.Placeholder);
            Assert.AreEqual("2018-01-14", dateInput.Value);

            var jsonString = dateInput.ToJson().ToString();
            Assert.AreEqual("{\"errorMessage\":\"Date Input Error Message\",\"height\":\"Stretch\",\"id\":\"DateInputId\",\"isRequired\":true,\"isVisible\":false,\"max\":\"2019-01-14\",\"min\":\"2017-01-14\",\"placeholder\":\"Placeholder\",\"separator\":true,\"spacing\":\"medium\",\"type\":\"Input.Date\",\"value\":\"2018-01-14\"}", jsonString);
        }

        [TestMethod]
        public void TimeInput()
        {
            AdaptiveTimeInput timeInput = new AdaptiveTimeInput
            {
                Max = "05:00",
                Min = "01:00",
                Placeholder = "Placeholder",
                Value = "02:00",
                Height = HeightType.Stretch,
                Id = "TimeInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(timeInput, "TimeInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.IsFalse(timeInput.IsRequired);
            Assert.IsTrue(timeInput.ErrorMessage.Length == 0);

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
                Title = "Title",
                Value = "Value",
                ValueOff = "ValueOff",
                ValueOn = "ValueOn",
                Wrap = true,
                Height = HeightType.Stretch,
                Id = "ToggleInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(toggleInput, "ToggleInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.IsFalse(toggleInput.IsRequired);
            Assert.IsTrue(toggleInput.ErrorMessage.Length == 0);

            Assert.AreEqual("Title", toggleInput.Title);
            Assert.AreEqual("Value", toggleInput.Value);
            Assert.AreEqual("ValueOff", toggleInput.ValueOff);
            Assert.AreEqual("ValueOn", toggleInput.ValueOn);
            Assert.AreEqual(true, toggleInput.Wrap);

            var jsonString = toggleInput.ToJson().ToString();
            Assert.AreEqual("{\"height\":\"Stretch\",\"id\":\"ToggleInputId\",\"isVisible\":false,\"separator\":true,\"spacing\":\"medium\",\"title\":\"Title\",\"type\":\"Input.Toggle\",\"value\":\"Value\",\"valueOff\":\"ValueOff\",\"valueOn\":\"ValueOn\",\"wrap\":true}", jsonString);
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
                ChoiceSetStyle = ChoiceSetStyle.Expanded,
                IsMultiSelect = true,
                Value = "Value2",
                Wrap = true,
                Height = HeightType.Stretch,
                Id = "ChoiceSetInputId",
                IsVisible = false,
                Separator = true,
                Spacing = Spacing.Medium,
            };

            ValidateBaseElementProperties(choiceSet, "ChoiceSetInputId", false, true, Spacing.Medium, HeightType.Stretch);

            Assert.AreEqual(ChoiceSetStyle.Expanded, choiceSet.ChoiceSetStyle);
            Assert.AreEqual(true, choiceSet.IsMultiSelect);
            Assert.AreEqual("Value2", choiceSet.Value);
            Assert.AreEqual(true, choiceSet.Wrap);

            choiceSet.Choices.Add(choice1);
            choiceSet.Choices.Add(choice2);

            Assert.AreEqual("Value1", choiceSet.Choices[0].Value);
            Assert.AreEqual("Value2", choiceSet.Choices[1].Value);

            var jsonString = choiceSet.ToJson().ToString();
            Assert.AreEqual("{\"choices\":[{\"title\":\"Title1\",\"value\":\"Value1\"},{\"title\":\"Title2\",\"value\":\"Value2\"}],\"height\":\"Stretch\",\"id\":\"ChoiceSetInputId\",\"isMultiSelect\":true,\"isVisible\":false,\"separator\":true,\"spacing\":\"medium\",\"style\":\"Expanded\",\"type\":\"Input.ChoiceSet\",\"value\":\"Value2\",\"wrap\":true}", jsonString);
        }

        public void ValidateBaseActionProperties(
            IAdaptiveActionElement element,
            string iconUrl,
            string id,
            string title,
            string style)
        {
            Assert.AreEqual(iconUrl, element.IconUrl);
            Assert.AreEqual(id, element.Id);
            Assert.AreEqual(style, element.Style);
            Assert.AreEqual(title, element.Title);
        }

        [TestMethod]
        public void OpenUrlAction()
        {
            var url = new System.Uri("http://www.stuff.com");
            AdaptiveOpenUrlAction openUrlAction = new AdaptiveOpenUrlAction
            {
                Url = url,
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(openUrlAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", "Title", "Destructive");
            Assert.AreEqual(url, openUrlAction.Url);

            var jsonString = openUrlAction.ToJson().ToString();
            Assert.AreEqual("{\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"style\":\"Destructive\",\"title\":\"Title\",\"type\":\"Action.OpenUrl\",\"url\":\"http://www.stuff.com/\"}", jsonString);
        }

        [TestMethod]
        public void SubmitAction()
        {
            JsonValue dataJson = JsonValue.CreateStringValue("foo");
            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                DataJson = dataJson,
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(submitAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", "Title", "Destructive");
            Assert.AreEqual(dataJson, submitAction.DataJson);

            var jsonString = submitAction.ToJson().ToString();
            Assert.AreEqual("{\"data\":\"foo\",\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"style\":\"Destructive\",\"title\":\"Title\",\"type\":\"Action.Submit\"}", jsonString);
        }

        [TestMethod]
        public void ShowCardAction()
        {
            AdaptiveShowCardAction showCardAction = new AdaptiveShowCardAction
            {
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "OpenUrlId",
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(showCardAction, "http://www.stuff.com/icon.jpg", "OpenUrlId", "Title", "Destructive");

            AdaptiveCard card = new AdaptiveCard();
            showCardAction.Card = card;
            Assert.IsNotNull(showCardAction.Card);

            var jsonString = showCardAction.ToJson().ToString();
            Assert.AreEqual("{\"card\":{\"actions\":[],\"body\":[],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"},\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"OpenUrlId\",\"style\":\"Destructive\",\"title\":\"Title\",\"type\":\"Action.ShowCard\"}", jsonString);
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
                IconUrl = "http://www.stuff.com/icon.jpg",
                Id = "ToggleVisibilityId",
                Style = "Destructive",
                Title = "Title"
            };

            ValidateBaseActionProperties(toggleAction, "http://www.stuff.com/icon.jpg", "ToggleVisibilityId", "Title", "Destructive");

            toggleAction.TargetElements.Add(toggleTarget1);
            toggleAction.TargetElements.Add(toggleTarget2);

            Assert.AreEqual("elementId", toggleAction.TargetElements[0].ElementId);
            Assert.AreEqual("element2Id", toggleAction.TargetElements[1].ElementId);

            var jsonString = toggleAction.ToJson().ToString();
            Assert.AreEqual("{\"iconUrl\":\"http://www.stuff.com/icon.jpg\",\"id\":\"ToggleVisibilityId\",\"style\":\"Destructive\",\"targetElements\":[\"elementId\",{\"elementId\":\"element2Id\",\"isVisible\":true}],\"title\":\"Title\",\"type\":\"Action.ToggleVisibility\"}", jsonString);
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
            Assert.IsTrue(textRun1.IsSubtle);
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
    }
}
