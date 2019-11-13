using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.Support.V4.App;
using Android.Support.V4.View;
using System;

using AdaptiveCards.BotConnection;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.Registration;
using AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom;
using System.IO;
using System.Text;
using Java.IO;
using Android.Drm;
using System.Runtime.InteropServices;
using Android.Renderscripts;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{
    [Activity(Label = "AdaptiveCards", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : FragmentActivity, ICardActionHandler
    {
        private const int FileSelectCard = 0;
        private const int FileSelectConfig = 1;

        private string CardJson = "";
        private HostConfig Config = null;
        private PayloadRetriever PayloadRetriever = null;

        public MainActivity()
        {
            Java.Lang.Runtime.GetRuntime().LoadLibrary("adaptivecards-native-lib");
        }

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            PayloadRetriever = new PayloadRetriever();

            Button localButton = FindViewById<Button>(Resource.Id.local);
            localButton.Click += OnLocalClick;

            Button cardSelectButton = FindViewById<Button>(Resource.Id.cardSelectButton);
            cardSelectButton.Click += CardSelectButton_Click;

            Button hostConfigSelectButton = FindViewById<Button>(Resource.Id.hostConfigSelectButton);
            hostConfigSelectButton.Click += HostConfigSelectButton_Click;

            // Button remoteButton = FindViewById<Button>(Resource.Id.remote);
            // remoteButton.Click += OnRemoteClickAsync;

            AddCustomRenderers();
        }

        private void CardSelectButton_Click(object sender, EventArgs e)
        {
            SelectFile(FileSelectCard);
        }

        private void HostConfigSelectButton_Click(object sender, EventArgs e)
        {
            SelectFile(FileSelectConfig);
        }

        private async void OnRemoteClickAsync(object sender, EventArgs e)
        {
            RenderAdaptiveCard(await PayloadRetriever.RequestRemoteAdaptiveCard());
        }

        private const int ReadRequestCode = 42;

        private void OnLocalClick(object sender, EventArgs e)
        {
            RenderAdaptiveCard(PayloadRetriever.RequestLocalAdaptiveCard());
        }

        private void SelectFile(int requestCode)
        {
            Intent filePicker = new Intent(Intent.ActionOpenDocument);
            filePicker.SetType("*/*");
            filePicker.AddCategory(Intent.CategoryOpenable);

            StartActivityForResult(filePicker, requestCode);
        }

        protected override void OnActivityResult(int requestCode, [GeneratedEnum] Result resultCode, Intent data)
        {
            if (resultCode == Result.Ok)
            {
                String fullString = LoadFile(data.Data);
                if (String.IsNullOrWhiteSpace(fullString))
                {
                    return;
                }

                if (requestCode == FileSelectCard)
                {
                    EditText fileEditText = (EditText)FindViewById(Resource.Id.cardPathEditText);
                    fileEditText.Text = (String)data.Data.LastPathSegment;

                    CardJson = fullString;
                    RenderAdaptiveCard(CardJson);
                }

                if (requestCode == FileSelectConfig)
                {
                    EditText fileEditText = (EditText)FindViewById(Resource.Id.hostConfigPathEditText);
                    fileEditText.Text = (String)data.Data.LastPathSegment;

                    LoadHostConfig(fullString);
                    RenderAdaptiveCard(CardJson);
                }
            }
        }

        private System.String LoadFile(global::Android.Net.Uri uri)
        {
            // Get the Uri of the selected file
            if (uri == null)
            {
                Toast.MakeText(this, "File was not selected.", ToastLength.Long).Show();
                return null;
            }

            Stream inputStream = null;
            try
            {
                inputStream = ContentResolver.OpenInputStream(uri);
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

                StringBuilder cardJson = new StringBuilder();
                string s = "";

                while ((s = reader.ReadLine()) != null)
                {
                    cardJson.Append(s);
                }

                return cardJson.ToString();
            }
            catch (Java.IO.FileNotFoundException fnfe)
            {
                Toast.MakeText(this, "File " + uri.Path + " was not found", ToastLength.Short);
            }
            catch (System.Exception e) {
                return null;
            }
            
            return null;
        }

        private void AddCustomRenderers()
        {
            CardRendererRegistration.Instance.RegisterRenderer("CustomElement", new CustomElementRenderer());
            CardRendererRegistration.Instance.RegisterActionRenderer("CustomAction", new CustomActionRenderer());

            CardRendererRegistration.Instance.RegisterActionLayoutRenderer(new CustomActionLayout());

            FeatureRegistration featureRegistration = new FeatureRegistration();
            featureRegistration.AddFeature("acTest", "1.0");

            CardRendererRegistration.Instance.RegisterFeatureRegistration(featureRegistration);
        }

        private void RenderAdaptiveCard(string jsonText)
        {
            try
            {
                ElementParserRegistration elementParserRegistration = new ElementParserRegistration();
                elementParserRegistration.AddParser("CustomElement", new CustomElementParser());

                ActionParserRegistration actionParserRegistration = new ActionParserRegistration();
                actionParserRegistration.AddParser("CustomAction", new CustomActionParser());

                ParseContext parseContext = new ParseContext(elementParserRegistration, actionParserRegistration);

                ParseResult parseResult = AdaptiveCard.DeserializeFromString(jsonText, AdaptiveCardRenderer.Version, parseContext);
                LinearLayout layout = (LinearLayout)FindViewById(Resource.Id.visualAdaptiveCardLayout);
                layout.RemoveAllViews();

                var renderedCard = AdaptiveCardRenderer.Instance.Render(this, SupportFragmentManager, parseResult.AdaptiveCard, this, Config ?? new HostConfig());
                layout.AddView(renderedCard.View);
            }
            catch (Exception ex)
            {
                string s = ex.ToString();
            }
        }

        private void LoadHostConfig(string configJson)
        {
            Config = HostConfig.DeserializeFromString(configJson);
        }

        public void OnAction(BaseActionElement element, RenderedAdaptiveCard renderedCard)
        {
            ActionType actionType = element.ElementType;
            var inputs = renderedCard.Inputs;
            string inputValues = string.Empty;
            foreach (var inputString in inputs)
            {
                inputValues += $"{{{inputString.Key} : {inputString.Value}}}\n";
            }
            if (actionType == ActionType.Submit)
            {
                var submitAction = SubmitAction.Dynamic_cast(element);
                var data = submitAction.DataJson;
                Toast.MakeText(this, data + "\n" + inputValues, ToastLength.Short).Show();
            }
            else if (actionType == ActionType.ShowCard)
            {
                var showcardAction = ShowCardAction.Dynamic_cast(element);
                var card = showcardAction.Card;
                Toast.MakeText(this, card.ToString() + "\n" + inputValues, ToastLength.Short).Show();
            }
            else if (actionType == ActionType.OpenUrl)
            {
                var openUrlAction = OpenUrlAction.Dynamic_cast(element);
                var url = openUrlAction.Url;
                Toast.MakeText(this, url + "\n" + inputValues, ToastLength.Short).Show();
            }
        }

        public void OnMediaPlay(BaseCardElement element, RenderedAdaptiveCard renderedCard)
        {
        }

        public void OnMediaStop(BaseCardElement element, RenderedAdaptiveCard renderedCard)
        {
        }
    }
}
