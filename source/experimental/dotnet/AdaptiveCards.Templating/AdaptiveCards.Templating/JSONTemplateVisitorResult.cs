using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;
using System.Xml.XPath;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitorResult
    {
        class TemplatePartialResult
        {
            public StringBuilder StringResult { get; set; }
            public bool IsExpanded { get; set; }
            public AdaptiveCardsTemplatingVisitorResult Keys { get; set; }

            public TemplatePartialResult(string a = "", bool b = true, AdaptiveCardsTemplatingVisitorResult c = null)
            {
                StringResult = new StringBuilder(a);
                IsExpanded = b;
                Keys = c;
            }
        }

        private readonly LinkedList<TemplatePartialResult> partialResultLinkedList = new LinkedList<TemplatePartialResult>();

        public JSONTemplateVisitorResult()
        {
            partialResultLinkedList.AddLast(new TemplatePartialResult());
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

        private int GetCount()
        {
            return partialResultLinkedList.Count;
        }

        public void Append(string capturedString = "", bool isExpanded = true, AdaptiveCardsTemplatingVisitorResult templateExpansionResult = null)
        {
            var tail = GetTail().Value; 
            if (tail.IsExpanded && isExpanded)
            {
                tail.StringResult.Append(capturedString);
            }
            else
            {
                partialResultLinkedList.AddLast(new TemplatePartialResult(capturedString, isExpanded, templateExpansionResult));
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
                    foreach (var word in elem.Keys.Keys)
                    {
                        output.Append(word);
                    }
                    output.Append('}');
                }
                else
                {
                    output.Append(elem.StringResult);
                }
            }
            return output.ToString();
        }
    }
}
