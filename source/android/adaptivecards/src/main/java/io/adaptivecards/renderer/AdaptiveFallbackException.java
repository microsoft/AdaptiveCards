package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.BaseElement;

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

    // I'm saving this object in case I ever need to debug this
    // No getters or setters are provided as outside developers shouldn't have
    // to find this Exception (unless overriding the action layout renderer)
    private BaseElement m_element = null;
}
