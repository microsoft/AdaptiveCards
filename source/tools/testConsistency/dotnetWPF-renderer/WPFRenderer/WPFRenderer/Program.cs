// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License.
using AdaptiveCards;
using AdaptiveCards.Rendering.Wpf;
using AdaptiveCards.Templating;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace WPFRenderer
{
    public class Program
    {
        public static void Main()
        {
            JObject resultJson = new JObject();
            List<string> errorList = new List<string>();
            List<string> warningList = new List<string>();
            resultJson.Add("imageData", "");
            resultJson.Add("warnings", "");
            resultJson.Add("errors", "");
            Console.OutputEncoding = Encoding.UTF8;
            try
            {
                StringBuilder inputSb = new StringBuilder();
                string currLine;

                //read a multi line input from stdin
                do
                {
                    currLine = Console.ReadLine();
                    inputSb = inputSb.Append(currLine);
                }
                while ((currLine != null) && (currLine != ""));

                JObject jsonInput = JObject.Parse(inputSb.ToString());
                string cardData = jsonInput.GetValue("data").ToString();
                string cardTemplate = jsonInput.GetValue("template").ToString();

                AdaptiveCardTemplate adaptiveCardTemplate = new AdaptiveCardTemplate(cardTemplate);
                string adaptiveCardJson = adaptiveCardTemplate.Expand(cardData);
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(adaptiveCardJson);
                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

                GetResultJsonString(parseResult, renderer, resultJson, warningList).GetAwaiter().GetResult();
            }

            catch (Newtonsoft.Json.JsonReaderException e)
            {
                errorList.Add("Exception: " + e.Message);
                errorList.Add("The input is not a valid json");
            }
            catch (AdaptiveTemplateException e)
            {
                errorList.Add("Exception: " + e.Message);
                errorList.Add("Unable to bind the data with the template. The supplied card data is not valid");
            }
            catch (AdaptiveSerializationException e)
            {
                errorList.Add("Exception: " + e.Message);
                errorList.Add("The supplied json input is not a valid Adaptive Card");

            }
            catch (ArgumentNullException e)
            {
                errorList.Add("Exception: " + e.Message);
                errorList.Add("Unable to capture the image of the card. Ensure that the card template and card data are valid and try again.");
            }
            catch (Exception e)
            {
                errorList.Add("Exception: " + e.Message);
                errorList.Add("An error was encountered: " + e.Message);
            }

            finally
            {
                resultJson["warnings"] = new JArray(warningList);
                resultJson["errors"] = new JArray(errorList);
                Console.WriteLine(resultJson.ToString());
            }
        }

        private static async Task GetResultJsonString(AdaptiveCardParseResult parseResult, AdaptiveCardRenderer renderer, JObject resultJson, List<string> warningList)
        {
            AdaptiveCard adaptiveCard = parseResult.Card;
            CancellationTokenSource cts = new CancellationTokenSource(TimeSpan.FromSeconds(30));
            RenderedAdaptiveCardImage adaptiveCardImage = await renderer.RenderCardToImageAsync(adaptiveCard, true, 400, cts.Token);

            foreach (var warning in parseResult.Warnings.Union(adaptiveCardImage.Warnings))
            {
                warningList.Add(warning.Message);
            }

            Stream cardImgStream = adaptiveCardImage.ImageStream;
            byte[] imageByteArray = new byte[cardImgStream.Length];
            int currIndex = 0;
            while (currIndex < cardImgStream.Length)
            {
                imageByteArray[currIndex] = Convert.ToByte(cardImgStream.ReadByte());
                currIndex++;
            }
            string base64EncodedCardImage = Convert.ToBase64String(imageByteArray);

            resultJson["imageData"] = base64EncodedCardImage;
        }
    }
}
