// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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

        function activateMedia(button) {{
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
        }}

        for (var i = 0; i < mediaPosterButtons.length; i++)
        {{
            const button = mediaPosterButtons[i];
            button.addEventListener('click', function() {{
                if ({jsAllowInlinePlayback}) {{
                    activateMedia(button);
                }} else {{
                    const mediaSources = button.dataset.acMediaSources;
                    alert(mediaSources);
                }}
            }});
            button.addEventListener('keydown', function(e) {{
                if (e.key == "" "") {{
                    if ({jsAllowInlinePlayback}) {{
                        activateMedia(button);
                    }} else {{
                        const mediaSources = button.dataset.acMediaSources;
                        alert(mediaSources);
                    }}
                }}
            }});
        }}

        // Sample JavaScript code to test showCard action
        const showCardActions = document.getElementsByClassName('ac-action-showCard');
        for (var i = 0; i < showCardActions.length; i++)
        {{
            const showCardAction = showCardActions[i];
            showCardAction.addEventListener('click', function() {{
                if (true) {{
                    const showCardId = showCardAction.dataset.acShowcardid;
                    const showCard = document.getElementById(showCardId);

                    if(showCard.style.display == 'none') {{
                        showCard.style.display = 'inline';
                    }}
                    else {{
                        showCard.style.display = 'none'
                    }}
                }} else {{
                    const showCardId = showCardAction.dataset.acShowCardId;
                    alert(showCardId);
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
                if (e.key == ""Enter"") {{
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

        // Sample JavaScript code to test toggleVisibility action
        const toggleVisibilityActions = document.getElementsByClassName('ac-action-toggleVisibility');
        for (var i = 0; i < toggleVisibilityActions.length; i++) {{
            const toggleVisibilityAction = toggleVisibilityActions[i];

            toggleVisibilityAction.addEventListener('click', function() {{
                if ({jsAllowInlinePlayback}) {{
                    // Read list of targets with defined behaviour
                    // List will be in format id-targets='id1:True,id2:Toggle,id3:False'
                    const targetElementsString = toggleVisibilityAction.dataset.acTargetelements;
                    var targetElements = targetElementsString.split(',');

                    // For each target in list of targets
                    for(var j = 0; j < targetElements.length; j++) {{
                        /// Do a split for commas and for each element, find the : to divide both strings
                        const targetElementIdWithAction = targetElements[j].split(':');
                        const targetElementId = targetElementIdWithAction[0];
                        const targetElementAction = targetElementIdWithAction[1];

                        var targetElementsInDocument = document.getElementsByName(targetElementId);
                        // There is no singular version of getElementByName so just take the first element
                        var targetElement = targetElementsInDocument[0];
                        // The way to discern between checkbox elements and inline-actions is that inline-actions contain a textinput
                        var isCheckBoxElement = ((targetElementsInDocument.length > 1) && !(targetElement.className.includes('ac-textinput')));

                        const targetSeparatorId = targetElement.dataset.acSeparatorid;
                        const separator = document.getElementById(targetSeparatorId);

                        if(targetElementAction == 'True' || (targetElementAction == 'Toggle' && targetElement.style.display == 'none')) {{
                            if( isCheckBoxElement ) {{
                                targetElement.style.display = 'inline-block';
                            }}
                            else {{
                                targetElement.style.display = 'flex';
                            }}

                            if(targetElement.className.includes('ac-container')){{
                                targetElement.style.display = 'block';
                            }}

                            if(separator != null) {{
                                separator.style.display = 'block';
                            }}
                        }}
                        else if(targetElementAction == 'False' || (targetElementAction == 'Toggle' && targetElement.style.display != 'none')) {{
                            targetElement.style.display = 'none';

                            if(separator != null) {{
                                separator.style.display = 'none';
                            }}
                        }}

                        const parent = targetElement.parentNode;
                        var isFirstElement = true;
                        for(var k = 0; k < parent.childNodes.length; k++){{

                            var child = parent.childNodes[k];

                            <!-- if element is separator -> skip (As we don't care of this one) -->
                            if(child.className.includes('ac-separator') || child.className.includes('ac-columnseparator')){{
                                continue;
                            }}

                            <!-- if element is not visible -> skip (The separator was hidden in the previous step) -->
                            if(child.style.display == 'none'){{
                                continue;
                            }}

                            const childSeparatorId = child.dataset.acSeparatorid;
                            var childSeparator = document.getElementById(childSeparatorId);

                            if(isFirstElement){{
                                <!-- if element is visible -> hide separator -->
                                if(childSeparator != null){{
                                    childSeparator.style.display = 'none';
                                }}
                                isFirstElement = false;
                            }}
                            else{{
                                <!-- if element is visible -> show separator -->
                                if(childSeparator != null){{
                                    childSeparator.style.display = 'block';
                                }}
                            }}
                        }}

                    }}

                }} else {{
                    const targetElementsString = toggleVisibilityAction.dataset.acTargetelements;
                    alert(targetElementsString);
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
