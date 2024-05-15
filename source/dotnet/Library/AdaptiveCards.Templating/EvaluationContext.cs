// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Diagnostics.CodeAnalysis;

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
        {
            get;
            [RequiresDynamicCode("For AOT compatibility, use RootString instead")]
            [RequiresUnreferencedCode("For AOT compatibility, use RootString instead")]
            set;
        }

        /// <summary>
        /// AOT compatible version of Root property.
        /// </summary>
        public string RootString
        {
            get => (string)Root;
            [UnconditionalSuppressMessage("Trimming", "IL2026:Members annotated with 'RequiresUnreferencedCodeAttribute' require dynamic access otherwise can break functionality when trimming application code", Justification = "This path guarantees Root is a known type.")]
            [UnconditionalSuppressMessage("AOT", "IL3050:Calling members annotated with 'RequiresDynamicCodeAttribute' may break functionality when AOT compiling.", Justification = "This path guarantees Root is a known type.")]
            set => Root = value;
        }

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
        {
            get;
            [RequiresDynamicCode("For AOT compatibility, use HostString instead")]
            [RequiresUnreferencedCode("For AOT compatibility, use HostString instead")]
            set;
        }

        /// <summary>
        /// AOT compatible version of Host property.
        /// </summary>
        public string HostString
        {
            get => (string)Host;
            [UnconditionalSuppressMessage("Trimming", "IL2026:Members annotated with 'RequiresUnreferencedCodeAttribute' require dynamic access otherwise can break functionality when trimming application code", Justification = "This path guarantees Host is a known type")]
            [UnconditionalSuppressMessage("AOT", "IL3050:Calling members annotated with 'RequiresDynamicCodeAttribute' may break functionality when AOT compiling.", Justification = "This path guarantees Host is a known type")]
            set => Host = value;
        }

        /// <summary>
        /// default consturctor
        /// </summary>
        public EvaluationContext()
        {
        }

        /// <summary>
        /// constructor for <c>EvaluationContext</c> that takes one required argument used for root data context and one optional argument supplying host data
        /// </summary>
        /// <param name="rootData">Data to use while binding</param>
        /// <param name="hostData">Data supplied by the host for use while binding</param>
        [RequiresDynamicCode("For AOT compatibility, use the overload that takes a string and call JsonSerializer.Serialize on user-defined objects")]
        [RequiresUnreferencedCode("For AOT compatibility, use the overload that takes a string and call JsonSerializer.Serialize on user-defined objects")]
        public EvaluationContext(object rootData, object hostData = null)
        {
            Root = rootData;
            Host = hostData;
        }

        /// <summary>
        /// constructor for <c>EvaluationContext</c> that takes one required argument used for root data context and one optional argument supplying host data
        /// </summary>
        /// <param name="rootData">Data to use while binding</param>
        /// <param name="hostData">Data supplied by the host for use while binding</param>
        public EvaluationContext(string rootData, string hostData = null)
        {
            RootString = rootData;
            HostString = hostData;
        }
    }
}
