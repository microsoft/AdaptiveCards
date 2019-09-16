// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards;
using Xamarin.Forms;

namespace AdaptiveCards.XamarinForms.BotClient
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();

            MainPage = new AdaptiveCards.XamarinForms.BotClient.MainPage();
        }

        protected override void OnStart()
        {
            // Handle when your app starts
        }

        protected override void OnSleep()
        {
            // Handle when your app sleeps
        }

        protected override void OnResume()
        {
            // Handle when your app resumes
        }
    }
}
