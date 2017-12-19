using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class KeyEventArgs : EventArgs
    {
        /// <summary>
        /// Key that was pressed
        /// </summary>
        public string Key { get; set; }
    }

    public class TextChangedEventArgs : EventArgs
    {
        /// <summary>
        /// New text value
        /// </summary>
        public string Text { get; set; }
    }

    public class SelectionChangedEventArgs : EventArgs
    {
        /// <summary>
        /// indices of selected items
        /// </summary>
        public int[] Selection { get; set; }
    }

}
