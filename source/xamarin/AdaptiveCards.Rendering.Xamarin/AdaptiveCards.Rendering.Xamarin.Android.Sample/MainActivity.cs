using Android.App;
using Android.Widget;
using Android.OS;
using Android.Views;
using Com.Microsoft.Adaptivecards.Objectmodel;
using Android.Support.V4.App;
using Com.Microsoft.Adaptivecards.Renderer;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{
    
    [Activity(Label = "AdaptiveCards", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : Activity
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

            // Get our button from the layout resource,
            // and attach an event to it
            Button button = FindViewById<Button>(Resource.Id.myButton);

            button.Click += delegate
            {
                renderAdaptiveCard(card, true);
            };


        }

        private void renderAdaptiveCard(string jsonText, bool showErrorToast)
        {
            try
            {
                AdaptiveCard adaptiveCard = AdaptiveCard.DeserializeFromString(jsonText);
                Toast.MakeText(this, adaptiveCard.Body.Capacity().ToString(), ToastLength.Short).Show();
                //LinearLayout layout = (LinearLayout)FindViewById(R.id.visualAdaptiveCardLayout);
                //layout.RemoveAllViews();


                AdaptiveCardRenderer.Instance.Render(Application.Context, FragmentManager, adaptiveCard, this, this, new HostConfig());
                //layout.AddView();
            }
            catch (Java.IO.IOException ex)
            {
                if (showErrorToast)
                {
                    Toast.MakeText(this, ex.Message, ToastLength.Short).Show();
                }
            }
        }
    }
}

