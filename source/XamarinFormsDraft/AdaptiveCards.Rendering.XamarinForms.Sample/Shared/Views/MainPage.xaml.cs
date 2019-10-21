using AdaptiveCards.Rendering.XamarinForms.Sample.Services;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace AdaptiveCards.Rendering.XamarinForms.Sample.Views
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class MainPage : ContentPage
    {
        private AdaptiveCardRetriever retriever;

        AdaptiveCardControl cardControl;
        Label inputLabel;

        public MainPage()
        {
            InitializeComponent();

            retriever = new AdaptiveCardRetriever();

            inputLabel = this.FindByName<Label>("inputs");

            cardControl = this.FindByName<AdaptiveCardControl>("CardControl");

            cardControl.OnAction += CardControl_OnAction;

            cardControl.CardContent = retriever.NextCard();
        }

        private void CardControl_OnAction(object sender, EventArgs e)
        {
            AdaptiveEventArgs eventArgs = e as AdaptiveEventArgs;

            string inputsResult = "";
            foreach (KeyValuePair<string, string> keyValue in eventArgs.Inputs)
            {
                if (!String.IsNullOrEmpty(inputsResult))
                {
                    inputsResult += "\n";
                }
                inputsResult += (keyValue.Key + ": " + keyValue.Value);
            }

            inputLabel.Text = inputsResult;
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            cardControl.CardContent = retriever.NextCard();

            inputLabel.Text = "";
        }
    }
}
