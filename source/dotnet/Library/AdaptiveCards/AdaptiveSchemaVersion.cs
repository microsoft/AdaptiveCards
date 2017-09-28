using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveSchemaVersion
    {
        public int Major { get; private set; }
        public int Minor { get; private set; }

        public AdaptiveSchemaVersion(int major, int minor)
        {
            Major = major;
            Minor = minor;
        }

        public override string ToString()
        {
            return $"{Major}.{Minor}";
        }
    }
}
