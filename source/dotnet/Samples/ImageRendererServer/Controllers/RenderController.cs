using System;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Internal.AntiSSRF;
using Newtonsoft.Json.Linq;

namespace ImageRendererServer.Controllers
{
    public class RenderController : Controller
    {
        private readonly IHostingEnvironment _env;
        private readonly string[] _allowedDomains = new string[]
        {
            "raw.githubusercontent.com",
            "github.com"
        };

        public RenderController(IHostingEnvironment env)
        {
            _env = env;
        }

        public async Task<ActionResult> Index(string cardUrl = null)
        {
            cardUrl = cardUrl ??
                      "https://raw.githubusercontent.com/Microsoft/AdaptiveCards/main/samples/v1.0/Scenarios/ActivityUpdate.json";

            try
            {
                // Validate the URL domain
                if (!URIValidate.InDomain(cardUrl, _allowedDomains))
                {
                    return BadRequest("URL domain not allowed");
                }

                var cts = new CancellationTokenSource(TimeSpan.FromSeconds(30));

                // Get the JSON from the card URL
                var client = new HttpClient();
                var response = await client.GetAsync(cardUrl, cts.Token);  // CodeQL [SM03781] InDomain is used to validate the URL domain, so this is safe. Adding suppression for CodeQL since known pattern not currently supported for SSRF query yet.
                var json = await response.Content.ReadAsStringAsync();

                // Make sure the payload has a version property
                var jObject = JObject.Parse(json);
                if (!jObject.TryGetValue("version", out var _))
                    jObject["version"] = "0.5";

                // Parse the Adaptive Card JSON
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(jObject.ToString());
                AdaptiveCard card = parseResult.Card;

                // Create a host config
                AdaptiveHostConfig hostConfig = new AdaptiveHostConfig()
                {
                    SupportsInteractivity = false
                };

                // TODO: Load custom host configs

                // Create a renderer
                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);

                // Set any XAML resource Dictionary if you have one
                renderer.ResourcesPath = System.IO.Path.Combine(_env.WebRootPath, "Styles", "MyStyles.xaml");

                // Render the card to bitmap
                RenderedAdaptiveCardImage renderedCard =
                    await renderer.RenderCardToImageAsync(card, createStaThread: true, cancellationToken: cts.Token);

                return File(renderedCard.ImageStream, "image/png");
            }
            catch (OperationCanceledException)
            {
                // Timed out
                return StatusCode((int)HttpStatusCode.RequestTimeout);
            }
            catch (Exception)
            {
                // TODO: log
                throw;
            }
        }
    }
}
