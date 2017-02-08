using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    public class TextInput : Input
    {
        public TextInput()
        {
            this.Size = Size.Stretch;
        }

        public int MaxLength { get; set; } = int.MaxValue;

        public bool IsMultiline { get; set; } = false;
    }
}
