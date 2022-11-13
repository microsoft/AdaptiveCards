using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace AdaptiveCards
{
    internal class ColumnWidthConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();
        public ColumnWidthConverter()
        {
        }

        public override bool CanConvert(Type objectType)
        {
            return (objectType == typeof(string)) || (objectType == typeof(int));
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            TableColumnWidth tableColumnWidth = new TableColumnWidth();
            if (reader.ValueType == typeof(string))
            {
                string pixelWidth = (string)reader.Value;
                if (pixelWidth.EndsWith("px"))
                {
                    try
                    {
                        tableColumnWidth.PixelWidth = Convert.ToDouble(pixelWidth.Substring(0, pixelWidth.Length - 2));
                    }
                    catch
                    {
                        Warnings.Add(new AdaptiveWarning(-1,
                            $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    }
                }
                else
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                }
            }
            else
            {
                long relativeWidth = (long)reader.Value;
                if (relativeWidth < 0)
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was invalid, default value (0) will be used."));
                    relativeWidth = 0;
                }
                tableColumnWidth.RelativeWidth = relativeWidth; 
            }

            return tableColumnWidth;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            var tableColumnWidth = value as TableColumnWidth;
            if (tableColumnWidth.PixelWidth > 0)
            {
                writer.WriteValue(tableColumnWidth.PixelWidth.ToString() + "px");
            }
            else
            {
                writer.WriteValue(tableColumnWidth.RelativeWidth);
            }
        }
    }
}
