using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Html;
using System.Diagnostics;
using System.Text;

namespace AdaptiveCards.Sample.Html
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            Console.WriteLine(@"<!DOCTYPE html>");
            Console.WriteLine(@"<html>");
            Console.WriteLine(@"<head>");
            Console.WriteLine(@"<title>Adaptive Cards HTML Renderer Test Bed</title>");
            Console.WriteLine(@"<meta charset=""UTF-8"">");
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
            

            if (args.Length == 0)
            {
                args = new[] { "..\\..\\..\\..\\samples\\v1.0\\Scenarios" };
                Console.WriteLine($"<p>No path specified as first arg, trying '{args[0]}'</p>");
            }

            var noInteractivity = args.Contains("--no-interactivity");


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


            foreach (var file in files)
            {
                try
                {
                    Console.WriteLine("<hr/>");
                    Console.WriteLine($"<h2>{file}</h2>");

                    AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(File.ReadAllText(file, Encoding.UTF8));
                    if (parseResult.Card != null)
                    {
                        AdaptiveCard card = parseResult.Card;

                        AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(new AdaptiveHostConfig()
                        {
                            SupportsInteractivity = !noInteractivity
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
                    Debugger.Break();
                    Console.WriteLine($"{file} failed: {err.Message}<br/>");
                }
            }

            Console.WriteLine("</body>");
            Console.WriteLine("</html>");

#if DEBUG
            // Leave the console up while debugging
            if (Debugger.IsAttached)
            {
                Console.ReadLine();
            }
#endif
        }
    }
}
