using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveExpressions.Memory;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// Implements AEL's IMemory interface
    /// </summary>
    public class AdaptiveCardsTemplateSimpleObjectMemory : IMemory 
    {
        private SimpleObjectMemory simpleObjectMemory;
        /// <summary>
        /// Simple implementation of AEL.Memory.IMemory
        /// It serves as an entry points to additional customazation and optimazation
        /// </summary>
        /// <param name="memory"></param>
        public AdaptiveCardsTemplateSimpleObjectMemory(object memory)
        {
            simpleObjectMemory = new SimpleObjectMemory(memory);
        }

        /// <summary>
        /// Try get value from a given path.
        /// Expansion of the template is done in the context of serialized json payload,
        /// However, the memory that bounds to the template is in deserialized form.
        /// This is normally not an issue for types other than string
        /// This override serializes the value if it's string
        /// </summary>
        /// <param name="path">Given path</param>
        /// <param name="value">Resolved value</param>
        /// <returns>True if the memory contains an element with the specified key; otherwise, false</returns>
        public bool TryGetValue(string path, out object value)
        {
            return simpleObjectMemory.TryGetValue(path, out value);
        }

        /// <summary>
        /// Set value to a given path
        /// </summary>
        /// <param name="path">Memory path</param>
        /// <param name="value">Value to set</param>
        public void SetValue(string path, object value)
        {
            simpleObjectMemory.SetValue(path, value);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public string Version()
        {
            return simpleObjectMemory.Version();
        }
    }
}
