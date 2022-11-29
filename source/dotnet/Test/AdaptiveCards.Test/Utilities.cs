// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace AdaptiveCards.Test
{
    public static class Utilities
    {
        public static string SamplesPath => Path.Combine(System.AppContext.BaseDirectory, "..", "..", "..", "..", "..", "..", "..", "samples");
        internal static AdaptiveTypedElement GetAdaptiveElementWithId(AdaptiveCard card, string Id)
        {
            Stack<AdaptiveTypedElement> stack = new Stack<AdaptiveTypedElement>();

            foreach (var element in card.Body)
            {
                stack.Push(element);
            }

            foreach (var action in card.Actions)
            {
                stack.Push(action);
            }

            while (stack?.Count > 0)
            {
                var element = stack.Pop();
                if (element.Id == Id)
                {
                    return element;
                }

                if (element is AdaptiveCollectionElement)
                {
                    foreach (var childElement in element as AdaptiveCollectionElement)
                    {
                        stack.Push(childElement);
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Injects a key value pair to an AdaptiveCard using AdditionalProperites of AdaptiveTypedElement. If no kv is provided, injection is skipped
        /// </summary>
        /// <param name="card"></param>
        /// <param name="id"></param>
        /// <param name="testProperty"></param>
        /// <returns></returns>
        internal static string SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(AdaptiveCard card, string id, SerializableDictionary<string, object> testProperty = null)
        {
            AdaptiveTypedElement element = GetAdaptiveElementWithId(card, id);

            if (element != null && testProperty != null)
            {
                if (element is AdaptiveCollectionElement)
                {
                    (element as AdaptiveCollectionElement).SelectAction.AdditionalProperties = testProperty;
                }
                else
                {
                    element.AdditionalProperties = testProperty;
                }
            }

            return card.ToJson();
        }

        internal static AdaptiveCard BuildASimpleTestCard()
        {
            AdaptiveCard card = new AdaptiveCard(new AdaptiveSchemaVersion("1.5"));

            AdaptiveTextBlock textBlock = new AdaptiveTextBlock
            {
                Id = "textBlock",
                Text = "Hello World",
            };

            card.Body.Add(textBlock);

            AdaptiveTextInput textInput = new AdaptiveTextInput
            {
                Id = "textInput"
            };

            card.Body.Add(textInput);

            AdaptiveContainer container = new AdaptiveContainer();
            AdaptiveTextBlock innerTextBlock = new AdaptiveTextBlock();
            innerTextBlock.Text = "Inner TextBlock";
            innerTextBlock.Id = "innerTextBlock";
            container.Items.Add(innerTextBlock);
            container.Id = "container";

            AdaptiveSubmitAction selectAction = new AdaptiveSubmitAction
            {
                Id = "selectAction",
                Title = "Action.Submit",
                DataJson = "{\"x\": 20}",
            };

            container.SelectAction = selectAction;

            card.Body.Add(container);


            AdaptiveChoiceSetInput choiceSetInput = new AdaptiveChoiceSetInput
            {
                Id = "choiceSetInput"
            };

            card.Body.Add(choiceSetInput);

            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Id = "submitAction",
                Title = "Action.Submit",
                DataJson = "{\"x\": 13}",
            };

            card.Actions.Add(submitAction);

            return card;
        }

        internal static string BuildExpectedCardJSON(String id, SerializableDictionary<string, object> testProperty = null)
        {
            return Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(BuildASimpleTestCard(), id, testProperty);
        }

        internal static string RemoveWhiteSpacesFromJSON(String json)
        {
            string[] tokens = json.Split();
            var buffer = new StringBuilder();
            for (var i = 0; i < tokens.Length; i++)
            {
                var token = tokens.GetValue(i) as string;
                buffer.Append(token.Trim());
            }
            return buffer.ToString();
        }

        internal static string GetJSONCardFromFile(String fileName, string version, string type)
        {
            try
            {
                return File.ReadAllText(Path.Combine(Utilities.SamplesPath, version, type, fileName), Encoding.UTF8);
            }
            catch
            {
                return ""; 
            }
        }
    }
}
