using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Html;
using System.Diagnostics;
using System.Text;
using McMaster.Extensions.CommandLineUtils;

namespace AdaptiveCards.Sample.Html
{
    class Program
    {
        static int Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            var app = new CommandLineApplication();

            app.HelpOption("-h|--help");

            var pathArg = app.Argument("path", "The path that contains JSON card payloads");
            var optionRecurse = app.Option("-r|--recursive", "Recurse the directory for all JSON files", CommandOptionType.NoValue);
            var optionOutput = app.Option("-o|--out", "The file to output the HTML to", CommandOptionType.SingleValue);
            var optionSupportsInteracitivty = app.Option("-i|--supports-interactivity", "Include actions and inputs in the output", CommandOptionType.NoValue);

            app.OnExecute(() =>
            {
                FileStream outputFile = null;
                var writer = Console.Out;

                // Output to file instead of console
                if (optionOutput.HasValue())
                {
                    outputFile = File.OpenWrite(optionOutput.Value());
                    writer = new StreamWriter(outputFile);
                }

                // Get payload search path
                var payloadPath = pathArg.Value ?? "..\\..\\..\\..\\samples\\v1.0\\Scenarios";
                if (pathArg.Value == null)
                {
                    Console.WriteLine($"No path argument specified, trying {payloadPath}...");
                }

                var files = new List<string>();
    
                if (File.Exists(payloadPath))
                {
                    files.Add(payloadPath);
                }
                else if (Directory.Exists(payloadPath))
                {
                    var recurse = optionRecurse.HasValue()
                        ? SearchOption.AllDirectories
                        : SearchOption.TopDirectoryOnly;

                    files = Directory.GetFiles(payloadPath, "*.json", recurse).ToList();
                    Console.WriteLine($"Found {files.Count} card payloads...");
                }
                else
                {
                    Console.WriteLine($"{payloadPath} does not contain any JSON files");
                    return;
                }


                writer.WriteLine(@"<!DOCTYPE html>");
                writer.WriteLine(@"<html>");
                writer.WriteLine(@"<head>");
                writer.WriteLine(@"  <title>Adaptive Cards HTML Renderer Test Bed</title>");
                writer.WriteLine(@"  <meta charset=""UTF-8"">");
                writer.WriteLine(@"  <link rel='stylesheet' type='text/css' href='AdaptiveCards.css' />");
                writer.WriteLine(@"</head>");
                writer.WriteLine(@"<body>");

                AdaptiveHostConfig hostConfig = new AdaptiveHostConfig()
                {
                    SupportsInteractivity = optionSupportsInteracitivty.HasValue()
                };

                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);


                writer.WriteLine($"<h3>Renderer schema version: {renderer.SupportedSchemaVersion}</h3>");
                writer.WriteLine($"<h4>Supports Interactivty Enabled: {hostConfig.SupportsInteractivity}</h4>");

                foreach (var file in files)
                {
                    try
                    {
                        writer.WriteLine("<hr/>");
                        writer.WriteLine($"<h2>{Path.GetFileName(file)}</h2>");

                        AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(File.ReadAllText(file, Encoding.UTF8));

                        AdaptiveCard card = parseResult.Card;

                        RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);

                        // Report any warnings
                        foreach (var warning in parseResult.Warnings.Union(renderedCard.Warnings))
                        {
                            writer.WriteLine($"<p class='warning'>WARNING: {warning.Message}</div>");
                        }

                        writer.WriteLine($"<div class='cardcontainer'>{renderedCard.Html}</div>");
                    }
                    catch (Exception err)
                    {
                        Debugger.Break();
                        writer.WriteLine($"<p class='error'>ERROR: {Path.GetFileName(file)} failed: {err.Message}</p>");
                    }
                }

                writer.WriteLine("</body>");
                writer.WriteLine("</html>");

                if (outputFile != null)
                {
                    outputFile.Flush();
                    outputFile.Dispose();

                    Console.WriteLine($"All cards were written to {outputFile.Name}");
                }


                // if output, launch the file
                if (Debugger.IsAttached)
                {
                    Console.ReadLine();
                }
            });

            return app.Execute(args);
        }
    }
}
