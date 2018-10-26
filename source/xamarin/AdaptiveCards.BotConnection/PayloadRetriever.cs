using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

// The intended use for this class is to connect to a given bot (or some other payload generator) and retrieve payloads from a set of available adaptive cards
// Right now it's only being hardcoded to always retrieve the same adaptive card

namespace AdaptiveCards.BotConnection
{
    public class PayloadRetriever
    {
        private int cardToShow = 0;
        private int remoteCardToShow = 0;
        private readonly string[] cards =
        {
            "{\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"version\": \"1.0\", \"type\": \"AdaptiveCard\"," +
                " \"speak\": \"<s>Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM</s>\"," +
                " \"body\": [ { \"type\": \"TextBlock\", \"text\": \"Passengers\", \"weight\": \"bolder\", \"isSubtle\": false }," +
                " { \"type\": \"TextBlock\", \"text\": \"Sarah Hum\", \"separator\": true }," +
                " { \"type\": \"TextBlock\", \"text\": \"Jeremy Goldberg\", \"spacing\": \"none\" }," +
                " { \"type\": \"TextBlock\", \"text\": \"Evan Litvak\", \"spacing\": \"none\" }," +
                " { \"type\": \"TextBlock\", \"text\": \"2 Stops\", \"weight\": \"bolder\", \"spacing\": \"medium\" }," +
                " { \"type\": \"TextBlock\", \"text\": \"Fri, October 10 8:30 AM\", \"weight\": \"bolder\", \"spacing\": \"none\" }," +
                " { \"type\": \"ColumnSet\", \"separator\": true, \"columns\": [ { \"type\": \"Column\", \"width\": 1, \"items\": [" +
                " { \"type\": \"TextBlock\", \"text\": \"San Francisco\", \"isSubtle\": true }," +
                " { \"type\": \"TextBlock\", \"size\": \"extraLarge\", \"color\": \"accent\", \"text\": \"SFO\", \"spacing\": \"none\" } ] }," +
                " { \"type\": \"Column\", \"width\": \"auto\", \"items\": [ { \"type\": \"TextBlock\", \"text\": \"&nbsp;\" }," +
                " { \"type\": \"Image\", \"url\": \"http://messagecardplayground.azurewebsites.net/assets/airplane.png\", \"size\": \"small\", \"spacing\": \"none\" } ] }," +
                " { \"type\": \"Column\", \"width\": 1, \"items\": [" +
                " { \"type\": \"TextBlock\", \"horizontalAlignment\": \"right\", \"text\": \"Amsterdam\", \"isSubtle\": true }, " +
                " { \"type\": \"TextBlock\", \"horizontalAlignment\": \"right\", \"size\": \"extraLarge\", \"color\": \"accent\", \"text\": \"AMS\", \"spacing\": \"none\" } ] } ] }," +
                " { \"type\": \"TextBlock\", \"text\": \"Non-Stop\", \"weight\": \"bolder\", \"spacing\": \"medium\" }," +
                " { \"type\": \"TextBlock\", \"text\": \"Fri, October 18 9:50 PM\", \"weight\": \"bolder\", \"spacing\": \"none\" }," +
                " { \"type\": \"ColumnSet\", \"separator\": true, \"columns\": [ { \"type\": \"Column\", \"width\": 1, \"items\": [" +
                " { \"type\": \"TextBlock\", \"text\": \"Amsterdam\", \"isSubtle\": true }," +
                " { \"type\": \"TextBlock\", \"size\": \"extraLarge\", \"color\": \"accent\", \"text\": \"AMS\", \"spacing\": \"none\" } ] }," +
                " { \"type\": \"Column\", \"width\": \"auto\", \"items\": [" +
                " { \"type\": \"TextBlock\", \"text\": \"&nbsp;\" }," +
                " { \"type\": \"Image\", \"url\": \"http://messagecardplayground.azurewebsites.net/assets/airplane.png\", \"size\": \"small\", \"spacing\": \"none\" } ] }," +
                " { \"type\": \"Column\", \"width\": 1, \"items\": [" +
                " { \"type\": \"TextBlock\", \"horizontalAlignment\": \"right\", \"text\": \"San Francisco\", \"isSubtle\": true }," +
                " { \"type\": \"TextBlock\", \"horizontalAlignment\": \"right\", \"size\": \"extraLarge\", \"color\": \"accent\", \"text\": \"SFO\", \"spacing\": \"none\" } ] } ] }," +
                " { \"type\": \"ColumnSet\", \"spacing\": \"medium\", \"columns\": [" +
                " { \"type\": \"Column\", \"width\": \"1\", \"items\": [" +
                " { \"type\": \"TextBlock\", \"text\": \"Total\", \"size\": \"medium\", \"isSubtle\": true } ] }," +
                " { \"type\": \"Column\", \"width\": 1, \"items\": [" +
                " { \"type\": \"TextBlock\", \"horizontalAlignment\": \"right\", \"text\": \"$4,033.54\", \"size\": \"medium\", \"weight\": \"bolder\" } ] } ] } ] }" ,
            "{\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", " +
                "\"version\": \"1.0\", \"speak\": \"Microsoft stock is trading at $62.30 a share, which is down .32%\", " +
                "\"body\": [ { \"type\": \"Container\", \"items\": [ " +
                "{ \"type\": \"TextBlock\", \"text\": \"Microsoft Corp (NASDAQ: MSFT)\", \"size\": \"medium\", \"isSubtle\": true }, " +
                "{ \"type\": \"TextBlock\", \"text\": \"September 19, 4:00 PM EST\", \"isSubtle\": true } ] }, " +
                "{ \"type\": \"Container\", \"spacing\": \"none\", \"items\": [ " +
                "{ \"type\": \"ColumnSet\", \"columns\": [ " +
                "{ \"type\": \"Column\", \"width\": \"stretch\", \"items\": [ " +
                "{ \"type\": \"TextBlock\", \"text\": \"75.30\", \"size\": \"extraLarge\" }, " +
                "{ \"type\": \"TextBlock\", \"text\": \"▼ 0.20 (0.32%)\", \"size\": \"small\", \"color\": \"attention\", \"spacing\": \"none\" } ] }, " +
                "{ \"type\": \"Column\", \"width\": \"auto\", \"items\": [ " +
                "{ \"type\": \"FactSet\", \"facts\": [ { \"title\": \"Open\", \"value\": \"62.24\" }, " +
                "{ \"title\": \"High\", \"value\": \"62.98\" }, { \"title\": \"Low\", \"value\": \"62.20\" } ] } ] } ] } ] } ] }",
            "{  \"type\": \"AdaptiveCard\",  \"version\": \"1.0\"," +
                "\"body\": [" +
                "{ \"type\": \"TextBlock\", \"text\": \"Your registration is almost complete\", \"size\": \"medium\", \"weight\": \"bolder\" }," +
                "{ \"type\": \"TextBlock\", \"text\": \"What type of food do you prefer?\", \"wrap\": true }," +
                "{ \"type\": \"ImageSet\", \"imageSize\": \"medium\", \"images\": [" +
                "{ \"type\": \"Image\", \"url\": \"http://contososcubademo.azurewebsites.net/assets/steak.jpg\" }," +
                "{ \"type\": \"Image\", \"url\": \"http://contososcubademo.azurewebsites.net/assets/chicken.jpg\" }," +
                "{ \"type\": \"Image\", \"url\": \"http://contososcubademo.azurewebsites.net/assets/tofu.jpg\" } ] } ]," +
                "\"actions\": [" +
                "{ \"type\": \"Action.ShowCard\", \"title\": \"Steak\", \"card\":" +
                "{ \"type\": \"AdaptiveCard\", \"body\": [" +
                "{ \"type\": \"TextBlock\", \"text\": \"How would you like your steak prepared?\", \"size\": \"medium\", \"wrap\": true }," +
                "{ \"type\": \"Input.ChoiceSet\", \"id\": \"SteakTemp\", \"style\": \"expanded\", \"choices\": [" +
                "{ \"title\": \"Rare\", \"value\": \"rare\" }," +
                "{ \"title\": \"Medium-Rare\", \"value\": \"medium-rare\" }," +
                "{ \"title\": \"Well-done\", \"value\": \"well-done\" } ] }," +
                "{ \"type\": \"Input.Text\", \"id\": \"SteakOther\", \"isMultiline\": true, \"placeholder\": \"Any other preparation requests?\" } ]," +
                "\"actions\": [ " +
                "{ \"type\": \"Action.Submit\",\"title\": \"OK\", \"data\": {\"FoodChoice\": \"Steak\" } } ] } }," +
                "{ \"type\": \"Action.ShowCard\", \"title\": \"Chicken\", \"card\":" +
                "{ \"type\": \"AdaptiveCard\", \"body\": [" +
                "{ \"type\": \"TextBlock\", \"text\": \"Do you have any allergies?\", \"size\": \"medium\", \"wrap\": true }," +
                "{ \"type\": \"Input.ChoiceSet\", \"id\": \"ChickenAllergy\", \"style\": \"expanded\", \"isMultiSelect\": true, \"choices\": [" +
                "{ \"title\": \"I'm allergic to peanuts\", \"value\": \"peanut\" } ] }," +
                "{ \"type\": \"Input.Text\", \"id\": \"ChickenOther\", \"isMultiline\": true, \"placeholder\": \"Any other preparation requests?\" } ]," +
                "\"actions\": [" +
                "{ \"type\": \"Action.Submit\", \"title\": \"OK\", \"data\": { \"FoodChoice\": \"Chicken\" } } ] } }," +
                "{ \"type\": \"Action.ShowCard\", \"title\": \"Tofu\", \"card\":" +
                "{ \"type\": \"AdaptiveCard\", \"body\": [" +
                "{ \"type\": \"TextBlock\", \"text\": \"Would you like it prepared vegan?\", \"size\": \"medium\", \"wrap\": true }," +
                "{ \"type\": \"Input.Toggle\", \"id\": \"Vegetarian\", \"title\": \"Please prepare it vegan\", \"valueOn\": \"vegan\", \"valueOff\": \"notVegan\" }," +
                "{ \"type\": \"Input.Text\", \"id\": \"VegOther\", \"isMultiline\": true, \"placeholder\": \"Any other preparation requests?\" } ]," +
                "\"actions\": [ { \"type\": \"Action.Submit\", \"title\": \"OK\", \"data\": { \"FoodChoice\": \"Vegetarian\" } } ] } } ] }"
        };

        private readonly string[] remoteScenarios =
        {
            "ActivityUpdate.json",
            "CalendarReminder.json",
            "FlightItinerary.json",
            "FlightUpdate.json",
            "FoodOrder.json",
            "ImageGallery.json",
            "InputForm.json",
            "Inputs.json",
            "Restaurant.json",
            "Solitaire.json",
            "SportingEvent.json",
            "StockUpdate.json",
            "WeatherCompact.json",
            "WeatherLarge.json"
        };

        public PayloadRetriever()
        {
        }

        public string RequestLocalAdaptiveCard()
        {
            cardToShow = (++cardToShow == cards.Length) ? 0 : cardToShow;
            return cards[cardToShow];
        }

        public async Task<string> RequestRemoteAdaptiveCard()
        {
            remoteCardToShow = (++remoteCardToShow == remoteScenarios.Length) ? 0 : remoteCardToShow;

            var httpClient = new HttpClient();
            var response = await httpClient.GetAsync($"https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/samples/v1.0/Scenarios/{remoteScenarios[remoteCardToShow]}");
            if (response.IsSuccessStatusCode)
            {
                var content = await response.Content.ReadAsStringAsync();
                return content;
            }

            return string.Empty;
        }
    }
}