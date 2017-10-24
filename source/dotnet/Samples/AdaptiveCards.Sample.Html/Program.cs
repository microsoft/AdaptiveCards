using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Html;

namespace AdaptiveCards.Sample.Html
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                args = new[] {"..\\..\\..\\..\\samples\\v1.0\\Scenarios"};
                Console.WriteLine($"No path specified as first arg, trying '{args[0]}'");
            }

            var files = new List<string>();

            try
            {
                if (File.Exists(args[0]))
                    files.Add(args[0]);
                else
                    files = Directory.GetFiles(args[0]).ToList();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return;
            }



            bool supportsInteractivity = false;

            const string supportsInteractivityFlag = "/supportsInteractivity";
            if (args.Contains(supportsInteractivityFlag))
            {
                supportsInteractivity = true;
                args = args.Except(new string[] { supportsInteractivityFlag }).ToArray();
            }

            Console.WriteLine(@"<!DOCTYPE html>");
            Console.WriteLine(@"<html><head>");
            Console.WriteLine(@"<title>Adaptive Cards HTML Renderer Test Bed</title>");
            Console.WriteLine(@"<style type='text/css'>");
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

            foreach (var file in files)
            {
                try
                {
                    Console.WriteLine("<hr/>");
                    Console.WriteLine($"<h2>{file}</h2>");

                    AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(File.ReadAllText(file));
                    if (parseResult.Card != null)
                    {
                        AdaptiveCard card = parseResult.Card;

                        AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(new AdaptiveHostConfig()
                        {
                            SupportsInteractivity = supportsInteractivity
                        });

                        Console.WriteLine($"<h3>Renderer schema version: {renderer.SupportedSchemaVersion}</h3>");

                        RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);

                        if (renderedCard.Html != null)
                        {
                            Console.WriteLine($"<div class='cardcontainer'>{renderedCard.Html}</div>");
                        }
                        else
                        {
                            Console.WriteLine($"<p>Rendering failed</p>");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"<p>Failed to parse card: {file}</p>");
                    }
                }
                catch (Exception err)
                {
                    Console.WriteLine($"{file} failed: {err.Message}<br/>");
                }
            }

            Console.WriteLine("</body>");
            Console.WriteLine("</html>");

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
