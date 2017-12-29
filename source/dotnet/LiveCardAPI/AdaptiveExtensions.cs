using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public static class AdaptiveExtensions
    {
        /// <summary>
        /// Helper method to look up element by id
        /// </summary>
        /// <typeparam name="ElementT"></typeparam>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public static bool TryGetElementById<ElementT>(this AdaptiveCard card, string id, out ElementT element, out AdaptiveTypedElement parent) where ElementT : AdaptiveTypedElement
        {
            ElementFinder finder = new ElementFinder(id);
            finder.VisitCard(card);
            element = finder.Element as ElementT;
            parent = finder.Parent;
            return (element != null);
        }

        public static bool TryGetElementById<ElementT>(this AdaptiveCard card, string id, out ElementT element) where ElementT : AdaptiveTypedElement
        {
            if (id == card.Id)
                element = card as ElementT;
            else 
                element = card.GetAllElements().Where(el => el.Id == id).Cast<ElementT>().FirstOrDefault();
            return (element != null);
        }


        /// <summary>
        /// Replace element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="newElement"></param>
        /// <returns></returns>
        public static AdaptiveTypedElement ReplaceElement(this AdaptiveCard card, AdaptiveElement newElement)
        {
            lock (card)
            {
                if (card.TryGetElementById(newElement.Id, out AdaptiveElement oldElement, out AdaptiveTypedElement parent))
                {
                    if (parent is AdaptiveCard)
                    {
                        var parentCard = parent as AdaptiveCard;
                        var index = parentCard.Body.IndexOf(oldElement);
                        if (index >= 0)
                            parentCard.Body[index] = newElement;
                        return parentCard;
                    }
                    else if (parent is AdaptiveContainer)
                    {
                        var container = parent as AdaptiveContainer;
                        var index = container.Items.IndexOf(oldElement);
                        container.Items[index] = newElement;
                        return parent;
                    }
                    else if (parent is AdaptiveColumnSet)
                    {
                        var container = parent as AdaptiveColumnSet;
                        var index = container.Columns.IndexOf((AdaptiveColumn)oldElement);
                        container.Columns[index] = (AdaptiveColumn)newElement;
                        return parent;
                    }
                }
                throw new KeyNotFoundException(newElement.Id);
            }
        }

        /// <summary>
        /// Remove element
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public static AdaptiveTypedElement RemoveElementById(this AdaptiveCard card, string id)
        {
            lock (card)
            {
                if (card.TryGetElementById(id, out AdaptiveElement oldElement, out AdaptiveTypedElement parent))
                {
                    if (parent is AdaptiveCard)
                    {
                        AdaptiveCard parentCard = (AdaptiveCard)parent;
                        parentCard.Body.Remove(oldElement);
                        return parent;
                    }
                    else if (parent is AdaptiveContainer)
                    {
                        var container = parent as AdaptiveContainer;
                        container.Items.Remove(oldElement);
                        return parent;
                    }
                    else if (parent is AdaptiveColumnSet)
                    {
                        var container = parent as AdaptiveColumnSet;
                        container.Columns.Remove((AdaptiveColumn)oldElement);
                        return parent;
                    }
                }
                throw new KeyNotFoundException(id);
            }
        }
    }
}
