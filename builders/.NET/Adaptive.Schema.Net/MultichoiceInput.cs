using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    public class MultichoiceInput : Input
    {
        public MultichoiceInput()
        {
        }

        [JsonRequired]
        public List<Choice> Choices { get; set; } = new List<Choice>();
    }
}
