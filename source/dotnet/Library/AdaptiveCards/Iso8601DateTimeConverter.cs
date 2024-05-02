// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Globalization;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    /// Format datetime as Iso8601 instant format "yyyy-MM-ddTHH:mm:ssZ";
    /// </summary>
    public class Iso8601DateTimeConverter : IsoDateTimeConverter
    {
        public Iso8601DateTimeConverter() : base()
        {
            DateTimeFormat = "yyyy-MM-ddTHH:mm:ssZ"; 
        }
    }
}
