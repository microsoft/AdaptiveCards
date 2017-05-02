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
            Console.WriteLine(@"<html><head><link rel='stylesheet' type='text/css' href='outlook.css'>");
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
                    var card = JsonConvert.DeserializeObject<AdaptiveCards.AdaptiveCard>(File.ReadAllText(file));
                    HtmlRenderer renderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = true });
                    var result = renderer.RenderAdaptiveCard(card);
                    Console.WriteLine(result.ToPrettyString());
                }
                catch (Exception err)
                {
                    Console.WriteLine($"{file} failed: {err.Message}<br/>");
                }
            }
        }
    }
}
