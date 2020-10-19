// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

namespace AdaptiveCards
{
    /// <summary>
    /// Contains information about a remote source.
    /// </summary>
    public struct RemoteResourceInformation
    {
        readonly string url;
        readonly string mimeType;

        /// <summary>
        /// Initializes a <see cref="RemoteResourceInformation"/> with the given properties.
        /// </summary>
        /// <param name="url">The URL of the remote resource.</param>
        /// <param name="mimeType">The mimetype of the remote resource.</param>
        public RemoteResourceInformation(string url, string mimeType)
        {
            this.url = url;
            this.mimeType = mimeType;
        }
    }
}
