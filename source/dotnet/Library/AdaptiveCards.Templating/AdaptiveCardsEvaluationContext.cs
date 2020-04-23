namespace AdaptiveCards.Templating
{
    /// <summary>
    /// Provides Data Context to AdaptiveCardsTemplate Parser
    /// </summary>
    public sealed class AdaptiveCardsEvaluationContext
    {
        /// <summary>
        /// Provides Root Data Context 
        /// </summary>
        /// <example>
        /// <code>
        /// 
        /// string jsonData = @"{
        ///     ""person"": {
        ///         ""firstName"": ""Hello"",
        ///         ""lastName"": ""World""
        /// }";
        ///
        /// var context = new AdaptiveCardsEvaluationContext()
        /// {
        ///     Root = jsonData
        /// };
        ///
        /// </code>
        /// </example>
        public object Root
        { get; set; }

    }
}
