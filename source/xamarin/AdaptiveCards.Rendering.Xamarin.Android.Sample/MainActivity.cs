using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V4.App;
using System.Collections.Generic;
using System.Net.Http;
using System;

using AdaptiveCards.BotConnection;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{

    [Activity(Label = "AdaptiveCards", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : FragmentActivity, ICardActionHandler
    {
        private PayloadRetriever m_payloadRetriever = null;

        public MainActivity()
        {
            Java.Lang.Runtime.GetRuntime().LoadLibrary("adaptivecards-native-lib");
        }

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            m_payloadRetriever = new PayloadRetriever();

            Button button = FindViewById<Button>(Resource.Id.myButton);
            button.Click += buttonClick;
        }

        private void buttonClick(object sender, EventArgs e)
        {
            /*
            var httpClient = new HttpClient();
            var response = await httpClient.GetAsync("https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/samples/v1.0/Scenarios/FlightUpdate.json");
            if (response.IsSuccessStatusCode)
            {
                var content = await response.Content.ReadAsStringAsync();
                renderAdaptiveCard(content, true);
            }
            */
            EditText adaptiveCardRequest = FindViewById<EditText>(Resource.Id.editText1);
            RenderAdaptiveCard(m_payloadRetriever.RequestAdaptiveCard(adaptiveCardRequest.Text));
        }

        private void RenderAdaptiveCard(string jsonText)
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
            catch (Exception ex)
            {
                String s = ex.ToString();
            }
        }

        public void OnAction(BaseActionElement element, RenderedAdaptiveCard renderedCard)
        {
        }

        public void OnSubmit(SubmitAction p0, IDictionary<string, string> p1)
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

