// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveExpressions.Memory;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Linq;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// Provides Data Context to AdaptiveCardsTemplate Parser
    /// </summary>
    public sealed class EvaluationContext : IMemory
    {
        private const char dollar = '$';

        private JToken root;
        private JToken data;

        /// <summary>
        /// default consturctor
        /// </summary>
        public EvaluationContext()
        {
            Root = new JObject();
        }

        /// <summary>
        /// constructor for <c>EvaluationContext</c> that takes one argument that will be used for root data context
        /// </summary>
        /// <param name="rootData"></param>
        public EvaluationContext(object rootData)
        {
            if (rootData != null)
            {
                Root = JToken.FromObject(rootData);
            }
            Data = Root;
        }

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
        public JToken Root
        {
            get { return root; }
            set { root = SmartAssign(value); }
        }

        /// <summary>
        /// Provides Data Context 
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
        ///     Data = jsonData
        /// };
        ///
        /// </code>
        /// </example>
        public JToken Data
        {
            get { return data; }
            set { data = SmartAssign(value); }
        }

        /// <summary>
        /// gets or sets current iteration index.
        /// </summary>
        public int Index { get; set; }

        internal EvaluationContext Clone(object data)
        {
            return new EvaluationContext()
            {
                Root = this.Root,
                Data = JToken.FromObject(data),
                NullSubstitution = this.NullSubstitution
            };
        }

        /// <summary>
        /// Null substitution
        /// </summary>
        internal Func<string, object> NullSubstitution { get; set; }

        /// <inheritdoc/>
        public void SetValue(string path, object value)
        {
            if (path != null && path.FirstOrDefault() == dollar)
            {
                ObjectPath.SetPathValue(this, path.TrimStart(dollar), JToken.FromObject(value));
            }
            ObjectPath.SetPathValue(this, $"data.{path}", JToken.FromObject(value));
        }

        /// <inheritdoc/>
        public bool TryGetValue(string path, out object value)
        {
            value = null;
            if (path != null)
            {
                if (path.StartsWith($"{dollar}", StringComparison.InvariantCultureIgnoreCase))
                {
                    return ObjectPath.TryGetPathValue(this, path.TrimStart('$'), out value);
                }

                if (ObjectPath.TryGetPathValue(this.Data, $"{path}", out value))
                {
                    return true;
                }

                if (ObjectPath.TryGetPathValue(this.Root, $"{path}", out value))
                {
                    return true;
                }
            }

            if (NullSubstitution != null)
            {
                value = NullSubstitution(path);
                return true;
            }

            value = $"${{{path}}}";
            return true;
        }

        /// <inheritdoc/>
        public string Version()
        {
            return String.Empty;
        }

        /// <summary>
        /// SmartAssign text values
        /// </summary>
        /// <remarks>If a value is a string this will attempt to deserialize as JSON, other wise it will call back to text</remarks>
        /// <param name="value">jtoken to evaluate.</param>
        /// <returns>jtoken.</returns>
        private static JToken SmartAssign(JToken value)
        {
            var token = JToken.FromObject(value);
            if (token.Type == JTokenType.String)
            {
                try
                {
                    var text = (string)token;
                    return (JToken)JsonConvert.DeserializeObject(text);
                }
                catch (Exception)
                {
                    // fall through
                }
            }
            return token;
        }
    }
}
