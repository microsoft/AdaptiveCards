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
            Console.WriteLine(@"<html><head>");
            Console.WriteLine(@"<style>");
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
                    HtmlRenderer renderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = false });
                    var result = renderer.RenderAdaptiveCard(card);
                    Console.WriteLine($"<div class='cardcontainer'>{result.ToPrettyString()}</div>");
                }
                catch (Exception err)
                {
                    Console.WriteLine($"{file} failed: {err.Message}<br/>");
                }
            }
        }
    }
}
