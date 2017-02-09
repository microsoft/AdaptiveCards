using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    public class MultichoiceInput : Input
    {
        public MultichoiceInput()
        {
            this.Size = Size.Medium;
        }

        public List<Choice> Items { get; set; } = new List<Choice>();
    }
}
