using System.IO;
using System.Runtime.CompilerServices;
using Xamarin.Forms;

[assembly: Xamarin.Forms.Dependency(typeof(AdaptiveCards.Sample.BotClient.UWP.CardsReaderImpl))]
namespace AdaptiveCards.Sample.BotClient.UWP
{
    class CardsReaderImpl : ICardsReader
    {
        public string[] ReadAdaptiveCardsJsons(string[] fileNames)
        {
            int fileCount = fileNames.Length;
            string[] adaptiveCardJsons = new string[fileCount];
            for (int i = 0; i < fileNames.Length; ++i)
            {
                string fileName = fileNames[i];
                adaptiveCardJsons[i] = File.ReadAllText("Samples//" + fileName);
            }

            return adaptiveCardJsons;
        }

        public string ReadHostConfigJson(string fileName)
        {
            string hostConfigJson = string.Empty;

            if (string.IsNullOrWhiteSpace(fileName))
            {
                return hostConfigJson;
            }

            hostConfigJson = File.ReadAllText("HostConfigs//" + fileName);

            return hostConfigJson;
        }
    }
}
