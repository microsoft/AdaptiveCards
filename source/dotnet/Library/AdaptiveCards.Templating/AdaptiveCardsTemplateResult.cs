using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.Text;
using System;

namespace AdaptiveCards.Templating
{
    public sealed class AdaptiveCardsTemplateResult
    {
        public enum EvaluationResult
        {
            NotEvaluated = 0,
            EvaluatedToTrue,
            EvaluatedToFalse
        }

        private sealed class AdaptiveCardsTemplatePartialResult
        {
            public StringBuilder StringResult { get; set; }
            public bool IsExpanded { get; set; }

            public List<LinkedList<AdaptiveCardsTemplatePartialResult>> whens;
            public bool isWhen;
            public bool isTemplatedString;
            public string predicate;
            public EvaluationResult whenEvaluationResult;

            public AdaptiveCardsTemplatePartialResult(string a = "", bool b = true, bool c = false)
            {
                StringResult = new StringBuilder(a);
                IsExpanded = b;
                isTemplatedString = c;
                whens = new List<LinkedList<AdaptiveCardsTemplatePartialResult>> ();
                whenEvaluationResult = EvaluationResult.NotEvaluated;
            }

            public AdaptiveCardsTemplatePartialResult(string predicateString, string a = "", bool b = false) : this (a, b, false)
            {
                isWhen = true;
                predicate = predicateString;
            }

            public string Expand(AdaptiveCardsTemplateVisitor evaluator, JObject data)
            {
                if (isWhen)
                {
                    // object is "$when" type and its evaluation failes, so return
                    if (!AdaptiveCardsTemplateVisitor.IsTrue(predicate, data))
                    {
                        whenEvaluationResult = EvaluationResult.EvaluatedToFalse;
                        return "";
                    }
                }

                whenEvaluationResult = EvaluationResult.EvaluatedToTrue;

                StringBuilder output = new StringBuilder();
                // expands results in When

                bool allWhenIsExpanded = true;

                foreach (var when in whens)
                {
                    var enumerator =  when.GetEnumerator();
                    enumerator.MoveNext();
                    var headOfWhen = enumerator.Current;
                    bool areAllElementsExpanded = true;
                    if (AdaptiveCardsTemplateVisitor.IsTrue(headOfWhen.predicate, data))
                    {
                        while(enumerator.MoveNext())
                        {
                            var elem = enumerator.Current;
                            output.Append(elem.Expand(evaluator, data));
                            areAllElementsExpanded &= elem.IsExpanded;
                        }
                    }

                    allWhenIsExpanded &= areAllElementsExpanded;
                }

                IsExpanded &= allWhenIsExpanded;
                StringBuilder expandedStringResult = new StringBuilder();

                if (IsExpanded)
                {
                    expandedStringResult.Append(StringResult).Append(output);
                }
                else
                {
                    expandedStringResult.Append(AdaptiveCardsTemplateVisitor.Expand(StringResult.ToString(), data, isTemplatedString)).Append(output);
                }

                return expandedStringResult.ToString(); 
            }
        }

        private readonly LinkedList<AdaptiveCardsTemplatePartialResult> partialResultLinkedList = new LinkedList<AdaptiveCardsTemplatePartialResult>();
        private bool isPair;


        public bool ShouldTryRemoveComman { get; set; }
        public bool IsExpanded
        {
            get
            {
                if (IsWhen)
                {
                    return !(WhenEvaluationResult == EvaluationResult.NotEvaluated);
                }
                return partialResultLinkedList.Count == 0 || partialResultLinkedList.Count == 1;
            }
        }
        // lists parsed result from the current node which has $when 
        public bool IsWhen { get => partialResultLinkedList.Count == 0 ? false : partialResultLinkedList.First.Value.isWhen; }
        public string Predicate { get => IsWhen && partialResultLinkedList.Count != 0 ? partialResultLinkedList.First.Value.predicate : ""; }
        public bool IsPair { get => isPair; set => isPair = value; }
        public EvaluationResult WhenEvaluationResult
        {
            get => IsWhen && partialResultLinkedList.Count != 0 ? partialResultLinkedList.First.Value.whenEvaluationResult : EvaluationResult.NotEvaluated;
            set
            {
                if (IsWhen && partialResultLinkedList.Count != 0)
                {
                    partialResultLinkedList.First.Value.whenEvaluationResult = value;
                }
            }
        }

        public AdaptiveCardsTemplateResult()
        {
            ShouldTryRemoveComman = false;
            partialResultLinkedList.AddLast(new AdaptiveCardsTemplatePartialResult());
        }

        public AdaptiveCardsTemplateResult(string capturedString = "", bool isExpanded = false, bool isTemplatedString = false)
        {
            ShouldTryRemoveComman = false;
            partialResultLinkedList.AddLast(new AdaptiveCardsTemplatePartialResult(capturedString, isExpanded, isTemplatedString));
        }

        public AdaptiveCardsTemplateResult(string capturedString) : this()
        {
            Append(capturedString, true);
        }

        public AdaptiveCardsTemplateResult(string capturedString = "", bool isExpanded = true) : this()
        {
            Append(capturedString, isExpanded);
        }
        public AdaptiveCardsTemplateResult(string capturedString, string predicate)
        {
            bool isExpanded = false;
            if (predicate == null || predicate.Length == 0)
            {
                isExpanded = true;
            }

            var partialResult = new AdaptiveCardsTemplatePartialResult(predicate, capturedString, isExpanded);
            partialResultLinkedList.AddLast(partialResult);
            ShouldTryRemoveComman = false;
        }

