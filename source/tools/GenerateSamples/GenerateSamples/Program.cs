using MarkedNet;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace GenerateSamples
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("GenerateSamples pathtosamples");
                return;
            }
            string preamble;
            using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("GenerateSamples.Preamble.txt"))
            using (StreamReader reader = new StreamReader(stream))
            {
                preamble = reader.ReadToEnd();
            }

            Marked marked = new Marked();

            string[] elements = new string[] {
                "TextBlock", "Image",
                "Container", "ColumnSet", "Column", "FactSet", "ImageSet",
                "Input.Text", "Input.Number", "Input.Date", "Input.Time", "Input.Toggle", "Input.ChoiceSet",
                "ActionOpenUrl", "ActionSubmit", "ActionHttp","ActionShowCard"
            };
            using (TextWriter writer = new StreamWriter(File.Open(Path.Combine(@"c:\\source\github\AdaptiveCards", "explorer.html"), FileMode.Create)))
            {
                writer.WriteLine(preamble);
                writer.WriteLine("<h1>AdaptiveCard Element Explorer</h1>");
                foreach (var element in elements)
                {
                    writer.WriteLine($"<h2 onclick='toggleContent(\"{element}Content\")'>{element}</h2>");
                    writer.WriteLine($"<div id='{element}Content' style='display:none'>");
                    string path = Path.Combine(args[0], $"..\\..\\docs\\schema\\{element}.md");
                    if (File.Exists(path))
                    {
                        string markdown = File.ReadAllText(path);
                        writer.WriteLine(marked.Parse(markdown));
                    }
                    foreach (var file in Directory.GetFiles(args[0], element + "*.json").Where(f => f.Contains(element + ".")))
                    {
                        var name = Path.GetFileNameWithoutExtension(file);
                        writer.WriteLine($"<h3 onclick='toggleContent(\"{name}Content\")'>{element}.{name.Split('.').Last()}</h3>");
                        writer.WriteLine($"<div id='{name}Content' style='display:block'>");
                        var json = File.ReadAllText(file, Encoding.UTF8);
                        writer.WriteLine($"<div id='{name}Card' class='card' ></div>");
                        writer.WriteLine($"<a target='_blank' href='/AdaptiveCards/?card=https://microsoft.github.io/AdaptiveCards/{file.Substring(file.IndexOf("samples")).Replace('\\', '/').Replace("/elements", "/Elements")}'>Try it</a>");
                        writer.WriteLine($"</div><script>renderCard('{name}Card', {json});</script>");
                    }
                    writer.WriteLine($"</div>");

                }
                writer.WriteLine("</body></html>");
                writer.Flush();
            }
        }
    }
}
