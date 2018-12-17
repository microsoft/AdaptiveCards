using Android.App;
using Android.Widget;
using Android.OS;
using IO.Adaptivecards.Objectmodel;
using IO.Adaptivecards.Renderer.Actionhandler;
using IO.Adaptivecards.Renderer;
using Android.Support.V4.App;
using System.Collections.Generic;
using System.Net.Http;
using System;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{

    [Activity(Label = "AdaptiveCards", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : FragmentActivity, ICardActionHandler
    {
        public MainActivity()
        {
            Java.Lang.Runtime.GetRuntime().LoadLibrary("adaptivecards-native-lib");
        }


        string card = @"
{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello""
        }
    ]
}";

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            Button button = FindViewById<Button>(Resource.Id.myButton);
            button.Click += buttonClick;
        }

        private async void buttonClick(object sender, EventArgs e)
        {
            var httpClient = new HttpClient();
            var response = await httpClient.GetAsync("https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/samples/v1.0/Scenarios/FlightUpdate.json");
            if (response.IsSuccessStatusCode)
            {
                var content = await response.Content.ReadAsStringAsync();
                renderAdaptiveCard(content, true);
            }
        }

        private void renderAdaptiveCard(string jsonText, bool showErrorToast)
        {
            try
            {
                ParseResult parseResult = AdaptiveCard.DeserializeFromString(jsonText, AdaptiveCardRenderer.Version);
                Toast.MakeText(this, parseResult.AdaptiveCard.Body.Capacity().ToString(), ToastLength.Short).Show();
                LinearLayout layout = (LinearLayout)FindViewById(Resource.Id.visualAdaptiveCardLayout);
                layout.RemoveAllViews();

                var renderedCard = AdaptiveCardRenderer.Instance.Render(Application.Context, SupportFragmentManager, parseResult.AdaptiveCard, this, new HostConfig());
                layout.AddView(renderedCard.View);
            }
            catch (Java.IO.IOException ex)
            {
                if (showErrorToast)
                {
                    Toast.MakeText(this, ex.Message, ToastLength.Short).Show();
                }
            }
        }

        public void OnAction(BaseActionElement element, RenderedAdaptiveCard renderedCard)
        {
        }

        public void OnMediaPlay(BaseCardElement element, RenderedAdaptiveCard renderedCard)
        {
        }

        public void OnMediaStop(BaseCardElement element, RenderedAdaptiveCard renderedCard)
        {
        }
    }
}
