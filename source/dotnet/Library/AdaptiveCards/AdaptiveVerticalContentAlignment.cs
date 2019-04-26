// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveVerticalContentAlignment>), true)]
    public enum AdaptiveVerticalContentAlignment
    {
        Top,
        Center,
        Bottom
    }
}
