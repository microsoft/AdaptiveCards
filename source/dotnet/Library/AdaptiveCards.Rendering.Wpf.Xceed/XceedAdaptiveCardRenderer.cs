namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedAdaptiveCardRenderer
    {
        public static void UseXceedElementRenderers(this AdaptiveCardRenderer renderer)
        {
            renderer.ElementRenderers.Set<TextInput>(XceedTextInput.Render);
            renderer.ElementRenderers.Set<NumberInput>(XceedNumberInput.Render);
            renderer.ElementRenderers.Set<DateInput>(XceedDateInput.Render);
            renderer.ElementRenderers.Set<TimeInput>(XceedTimeInput.Render);
        }
    }
}
