// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public struct RemoteResourceInformation
    {
        readonly string url;
        readonly string mimeType;

        public RemoteResourceInformation(string url, string mimeType)
        {
            this.url = url;
            this.mimeType = mimeType;
        }
    }
}
