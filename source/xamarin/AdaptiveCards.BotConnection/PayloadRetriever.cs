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
            // TextBlock Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { " +
              " \"type\": \"TextBlock\", \"text\": \"This is some text\", \"size\": \"large\" }, { \"type\": \"TextBlock\", \"text\": \"It doesn't wrap by default\", " +
              " \"weight\": \"bolder\" }, { \"type\": \"TextBlock\", \"text\": \"So set **wrap** to true if you plan on showing a paragraph of text\", \"wrap\": true " +
              " }, { \"type\": \"TextBlock\", \"text\": \"You can also use **maxLines** to prevent it from getting out of hand\", \"wrap\": true, \"maxLines\": 2 " +
              " }, { \"type\": \"TextBlock\", \"text\": \"You can even draw attention to certain text with color\", \"wrap\": true, \"color\": \"attention\" } ] } ",

            // Inputs Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"Input.Text\", " +
              " \"id\": \"input1\", \"placeholder\": \"enter comment\", \"maxLength\": 500 }, { \"type\": \"Input.Number\", \"id\": \"number\", \"placeholder\": \"Enter a number\", " +
              " \"min\": 1, \"max\": 10, \"value\": 3 }, { \"type\": \"Input.Date\", \"id\": \"date\", \"placeholder\": \"Enter a date\", \"value\": \"2017-10-12\" }, { " +
              " \"type\": \"Input.Time\", \"id\": \"time\", \"min\": \"09:00\", \"max\": \"17:00\", \"value\": \"15:30\" }, { \"type\": \"Input.Toggle\", \"id\": \"acceptTerms\", " +
              " \"title\": \"I accept the terms and agreements\", \"value\": \"true\", \"valueOn\": \"true\", \"valueOff\": \"false\" }, { \"type\": \"Input.ChoiceSet\", " +
              " \"id\": \"myColor\", \"style\": \"compact\", \"isMultiSelect\": false, \"value\": \"1\", \"choices\": [ { \"title\": \"Red\", \"value\": \"1\" }, { " +
              " \"title\": \"Green\", \"value\": \"2\" } ] } ], \"actions\": [ { \"type\": \"Action.Submit\", \"title\": \"OK\" } ] }",


            // Image Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"Image\", " +
              " \"url\": \"https://adaptivecards.io/content/cats/1.png\" } ] } ",
            // Media Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.1\", \"fallbackText\": " +
              " \"This card requires Media to be viewed. Ask your platform to update to Adaptive Cards v1.1 for this and more!\", \"body\": [ { \"type\": \"Media\", " +
              " \"poster\": \"https://adaptivecards.io/content/poster-video.png\", \"sources\": [ { \"mimeType\": \"video/mp4\", \"url\": " +
              " \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4\" } ] } ] } ",
            // RichTextBlock Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.2\", \"body\": [ { \"type\": \"RichTextBlock\", " +
              " \"wrap\": true, \"inlines\": [ \"This is the first inline. \", { \"type\": \"TextRun\", \"text\": \"We support colors, \", \"color\": \"good\" }, { \"type\": \"TextRun\", " +
              " \"text\": \"both regular and subtle. \", \"isSubtle\": true }, { \"type\": \"TextRun\", \"text\": \"Text \", \"size\": \"small\" }, { \"type\": \"TextRun\", " +
              " \"text\": \"of \", \"size\": \"medium\" }, { \"type\": \"TextRun\", \"text\": \"all \", \"size\": \"large\" }, { \"type\": \"TextRun\", \"text\": \"sizes! \", " +
              " \"size\": \"extraLarge\" }, { \"type\": \"TextRun\", \"text\": \"Light weight text. \", \"weight\": \"lighter\" }, { \"type\": \"TextRun\", \"text\": \"Bold weight text. \", " +
              " \"weight\": \"bolder\" }, { \"type\": \"TextRun\", \"text\": \"Highlights. \", \"highlight\": true }, { \"type\": \"TextRun\", \"text\": \"Italics. \", " +
              " \"italic\": true }, { \"type\": \"TextRun\", \"text\": \"Strikethrough. \", \"strikethrough\": true }, { \"type\": \"TextRun\", \"text\": \"Monospace too!\", " +
              " \"fontType\": \"monospace\" } ] }, { \"type\": \"RichTextBlock\", \"inlines\": [ { \"type\": \"TextRun\", \"text\": " +
              " \"Date-Time parsing: {{DATE(2017-02-14T06:08:39Z,LONG)}} {{TIME(2017-02-14T06:08:39Z)}}\" } ] }, { \"type\": \"RichTextBlock\", \"horizontalAlignment\": \"center\", " +
			  " \"inlines\": [ { \"type\": \"TextRun\", \"text\": \"Rich text blocks also support center alignment.\" } ] }, { \"type\": \"RichTextBlock\", " +
              " \"horizontalAlignment\": \"right\", \"inlines\": [ { \"type\": \"TextRun\", \"text\": \"Rich text blocks also support right alignment\" } ] }, { " +
              " \"type\": \"RichTextBlock\", \"inlines\": [] } ] } ",
            // ActionSet Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"TextBlock\", " +
              " \"wrap\": true, \"text\": \"Cards can have action sets in the middle of their body.\" }, { \"type\": \"ActionSet\", \"actions\": [ { \"type\": \"Action.ShowCard\", " +
              " \"title\": \"ShowCard\", \"card\": { \"type\": \"AdaptiveCard\", \"body\": [ { \"type\": \"TextBlock\", \"text\": \"This is a show card\" } ] } }, { " +
              " \"type\": \"Action.OpenUrl\", \"title\": \"OpenUrl\", \"url\": \"https://adaptivecards.io\" } ] }, { \"type\": \"TextBlock\", \"wrap\": true, " +
              " \"text\": \"There are also still \\\"actions\\\" at the bottom of the card\" } ], \"actions\": [ { \"type\": \"Action.ShowCard\", \"title\": \"ShowCard\", " +
              " \"card\": { \"type\": \"AdaptiveCard\", \"body\": [ { \"type\": \"TextBlock\", \"text\": \"This is a show card\" } ] } }, { \"type\": \"Action.OpenUrl\", " +
              " \"title\": \"OpenUrl\", \"url\": \"https://adaptivecards.io\" } ] } ",
            // Container Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"Container\", " +
              " \"items\": [ { \"type\": \"TextBlock\", \"text\": \"This is some text\" }, { \"type\": \"Image\", \"url\": \"https://adaptivecards.io/content/cats/1.png\" } ] } ] } ",
            // ColumnSet Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"ColumnSet\", " +
              " \"columns\": [ { \"type\": \"Column\", \"items\": [ { \"type\": \"TextBlock\", \"text\": \"Column 1\" }, { \"type\": \"Image\", " +
              " \"url\": \"https://adaptivecards.io/content/cats/1.png\" } ] }, { \"type\": \"Column\", \"items\": [ { \"type\": \"TextBlock\", \"text\": \"Column 2\" }, " +
              " { \"type\": \"Image\", \"url\": \"https://adaptivecards.io/content/cats/1.png\" } ] } ] } ] } ",
            // FactSet Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"FactSet\", " +
              " \"facts\": [ { \"title\": \"Fact 1\", \"value\": \"Value 1\" }, { \"title\": \"Fact 2\", \"value\": \"Value 2\" } ] } ] } ",
            // ImageSet Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"ImageSet\", " +
              " \"images\": [ { \"type\": \"Image\", \"url\": \"https://adaptivecards.io/content/cats/1.png\" }, { \"type\": \"Image\", " +
              " \"url\": \"https://adaptivecards.io/content/cats/1.png\" } ] } ] } ",
            // Actions Card
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"id\": \"id1\", " +
              " \"type\": \"TextBlock\", \"text\": \"This card's action will open a URL\" } ], \"actions\": [ { \"type\": \"Action.OpenUrl\", \"title\": \"Action.OpenUrl\", " +
              " \"url\": \"https://adaptivecards.io\" }, { \"type\": \"Action.Submit\", \"title\": \"Action.Submit\", \"data\": { \"x\": 13 } }, { \"type\": \"Action.ShowCard\", " +
              " \"title\": \"Action.ShowCard\", \"card\": { \"type\": \"AdaptiveCard\", \"body\": [ { \"type\": \"TextBlock\", \"text\": \"What do you think?\" } ], \"actions\": [ " +
              " { \"type\": \"Action.Submit\", \"title\": \"Neat!\" } ] } }, { \"type\": \"Action.ToggleVisibility\", \"title\": \"Toggle!\", \"targetElements\": [ \"id1\" ] } ] } ",
            

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
                "\"actions\": [ { \"type\": \"Action.Submit\", \"title\": \"OK\", \"data\": { \"FoodChoice\": \"Vegetarian\" } } ] } } ] }",
            " { \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"TextBlock\"," +
                " \"text\": \"This is some text\", \"size\": \"large\" }, { \"type\": \"CustomElement\", \"someData\": \"A\" } ], \"actions\": [ { \"type\": \"Action.OpenUrl\"," +
                " \"title\": \"Action.OpenUrl\", \"url\": \"https://adaptivecards.io\" }, { \"type\": \"CustomAction\", \"someData\": \"data\", \"url\": \"https://adaptivecards.io\" " +
                " } ] } ",
            " { \"version\": \"1.2\", \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\", \"type\": \"AdaptiveCard\", \"body\": [ { \"type\": \"TextBlock\", \"text\": " +
                " \"Requires Test\", \"weight\": \"bolder\", \"size\": \"large\" }, { \"type\": \"ColumnSet\", \"columns\": [ { \"type\": \"Column\", \"items\": [ { \"type\": \"TextBlock\", " +
                " \"text\": \"✓: This textblock requires adaptiveCards 1.2\", \"color\": \"good\", \"wrap\": true, \"requires\": { \"adaptiveCards\": \"1.2\" } } ] }, { \"type\": \"Column\", " +
                " \"items\": [ { \"type\": \"TextBlock\", \"text\": \"✓: This textblock requires adaptiveCards 1.2 and acTest 1.0\", \"color\": \"good\", \"wrap\": true, \"requires\": { " +
                " \"adaptiveCards\": \"1.2\", \"acTest\": \"1.0\" } } ] }, { \"type\": \"Column\", \"items\": [ { \"type\": \"TextBlock\", \"text\": \"✗: This textblock requires acTest 2.0\", " +
                " \"color\": \"attention\", \"wrap\": true, \"requires\": { \"acTest\": \"2.0\" }, \"fallback\": { \"type\": \"TextBlock\", \"color\": \"good\", \"text\": " +
                " \"✓:We don't support acTest 2.0\", \"wrap\": true } } ] }, { \"type\": \"Column\", \"items\": [ { \"type\": \"TextBlock\", \"text\": " +
                " \"✓: This textblock requires any version of acTest\", \"color\": \"good\", \"wrap\": true, \"requires\": { \"acTest\": \"*\" } } ] }, { \"type\": \"Column\", \"items\": [ { " +
                " \"type\": \"TextBlock\", \"text\": \"✗: This textblock requires adaptiveCards 5.0\", \"color\": \"attention\", \"wrap\": true, \"requires\": { \"adaptiveCards\": \"5\" }, " +
                " \"fallback\": { \"type\": \"TextBlock\", \"color\": \"good\", \"text\": \"✓:We don't support adaptiveCards 5.0\", \"wrap\": true } } ] } ] } ] } "
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
