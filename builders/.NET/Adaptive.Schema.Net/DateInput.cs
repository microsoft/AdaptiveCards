using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// Input control for date
    /// </summary>
    public class DateInput : Input
    {
        public DateInput() 
        {
            this.Size = Size.Medium;
        }

        public bool IncludeTime { get; set; }
        
        // ISSUE: WE NEED MORE PARAMETERS HERE
    }
}
