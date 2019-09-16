// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using MarkedNet;
using Microsoft.AspNetCore.Hosting;
using System.IO;
using ColorCode;

namespace Docs.Controllers
{
    public class CodeMarkdown : Renderer
    {
        public override string Code(string code, string lang, bool escaped)
        {
            switch (lang.ToLower())
            {
                case "vb":
                case "vbdotnet":
                    return new CodeColorizer().Colorize(code, Languages.VbDotNet);
                case "haskell":
                    return new CodeColorizer().Colorize(code, Languages.Haskell);
                case "typescript":
                    return new CodeColorizer().Colorize(code, Languages.Typescript);
                case "powershell":
                    return new CodeColorizer().Colorize(code, Languages.PowerShell);
                case "markdown":
                    return new CodeColorizer().Colorize(code, Languages.Markdown);
                case "f#":
                case "fsharp":
                    return new CodeColorizer().Colorize(code, Languages.FSharp);
                case "cpp":
                    return new CodeColorizer().Colorize(code, Languages.Cpp);
                case "c#":
                case "csharp":
                    return new CodeColorizer().Colorize(code, Languages.CSharp);
                case "json":
                case "javascript":
                    return new CodeColorizer().Colorize(code, Languages.JavaScript);
                case "java":
                    return new CodeColorizer().Colorize(code, Languages.Java);

                case "xml":
                    return new CodeColorizer().Colorize(code, Languages.Xml);

                case "html":
                    return new CodeColorizer().Colorize(code, Languages.Html);
            }

            return base.Code(code, lang, escaped);
        }
    }


    [Route("api/[controller]")]
    public class MarkdownController : Controller
    {
        private IHostingEnvironment _env;

        public MarkdownController(IHostingEnvironment env)
        {
            _env = env;
        }

        // GET api/markdown/file
        [HttpGet("{*file}")]
        public string Get(string file)
        {
            var path = Path.Combine(_env.WebRootPath, file.Replace("/","\\"));

            Marked marked = new Marked();
            marked.Options.Renderer = new CodeMarkdown();

            var text = System.IO.File.ReadAllText(path);
            HttpContext.Response.ContentType = "text/html";
            return marked.Parse(text);
        }

    }
}
