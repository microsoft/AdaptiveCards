using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using MarkedNet;
using Microsoft.AspNetCore.Hosting;
using System.IO;

namespace Docs.Controllers
{
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
            var path = Path.Combine(_env.WebRootPath, file);

            Marked marked = new Marked();
            var text = System.IO.File.ReadAllText(path);
            HttpContext.Response.ContentType = "text/html";
            return marked.Parse(text);
        }

    }
}
