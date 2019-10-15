using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

using XamarinFormsDraft.Models;
using XamarinFormsDraft.Views;
using XamarinFormsDraft.ViewModels;
using AdaptiveCards.Rendering.XamarinForms;

namespace XamarinFormsDraft.Views
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class ItemsPage : ContentPage
    {
        ItemsViewModel viewModel;
        AdaptiveCardControl cardControl;
        Label inputLabel;

        public ItemsPage()
        {
            InitializeComponent();

            inputLabel = this.FindByName<Label>("inputs");

            cardControl = this.FindByName<AdaptiveCardControl>("CardControl");

            cardControl.OnAction += CardControl_OnAction;

            cardControl.CardContent = @"{
                ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [
		            {
			            ""type"": ""TextBlock"",
			            ""text"": ""This card's action will open a URL""
                    },
                    {
                        ""type"": ""Input.Text"",
                        ""id"": ""input1"",
                        ""placeholder"": ""enter comment"",
                        ""maxLength"": 500
                    }
	            ],
	            ""actions"": [
                    {
                        ""type"": ""Action.OpenUrl"",
                        ""title"": ""Action.OpenUrl"",
                        ""url"": ""http://adaptivecards.io""
                    },
                    {
                        ""type"": ""Action.Submit"",
                        ""title"": ""Action.Submit"",
                        ""data"": {
                            ""x"": 13
                        }
                    },
                    {
                        ""type"": ""Action.Submit"",
                        ""title"": ""Neat!""
		            }
	            ]
            }";


    /*
            cardControl.CardContent = 
@"{
  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
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
}";*/

            BindingContext = viewModel = new ItemsViewModel();
        }

        private void CardControl_OnAction(object sender, EventArgs e)
        {
            AdaptiveEventArgs eventArgs = e as AdaptiveEventArgs;

            string inputsResult = "";
            foreach(KeyValuePair<string,string> keyValue in eventArgs.Inputs)
            {
                if (!String.IsNullOrEmpty(inputsResult) )
                {
                    inputsResult += "\n";
                }
                inputsResult += (keyValue.Key + ": " + keyValue.Value);
            }

            inputLabel.Text = inputsResult;
        }

        async void OnItemSelected(object sender, SelectedItemChangedEventArgs args)
        {
            var item = args.SelectedItem as Item;
            if (item == null)
                return;

            await Navigation.PushAsync(new ItemDetailPage(new ItemDetailViewModel(item)));

            // Manually deselect item.
            // ItemsListView.SelectedItem = null;
        }

        async void AddItem_Clicked(object sender, EventArgs e)
        {
            await Navigation.PushModalAsync(new NavigationPage(new NewItemPage()));
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();
            /*
            if (viewModel.Items.Count == 0)
                viewModel.LoadItemsCommand.Execute(null);
            */
        }
    }
}
