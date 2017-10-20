using System;
using System.Net.Http;
using UIKit;
using Xamarin.AdaptiveCards.iOS;

namespace XamarinAC
{
    public partial class ViewController : UIViewController
    {
        protected ViewController(IntPtr handle) : base(handle)
        {
            // Note: this .ctor should not contain any initialization logic.
        }

        string card = @"{
    ""$schema"":""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""This is some text"",
            ""size"": ""large""
        },
        {
            ""type"": ""TextBlock"",
            ""text"": ""It doesn't wrap by default"",
            ""weight"": ""bolder""
        },
        {
            ""type"": ""TextBlock"",
            ""text"": ""So set **wrap** to true if you plan on showing a paragraph of text"",
            ""wrap"": true
        },
        {
            ""type"": ""TextBlock"",
            ""text"": ""You can also use **maxLines** to prevent it from getting out of hand"",
            ""wrap"": true,
            ""maxLines"": 2
        },
        {
            ""type"": ""TextBlock"",
            ""text"": ""You can even draw attention to certain text with color"",
            ""wrap"": true,
            ""color"": ""attention""
        }
    ]
}";
        public  override void ViewDidLoad()
        {
            base.ViewDidLoad();

            //UIButton button = new UIButton();
            var testcard = ACOAdaptiveCard.FromJson(card);
            //LoadCard();           
            //string s = "";

            //ACRRenderer.Render(); card.Card

            // Perform any additional setup after loading the view, typically from a nib.
        }

        public async void LoadCard()
        {
            var httpClient = new HttpClient();
            var response = await httpClient.GetAsync("https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/samples/v1.0/Scenarios/FlightUpdate.json");
            if (response.IsSuccessStatusCode)
            {
                var json = await response.Content.ReadAsStringAsync();

                var card = ACOAdaptiveCard.FromJson(json);
            }
        }


        public override void DidReceiveMemoryWarning()
        {
            base.DidReceiveMemoryWarning();
            // Release any cached data, images, etc that aren't in use.
        }
    }
}
