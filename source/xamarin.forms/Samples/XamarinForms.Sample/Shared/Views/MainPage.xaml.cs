using AdaptiveCards.Rendering.XamarinForms.Sample.Services;
using Plugin.Permissions;
using Plugin.Permissions.Abstractions;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reflection;
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

            AskForPermissions();

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

        private async void AskForPermissions()
        {
            Permission[] permissionsToAsk = { Permission.Storage, Permission.Phone, Permission.Sensors };

            foreach (Permission permission in permissionsToAsk)
            {
                var status = PermissionStatus.Unknown;
                status = await CrossPermissions.Current.CheckPermissionStatusAsync(permission);

                await DisplayAlert("Pre - Results", status.ToString(), "OK");

                if (status != PermissionStatus.Granted)
                {
                    status = await PermissionUtils.CheckPermissions(permission);
                }

                await DisplayAlert("Results", status.ToString(), "OK");
            }
        }
    }
}
