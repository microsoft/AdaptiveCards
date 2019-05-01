using CardHub.Interfaces;
using CardHub.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace CardHub.Controllers
{
    public class CardController : ApiController
    {
        /*
         * Flow is...
         *  - Host calls POST to create card
         *  - Host makes card ID available via QR code
         *  - Client scans QR code, gets card ID
         *  - Client calls Subscribe to subscribe to new card changes
         *  - Client then calls Get to get the initial card contents (called after Subscribe to ensure it doesn't miss an event)
         *  - Host card edited, host calls PUT to update card
         *  - That signals out to all subscribed clients with the new CardData
         */

        // GET: api/Card/5
        /// <summary>
        /// Clients call this to get the card data.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public CardData Get(string id)
        {
            if (StoredCards.Current.TryGet(id, out CardData cardData))
            {
                return cardData;
            }
            else
            {
                throw new KeyNotFoundException("Card ID not found. Maybe subscription has expired?");
            }
        }

        /// <summary>
        /// Clients call this to subscribe to changes. Uses server sent events. The event message contents will be the new CardData.
        /// </summary>
        /// <param name="cardId"></param>
        /// <returns></returns>
        [Route("api/card/{cardId}/subscribe")]
        [HttpGet]
        public HttpResponseMessage Subscribe(string cardId)
        {
            return StoredCards.Current.AddSubscriber(cardId, base.Request);
        }

        // POST: api/Card
        /// <summary>
        /// Hosts call this to initially create the card
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public CreateCardResponse Post([FromBody]CardData value)
        {
            var storedCard = StoredCards.Current.Create(value);
            return new CreateCardResponse()
            {
                CardId = storedCard.CardId,
                Token = storedCard.Token
            };
        }

        // PUT: api/Card/5
        /// <summary>
        /// Hosts call this to update an existing card
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        public void Put(string id, [FromBody]UpdateCardRequest value)
        {
            StoredCards.Current.Update(id, value.Token, value.CardData);
        }

        // DELETE: api/Card/5
        public void Delete(int id)
        {
            throw new NotImplementedException();
        }
    }
}
