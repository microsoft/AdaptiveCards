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

                bool allowInlinePlayback = hostConfig.Media.AllowInlinePlayback;

                // Convert to JavaScript boolean values (False -> false, True -> true)
                string jsAllowInlinePlayback = allowInlinePlayback.ToString().ToLower();

                writer.WriteLine("</body>");
                writer.WriteLine($@"
    <script>
        // Sample JavaScript code to make media elements work
        const mediaPosterButtons = document.getElementsByClassName('ac-media-poster');
        const allowInlinePlayback = false;
        for (var i = 0; i < mediaPosterButtons.length; i++)
        {{
            const button = mediaPosterButtons[i];
            button.addEventListener('click', function() {{
                if ({jsAllowInlinePlayback}) {{
                    const mediaId = button.dataset.acMediaid;
                    const mediaPlayerContainer = document.getElementById(mediaId);

                    if (mediaPlayerContainer)
                    {{
                        // Hide the poster
                        button.style.display = 'none';

                        // Show the media player container
                        mediaPlayerContainer.style.display = '';

                        // Play the media
                        const mediaPlayer = document.getElementById(`${{mediaId}}-player`);
                        mediaPlayer.play();
                    }}
                }} else {{
                    const mediaSources = button.dataset.acMediaSources;
                    alert(mediaSources);
                }}
            }});
        }}
               
        // Sample JavaScript code to test inlienaction's keyboard event handler 
        const textinputWithInlineAction = document.getElementsByClassName('ac-textinput-inlineaction');
        for (var i = 0; i < textinputWithInlineAction.length; i++)
        {{
            const container = textinputWithInlineAction[i];
            const textinputId = container.dataset.acTextinputId;
            const textinput = document.getElementById(textinputId);
            textinput.addEventListener('keydown', function (e) {{
                if (e.keyCode == 13) {{
                    const inlineactionId = container.dataset.acInlineactionId;
                    const inlineaction = document.getElementById(inlineactionId);

                    if (inlineaction) {{
                        var actionAttribute = inlineaction.getAttribute('data-ac-url');
                        if (actionAttribute != null) {{
                            window.open(actionAttribute);
                        }}
                        else {{
                            actionAttribute = inlineaction.getAttribute('data-ac-submitData')
                            if (actionAttribute != null) {{
                                alert(textinput.value);
                            }}
                        }}
                    }}
                }} 
            }});
        }}
    </script>");
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
