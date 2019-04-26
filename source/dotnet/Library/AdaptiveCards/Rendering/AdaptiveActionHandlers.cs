// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveActionHandlers
    {
        private readonly List<Type> _supportedActions = new List<Type>()
        {
            typeof(AdaptiveOpenUrlAction),
            typeof(AdaptiveSubmitAction),
            typeof(AdaptiveShowCardAction),
            typeof(AdaptiveToggleVisibilityAction)
        };

        /// <summary>
        /// Adds support for a given action type. Any action in a payload not specified here will be dropped from the rendered card
        /// </summary>
        public void AddSupportedAction<TAction>()
            where TAction : AdaptiveAction
        {
            _supportedActions.Add(typeof(TAction));
        }

        /// <summary>
        /// Remove support for an action type. This will prevent these actions from appearing in the rendered card
        /// </summary>
        public void RemoveSupportedAction<TAction>()
            where TAction : AdaptiveAction
        {
            _supportedActions.Remove(typeof(TAction));
        }

        /// <summary>
        /// Whether or not the action is supported by the renderer
        /// </summary>
        /// <returns></returns>
        public bool IsSupported(Type type)
        {
            return _supportedActions.Contains(type);
        }
    }
}
