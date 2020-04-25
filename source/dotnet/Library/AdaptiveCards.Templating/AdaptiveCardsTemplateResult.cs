// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// Used by AdaptiveCardsTemplateVisitorClass to return result from its visitor methods
    /// </summary>
    public sealed class AdaptiveCardsTemplateResult
    {
        /// <summary>
        /// Indicates evaluation result of $when expression
        /// </summary>
        public enum EvaluationResult
        {
            /// <summary>
            /// Expression has not been evaluated
            /// </summary>
            NotEvaluated = 0,
            /// <summary>
            /// Expression evaluated true
            /// </summary>
            EvaluatedToTrue,
            /// <summary>
            /// Expression evaluated false
            /// </summary>
            EvaluatedToFalse
        }

        private readonly StringBuilder stringResult;

        /// <summary>
        /// Indicates that parsing Context has been dropped
        /// </summary>
        public bool HasItBeenDropped { get; set; }
        /// <summary>
        /// Indicates that this instance captures the result of $when
        /// </summary>
        public bool IsWhen { get; }
        /// <summary>
        /// Predicate of $when expression
        /// </summary>
        public string Predicate { get; }
        /// <summary>
        /// Indicates the result of evaluation result of $when expression
        /// </summary>
        public EvaluationResult WhenEvaluationResult { get; set; }

        /// <summary>
        /// constructor for <c>AdaptiveCardsTemplateResult</c> class
        /// </summary>
        public AdaptiveCardsTemplateResult()
        {
            stringResult = new StringBuilder("");
            HasItBeenDropped = false;
            IsWhen = false;
            Predicate = "";
            WhenEvaluationResult = EvaluationResult.NotEvaluated;
        }

        /// <summary>
        /// constructs a result instance with <paramref name="capturedString"/>
        /// </summary>
        /// <param name="capturedString"></param>
        public AdaptiveCardsTemplateResult(string capturedString) : this()
        {
            stringResult.Append(capturedString);
        }

        /// <summary>
        /// construct a result instance for $when expression
        /// </summary>
        /// <param name="capturedString">result string after parsing $when expression</param>
        /// <param name="predicate">predicate of $when</param>
        public AdaptiveCardsTemplateResult(string capturedString, string predicate) : this()
        {
            Predicate = predicate;
            IsWhen = true;
            stringResult.Append(capturedString);
        }

        /// <summary>
        /// Appends <paramref name="capturedString"/> to its result
        /// </summary>
        /// <param name="capturedString"></param>
        public void Append(string capturedString = "")
        {
            stringResult.Append(capturedString);
        }

        /// <summary>
        /// Appends another <paramref name="result"/> instance to its result
        /// </summary>
        /// <param name="result"></param>
        public void Append(AdaptiveCardsTemplateResult result)
        {
            if (result != null && result != this && !result.IsWhen)
            {
                stringResult.Append(result.stringResult);
            }
        }

        /// <summary>
        /// returns string representation
        /// </summary>
        /// <returns><c>string</c></returns>
        public override string ToString()
        {
            return stringResult.ToString();
        }
    }
}
