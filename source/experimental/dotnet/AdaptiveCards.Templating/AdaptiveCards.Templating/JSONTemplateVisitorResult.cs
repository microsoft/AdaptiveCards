using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml.XPath;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitorResult
    {
        class TemplatePartialResult
        {
            public StringBuilder StringResult { get; set; }
            public bool IsExpanded { get; set; }

            public TemplatePartialResult(string a = "", bool b = true)
            {
                StringResult = new StringBuilder(a);
                IsExpanded = b;
            }
            public string Expand(JSONTemplateVisitor evaluator, JObject data)
            {
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

        class ConditionalTemplateParitalResult : TemplatePartialResult
        { 
            // need to think more about when 
            // keeping the other tokens such as "$when" : {} when data binding fails
            // need to keep $when's value 
            public string Predicate { get; set; }
            private JSONTemplateVisitorResult partialResult;

            public ConditionalTemplateParitalResult(JSONTemplateVisitorResult parentResult)
            {
                partialResult = parentResult;
            }
            public new string Expand(JSONTemplateVisitor evaluator, JObject data)
            {
                if (evaluator.IsTrue(Predicate.ToString(), data))
                {
                    return partialResult.Expand(evaluator, data);
                }
                return "";
            }

        }

        private readonly LinkedList<TemplatePartialResult> partialResultLinkedList = new LinkedList<TemplatePartialResult>();
        private bool isExpanded { get; set; }

        public bool IsExpanded
        {
            get { return partialResultLinkedList.Count <= 1 && partialResultLinkedList.Count >= 0;  }
        }


        public JSONTemplateVisitorResult()
        {
            partialResultLinkedList.AddLast(new TemplatePartialResult());
        }

        public JSONTemplateVisitorResult(string capturedString) : this()
        {
            Append(capturedString, true);
        }

        public JSONTemplateVisitorResult(string capturedString = "", bool isExpanded = true) : this()
        {
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
            var tail = GetTail().Value;
            var headOfResult = result.GetHead().Value;
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
            StringBuilder output = new StringBuilder() ;
            foreach (var elem in partialResultLinkedList)
            {
                output.Append(elem.Expand(evaluator, data));
            }
            return output.ToString();
        }
    }
}
