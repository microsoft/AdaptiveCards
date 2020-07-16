using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using AdaptiveCards.Sample.BotClient;
using Foundation;
using UIKit;

using Xamarin.Forms;

[assembly: Xamarin.Forms.Dependency(typeof(AdaptiveCards.XamarinForms.BotClient.iOS.CardsReaderImpl))]
namespace AdaptiveCards.XamarinForms.BotClient.iOS
{
    class CardsReaderImpl : ICardsReader
    {
        public string[] ReadAdaptiveCardsJsons(string[] fileNames)
        {
            int fileCount = fileNames.Length;
            string[] adaptiveCardJsons = new string[fileCount];

            for (int i = 0; i < fileCount; ++i)
            {
                var assembly = System.Reflection.Assembly.GetExecutingAssembly();
                string fileName = fileNames[i];
                // Please pay attention to this stream's name: project's name + folder's name + file's name
                using (var stream = assembly.GetManifestResourceStream("AdaptiveCards.XamarinForms.BotClient.iOS.Resources." + fileName))
                {
                    byte[] buffer = new byte[stream.Length];
                    StreamReader reader = new StreamReader(stream);
                    string cardJson = reader.ReadToEnd();
                    adaptiveCardJsons[i] = cardJson;
                }
            }

            return adaptiveCardJsons;
        }

        public string ReadHostConfigJson(string filename)
        {
            string hostConfigJson = string.Empty;

            if (string.IsNullOrWhiteSpace(filename))
            {
                return hostConfigJson;
            }

            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            // Please pay attention to this stream's name: project's name + folder's name + file's name
            using (var stream = assembly.GetManifestResourceStream("AdaptiveCards.XamarinForms.BotClient.iOS.Resources." + filename))
            {
                StreamReader reader = new StreamReader(stream);
                hostConfigJson = reader.ReadToEnd();
            }

            return hostConfigJson;
        }
    }
}
