// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using System.Threading.Tasks;
using UWPTestLibrary;
using AdaptiveCards.Rendering.Uwp;

namespace UWPUnitTests
{
    [TestClass]
    public class RenderTests
    {
        [TestMethod]
        public async Task Media()
        {
            AdaptiveCard card = new AdaptiveCard
            {
                Version = "1.3"
            };

            AdaptiveMediaSource mediaSource = new AdaptiveMediaSource
            {
                MimeType = "audio/mp4",
                Url = "https://www.stuff.com/media.mp4"
            };

            AdaptiveMedia media = new AdaptiveMedia();
            media.Sources.Add(mediaSource);

            card.Body.Add(media);

            var renderedCard = await RenderInDispatcher(card);

            Assert.AreEqual(0, renderedCard.Warnings.Count);
            Assert.AreEqual(0, renderedCard.Errors.Count);
        }

        [TestMethod]
        public async Task InputWarnings()
        {
            // This test confirms that EmptyLabelInRequiredInput and MissingValidationErrorMessage
            // warnings are returned as expected for all input types

            AdaptiveCard card = new AdaptiveCard
            {
                Version = "1.3"
            };

            // Create a required text input
            AdaptiveTextInput requiredTextInput = new AdaptiveTextInput
            {
                Id = "textInputId",
                IsRequired = true
            };

            card.Body.Add(requiredTextInput);

            // Required inputs should have labels and error messages
            var renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create text input with a regex
            AdaptiveTextInput regexTextInput = new AdaptiveTextInput
            {
                Id = "textInputId",
                Regex = "([A-Z])\\w+"
            };
            card.Body.Clear();
            card.Body.Add(regexTextInput);

            // Input with regex should have an error message
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(1, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create text input with maxLength
            AdaptiveTextInput maxLengthTextInput = new AdaptiveTextInput
            {
                Id = "textInputId",
                MaxLength = 5
            };
            card.Body.Clear();
            card.Body.Add(maxLengthTextInput);

            // MaxLength is enforced by the control, so no error message is required. Don't expect any warnings.
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(0, renderedCard.Warnings.Count);

            // Create required date input
            AdaptiveDateInput requiredDateInput = new AdaptiveDateInput
            {
                Id = "textInputId",
                IsRequired = true
            };
            card.Body.Clear();
            card.Body.Add(requiredDateInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create date input with min and max values
            AdaptiveDateInput minMaxDateInput = new AdaptiveDateInput
            {
                Id = "textInputId",
                Min = "2012-07-04",
                Max = "2015-09-16"
            };

            card.Body.Clear();
            card.Body.Add(minMaxDateInput);

            // min and max are enforced by the control, so no error message is required. Don't expect any warnings.
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(0, renderedCard.Warnings.Count);

            // Create required time input
            AdaptiveTimeInput requiredTimeInput = new AdaptiveTimeInput
            {
                Id = "textInputId",
                IsRequired = true
            };
            card.Body.Clear();
            card.Body.Add(requiredTimeInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create time input with min and max values
            AdaptiveTimeInput minMaxTimeInput = new AdaptiveTimeInput
            {
                Id = "textInputId",
                Min = "08:00",
                Max = "20:00"
            };

            card.Body.Clear();
            card.Body.Add(minMaxTimeInput);

            // Date inputs with min and max should have an error message
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(1, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create required Number input
            AdaptiveNumberInput requiredNumberInput = new AdaptiveNumberInput
            {
                Id = "textInputId",
                IsRequired = true
            };
            card.Body.Clear();
            card.Body.Add(requiredNumberInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create Number input with min and max values
            AdaptiveNumberInput minMaxNumberInput = new AdaptiveNumberInput
            {
                Id = "textInputId",
                Min = 2,
                Max = 5
            };

            card.Body.Clear();
            card.Body.Add(minMaxNumberInput);

            // Number inputs with min and max should have an error message
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(1, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create required ChoiceSet input (compact)
            AdaptiveChoiceSetInput requiredCompactChoiceSetInput = new AdaptiveChoiceSetInput
            {
                Id = "textInputId",
                IsRequired = true,
                ChoiceSetStyle = ChoiceSetStyle.Compact
            };
            card.Body.Clear();
            card.Body.Add(requiredCompactChoiceSetInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create required ChoiceSet input (expanded)
            AdaptiveChoiceSetInput requiredExpandedChoiceSetInput = new AdaptiveChoiceSetInput
            {
                Id = "textInputId",
                IsRequired = true,
                ChoiceSetStyle = ChoiceSetStyle.Expanded
            };
            card.Body.Clear();
            card.Body.Add(requiredExpandedChoiceSetInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create required ChoiceSet input (MultiSelect)
            AdaptiveChoiceSetInput requiredMultiSelectChoiceSetInput = new AdaptiveChoiceSetInput
            {
                Id = "textInputId",
                IsRequired = true,
                ChoiceSetStyle = ChoiceSetStyle.Expanded,
                IsMultiSelect = true
            };
            card.Body.Clear();
            card.Body.Add(requiredMultiSelectChoiceSetInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));

            // Create required Toggle input 
            AdaptiveToggleInput requiredToggleInput = new AdaptiveToggleInput
            {
                Id = "textInputId",
                IsRequired = true,
            };
            card.Body.Clear();
            card.Body.Add(requiredToggleInput);

            // Required inputs should have labels and error messages
            renderedCard = await RenderInDispatcher(card);
            Assert.AreEqual(2, renderedCard.Warnings.Count);
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.EmptyLabelInRequiredInput));
            Assert.IsTrue(FindWarning(renderedCard, WarningStatusCode.MissingValidationErrorMessage));
        }

        private bool FindWarning(RenderedAdaptiveCard renderedCard, WarningStatusCode warningToFind)
        {
            foreach (var warning in renderedCard.Warnings)
            {
                if (warning.StatusCode == warningToFind)
                {
                    return true;
                }
            }

            return false;
        }

        public async Task<RenderedAdaptiveCard> RenderInDispatcher(AdaptiveCard card)
        {
            RenderedAdaptiveCard renderedCard = null;

            // Need to move the test to the UI Thread to render the card
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;
            Exception dispatcherException = null;
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {

                    var renderer = new AdaptiveCardRenderer();

                    renderedCard = renderer.RenderAdaptiveCard(card);
                }
                catch (Exception e)
                {
                    // If we throw an exception from inside the dispatcher the test infrastructure loses its
                    // connection with the tests. Hold onto this and throw it from the main test thread so
                    // it is reported properly as a test failure.
                    dispatcherException = e;
                }
            });

            if (dispatcherException != null)
            {
                // Rethrow any exceptions that may have happened within the dispatcher
                throw dispatcherException;
            }

            return renderedCard;
        }
    }
}
