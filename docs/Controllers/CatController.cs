using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using MarkedNet;
using Microsoft.AspNetCore.Hosting;
using System.IO;
using System.Net.Http;
using System.Net;
using System.Net.Http.Headers;

namespace Docs.Controllers
{
    [Route("api/[controller]")]
    public class CatController : Controller
    {
        private IHostingEnvironment _env;

        public CatController(IHostingEnvironment env)
        {
            _env = env;
        }

        private static Random rnd = new Random();

        [HttpGet]
        [Route("")]
        [Route("{id}")]
        public FileContentResult Get(int? id = null)
        {
            var path = Path.Combine(_env.WebRootPath, "content");
            var cats = Directory.EnumerateFiles(path, "Cat*.png").ToList();
            if (id.HasValue)
                return new FileContentResult(System.IO.File.ReadAllBytes(cats[id.Value]), "image/png");
            return new FileContentResult(System.IO.File.ReadAllBytes(cats[rnd.Next(0, cats.Count)]), "image/png");
        }

    }
}
