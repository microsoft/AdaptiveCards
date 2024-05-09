// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// This class contains all properties that are used for rendering and need to be passed down between parent and child elements
namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Adaptive Bleed Direction (these are flags and so can be combined.)
    /// </summary>
    public enum BleedDirection
    {
        /// <summary>
        /// no bleed
        /// </summary>
        BleedNone = 0x0000,

        /// <summary>
        /// bleed left
        /// </summary>
        BleedLeft = 0x0001,

        /// <summary>
        /// bleed right
        /// </summary>
        BleedRight = 0x0010,

        /// <summary>
        /// Bleed up
        /// </summary>
        BleedUp = 0x0100,

        /// <summary>
        /// Bleed down
        /// </summary>
        BleedDown = 0x1000,

        /// <summary>
        /// Bleed in all directions.
        /// </summary>
        BleedAll = 0x1111
    };

    /// <summary>
    /// Render args
    /// </summary>
    public class AdaptiveRenderArgs
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public AdaptiveRenderArgs() { }

        /// <summary>
        /// Constructor with parameters
        /// </summary>
        /// <param name="previousRenderArgs"></param>
        public AdaptiveRenderArgs(AdaptiveRenderArgs previousRenderArgs)
        {
            ParentStyle = previousRenderArgs.ParentStyle;
            ForegroundColors = previousRenderArgs.ForegroundColors;
            BleedDirection = previousRenderArgs.BleedDirection;
            HasParentWithPadding = previousRenderArgs.HasParentWithPadding;
            ContainerCardId = previousRenderArgs.ContainerCardId;
        }

        /// <summary>
        /// Default value for the container style of the first adaptiveCard
        /// </summary>
        public AdaptiveContainerStyle ParentStyle { get; set; } = AdaptiveContainerStyle.Default;

        /// <summary>
        /// ForegoundColors config to use.
        /// </summary>
        public ForegroundColorsConfig ForegroundColors { get; set; }

        /// <summary>
        /// Bleed direction
        /// </summary>
        public BleedDirection BleedDirection { get; set; } = BleedDirection.BleedAll;

        /// <summary>
        /// Flag for wether the parent already has padding.
        /// </summary>
        public bool HasParentWithPadding { get; set; } = true;

        /// <summary>
        /// ContainerId context.
        /// </summary>
        public AdaptiveInternalID ContainerCardId { get; set; } = new AdaptiveInternalID();
    }
}
