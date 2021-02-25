// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

namespace AdaptiveCards
{
    /// <summary>
    /// A collection of utilities for processing colors.
    /// </summary>
    public class ColorUtil
    {
        /// <summary>
        /// The length of a string in the "#AARRGGBB" format.
        /// </summary>
        public static readonly int alphaColorLength = "#AARRGGBB".Length;

        /// <summary>
        /// The length of a string in the "#RRGGBB" format.
        /// </summary>
        public static readonly int colorStringLength = "#RRGGBB".Length;

        /// <summary>
        /// Determines if a string is a valid string of the format #AARRGGBB or #RRGGBB.
        /// </summary>
        /// <param name="color">The string to test for color format.</param>
        /// <returns>true iff the string is of the format #AARRGGBB or #RRGGBB.</returns>
        public static bool IsValidColor(string color)
        {
            if (!string.IsNullOrEmpty(color) && (color.Length == colorStringLength || color.Length == alphaColorLength)
                && color[0] == '#')
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

        /// <summary>
        /// Attempts to parse the supplied string as an integer if it is a valid color format.
        /// </summary>
        /// <param name="color">The string to convert to an int.</param>
        /// <param name="result">The result of converting the string.</param>
        /// <returns>true iff the string was successfully converted.</returns>
        public static bool TryParseColor(string color, out int result)
        {
            result = 0;

            if (IsValidColor(color))
            {
                result = int.Parse(color.Substring(1), System.Globalization.NumberStyles.HexNumber);
                return true;
            }

            return false;
        }

        /// <summary>
        /// Create a color that's 25% lighter than the given color.
        /// </summary>
        /// <param name="hexColor">A string in the format of #AARRGGBB or #RRGGBB to lighten.</param>
        /// <returns>A 25% brighter version of the supplied color, or "#FF000000" if hexColor is an invalid format.</returns>
        public static string GenerateLighterColor(string hexColor)
        {
            int color;
            if (TryParseColor(hexColor, out color))
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
