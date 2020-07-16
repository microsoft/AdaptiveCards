using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards.Sample.BotClient;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System.IO;
using Xamarin.Forms;
using Android.Content.Res;
using Android.Content;

[assembly: Xamarin.Forms.Dependency(typeof(AdaptiveCards.XamarinForms.BotClient.Droid.CardsReaderImpl))]
namespace AdaptiveCards.XamarinForms.BotClient.Droid
{
    class CardsReaderImpl : ICardsReader
    {
        public string[] ReadAdaptiveCardsJsons(string[] fileNames)
        {
            Context context = Android.App.Application.Context;
            AssetManager assetManager = context.Assets;

            int fileCount = fileNames.Length;
            string[] adaptiveCardJsons = new string[fileCount];
            for (int i = 0; i < fileNames.Length; ++i)
            {
                string fileName = fileNames[i];
                string cardJson;

                using (StreamReader sr = new StreamReader(assetManager.Open(fileName)))
                {
                    cardJson = sr.ReadToEnd();
                }
                adaptiveCardJsons[i] = cardJson;
            }

            return adaptiveCardJsons;
        }

        public string ReadHostConfigJson(string filename)
        {
            Context context = Android.App.Application.Context;
            AssetManager assetManager = context.Assets;

            string hostConfigJson = string.Empty;

            if (string.IsNullOrWhiteSpace(filename))
            {
                return hostConfigJson;
            }

            using (StreamReader sr = new StreamReader(assetManager.Open(filename)))
            {
                hostConfigJson = sr.ReadToEnd();
            }

            return hostConfigJson;
        }
    }
}
