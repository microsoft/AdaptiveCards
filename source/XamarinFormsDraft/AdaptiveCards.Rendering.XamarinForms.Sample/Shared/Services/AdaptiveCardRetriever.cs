using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using System.Runtime;
using AdaptiveCards.Rendering.XamarinForms.Sample.Views;

namespace AdaptiveCards.Rendering.XamarinForms.Sample.Services
{
    class AdaptiveCardRetriever
    {
        private List<string> CardContents { get; set; } = new List<string>();

        private int CardIndex = 0;

        public AdaptiveCardRetriever()
        {
            LoadCardsContentFromFiles();
        }

        private void LoadCardsContentFromFiles()
        {
            var assembly = IntrospectionExtensions.GetTypeInfo(typeof(MainPage)).Assembly;

            foreach (var fileName in assembly.GetManifestResourceNames())
            {
                if (fileName.StartsWith("Shared.CardSamples."))
                {
                    System.IO.Stream stream = assembly.GetManifestResourceStream(fileName);
                    string cardContent = "";
                    using (var reader = new System.IO.StreamReader(stream))
                    {
                        cardContent = reader.ReadToEnd();
                    }
                    CardContents.Add(cardContent);
                }
            }
        }

        public string NextCard()
        {
            if (CardContents.Count == 0)
            {
                return "";
            }

            CardIndex = (CardIndex + 1) % CardContents.Count;
            return CardContents[CardIndex];
        }

    }
}
