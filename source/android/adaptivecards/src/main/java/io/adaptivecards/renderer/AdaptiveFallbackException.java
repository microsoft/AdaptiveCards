// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.FeatureRegistration;

/***
 * Exception for signalizing that an element could not be rendered and fallback should be performed
 */
public class AdaptiveFallbackException extends Exception
{
    public AdaptiveFallbackException(BaseElement element)
    {
        super("No renderer exists for element type: " + element.GetElementTypeString());
        m_element = element;
    }

    public AdaptiveFallbackException(BaseElement element, FeatureRegistration featureRegistration)
    {
        super("Requirements are not met for element type: " + element.GetElementTypeString());
        m_element = element;
        m_featureRegistration = featureRegistration;
    }

    // I'm saving this object in case I ever need to debug this
    // No getters or setters are provided as outside developers shouldn't have
    // to find this Exception (unless overriding the action layout renderer)
    private BaseElement m_element = null;
    private FeatureRegistration m_featureRegistration = null;
}
