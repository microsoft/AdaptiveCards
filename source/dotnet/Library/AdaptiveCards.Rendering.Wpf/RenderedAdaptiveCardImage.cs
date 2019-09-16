// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.IO;

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCardImage : RenderedAdaptiveCardBase
    {
        /// <summary>
        /// The rendered image stream as image/png
        /// </summary>
        public Stream ImageStream { get; }

        public RenderedAdaptiveCardImage(Stream stream, AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings) : base(originatingCard, warnings)
        {
            ImageStream = stream;
        }
    }
}
