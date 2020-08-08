using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ChartOptions
    {
        /// <summary>
        /// Control pie chart cutut percentage.  > 0 gives you a donut chart. max value 50.
        /// </summary>
        [JsonProperty("cutoutPercentage")]
        public float CutoutPercentage { get; set; } = 0F;
    }
}
