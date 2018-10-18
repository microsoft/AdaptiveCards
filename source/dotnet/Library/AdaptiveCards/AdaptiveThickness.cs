using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveThickness
    {
        public AdaptiveThickness()
        {

        }

        public AdaptiveThickness(AdaptiveSpacing spacing)
        {
            Left = spacing;
            Top = spacing;
            Right = spacing;
            Bottom = spacing;
        }

        public AdaptiveSpacing? Left { get; set; }
        public AdaptiveSpacing? Top { get; set; }
        public AdaptiveSpacing? Right { get; set; }
        public AdaptiveSpacing? Bottom { get; set; }

        public override string ToString()
        {
            return $"{Left}, {Top}, {Right}, {Bottom}";
        }

        /// <summary>
        /// Combines any of the assigned properties on the newer one with the properites of the current one
        /// </summary>
        /// <param name="newer"></param>
        /// <returns></returns>
        public AdaptiveThickness CombineWith(AdaptiveThickness newer)
        {
            return new AdaptiveThickness()
            {
                Left = newer?.Left ?? Left,
                Top = newer?.Top ?? Top,
                Right = newer?.Right ?? Right,
                Bottom = newer?.Bottom ?? Bottom
            };
        }
    }
}
