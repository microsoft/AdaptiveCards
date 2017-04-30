using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Config
{
    public class DateInputConfig : CardElementConfig
    {
        public DateInputConfig() { }
    }
    public class TimeInputConfig : CardElementConfig
    {
        public TimeInputConfig() { }
    }
    public class NumberInputConfig : CardElementConfig
    {
        public NumberInputConfig() { }
    }
    public class TextInputConfig : CardElementConfig
    {
        public TextInputConfig() { }
    }
    public class ChoiceSetConfig : CardElementConfig
    {
        public ChoiceSetConfig() { }
    }
    public class ToggleInputConfig : CardElementConfig
    {
        public ToggleInputConfig() { }
    }
}
