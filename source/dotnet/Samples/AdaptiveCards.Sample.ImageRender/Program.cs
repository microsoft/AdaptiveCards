using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using McMaster.Extensions.CommandLineUtils;

namespace AdaptiveCards.Sample.ImageRender
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {

            var app = new CommandLineApplication();

            app.HelpOption("-h|--help");

            var pathArg = app.Argument("path", "The path that contains JSON card payloads");
            var optionRecurse = app.Option("-r|--recursive", "Recurse the directory for all JSON files", CommandOptionType.NoValue);
            var optionOutput = app.Option("-o|--out", "The directory to output the image(s) to", CommandOptionType.SingleValue);
            var optionSupportsInteracitivty = app.Option("-i|--supports-interactivity", "Include actions and inputs in the output", CommandOptionType.NoValue);
            var hostConfigOption = app.Option("--host-config", "Specify a host config file", CommandOptionType.SingleValue);

            app.OnExecute(async () =>
            {
                var outPath = optionOutput.HasValue()
                    ? optionOutput.Value()
                    : Environment.CurrentDirectory;

                if (!Directory.Exists(outPath))
                    Directory.CreateDirectory(outPath);

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

                foreach (var file in files)
                {
                    await Task.Factory.StartNewSta(() =>
                    {
                        AsyncPump.Run(async () =>
                        {
                            await RenderCard(file, renderer, outPath);
                        });

                        return new object();
                    });
                }

                Console.WriteLine($"All cards were written to {Path.GetFullPath(outPath)}");
            });


            app.Execute(args);
            // TODO: this is required when running from PS. Main thread is dying early
            //Console.ReadLine();

            // if output, launch the file
            if (Debugger.IsAttached)
            {
                Console.ReadLine();
            }
        }

        private static async Task RenderCard(string file, AdaptiveCardRenderer renderer, string outPath)
        {
            try
            {
                var watch = new Stopwatch();
                watch.Start();

                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(File.ReadAllText(file, Encoding.UTF8));

                AdaptiveCard card = parseResult.Card;

                RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);

                // Timeout after 30 seconds
                var cts = new CancellationTokenSource(TimeSpan.FromSeconds(30));

                // Render the card to an image
                Stream imageStream = await renderedCard.ToImageAsync(400, cts.Token);

                // Report any warnings
                foreach (var warning in parseResult.Warnings.Union(renderedCard.Warnings))
                {
                    Console.WriteLine($"[{Path.GetFileName(file)}] WARNING: {warning.Message}");
                }

                // Write to a png file with the same name as the json file
                var outputFile = Path.Combine(outPath,
                    Path.ChangeExtension(Path.GetFileName(file), ".png"));

                using (var fileStream = new FileStream(outputFile, FileMode.Create))
                {
                    imageStream.CopyTo(fileStream);
                    Console.WriteLine($"[{watch.ElapsedMilliseconds}ms T{Thread.CurrentThread.ManagedThreadId}]\t\t{Path.GetFileName(file)} => {Path.GetFileName(outputFile)}");
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"[FAILED]\t{Path.GetFileName(file)} => {ex.Message}");
            }
        }
    }
}
