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
            var hostConfigOption = app.Option("--host-config", "Specify a host config file", CommandOptionType.SingleValue);

            app.OnExecute(() =>
            {
                FileStream outputFile = null;
                var writer = Console.Out;

                // Output to file instead of console
                if (optionOutput.HasValue())
                {
                    outputFile = File.Open(optionOutput.Value(), FileMode.Create);
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
                    Console.WriteLine($"{payloadPath} does not contain any JSON files. Nothing to do.");
                    return;
                }

                writer.WriteLine(@"<!DOCTYPE html>
<html>
<head>
    <title>Adaptive Cards HTML Renderer Test Bed</title>
    <meta charset=""UTF-8"">
    <style type""text/css"">
                
        * {
            box-sizing: border-box;
            font-family: 'Segoe UI'
        }

        .cardcontainer {
            width: 400px;
            border-width: 1px;
            border-color: #808080;
            border-style: solid;
        }

        .error {
            border: solid 1px maroon;
            color: white;
            background: maroon;
            padding: 5px;
            width: 400px;
        }

        .warning {
            border: solid 1px orange;
            color: white;
            background: orange;
            padding: 5px;
            width: 400px;
        } 
    </style>
</head>
<body>");


                AdaptiveHostConfig hostConfig = new AdaptiveHostConfig()
                {
                    SupportsInteractivity = optionSupportsInteracitivty.HasValue()
                };

                if (hostConfigOption.HasValue())
                {
                    hostConfig = AdaptiveHostConfig.FromJson(File.ReadAllText(hostConfigOption.Value()));
                }

                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);


                writer.WriteLine($"<h3>Renderer schema version: {renderer.SupportedSchemaVersion}</h3>");
                writer.WriteLine($"<h4>Interactivty Enabled: {hostConfig.SupportsInteractivity}</h4>");
                writer.WriteLine($"<h4>Generated at: {DateTime.Now:G}</h4>");

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
                            writer.WriteLine($"<p class='warning'>WARNING: {warning.Message}</p>");
                        }

                        writer.WriteLine($"<div class='cardcontainer'>{renderedCard.Html}</div>");
                    }
                    catch (Exception err)
                    {
                        Debugger.Break();
                        writer.WriteLine($"<p class='error'>ERROR: {err.Message}</p>");
                    }
                }

                writer.WriteLine("</body>");
                writer.WriteLine("</html>");

                if (outputFile != null)
                {
                    writer.Flush();
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
