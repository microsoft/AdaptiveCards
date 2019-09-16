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
        public RedirectResult Get()
        {
            var path = Path.Combine(_env.WebRootPath, @"content\cats");
            var cats = Directory.EnumerateFiles(path, "Cat*.png").ToList();
            return new RedirectResult($"/api/cat/{rnd.Next(cats.Count)}");
        }

        [HttpGet]
        [Route("{id}")]
        public FileContentResult Get(int id)
        {
            var path = Path.Combine(_env.WebRootPath, @"content\cats");
            var cats = Directory.EnumerateFiles(path, "Cat*.png").ToList();
            return new FileContentResult(System.IO.File.ReadAllBytes(cats[id]), "image/png");
        }

    }
}
