using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Options;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RenderImage
{
    class Program
    {
        static async Task RenderImage(AdaptiveCard card, string image)
        {
            var renderer = new ImageRenderer(new HostOptions(), String.Empty);
            var imageStream = await renderer.RenderAdaptiveCardAsync(card, 480);
            using (FileStream fileStream = new FileStream(image, FileMode.Create))
            {
                await imageStream.CopyToAsync(fileStream);
            }
        }

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Render2Image card image [-show]");
                return;
            }

            var card = JsonConvert.DeserializeObject<AdaptiveCard>(File.ReadAllText(args.First(arg => arg.EndsWith(".json"))));
            RenderImage(card, args.First(arg => arg.EndsWith(".png"))).Wait();
            if (args.Contains("-show"))
                Process.Start(args[1]);
        }
    }
}
