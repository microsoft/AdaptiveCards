// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Linq;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility methods for dealing with body and binding
    /// </summary>
    public static class RendererUtilities
    {
        private static readonly Regex TextFunctionRegex =
            new Regex(@"\{\{(?<func>DATE|TIME){1}\((?<date>[\d]{4}-[\d]{2}-[\d]{2}T[\d]{2}:[\d]{2}:[\d]{2}[Z+-].*?){1}(?:,\s*(?<hint>SHORT|LONG|COMPACT){1}\s*)??\)\}\}",
                RegexOptions.ExplicitCapture);

        private static readonly Regex _regexBinding = new Regex(@"(?<property>\{\{\w+?\}\})+?",
            RegexOptions.ExplicitCapture);

        public static string HandleHtmlSpaces(string text)
        {
            return text.Replace("&amp;nbsp;", "&#x00A0;")
                .Replace("&amp;ensp;", "&#x2002;")
                .Replace("&amp;emsp;", "&#x2003;");
        }

        /// <summary>
        ///     This funct will return modified text replacing {{DATE|TIME()}} style functions as the formatted text
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static string ApplyTextFunctions(string text, string lang)
        {
            if (text != null)
            {
                foreach (Match match in TextFunctionRegex.Matches(text))
                {
                    Functions function;
                    if (Enum.TryParse(match.Groups[1].Value.ToUpper(), out function))
                    {
                        DateTime date;
                        if (DateTime.TryParse(match.Groups[2].Value, out date))
                        {
                            // Default interpretation: Compact
                            TimeHints timeHint = TimeHints.COMPACT;
                            string dateTimeFormat = "d";

                            if (function == Functions.DATE)
                            {
                                if (Enum.TryParse(match.Groups[3].Value, out timeHint))
                                {
                                    switch (timeHint)
                                    {
                                        case TimeHints.LONG:
                                            dateTimeFormat = "D";
                                            break;
                                        case TimeHints.SHORT:
                                            dateTimeFormat = "ddd, MMM d, yyyy";
                                            break;
                                        default:
                                            dateTimeFormat = "d";
                                            break;
                                    }
                                }
                            }
                            else if (function == Functions.TIME)
                            {
                                // TIME function has param. Ignore and move on.
                                if (!string.IsNullOrEmpty(match.Groups[3].Value))
                                {
                                    continue;
                                }
                                dateTimeFormat = "t";
                            }

                            var provider = GetValidCultureInfo(lang);
                            text = text.Replace(match.Value, date.ToString(dateTimeFormat, provider));
                        }
                    }
                }
            }
            return text ?? String.Empty;
        }

        // Get appropriate CultureInfo for lang
        private static CultureInfo GetValidCultureInfo(string val)
        {
            try
            {
                if (string.IsNullOrEmpty(val))
                {
                    return CultureInfo.CurrentCulture;
                }
                return new CultureInfo(val);
            }
            catch (CultureNotFoundException)
            {
                return CultureInfo.CurrentCulture;
            }
        }

        private enum Functions
        {
            DATE,
            TIME
        }

        private enum TimeHints
        {
            COMPACT,
            SHORT,
            LONG
        }

        public static string JoinString(List<string> choices, string sep, string last)
        {
            if (choices == null || choices.Count == 0)
                return "";

            var sb = new StringBuilder();
            var s = string.Empty;
            for (var i = 0; i < choices.Count - 1; i++)
            {
                sb.Append(s);
                sb.Append(choices[i]);
                s = sep;
            }
            if (choices.Count > 1)
                sb.Append(last);
            sb.Append(choices.Last());
            return sb.ToString();
        }

        public static T TryGetValue<T>(this IDictionary dictionary, string key)
        {
            if (dictionary != null && dictionary.Contains(key))
            {
                return (T)dictionary[key];
            }

            return default(T);
        }

        public static T TryGetValue<T>(this IDictionary<string, object> dictionary, string key)
        {
            if (dictionary != null && dictionary.ContainsKey(key))
            {
                return (T)dictionary[key];
            }

            return default(T);
        }
    }
}
