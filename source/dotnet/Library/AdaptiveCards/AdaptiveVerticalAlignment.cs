// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;


namespace AdaptiveCards
{
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveVerticalAlignment
    {
        Top,
        Center,
        Bottom
    }
}
