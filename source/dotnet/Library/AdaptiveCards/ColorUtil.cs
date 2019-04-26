// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ColorUtil
    {
        // We need to have a string in the format #AARRGGBB or #RRGGBB
        public static bool IsValidColor(string color)
        {
            if (!string.IsNullOrEmpty(color) && (color.Length == 7 || color.Length == 9) && color[0] == '#')
            {
                // Verify that each character is a proper hex digit
                for (int i = 1; i < color.Length; i++)
                {
                    if (!color[i].IsHexDigit())
                    {
                        return false;
                    }
                }
                return true;
            }

            return false;
        }

        public static bool TryParseColor(string color, out int result)
        {
            result = 0;

            if(IsValidColor(color))
            {
                result = int.Parse(color.Substring(1), System.Globalization.NumberStyles.HexNumber);
                return true;
            }

            return false;
        }

        public static string GenerateLighterColor(string hexColor)
        {
            int color;
            if(TryParseColor(hexColor, out color))
            {
                const double colorIncrement = 0.25;
                int originalR = (color & 0xFF0000) >> 16;
                int originalG = (color & 0x00FF00) >> 8;
                int originalB = (color & 0x0000FF);

                int newColorR = originalR + (int)((255 - originalR) * colorIncrement);
                int newColorG = originalG + (int)((255 - originalG) * colorIncrement);
                int newColorB = originalB + (int)((255 - originalB) * colorIncrement);

                int newColor = ((newColorR << 16) | (newColorG << 8) | (newColorB));

                return "#" + newColor.ToString("X");
            }
            else
            {
                // Reset to black as original color was not valid
                return "#FF000000";
            }
        }

    }
}
