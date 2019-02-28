using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements that contain elements
    /// </summary>
    public abstract class AdaptiveCollectionElement : AdaptiveElement
    {

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

        /// <summary>
        ///     The content alignment for the eelment inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        ///     Defines if the element can bleed through its parent's padding
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(false)]
        public bool Bleed { get; set; }

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        public bool Padding { get; set; }

        public bool CanBleed { get; set; }

        internal AdaptiveTypedElement ParentToBleed { get; set; }

        public void ConfigPadding()
        {
            if (ParentToBleed is AdaptiveCollectionElement)
            {
                AdaptiveCollectionElement parentContainer = ParentToBleed as AdaptiveCollectionElement;
                if (Style != AdaptiveContainerStyle.Default && parentContainer.Style != Style)
                {
                    Padding = (parentContainer.Style != AdaptiveContainerStyle.Default);
                }
                else
                {
                    Padding = false;
                }
            }
            else if(ParentToBleed is AdaptiveCard)
            {
                Padding = true; // Cards have no styles, we must set this to true
            }
        }

        public void ConfigBleed()
        {
            if (ParentToBleed is AdaptiveCollectionElement)
            {
                AdaptiveCollectionElement parentContainer = ParentToBleed as AdaptiveCollectionElement;
                CanBleed = (Bleed && parentContainer.Padding);
            }
            else
            {
                CanBleed = true; // Set to true, otherwise no element will be able to bleed
            }
        }

        private void ConfigForContainerStyle()
        {
            ConfigPadding();
            ConfigBleed();
        }

        public override void PropagateBleedProperty(AdaptiveTypedElement parentContainer)
        {
            ParentToBleed = parentContainer;
            ConfigForContainerStyle();

            AdaptiveCollectionElement parentCollectionElement = parentContainer as AdaptiveCollectionElement;

            if (Padding)
            {
                PropagateBleedPropertyToChildren(this);
            }
            else
            {
                PropagateBleedPropertyToChildren(parentContainer);
            }
        }

        protected abstract void PropagateBleedPropertyToChildren(AdaptiveTypedElement parent);
    }
}
