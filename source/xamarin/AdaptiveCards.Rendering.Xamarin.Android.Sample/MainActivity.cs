using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V4.App;
using System.Collections.Generic;
using System.Net.Http;
using System;

using AdaptiveCards.BotConnection;
using Microsoft.AdaptiveCards.ObjectModel;
using Microsoft.AdaptiveCards.Renderer;
using Microsoft.AdaptiveCards.Renderer.ActionHandler;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{
    
    [Activity(Label = "AdaptiveCards", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : FragmentActivity, IShowCardActionHandler, ISubmitActionHandler
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
                AdaptiveCard adaptiveCard = AdaptiveCard.DeserializeFromString(jsonText);
                LinearLayout layout = FindViewById<LinearLayout>(Resource.Id.visualAdaptiveCardLayout);
                layout.RemoveAllViews();

                layout.AddView(AdaptiveCardRenderer.Instance.Render(ApplicationContext, SupportFragmentManager, adaptiveCard, this, this, new HostConfig()));
            }
            catch (Exception ex)
            {
                String s = ex.ToString();
            }
        }

        public void OnShowCard(ShowCardAction p0, AdaptiveCard p1)
        {
        }

        public void OnSubmit(SubmitAction p0, IDictionary<string, string> p1)
        {   
        }
    }
}

