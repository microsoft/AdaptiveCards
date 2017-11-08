using System;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using Microsoft.AspNetCore.Mvc;

namespace ImageRendererServer.Controllers
{
    public class RenderController : Controller
    {

        public async Task<ActionResult> Index(string cardUrl = null)
        {
            cardUrl = cardUrl ??
                      "https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/samples/v1.0/Scenarios/ActivityUpdate.json";

            //if (context.Request.GetUri())
            //{
            //    hostConfig = AdaptiveHostConfig.FromJson(File.ReadAllText(hostConfigOption.Value()));
            //}

            try
            {
                var cts = new CancellationTokenSource(TimeSpan.FromSeconds(30));


                // Get the JSON from the card URL
                var client = new HttpClient();
                var res = await client.GetAsync(cardUrl, cts.Token);
                var json = await res.Content.ReadAsStringAsync();

                // Create a host config
                AdaptiveHostConfig hostConfig = new AdaptiveHostConfig()
                {
                    SupportsInteractivity = false
                };

                // Create a renderer
                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);

                // Parse the Adaptive Card JSON
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(json);
                AdaptiveCard card = parseResult.Card;

                // Render the card to bitmap
                RenderedAdaptiveCardImage renderedCard =
                    await renderer.RenderCardToImageAsync(card, cancellationToken: cts.Token);

                return File(renderedCard.ImageStream, "image/png");
            }
            catch (OperationCanceledException e)
            {
                // Timed out
                return StatusCode((int)HttpStatusCode.RequestTimeout);
            }
            catch (Exception ex)
            {
                // TODO: log
                throw;
            }      
        }
    }
}
