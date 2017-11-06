using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using McMaster.Extensions.CommandLineUtils;

namespace AdaptiveCards.Sample.ImageRender
{
    class Program
    {

        [STAThread]
        static int Main(string[] args)
        {

            var app = new CommandLineApplication();

            app.HelpOption("-h|--help");

            var pathArg = app.Argument("path", "The path that contains JSON card payloads");
            var optionRecurse = app.Option("-r|--recursive", "Recurse the directory for all JSON files",
                CommandOptionType.NoValue);
            var optionOutput = app.Option("-o|--out", "The directory to output the image(s) to",
                CommandOptionType.SingleValue);
            var optionSupportsInteracitivty = app.Option("-i|--supports-interactivity",
                "Include actions and inputs in the output", CommandOptionType.NoValue);
            var hostConfigOption =
                app.Option("--host-config", "Specify a host config file", CommandOptionType.SingleValue);

            var uri = new Uri("skype:play");
            app.OnExecute(async () =>
            {
                var outPath = optionOutput.HasValue()
                    ? optionOutput.Value()
                    : Environment.CurrentDirectory;

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

                AdaptiveHostConfig hostConfig = new AdaptiveHostConfig()
                {
                    SupportsInteractivity = optionSupportsInteracitivty.HasValue()
                };

                if (hostConfigOption.HasValue())
                {
                    hostConfig = AdaptiveHostConfig.FromJson(File.ReadAllText(hostConfigOption.Value()));
                }

                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);
                renderer.ResourceResolvers.Add("ms-appx", assetUri => Task.FromResult(new MemoryStream()));

                foreach (var file in files)
                {
                    Stopwatch watch = new Stopwatch();
                    watch.Start();
                 
                         AsyncPump.Run(async () =>
                         {

                             AdaptiveCardParseResult parseResult =
                                 AdaptiveCard.FromJson(File.ReadAllText(file, Encoding.UTF8));

                             AdaptiveCard card = parseResult.Card;

                             //var assets = await renderer.LoadAssetsForCardAsync(card);
                             RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);
                             var cts = new CancellationTokenSource();

                             //await renderedCard.WaitForAssetsAsync(cts.Token);
                             var imageStream = await renderedCard.ToImageAsync();

                             // Report any warnings
                             foreach (var warning in parseResult.Warnings.Union(renderedCard.Warnings))
                             {
                                 Console.WriteLine($"[{Path.GetFileName(file)}] WARNING: {warning.Message}");
                             }


                             // Write to a png file with the same name as the json file
                             var outputFile = Path.Combine(outPath,
                                  Path.ChangeExtension(Path.GetFileName(file), ".png"));

                             using (FileStream fileStream = new FileStream(outputFile, FileMode.Create))
                             {
                                 imageStream.CopyTo(fileStream);
                                 Console.WriteLine($"[{watch.ElapsedMilliseconds}ms] Rendered {Path.GetFullPath(outputFile)}");
                             }
                         });

                
                }

                Console.WriteLine($"All cards were written to {Path.GetFullPath(outPath)}");

            });


            int code = app.Execute(args);
            // if output, launch the file
            if (Debugger.IsAttached)
            {
                Console.ReadLine();
            }
            return code;

        }
    }
}
