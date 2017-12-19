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
        private static SetEventsVisitor setEventsVisitor = new SetEventsVisitor();

        /// <summary>
        /// Helper method to look up element by id
        /// </summary>
        /// <typeparam name="ElementT"></typeparam>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public static bool TryGetElementById<ElementT>(this AdaptiveCard card, string id, out ElementT element, out object parent) where ElementT : AdaptiveTypedElement
        {
            ElementFinder finder = new ElementFinder(id);
            finder.Visit(card);
            element = finder.Element as ElementT;
            parent = finder.Parent;
            return (element != null);
        }

        public static bool TryGetElementById<ElementT>(this AdaptiveCard card, string id, out ElementT element) where ElementT : AdaptiveTypedElement
        {
            ElementFinder finder = new ElementFinder(id);
            finder.Visit(card);
            element = finder.Element as ElementT;
            return (element != null);
        }

        /// <summary>
        /// Insert new element
        /// </summary>
        /// <param name="id">id of element to insert before or after</param>
        /// <param name="newElement"></param>
        /// <returns></returns>
        public static Task InsertElement(this AdaptiveCard card, string id, InsertPosition position, AdaptiveElement newElement)
        {
            setEventsVisitor.Visit(null, newElement);
            if (id == null)
            {
                switch (position)
                {
                    case InsertPosition.FirstChild:
                        card.Body.Insert(0, newElement);
                        break;
                    case InsertPosition.LastChild:
                        card.Body.Add(newElement);
                        break;
                    default:
                        throw new ArgumentException($"Can't add before or after card");
                }
                return Task.CompletedTask;
            }

            if (card.TryGetElementById(id, out AdaptiveElement targetElement, out object parent))
            {
                if (position == InsertPosition.Before || position == InsertPosition.After)
                {
                    if (parent is AdaptiveCard)
                    {
                        var container = parent as AdaptiveCard;
                        var index = container.Body.IndexOf(targetElement);
                        switch (position)
                        {
                            case InsertPosition.Before:
                                card.Body.Insert(index, newElement);
                                break;
                            case InsertPosition.After:
                                card.Body.Insert(index + 1, newElement);
                                break;
                        }
                        return Task.CompletedTask;
                    }
                    else if (parent is AdaptiveContainer)
                    {
                        var container = parent as AdaptiveContainer;
                        var index = container.Items.IndexOf(targetElement);
                        switch (position)
                        {
                            case InsertPosition.Before:
                                container.Items.Insert(index, newElement);
                                break;
                            case InsertPosition.After:
                                container.Items.Insert(index + 1, newElement);
                                break;
                        }
                        return Task.CompletedTask;
                    }
                    else if (parent is AdaptiveColumnSet)
                    {
                        var container = parent as AdaptiveColumnSet;
                        var index = container.Columns.IndexOf((AdaptiveColumn)targetElement);
                        switch (position)
                        {
                            case InsertPosition.Before:
                                container.Columns.Insert(index, (AdaptiveColumn)newElement);
                                break;
                            case InsertPosition.After:
                                container.Columns.Insert(index + 1, (AdaptiveColumn)newElement);
                                break;
                        }
                        return Task.CompletedTask;
                    }
                }
                else if (position == InsertPosition.LastChild || position == InsertPosition.FirstChild)
                {
                    if (targetElement is AdaptiveContainer)
                    {
                        var container = parent as AdaptiveContainer;
                        switch (position)
                        {
                            case InsertPosition.FirstChild:
                                container.Items.Insert(0, newElement);
                                break;
                            case InsertPosition.LastChild:
                                container.Items.Add(newElement);
                                break;
                        }
                        return Task.CompletedTask;
                    }
                    else if (targetElement is AdaptiveColumnSet)
                    {
                        var container = parent as AdaptiveColumnSet;
                        switch (position)
                        {
                            case InsertPosition.FirstChild:
                                container.Columns.Insert(0, (AdaptiveColumn)newElement);
                                break;
                            case InsertPosition.LastChild:
                                container.Columns.Add((AdaptiveColumn)newElement);
                                break;
                        }
                        return Task.CompletedTask;
                    }
                    throw new ArgumentException($"trying to add to non collection type: {targetElement.Type}");
                }
            }
            throw new ArgumentException($"{id} not found");
        }

        /// <summary>
        /// Replace element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="newElement"></param>
        /// <returns></returns>
        public static Task ReplaceElement(this AdaptiveCard card, AdaptiveElement newElement)
        {
            if (card.TryGetElementById(newElement.Id, out AdaptiveElement oldElement, out object parent))
            {
                setEventsVisitor.Visit(null, newElement);

                if (parent is AdaptiveCard)
                {
                    var index = card.Body.IndexOf(oldElement);
                    card.Body[index] = newElement;
                    return Task.CompletedTask;
                }
                else if (parent is AdaptiveContainer)
                {
                    var container = parent as AdaptiveContainer;
                    var index = container.Items.IndexOf(oldElement);
                    container.Items[index] = newElement;
                    return Task.CompletedTask;
                }
                else if (parent is AdaptiveColumnSet)
                {
                    var container = parent as AdaptiveColumnSet;
                    var index = container.Columns.IndexOf((AdaptiveColumn)oldElement);
                    container.Columns[index] = (AdaptiveColumn)newElement;
                    return Task.CompletedTask;
                }
            }
            throw new KeyNotFoundException(newElement.Id);
        }

        /// <summary>
        /// Remove element
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public static Task RemoveElement(this AdaptiveCard card, string id)
        {
            if (card.TryGetElementById(id, out AdaptiveElement oldElement, out object parent))
            {
                if (parent is AdaptiveCard)
                {
                    card.Body.Remove(oldElement);
                    return Task.CompletedTask;
                }
                else if (parent is AdaptiveContainer)
                {
                    var container = parent as AdaptiveContainer;
                    container.Items.Remove(oldElement);
                    return Task.CompletedTask;
                }
                else if (parent is AdaptiveColumnSet)
                {
                    var container = parent as AdaptiveColumnSet;
                    container.Columns.Remove((AdaptiveColumn)oldElement);
                    return Task.CompletedTask;
                }
            }
            throw new KeyNotFoundException(id);
        }

        public static Task SetProperties(this AdaptiveCard card, string id, IEnumerable<SetProperty> properties)
        {
            if (card.TryGetElementById(id, out AdaptiveElement element, out object parent))
            {
                foreach(var property in properties)
                {
                    
                }
                return Task.CompletedTask;
            }
            throw new KeyNotFoundException(id);
        }
    }
}
