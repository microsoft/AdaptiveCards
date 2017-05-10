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
            string header;
            using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("GenerateSamples.Header.txt"))
            using (StreamReader reader = new StreamReader(stream))
            {
                header = reader.ReadToEnd();
            }

            Marked marked = new Marked();

            GenerateSchemaExplorerPage(header, marked);
            GenerateSamplesPage(header);
        }

        private static void GenerateSchemaExplorerPage(string header, Marked marked)
        {
            string[] elements = new string[] {
                "TextBlock", "Image",
                "Input.Text", "Input.Number", "Input.Date", "Input.Time", "Input.Toggle", "Input.ChoiceSet",
                "Container", "ColumnSet", "Column", "FactSet", "ImageSet",/* "ActionSet",*/
                "Action.OpenUrl", "Action.Submit", "Action.Http","Action.ShowCard"
            };
            using (TextWriter writer = new StreamWriter(File.Open(@"..\..\..\..\..\..\docs\wwwroot\explorer\index.html", FileMode.Create)))
            {
                writer.WriteLine(header.Replace("$PAGE$", "explorer"));

                // side bar
                writer.WriteLine("<div class=\"w3-sidebar w3-light-grey w3-card-2 w3-bar-block\">");
                string firstLink = null;
                foreach (var element in elements)
                {
                    var id = element.Replace(".", string.Empty);
                    if (firstLink == null)
                        firstLink = id;
                    writer.WriteLine($"<a href=\"#{id}\" id='{id}Link' class=\"elementLink w3-bar-item w3-button\">{element}</a>");
                }
                WriteLoadFirstLink(writer, firstLink);
                writer.WriteLine("</div>");

                writer.WriteLine("<div class=\"w3-container content-sidebar maincontent\">");
                foreach (var element in elements)
                {
                    writer.WriteLine($"<div class='element' id='{element.Replace(".", String.Empty)}Content' style='display:none'>");
                    writer.WriteLine($"<h1>{element}</h1>");
                    string path = $@"..\..\..\..\..\..\docs\wwwroot\explorer\markdown\{element}.md";
                    if (File.Exists(path))
                    {
                        string markdown = File.ReadAllText(path);
                        writer.WriteLine(marked.Parse(markdown));
                    }

                    foreach (var file in Directory.GetFiles($@"..\..\..\..\..\..\docs\wwwroot\explorer\cards", element + "*.json").Where(f => f.Contains(element + ".")))
                    {
                        var name = Path.GetFileNameWithoutExtension(file);
                        writer.WriteLine($"<h2 onclick='toggleContent(\"{name}Content\")'>{name}</h2>");
                        writer.WriteLine($"<div id='{name}Content' style='display:block'>");
                        var json = File.ReadAllText(file, Encoding.UTF8);
                        writer.WriteLine($"<div id='{name}Card' class='card' ></div>");
                        writer.WriteLine($"<a class='trymelink' target='_blank' href='/visualizer?card=/explorer/cards/{Path.GetFileName(file)}'>Try it Yourself »</a>");
                        writer.WriteLine($"</div><script>renderCard('{name}Card', {json});</script>");
                    }
                    writer.WriteLine($"</div>");

                }
                writer.WriteLine("</div>");
                writer.WriteLine("</body></html>");
                writer.Flush();
            }
        }

        private static void WriteLoadFirstLink(TextWriter writer, string firstLink)
        {
            writer.WriteLine(@"
<script>
    $(document).ready(() => {
        if (window.location.hash == '')
            showElement('" + firstLink + @"');
        else
            showElement(window.location.hash.slice(1));
    });
</script>");
        }

        private static void GenerateSamplesPage(string header)
        {
            using (TextWriter writer = new StreamWriter(File.Open(@"..\..\..\..\..\..\docs\wwwroot\samples\index.html", FileMode.Create)))
            {
                writer.WriteLine(header.Replace("$PAGE$", "samples"));

                // side bar
                writer.WriteLine("<div class=\"w3-sidebar w3-light-grey w3-card-2 w3-bar-block\">");
                string firstLink = null;
                var files = Directory.EnumerateFiles(@"..\..\..\..\..\..\docs\wwwroot\samples\cards", "*.json").ToList();
                foreach (var file in files)
                {
                    var id = Path.GetFileNameWithoutExtension(file).Replace(" ", "");
                    if (firstLink == null)
                        firstLink = id;
                    writer.WriteLine($"<a href=\"#{id}\" id='{id}Link' class=\"elementLink w3-bar-item w3-button\">{Path.GetFileNameWithoutExtension(file)}</a>");
                }
                writer.WriteLine("</div>");
                WriteLoadFirstLink(writer, firstLink);

                writer.WriteLine("<div class=\"w3-container content-sidebar maincontent\">");
                foreach (var file in files)
                {
                    var id = Path.GetFileNameWithoutExtension(file).Replace(" ", "");
                    writer.WriteLine($"<div class='element' id='{id}Content' style='display:none'>");
                    var json = File.ReadAllText(file, Encoding.UTF8);
                    writer.WriteLine($"<div id='{id}Card' class='card' ></div>");
                    writer.WriteLine($"<a class='trymelink' target='_blank' href='/visualizer/?card=/samples/cards/{Path.GetFileName(file)}'>Try it Yourself »</a>");
                    writer.WriteLine($"<script>renderCard('{id}Card', {json});</script>");
                    writer.WriteLine($"</div>");

                }
                writer.WriteLine("</div>");
                writer.WriteLine("</body></html>");
                writer.Flush();
            }
        }
    }
}
