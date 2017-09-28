using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Render2Html
{
    class Program
    {
        static void Main(string[] args)
        {
            bool supportsInteractivity = false;

            const string supportsInteractivityFlag = "/supportsInteractivity";
            if (args.Contains(supportsInteractivityFlag))
            {
                supportsInteractivity = true;
                args = args.Except(new string[] { supportsInteractivityFlag }).ToArray();
            }

            Console.WriteLine(@"<html><head>");
            Console.WriteLine(@"<style>");
            Console.WriteLine(@".cardcontainer { ");
            Console.WriteLine(@"  width: 400px;");
            Console.WriteLine(@"  border-width: 1px;");
            Console.WriteLine(@"  border-color: #808080;");
            Console.WriteLine(@"  border-style: solid;");
            Console.WriteLine(@"  padding: 8px;");
            Console.WriteLine(@"}");
            Console.WriteLine(@"</style>");
            Console.WriteLine(@"</head>");
            Console.WriteLine(@"<body>");
            List<string> files = new List<string>();
            if (File.Exists(args[0]))
                files.Add(args[0]);
            else
                files = Directory.GetFiles(args[0]).ToList();

            foreach (var file in files)
            {
                try
                {
                    Console.WriteLine("<hr/>");
                    Console.WriteLine($"<h1>{file}</h1>");

                    AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(File.ReadAllText(file));
                    if (parseResult.Card != null)
                    {
                        AdaptiveCard card = parseResult.Card;

                        AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(new HostConfig()
                        {
                            SupportsInteractivity = supportsInteractivity
                        });

                        RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);

                        if (renderedCard.HtmlTag != null)
                        {
                            Console.WriteLine($"<div class='cardcontainer'>{renderedCard.HtmlTag.ToString()}</div>");
                        }
                        else
                        {
                            Console.WriteLine($"<p>{renderedCard.Errors.First()}</p>");
                        }
                    }
                }
                catch (Exception err)
                {
                    Console.WriteLine($"{file} failed: {err.Message}<br/>");
                }
            }

#if DEBUG
            // Leave the console up while debugging
            if (System.Diagnostics.Debugger.IsAttached)
            {
                Console.ReadLine();
            }
#endif
        }
    }
}