        public AdaptiveCardsTemplateResult(AdaptiveCardsTemplateResult result) : this()
        {
            Append(result);
        }

        private LinkedListNode<AdaptiveCardsTemplatePartialResult> GetHead()
        {
            return partialResultLinkedList.First;
        }

        private LinkedListNode<AdaptiveCardsTemplatePartialResult> GetTail()
        {
            return partialResultLinkedList.Last;
        }

        private void RemoveHead()
        {
            partialResultLinkedList.RemoveFirst();
        }

        public void RemoveWhen()
        {
            if (IsWhen && partialResultLinkedList.Count > 0)
            {
                RemoveHead();
            }
        }

        /// <summary>
        /// Remove a comma if the comma exists at the end
        /// returns true if the comma removed
        /// </summary>
        public bool TryRemoveACommaAtEnd()
        {
            return TryRemoveCharAtEnd(',');
        }
        public bool TryRemoveCharAtEnd(char ch)
        {
            var chars = partialResultLinkedList.Last.Value.StringResult;
            if (chars.Length > 0 && chars[chars.Length - 1] == ch)
            {
                _ = chars.Remove(chars.Length - 1, 1);
                return true;
            }
            return false;
        }
        public static void TryRemoveCommarAtTheEndFromStringBuilder(StringBuilder input)
        {
            if (input == null || input.Length <= 0)
            {
                return;
            }

            for (int i = input.Length - 1; i >= 0; i--)
            {
                if (Char.IsWhiteSpace(input[i]))
                {
                    input.Remove(i, 1);
                    continue;
                }

                if (input[i] == ',')
                {
                    input.Remove(i, 1);
                    break;
                }

                return;
            }
        }
        public void Append(string capturedString = "", bool isExpanded = true)
        {
            var tail = GetTail().Value; 
            if (tail.IsExpanded && isExpanded)
            {
                tail.StringResult.Append(capturedString);
            }
            else
            {
                partialResultLinkedList.AddLast(new AdaptiveCardsTemplatePartialResult(capturedString, isExpanded));
            }
        }

        public void Append(AdaptiveCardsTemplateResult result)
        {
            if (result == null)
            {
                return;
            }

            if (result.ShouldTryRemoveComman)
            {
                TryRemoveACommaAtEnd();
            }

            var tail = GetTail().Value;
            var headOfResult = result.GetHead().Value;

            if (result.IsWhen)
            {
                // if result is pair, result is captured as such "$when" : "${expression}"
                // we are adding this pair to the existing result which is an object since only objects
                // can have pairs in json
                // we then make entir object as when object, a conditional object with predicate defined in ${expression} of $when pair
                // depending on the evaluation result of predicate, we decide whether to keep the object or not
                // make the when the head of the partial results of result to ensure that the object correctly behaves
                if (result.IsPair)
                {
                    TryRemoveACommaAtEnd();
                    partialResultLinkedList.AddFirst(headOfResult);
                    return;
                }
                else
                {
                    // result is returned as object
                    // we put the result to when lists
                    tail.whens.Add(result.partialResultLinkedList);
                    return;
                }
            }


            if (tail.IsExpanded && headOfResult.IsExpanded && tail.whens.Count == 0 && headOfResult.whens.Count == 0)
            {
                tail.StringResult.Append(headOfResult.StringResult);
                result.RemoveHead();
            }

            foreach (var elem in result.partialResultLinkedList)
            {
                partialResultLinkedList.AddLast(elem);
            }
        }

        public override string ToString()
        {
            StringBuilder output = new StringBuilder() ;
            foreach (var elem in partialResultLinkedList)
            {
                if (elem.IsExpanded == false)
                {
                    output.Append('{');
                    output.Append(elem.StringResult);
                    output.Append('}');
                }
                else
                {
                    output.Append(elem.StringResult);
                }
            }
            return output.ToString();
        }

        public string Expand(AdaptiveCardsTemplateVisitor evaluator, JObject data)
        {
            if (evaluator == null)
            {
                throw new ArgumentNullException(nameof(evaluator));
            }

            var enumerator =  partialResultLinkedList.GetEnumerator();
            if (IsWhen)
            {
                // object is "$when" type and its evaluation failes, so return
                if(!AdaptiveCardsTemplateVisitor.IsTrue(Predicate, data))
                {
                    return "";
                }
                enumerator.MoveNext();
            }

            StringBuilder output = new StringBuilder() ;

            while(enumerator.MoveNext())
            {
                var elem = enumerator.Current;
                char ch = '\0';
                if (output.Length != 0)
                {
                    ch = output[output.Length - 1];
                }

                var elemLength = elem.StringResult.Length;
                var wasElemEmptyBeforeExpansion = false;
                var hasCommandAtTheEnd = ch == ',';

                if (hasCommandAtTheEnd)
                {
                    wasElemEmptyBeforeExpansion = elemLength == 0 && elem.whens.Count == 0;
                }

                var partialResult = elem.Expand(evaluator, data);
                var isElemEmptyAfterExpansion = partialResult.Length == 0;

                if (!wasElemEmptyBeforeExpansion && isElemEmptyAfterExpansion && hasCommandAtTheEnd)
                {
                    // then remove commad at the end;
                    TryRemoveCommarAtTheEndFromStringBuilder(output);
                }
                output.Append(partialResult);
            }
            return output.ToString();
        }
    }
}
