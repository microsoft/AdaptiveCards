using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    public class TextBlock : CardElement
    {
        public TextBlock() 
        {

        }

        public TextSize TextSize { get; set; } = TextSize.Normal;

        public TextWeight TextWeight { get; set; } = TextWeight.Normal;

        public TextColor TextColor { get; set; } = TextColor.Default;

        public string Text { get; set; }

        public string Speak { get; set; }

        public bool IsSubtle { get; set; } = false;

        public bool Wrap { get; set; } = false;

    }
}
