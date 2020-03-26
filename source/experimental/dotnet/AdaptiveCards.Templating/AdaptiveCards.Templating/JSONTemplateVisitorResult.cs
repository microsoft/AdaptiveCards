using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.Text;
using System;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitorResult
    {
        public enum EvaluationResult
        {
            NotEvaluated = 0,
            EvaluatedToTrue,
            EvaluatedToFalse
        }
        class TemplatePartialResult
        {
            public StringBuilder StringResult { get; set; }
            public bool IsExpanded { get; set; }

            public List<LinkedList<TemplatePartialResult>> whens;
            public bool isWhen;
            public string predicate;
            public EvaluationResult whenEvaluationResult;

            public TemplatePartialResult(string a = "", bool b = true)
            {
                StringResult = new StringBuilder(a);
                IsExpanded = b;
                whens = new List<LinkedList<TemplatePartialResult>> ();
                whenEvaluationResult = EvaluationResult.NotEvaluated;
            }

            public TemplatePartialResult(string predicateString, string a = "", bool b = true) : this (a, b)
            {
                isWhen = true;
                predicate = predicateString;
            }

            public string Expand(JSONTemplateVisitor evaluator, JObject data)
            {
                if (isWhen)
                {
                    // object is "$when" type and its evaluation failes, so return
                    if (!evaluator.IsTrue(predicate, data))
                    {
                        whenEvaluationResult = EvaluationResult.EvaluatedToFalse;
                        return "";
                    }

                    whenEvaluationResult = EvaluationResult.EvaluatedToTrue;

                    StringBuilder output = new StringBuilder();
                    // expands results in When

                    bool allWhenIsExpanded = true;
                    foreach (var when in whens)
                    {
                        var headOfWhen = when.First.Value;
                        headOfWhen.IsExpanded = true;
                        bool areAllElementsExpanded = true;
                        if (evaluator.IsTrue(headOfWhen.predicate, data))
                        {
                            foreach (var elem in when)
                            {
                                output.Append(elem.Expand(evaluator, data));
                                areAllElementsExpanded &= elem.IsExpanded;
                            }
                        }

                        allWhenIsExpanded &= areAllElementsExpanded;

                        StringResult.Append(output);
                    }

                    IsExpanded = allWhenIsExpanded;
                }


                if (IsExpanded)
                {
                    return StringResult.ToString(); 
                }
                else
                {
                    return evaluator.Expand(StringResult.ToString(), data);
                }
            }
        }

        private readonly LinkedList<TemplatePartialResult> partialResultLinkedList = new LinkedList<TemplatePartialResult>();
        private bool isExpanded { get; set; }
        private List<JSONTemplateVisitorResult> whens;
        private bool isWhen;
        private string predicate;
        private bool isPair;
        private EvaluationResult whenEvaluationResult;

        public bool IsExpanded
        {
            get
            {
                if (isWhen)
                {
                    return !(whenEvaluationResult == EvaluationResult.NotEvaluated);
                }
                return partialResultLinkedList.Count == 0 || partialResultLinkedList.Count == 1;
            }
        }
        // lists parsed result from the current node which has $when 
        public List<JSONTemplateVisitorResult> Whens { get => whens; set => whens = value; }
        public bool IsWhen { get => isWhen; set => isWhen = value; }
        public string Predicate { get => predicate; set => predicate = value; }
        public bool IsPair { get => isPair; set => isPair = value; }
        public EvaluationResult WhenEvaluationResult { get => whenEvaluationResult; set => whenEvaluationResult = value; }

        public JSONTemplateVisitorResult()
        {
            partialResultLinkedList.AddLast(new TemplatePartialResult());
            Whens = new List<JSONTemplateVisitorResult>();

        }

        public JSONTemplateVisitorResult(string capturedString) : this()
        {
            Append(capturedString, true);
        }

        public JSONTemplateVisitorResult(string capturedString = "", bool isExpanded = true) : this()
        {
            Append(capturedString, isExpanded);
        }
        public JSONTemplateVisitorResult(string capturedString, string predicate) : this()
        {
            bool isExpanded = false;
            if (predicate.Length == 0)
            {
                isExpanded = true;
            }

            IsWhen = true;
            Predicate = predicate;
            WhenEvaluationResult = EvaluationResult.NotEvaluated; 
            Append(capturedString, isExpanded);
        }

        public JSONTemplateVisitorResult(JSONTemplateVisitorResult result) : this()
        {
            Append(result);
        }

        private LinkedListNode<TemplatePartialResult> GetHead()
        {
            return partialResultLinkedList.First;
        }

        private LinkedListNode<TemplatePartialResult> GetTail()
        {
            return partialResultLinkedList.Last;
        }

        private void RemoveHead()
        {
            partialResultLinkedList.RemoveFirst();
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
        public void TryRemoveCharAtEndFromStringBuilder(StringBuilder input)
        {
            if (input.Length <= 0)
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
                partialResultLinkedList.AddLast(new TemplatePartialResult(capturedString, isExpanded));
            }
        }

        public void Append(JSONTemplateVisitorResult result)
        {
            if (result == null)
            {
                return;
            }
            var tail = GetTail().Value;
            var headOfResult = result.GetHead().Value;

            if (result.isWhen && !result.IsPair)
            {
                tail.IsExpanded = false;
                tail.whens.Add(result.partialResultLinkedList);
                tail.isWhen = true;
                tail.predicate = result.predicate;
                return;
            }

            if (tail.IsExpanded && headOfResult.IsExpanded)
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

        public string Expand(JSONTemplateVisitor evaluator, JObject data)
        {
            if (IsWhen)
            {
                // object is "$when" type and its evaluation failes, so return
                if(!evaluator.IsTrue(predicate, data))
                {
                    return "";
                }
            }

            StringBuilder output = new StringBuilder() ;
            // expands results in When
            foreach (var when in Whens)
            {
                output.Append(when.Expand(evaluator, data));
            }

            foreach (var elem in partialResultLinkedList)
            {
                var partialResultString = elem.Expand(evaluator, data);
                if (elem.isWhen && elem.whenEvaluationResult == EvaluationResult.EvaluatedToFalse)
                {
                    TryRemoveCharAtEndFromStringBuilder(output);
                }
                output.Append(partialResultString);
            }
            return output.ToString();
        }
    }
}
