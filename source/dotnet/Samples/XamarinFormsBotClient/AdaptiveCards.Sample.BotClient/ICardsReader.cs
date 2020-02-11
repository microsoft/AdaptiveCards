using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Sample.BotClient
{
    public interface ICardsReader
    {
        string[] ReadAdaptiveCardsJsons(string[] fileNames);
    }
}
