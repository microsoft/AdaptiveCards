// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedAdaptiveCardRenderer
    {
        public static void UseXceedElementRenderers(this AdaptiveCardRenderer renderer)
        {
            renderer.ElementRenderers.Set<AdaptiveTextInput>(XceedTextInput.Render);
            renderer.ElementRenderers.Set<AdaptiveCards.AdaptiveNumberInput>(XceedNumberInput.Render);
            renderer.ElementRenderers.Set<AdaptiveDateInput>(XceedDateInput.Render);
            renderer.ElementRenderers.Set<AdaptiveTimeInput>(XceedTimeInput.Render);
        }
    }
}
