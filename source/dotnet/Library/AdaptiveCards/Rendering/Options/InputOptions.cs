using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Options
{
    public class DateInputOptions : CardElementOptions
    {
        public DateInputOptions() { }
    }
    public class TimeInputOptions : CardElementOptions
    {
        public TimeInputOptions() { }
    }
    public class NumberInputOptions : CardElementOptions
    {
        public NumberInputOptions() { }
    }
    public class TextInputOptions : CardElementOptions
    {
        public TextInputOptions() { }
    }
    public class ChoiceSetOptions : CardElementOptions
    {
        public ChoiceSetOptions() { }
    }
    public class ToggleInputOptions : CardElementOptions
    {
        public ToggleInputOptions() { }
    }
}
