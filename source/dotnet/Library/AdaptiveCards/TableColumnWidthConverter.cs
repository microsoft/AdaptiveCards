using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    internal class TableColumnWidthConverter : JsonConverter<TableColumnWidth>, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public TableColumnWidthConverter() { }

        public TableColumnWidthConverter(List<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
        }

        public override TableColumnWidth Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            TableColumnWidth tableColumnWidth = new TableColumnWidth();

            if (reader.TokenType == JsonTokenType.String)
            {
                string pixelWidth = reader.GetString();
                if (pixelWidth.EndsWith("px"))
                {
                    try
                    {
                        tableColumnWidth.PixelWidth = Convert.ToDouble(pixelWidth.Substring(0, pixelWidth.Length - 2));
                    }
                    catch
                    {
                        WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                            $"The Value \"{pixelWidth}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    }
                }
                else
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{pixelWidth}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                }
            }
            else if (reader.TokenType == JsonTokenType.Number)
            {
                double relativeWidth = reader.GetDouble();
                if (relativeWidth < 0)
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{relativeWidth}\" was invalid, default value (0) will be used."));
                    relativeWidth = 0;
                }
                tableColumnWidth.RelativeWidth = relativeWidth;
            }
            else
            {
                reader.Skip();
            }

            return tableColumnWidth;
        }

        public override void Write(Utf8JsonWriter writer, TableColumnWidth value, JsonSerializerOptions options)
        {
            if (value.PixelWidth > 0)
            {
                writer.WriteStringValue(value.PixelWidth.ToString() + "px");
            }
            else
            {
                if (value.PixelWidth == (int)value.PixelWidth)
                    writer.WriteNumberValue((int)value.RelativeWidth);
                else
                    writer.WriteNumberValue(value.RelativeWidth);
            }
        }
    }
}
