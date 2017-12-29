using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public enum InsertPosition
    {
        Before, After, FirstChild, LastChild
    }

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
            ElementFinder finder = new ElementFinder(id);
            finder.VisitCard(card);
            element = finder.Element as ElementT;
            return (element != null);
        }

        ///// <summary>
        ///// Insert new element
        ///// </summary>
        ///// <param name="id">id of element to insert before or after</param>
        ///// <param name="newElement"></param>
        ///// <returns></returns>
        //public static AdaptiveTypedElement InsertElement(this AdaptiveCard card, InsertPosition position, string id, AdaptiveElement newElement)
        //{
        //    lock (card)
        //    {

        //        setEventsVisitor.Visit(null, newElement);
        //        if (id == null)
        //        {
        //            switch (position)
        //            {
        //                case InsertPosition.FirstChild:
        //                    card.Body.Insert(0, newElement);
        //                    return card;
        //                case InsertPosition.LastChild:
        //                    card.Body.Add(newElement);
        //                    return card;
        //                default:
        //                    throw new ArgumentException($"Can't add before or after card");
        //            }
        //        }

        //        if (card.TryGetElementById(id, out AdaptiveElement targetElement, out AdaptiveTypedElement parent))
        //        {
        //            if (position == InsertPosition.Before || position == InsertPosition.After)
        //            {
        //                if (parent is AdaptiveCard)
        //                {
        //                    var container = parent as AdaptiveCard;
        //                    var index = container.Body.IndexOf(targetElement);
        //                    switch (position)
        //                    {
        //                        case InsertPosition.Before:
        //                            card.Body.Insert(index, newElement);
        //                            return card;
        //                        case InsertPosition.After:
        //                            card.Body.Insert(index + 1, newElement);
        //                            return card;
        //                    }
        //                }
        //                else if (parent is AdaptiveContainer)
        //                {
        //                    var container = parent as AdaptiveContainer;
        //                    var index = container.Items.IndexOf(targetElement);
        //                    switch (position)
        //                    {
        //                        case InsertPosition.Before:
        //                            container.Items.Insert(index, newElement);
        //                            return container;
        //                        case InsertPosition.After:
        //                            container.Items.Insert(index + 1, newElement);
        //                            return container;
        //                    }
        //                }
        //                else if (parent is AdaptiveColumnSet)
        //                {
        //                    var container = parent as AdaptiveColumnSet;
        //                    var index = container.Columns.IndexOf((AdaptiveColumn)targetElement);
        //                    switch (position)
        //                    {
        //                        case InsertPosition.Before:
        //                            container.Columns.Insert(index, (AdaptiveColumn)newElement);
        //                            return container;
        //                        case InsertPosition.After:
        //                            container.Columns.Insert(index + 1, (AdaptiveColumn)newElement);
        //                            return container;
        //                    }
        //                }
        //            }
        //            else if (position == InsertPosition.LastChild || position == InsertPosition.FirstChild)
        //            {
        //                if (targetElement is AdaptiveContainer)
        //                {
        //                    var container = parent as AdaptiveContainer;
        //                    switch (position)
        //                    {
        //                        case InsertPosition.FirstChild:
        //                            container.Items.Insert(0, newElement);
        //                            return container;
        //                        case InsertPosition.LastChild:
        //                            container.Items.Add(newElement);
        //                            return container;
        //                    }
        //                }
        //                else if (targetElement is AdaptiveColumnSet)
        //                {
        //                    var container = parent as AdaptiveColumnSet;
        //                    switch (position)
        //                    {
        //                        case InsertPosition.FirstChild:
        //                            container.Columns.Insert(0, (AdaptiveColumn)newElement);
        //                            return container;
        //                        case InsertPosition.LastChild:
        //                            container.Columns.Add((AdaptiveColumn)newElement);
        //                            return container;
        //                    }
        //                }
        //                throw new ArgumentException($"trying to add to non collection type: {targetElement.Type}");
        //            }
        //        }
        //        throw new ArgumentException($"{id} not found");
        //    }
        //}

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
