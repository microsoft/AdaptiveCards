using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(AdaptiveTypedElementConverter))]
    public abstract class AdaptiveTypedElement
    {
        /// <summary>
        /// The type name of the element 
        /// </summary>
        [JsonProperty(Order = -10, Required = Required.Always, DefaultValueHandling = DefaultValueHandling.Include)]
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public abstract string Type { get; set; }

        /// <summary>
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Id { get; set; }

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public IDictionary<string, object> AdditionalProperties { get; set; } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        /// <summary>
        /// Get an <see cref="AdaptiveTypedElement" /> by Id
        /// </summary>
        /// <param name="id">Id of the <see cref="AdaptiveTypedElement" /></param>
        /// <returns></returns>
        public abstract AdaptiveTypedElement GetElementById(string id);

        /// <summary>
        /// Get an <see cref="AdaptiveTypedElement" /> by Id
        /// </summary>
        /// <param name="id">Id of the <see cref="AdaptiveTypedElement" /></param>
        /// <returns></returns>
        public T GetElementById<T>(string id) where T : AdaptiveTypedElement
        {
            return GetElementById(id) as T;
        }

        /// <summary>
        /// Set the <see cref="AdaptiveImage.Url" /> of an <see cref="AdaptiveImage" /> by its Id
        /// </summary>
        /// <param name="id">Id of the <see cref="AdaptiveImage" /></param>
        /// <param name="url">Url to the image</param>
        public void SetImage(string id, string url)
        {
            var image = GetElementById<AdaptiveImage>(id);

            if (image != null)
                image.Url = new Uri(url);
        }

        /// <summary>
        /// Set the <see cref="AdaptiveTextBlock.Text" /> of an <see cref="AdaptiveTextBlock" /> 
        /// or <see cref="AdaptiveTextInput.Value" /> of an <see cref="AdaptiveTextInput" /> by its Id
        /// </summary>
        /// <param name="id">Id of the <see cref="AdaptiveTextBlock" /> or <see cref="AdaptiveTextInput" /></param>
        /// <param name="text">Text to set</param>
        public void SetText(string id, string text)
        {
            var element = GetElementById(id);

            if (element is AdaptiveTextBlock textBlock)
                textBlock.Text = text;

            if (element is AdaptiveTextInput textInput)
                textInput.Value = text;
        }
    }
}