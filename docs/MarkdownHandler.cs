using MarkedNet;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace AdaptiveCardDocs
{
    public class MarkdownHandler : IHttpHandler
    {
        public MarkdownHandler()
        {
        }


        public bool IsReusable => true;

        public void ProcessRequest(HttpContext context)
        {
            string path = context.Request.MapPath(context.Request.Path);
            Marked marked = new Marked();
            context.Response.ContentType = "text/html";
            var text = File.ReadAllText(path);
            var html = marked.Parse(text);
            context.Response.Write(html);
            context.Response.Flush();
        }
    }

}