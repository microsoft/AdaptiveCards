using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public interface ILiveCard
    {
        ILiveCardClientAPI Client { get; set; }

        /// <summary>
        /// Class which handles client events -> code behind
        /// </summary>
        ILiveCardServerAPI Server { get; set; }

        /// <summary>
        /// Card which is being worked on
        /// </summary>
        AdaptiveCard Card { get; set; }

        Task StartListening();
    }
}
