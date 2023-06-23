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
        ///     }
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
        /// Provides Host Data Context 
        /// </summary>
        /// <remarks>
        /// Typically this is supplied by the host application providing additional context for template binding. For example, the host might supply language or theming information that the template can use for layout.
        /// </remarks>
        /// <example>
        /// <code>
        /// 
        /// string jsonData = @"{
        ///     ""person"": {
        ///         ""firstName"": ""Hello"",
        ///         ""lastName"": ""World""
        ///     }
        /// }";
        ///
        /// string hostData = @"{
        ///     ""applicationName"": ""Contoso AdaptiveCards Host",
        ///     ""platform"": ""mobile""
        /// }";
        ///
        /// var context = new EvaluationContext()
        /// {
        ///     Root = jsonData,
        ///     Host = hostData
        /// };
        ///
        /// </code>
        /// </example>
        public object Host
        { get; set; }

        /// <summary>
        /// default consturctor
        /// </summary>
        public EvaluationContext()
        {
            Root = null;
            Host = null;
        }

        /// <summary>
        /// constructor for <c>EvaluationContext</c> that takes one required argument used for root data context and one optional argument supplying host data
        /// </summary>
        /// <param name="rootData">Data to use while binding</param>
        /// <param name="hostData">Data supplied by the host for use while binding</param>
        public EvaluationContext(object rootData, object hostData = null)
        {
            Root = rootData;
            Host = hostData;
        }
    }
}
