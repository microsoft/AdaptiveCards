using System;
using System.Collections.Generic;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerWarnings
    {
        private List<string> _warnings = new List<string>();
        public IEnumerable<string> GetWarnings()
        {
            return _warnings;
        }

        public void AddWarning(string warning)
        {
            _warnings.Add(warning);
        }
    }
}
