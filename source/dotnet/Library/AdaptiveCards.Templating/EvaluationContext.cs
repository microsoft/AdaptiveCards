// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards.Templating
{
    /// <summary>
    /// Provides Data Context to AdaptiveCardsTemplate Parser
    /// </summary>
    public sealed class EvaluationContext
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
        /// var context = new EvaluationContext()
        /// {
        ///     Root = jsonData
        /// };
        ///
        /// </code>
        /// </example>
        public object Root
        { get; set; }

        /// <summary>
        /// default consturctor
        /// </summary>
        public EvaluationContext()
        {
            Root = null;
        }

        /// <summary>
        /// constructor for <c>EvaluationContext</c> that takes one argument that will be used for root data context
        /// </summary>
        /// <param name="rootData"></param>
        public EvaluationContext(object rootData)
        {
            Root = rootData;
        }

    }
}
