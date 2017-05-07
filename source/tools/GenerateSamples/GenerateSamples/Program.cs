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
                "Input.Text", "Input.Number", "Input.Date", "Input.Time", "Input.Toggle", "Input.ChoiceSet",
                "Container", "ColumnSet", "Column", "FactSet", "ImageSet", "ActionSet",
                "Action.OpenUrl", "Action.Submit", "Action.Http","Action.ShowCard"
            };
            using (TextWriter writer = new StreamWriter(File.Open(@"..\..\..\..\..\..\docs\wwwroot\explorer\index.html", FileMode.Create)))
            {
                writer.WriteLine(preamble);
                // side bar
                writer.WriteLine("<div class=\"w3-sidebar w3-light-grey w3-card-2 w3-bar-block\">");
                int i = 0;
                foreach (var element in elements)
                {
                    string highlight = (i++ == 0) ? " w3-gray" : String.Empty;
                    var elementName = element.Replace(".", string.Empty);
                    writer.WriteLine($"<a href=\"#{elementName}\" id='{elementName}Link' class=\"elementLink w3-bar-item w3-button{highlight}\">{element}</a>");
                }
                writer.WriteLine("</div>");

                writer.WriteLine("<div class=\"w3-container content-sidebar\">");
                i = 0;
                foreach (var element in elements)
                {
                    string display = (i++ == 0) ? "inline-block" : "none";
                    writer.WriteLine($"<div class='element' id='{element.Replace(".",String.Empty)}Content' style='display:{display}'>");
                    writer.WriteLine($"<h1>{element}</h1>");
                    string path = $@"..\..\..\..\..\..\pages\schema\{element}.md";
                    if (File.Exists(path))
                    {
                        string markdown = File.ReadAllText(path);
                        writer.WriteLine(marked.Parse(markdown));
                    }

                    foreach (var file in Directory.GetFiles(args[0], element + "*.json").Where(f => f.Contains(element + ".")))
                    {
                        var name = Path.GetFileNameWithoutExtension(file);
                        writer.WriteLine($"<h2 onclick='toggleContent(\"{name}Content\")'>{name}</h2>");
                        writer.WriteLine($"<div id='{name}Content' style='display:block'>");
                        var json = File.ReadAllText(file, Encoding.UTF8);
                        writer.WriteLine($"<div id='{name}Card' class='card' ></div>");
                        writer.WriteLine($"<a class='trymelink' target='_blank' href='/AdaptiveCards/?card=https://microsoft.github.io/AdaptiveCards/{file.Substring(file.IndexOf("samples")).Replace('\\', '/').Replace("/elements", "/Elements")}'>Try it Yourself »</a>");
                        writer.WriteLine($"</div><script>renderCard('{name}Card', {json});</script>");
                    }
                    writer.WriteLine($"</div>");

                }
                writer.WriteLine("</div>");
                writer.WriteLine("</body></html>");
                writer.Flush();
            }
        }
    }
}
