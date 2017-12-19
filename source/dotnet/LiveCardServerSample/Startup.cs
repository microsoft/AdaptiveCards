using Microsoft.Owin;
using Owin;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

[assembly: OwinStartup(typeof(LiveCardServerSample.Startup))]

namespace LiveCardServerSample
{
    public class Startup
    {
        public void Configuration(IAppBuilder app)
        {
        }
    }
}