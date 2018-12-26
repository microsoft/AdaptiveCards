using AdaptiveCards.Rendering.Uwp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Core;
using Windows.Data.Json;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace UWPUnitTests
{
    [TestClass]
    public class UnitTest
    {
        public TestContext TestContext { get; set; }

        private EventWaitHandle _testCompleted = new ManualResetEvent(false);
        private Exception _exceptionThrown = null;
        private StorageFolder _tempResultsFolder;
        private StorageFolder _sourceHostConfigsFolder;
        private StorageFolder _sourceCardsFolder;
        private StorageFolder _expectedFolder;

        [ClassInitialize]
        static public async Task Init(TestContext context)
        {
            StorageFolder expectedFolder = await Package.Current.InstalledLocation.GetFolderAsync("Expected");

            context.Properties.Add("ExpectedFolder", expectedFolder);
            context.Properties.Add("ResultsFolder", await ApplicationData.Current.TemporaryFolder.CreateFolderAsync("Results", CreationCollisionOption.OpenIfExists));
            context.Properties.Add("SourceHostConfigsFolder", await expectedFolder.CreateFolderAsync("SourceHostConfigs", CreationCollisionOption.OpenIfExists));
            context.Properties.Add("SourceCardsFolder", await expectedFolder.CreateFolderAsync("SourceCards", CreationCollisionOption.OpenIfExists));
        }

        [TestMethod]
        public async Task TestAllCards()
        {
            _expectedFolder = (TestContext.Properties["ExpectedFolder"] as StorageFolder);
            _tempResultsFolder = (TestContext.Properties["ResultsFolder"] as StorageFolder);
            _sourceCardsFolder = (TestContext.Properties["SourceCardsFolder"] as StorageFolder);
            _sourceHostConfigsFolder = (TestContext.Properties["SourceHostConfigsFolder"] as StorageFolder);

            ObservableCollection<FileViewModel> cards = new ObservableCollection<FileViewModel>();
            ObservableCollection<FileViewModel> hostConfigs = new ObservableCollection<FileViewModel>();

            await FileLoadHelpers.LoadAsync(cards, hostConfigs);

            List<Exception> exceptions = new List<Exception>();
            foreach (var hostConfig in hostConfigs)
            {
                foreach (var card in cards)
                {
                    try
                    {
                        await TestCardInDispatcher(hostConfig, card);
                    }
                    catch (Exception thrown)
                    {
                        exceptions.Add(thrown);
                    }
                }
            }

            if (exceptions.Count != 0)
            {
                string message = string.Empty;
                foreach (var e in exceptions)
                {
                    message += $"{e.Message}{Environment.NewLine}";
                }

                throw new Exception($"Test failed with {exceptions.Count} failures.{Environment.NewLine}{message}");
            }
        }

        public async Task TestCardInDispatcher(FileViewModel hostConfig, FileViewModel card)
        {
            _exceptionThrown = null;
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            _testCompleted.Reset();

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    await TestCard(hostConfig, card);
                }
                catch (Exception e)
                {
                    _exceptionThrown = e;
                }
                finally
                {
                    _testCompleted.Set();
                }
            });

            _testCompleted.WaitOne();
            if (_exceptionThrown != null)
            {
                throw new Exception(_exceptionThrown.Message, _exceptionThrown);
            }
        }

        async public Task TestCard(FileViewModel hostConfigFile, FileViewModel cardFile)
        {
            var renderResult = await UWPTestLibrary.RenderTestHelpers.RenderCard(cardFile, hostConfigFile);

            if (renderResult.Tree != null)
            {
                UWPTestLibrary.ImageWaiter imageWaiter = new ImageWaiter(renderResult.Tree);

                StackPanel stackPanel = new StackPanel();
                stackPanel.Children.Add(renderResult.Tree);

                Border border = new Border();
                border.Width = renderResult.CardWidth;
                border.Child = stackPanel;
                (Window.Current.Content as Frame).Content = border;

                await imageWaiter.WaitOnAllImagesAsync();

            }

            StorageFile imageResultFile = null;
            StorageFile jsonResultFile = null;
            if (renderResult.Error == null)
            {
                imageResultFile = await _tempResultsFolder.CreateFileAsync("Result.png", CreationCollisionOption.GenerateUniqueName);
                jsonResultFile = await _tempResultsFolder.CreateFileAsync("Result.json", CreationCollisionOption.GenerateUniqueName);

                await UWPTestLibrary.RenderTestHelpers.ResultsToFile(imageResultFile, jsonResultFile, renderResult.RoundTrippedJSON, renderResult.Tree);
            }

            await Task.Delay(10);

            var result = await TestResultViewModel.CreateAsync(
                cardFile: cardFile,
                hostConfigFile: hostConfigFile,
                renderedTestResult: renderResult,
                actualImageFile: imageResultFile,
                actualJsonFile: jsonResultFile,
                expectedFolder: _expectedFolder,
                sourceHostConfigsFolder: _sourceHostConfigsFolder,
                sourceCardsFolder: _sourceCardsFolder);

            if ((result.Status != TestStatus.Passed) &&
                (result.Status != TestStatus.PassedButSourceWasChanged))
            {
                throw new Exception(result.Status.ToString() + ": " + result.HostConfigName + "\\" + result.CardName);
            }
        }

        [TestMethod]
        public void ElementParserRegistraton_DefaultElementsTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<IAdaptiveWarning> warnings = new List<IAdaptiveWarning>();

            JsonObject jsonObject;

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.ChoiceSet\",\"id\":\"ChoiceSetId\", \"choices\":[{\"type\":\"Input.Choice\",\"title\":\"title\",\"value\":\"value\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.ChoiceSetInput, elementParserRegistration.Get("Input.ChoiceSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"ColumnSet\"}", out jsonObject));
            Assert.AreEqual(ElementType.ColumnSet, elementParserRegistration.Get("ColumnSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Container\", \"items\":[]}", out jsonObject));
            Assert.AreEqual(ElementType.Container, elementParserRegistration.Get("Container").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Date\", \"id\":\"DateId\"}", out jsonObject));
            Assert.AreEqual(ElementType.DateInput, elementParserRegistration.Get("Input.Date").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"FactSet\", \"facts\":[{\"title\":\"title\",\"value\":\"value\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.FactSet, elementParserRegistration.Get("FactSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Image\", \"url\":\"www.foo.com\"}", out jsonObject));
            Assert.AreEqual(ElementType.Image, elementParserRegistration.Get("Image").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"ImageSet\", \"images\":[{\"type\":\"Image\", \"url\":\"www.foo.com\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.ImageSet, elementParserRegistration.Get("ImageSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Media\", \"sources\":[{\"mimeType\":\"foo\",\"url\":\"www.foo.com\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.Media, elementParserRegistration.Get("Media").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Number\", \"id\":\"NumberId\"}", out jsonObject));
            Assert.AreEqual(ElementType.NumberInput, elementParserRegistration.Get("Input.Number").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"TextBlock\",\"text\":\"Hello World\"}", out jsonObject));
            Assert.AreEqual(ElementType.TextBlock, elementParserRegistration.Get("TextBlock").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Text\", \"id\":\"TextId\"}", out jsonObject));
            Assert.AreEqual(ElementType.TextInput, elementParserRegistration.Get("Input.Text").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Time\", \"id\":\"TimeId\"}", out jsonObject));
            Assert.AreEqual(ElementType.TimeInput, elementParserRegistration.Get("Input.Time").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Toggle\", \"id\":\"ToggleId\", \"title\":\"title\"}", out jsonObject));
            Assert.AreEqual(ElementType.ToggleInput, elementParserRegistration.Get("Input.Toggle").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);
        }

        class TestCustomElement : IAdaptiveCardElement
        {
            public TestCustomElement(IAdaptiveCardElement internalTextBlock)
            {
                InternalTextBlock = internalTextBlock;
            }

            public IAdaptiveCardElement InternalTextBlock { get; set; }
            public IAdaptiveActionElement InternalSubmitAction { get; set; }

            public JsonObject ToJson()
            {
                return new JsonObject();
            }
            public JsonObject AdditionalProperties { get; set; }
            public ElementType ElementType { get { return ElementType.Custom; } }
            public string ElementTypeString { get { return "TestCustomElement"; } }
            public HeightType Height { get; set; }
            public string Id { get { return "TestID"; } set { } }
            public bool Separator { get; set; }
            public Spacing Spacing { get; set; }
            public bool IsVisible { get; set; }
        };
        class TestElementParser : IAdaptiveElementParser
        {
            public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<IAdaptiveWarning> warnings)
            {
                JsonObject jsonTextBlock = inputJson.GetNamedObject("internalTextBlock");
                var textBlockParser = elementParsers.Get("TextBlock");

                IAdaptiveCardElement textBlockElement = textBlockParser.FromJson(jsonTextBlock, elementParsers, actionParsers, warnings);
                return new TestCustomElement(textBlockElement) as IAdaptiveCardElement;
            }
        };

        [TestMethod]
        public void ElementParserRegistraton_CustomElementTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<IAdaptiveWarning> warnings = new List<IAdaptiveWarning>();

            elementParserRegistration.Set("TestCustomElement", new TestElementParser());
            IAdaptiveElementParser testElementParserRetrieved = elementParserRegistration.Get("TestCustomElement");
            Assert.IsNotNull(testElementParserRetrieved);
            Assert.IsNotNull(testElementParserRetrieved as TestElementParser);

            String testCard =
                "{" +
                "   \"type\":\"AdaptiveCard\"," +
                "   \"version\":\"1.0\"," +
                "   \"body\":" +
                "   [" +
                "       {" +
                "           \"type\":\"TestCustomElement\"," +
                "           \"internalTextBlock\":" +
                "           {" +
                "               \"type\":\"TextBlock\"," +
                "               \"text\":\"Here is some text\"" +
                "           }" +
                "       }" +
                "   ]" +
                "}";

            AdaptiveCard card = AdaptiveCard.FromJsonString(testCard, elementParserRegistration, actionParserRegistration).AdaptiveCard;
            Assert.IsNotNull(card);

            Assert.AreEqual(1, card.Body.Count);

            IAdaptiveCardElement cardElement = card.Body[0];
            Assert.IsNotNull(cardElement);

            Assert.AreEqual(ElementType.Custom, cardElement.ElementType);
            Assert.AreEqual("TestCustomElement", cardElement.ElementTypeString);

            TestCustomElement customElement = card.Body[0] as TestCustomElement;
            Assert.IsNotNull(customElement);

            Assert.AreEqual(ElementType.TextBlock, customElement.InternalTextBlock.ElementType);
        }

        [TestMethod]
        public void ActionParserRegistraton_DefaultActionsTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<IAdaptiveWarning> warnings = new List<IAdaptiveWarning>();

            JsonObject jsonObject;

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.OpenUrl\", \"url\":\"http:\\\\www.foo.com\"}", out jsonObject));
            Assert.AreEqual(ActionType.OpenUrl, actionParserRegistration.Get("Action.OpenUrl").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.ShowCard\", \"card\":{\"type\":\"AdaptiveCard\", \"version\":\"1.0\"}}", out jsonObject));
            Assert.AreEqual(ActionType.ShowCard, actionParserRegistration.Get("Action.ShowCard").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.Submit\"}", out jsonObject));
            Assert.AreEqual(ActionType.Submit, actionParserRegistration.Get("Action.Submit").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);
        }

        class TestCustomAction : IAdaptiveActionElement
        {
            public TestCustomAction(IAdaptiveActionElement internalSubmitAction)
            {
                InternalSubmitAction = internalSubmitAction;
            }

            public IAdaptiveActionElement InternalSubmitAction { get; set; }

            public JsonObject ToJson()
            {
                return new JsonObject();
            }
            public JsonObject AdditionalProperties { get; set; }
            public string Id { get { return "TestID"; } set { } }
            public ActionType ActionType { get { return ActionType.Custom; } }
            public string ActionTypeString { get { return "TestCustomAction"; } }
            public string IconUrl { get; set; }
            public Sentiment Sentiment { get; set; }
            public string Title { get; set; }
        };

        class TestActionParser : IAdaptiveActionParser
        {
            public IAdaptiveActionElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<IAdaptiveWarning> warnings)
            {
                JsonObject jsonSubmitAction = inputJson.GetNamedObject("internalSubmitAction");
                var submitActionParser = actionParsers.Get("Action.Submit");

                IAdaptiveActionElement submitAction = submitActionParser.FromJson(jsonSubmitAction, elementParsers, actionParsers, warnings);
                return new TestCustomAction(submitAction) as IAdaptiveActionElement;
            }
        };

        [TestMethod]
        public void ActionParserRegistraton_CustomActionTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<IAdaptiveWarning> warnings = new List<IAdaptiveWarning>();

            actionParserRegistration.Set("TestCustomAction", new TestActionParser());
            IAdaptiveActionParser testActionParserRetrieved = actionParserRegistration.Get("TestCustomAction");
            Assert.IsNotNull(testActionParserRetrieved);
            Assert.IsNotNull(testActionParserRetrieved as TestActionParser);

            String testCard =
                "{" +
                "   \"type\":\"AdaptiveCard\"," +
                "   \"version\":\"1.0\"," +
                "   \"body\":" +
                "   [" +
                "   ]," +
                "   \"actions\":" +
                "   [" +
                "       {" +
                "           \"type\":\"TestCustomAction\"," +
                "           \"internalSubmitAction\":" +
                "           {" +
                "			    \"type\": \"Action.Submit\"" +
                "           }" +
                "       }" +
                "   ]" +
                "}";

            AdaptiveCard card = AdaptiveCard.FromJsonString(testCard, elementParserRegistration, actionParserRegistration).AdaptiveCard;
            Assert.IsNotNull(card);

            Assert.AreEqual(1, card.Actions.Count);

            IAdaptiveActionElement action = card.Actions[0];
            Assert.IsNotNull(action);

            Assert.AreEqual(ActionType.Custom, action.ActionType);
            Assert.AreEqual("TestCustomAction", action.ActionTypeString);

            TestCustomAction customElement = card.Actions[0] as TestCustomAction;
            Assert.IsNotNull(customElement);

            Assert.AreEqual(ActionType.Submit, customElement.InternalSubmitAction.ActionType);
        }
    }
}
