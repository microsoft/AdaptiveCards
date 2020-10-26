// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.provider.ContactsContract;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;

import java.lang.reflect.Method;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.CharVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.ColumnSet;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.FactSet;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSet;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.objectmodel.RichTextBlock;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.objectmodel.SubmitActionParser;
import io.adaptivecards.objectmodel.TextBlock;
import io.adaptivecards.objectmodel.TextBlockParser;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;

public final class Util {

    /**
     * Convert dp to px
     * @param context
     * @param dp The number of Android dips (display-independent pixels)
     * @return The number of equivalent physical pixels
     */
    public static int dpToPixels(Context context, long dp)
    {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        int returnVal = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, metrics);
        return returnVal;
    }

    /**
     * Convert px to dp
     * @param context
     * @param pixels The number of physical pixels
     * @return The number of equivalent Android dips (display-independent pixels)
     */
    public static double pixelsToDp(Context context, double pixels)
    {
        return pixels / dpToPixels(context, 1);
    }

    public static byte[] getBytes(CharVector charVector)
    {
        long vectorSize = charVector.size();
        byte[] byteArray = new byte[(int)vectorSize];
        for(int i = 0; i < vectorSize; ++i)
        {
            byteArray[i] = (byte)charVector.get(i).charValue();
        }

        return byteArray;
    }

    /**
     * Clear any existing focus by temporarily adding then removing focus to a given helper View.
     * @param v The helper View that will temporarily grab and release focus.
     */
    public static void clearFocus(View v) {
        boolean focusable = v.isFocusable();
        boolean focusableInTouchMode = v.isFocusableInTouchMode();

        v.setFocusable(true);
        v.setFocusableInTouchMode(true);

        v.requestFocusFromTouch();
        v.clearFocus();

        v.setFocusable(focusable);
        v.setFocusableInTouchMode(focusableInTouchMode);
    }

    public static void MoveChildrenViews(ViewGroup origin, ViewGroup destination)
    {
        final int childCount = origin.getChildCount();
        for (int i = 0; i < childCount; ++i)
        {
            View v = origin.getChildAt(i);
            origin.removeView(v);
            destination.addView(v);
        }
    }

    /**
     * Casts the baseElement into a BaseCardElement
     *
     * @param baseElement BaseElement to be casted into BaseCardElement
     * @return Casted BaseCardElement object if succeeded, null otherwise
     */
    public static BaseCardElement tryCastToBaseCardElement(BaseElement baseElement)
    {
        try
        {
            return castToBaseCardElement(baseElement);
        }
        catch (ClassCastException ex)
        {
            return null;
        }
    }

    /**
     * Casts the baseElement into a BaseCardElement. Throws a ClassCastException if the element cannot be casted
     *
     * @param baseElement BaseElement to be casted into BaseCardElement
     * @return Casted BaseCardElement object
     * @throws ClassCastException
     */
    public static BaseCardElement castToBaseCardElement(BaseElement baseElement) throws ClassCastException
    {
        BaseCardElement baseCardElement;
        if (baseElement instanceof BaseCardElement)
        {
            baseCardElement = (BaseCardElement) baseElement;
        }
        else if ((baseCardElement = BaseCardElement.dynamic_cast(baseElement)) == null)
        {
            throw new ClassCastException("Unable to convert BaseElement to BaseCardElement object model.");
        }
        return baseCardElement;
    }

    /**
     * Checks if the provided cardElement is of the specified type
     *
     * @param cardElement BaseCardElement to be queried
     * @param cardElementType Type of card element to be queried
     * @param <T> Class of card element to be queried, extends from BaseCardElement
     * @return True if the card element is of the queried type
     */
    public static<T extends BaseCardElement> boolean isOfType(BaseCardElement cardElement, Class<T> cardElementType)
    {
        return (tryCastTo(cardElement, cardElementType) != null);
    }

    /**
     * Casts the provided cardElement into the specified type
     *
     * @param cardElement BaseCardElement to be casted
     * @param cardElementType Class for the cardElement to be casted into
     * @param <T> Class of card to be casted to, extends from BaseCardElement
     * @return The casted card element if cardElement is of type cardElementType, null otherwise
     */
    public static<T extends BaseCardElement> T tryCastTo(BaseCardElement cardElement, Class<T> cardElementType)
    {
        try
        {
            return castTo(cardElement, cardElementType);
        }
        catch (Exception e)
        {
            return null;
        }
    }

    /**
     * Casts the provided cardElement into the specified type. Throws an Exception if it doesn't
     * match the specified type
     *
     * @param cardElement BaseCardElement to be casted
     * @param cardElementType Class for the cardElement to be casted into
     * @param <T> Class of card to be casted to, extends from BaseCardElement
     * @return The casted card element if cardElement is of type cardElementType, otherwise throws ClassCastException
     * @throws ClassCastException
     */
    public static<T extends BaseCardElement> T castTo(BaseCardElement cardElement, Class<T> cardElementType) throws ClassCastException
    {
        try
        {
            T castedElement = null;
            // As T is a generic, we cannot use instanceOf, so we have to use the isAssignableFrom method which provides the same functionality
            if (cardElementType.isAssignableFrom(cardElement.getClass()))
            {
                castedElement = (T)cardElement;
            }
            else
            {
                // If the element could not be casted, we use reflection to retrieve and execute the dynamic_cast method, if the method is not found it throws
                Method dynamicCastMethod = cardElementType.getMethod("dynamic_cast", BaseCardElement.class);
                if ((castedElement = (T)dynamicCastMethod.invoke(null, cardElement)) == null)
                {
                     // If after both tries, the element could not be casted, we throw a conversion exception
                    throw new InternalError("Unable to convert " + cardElement.getClass().getName() + " to " + cardElementType.getName() + " object model.");
                }
            }
            return castedElement;
        }
        catch (Exception e)
        {
            throw new ClassCastException("Unable to find dynamic_cast method in " + cardElementType.getName() + ".");
        }
    }

    /**
     * Casts the baseElement into a BaseActionElement
     *
     * @param baseElement BaseElement to be casted into BaseActionElement
     * @return Casted BaseActionElement object if succeeded, null otherwise
     */
    public static BaseActionElement tryCastToBaseActionElement(BaseElement baseElement)
    {
        try
        {
            return castToBaseActionElement(baseElement);
        }
        catch (ClassCastException ex)
        {
            return null;
        }
    }

    /**
     * Casts the baseElement into a BaseActionElement. Throws a ClassCastException if the element cannot be casted
     *
     * @param baseElement BaseElement to be casted into BaseActionElement
     * @return Casted BaseActionElement object
     * @throws ClassCastException
     */
    public static BaseActionElement castToBaseActionElement(BaseElement baseElement) throws ClassCastException
    {
        BaseActionElement baseActionElement;
        if (baseElement instanceof BaseActionElement)
        {
            baseActionElement = (BaseActionElement) baseElement;
        }
        else if ((baseActionElement = BaseActionElement.dynamic_cast(baseElement)) == null)
        {
            throw new ClassCastException("Unable to convert BaseElement to BaseCardElement object model.");
        }
        return baseActionElement;
    }

    /**
     * Checks if the provided actionElement is of the specified type
     *
     * @param actionElement BaseActionElement to be queried
     * @param actionElementType Type of action to be queried
     * @param <T> Class of action to be queried, extends from BaseActionElement
     * @return True if the action is of the queried type
     */
    public static<T extends BaseActionElement> boolean isOfType(BaseActionElement actionElement, Class<T> actionElementType)
    {
        return (tryCastTo(actionElement, actionElementType) != null);
    }

    /**
     * Casts the provided actionElement into the specified type
     *
     * @param actionElement BaseActionElement to be casted
     * @param actionElementType Class for the actionElement to be casted into
     * @param <T> Class of action to be casted to, extends from BaseActionElement
     * @return The casted action element if actionElement is of type actionElementType, null otherwise
     */
    public static<T extends BaseActionElement> T tryCastTo(BaseActionElement actionElement, Class<T> actionElementType)
    {
        try
        {
            return castTo(actionElement, actionElementType);
        }
        catch (Exception e)
        {
            return null;
        }
    }

    /**
     * Casts the provided actionElement into the specified type. Throws an Exception if it doesn't
     * match the specified type
     *
     * @param actionElement BaseActionElement to be casted
     * @param actionElementType Class for the actionElement to be casted into
     * @param <T> Class of action to be casted to, extends from BaseActionElement
     * @return The casted action element if actionElement is of type actionElementType, otherwise throws ClassCastException
     * @throws ClassCastException
     */
    public static<T extends BaseActionElement> T castTo(BaseActionElement actionElement, Class<T> actionElementType) throws ClassCastException
    {
        try
        {
            T castedElement = null;
            // As T is a generic, we cannot use instanceOf, so we have to use the isAssignableFrom method which provides the same functionality
            if (actionElementType.isAssignableFrom(actionElement.getClass()))
            {
                castedElement = (T)actionElement;
            }
            else
            {
                // If the element could not be casted, we use reflection to retrieve and execute the dynamic_cast method, if the method is not found it throws
                Method dynamicCastMethod = actionElementType.getMethod("dynamic_cast", BaseActionElement.class);
                if ((castedElement = (T)dynamicCastMethod.invoke(null, actionElement)) == null)
                {
                    // If after both tries, the element could not be casted, we throw a conversion exception
                    throw new InternalError("Unable to convert " + actionElement.getClass().getName() + " to " + actionElementType.getName() + " object model.");
                }
            }
            return castedElement;
        }
        catch (Exception e)
        {
            throw new ClassCastException("Unable to find dynamic_cast method in " + actionElementType.getName() + ".");
        }
    }

    private static void CopyActionProperties(BaseActionElement origin, BaseActionElement dest)
    {
        dest.SetId(origin.GetId());
        dest.SetIconUrl(origin.GetIconUrl());
        dest.SetStyle(origin.GetStyle());
        dest.SetTitle(origin.GetTitle());
        dest.SetFallbackContent(origin.GetFallbackContent());
        dest.SetFallbackType(origin.GetFallbackType());
    }

    /**
     * Deserializes the properties in all base action elements (id, iconUrl, style, title, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the Deserialize method
     * @param value JsonValue object passed down as a parameter in the Deserialize method
     * @param actionElement BaseActionElement to be populated
     */
    public static void deserializeBaseActionProperties(ParseContext context, JsonValue value, BaseActionElement actionElement)
    {
        BaseActionElement baseActionElement = BaseActionElement.DeserializeBaseProperties(context, value);
        CopyActionProperties(baseActionElement, actionElement);
    }

    /**
     * Deserializes the properties in all base action elements (id, iconUrl, style, title, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the Deserialize method
     * @param jsonString Json string to be deserialized (passed down as a parameter in the DeserializeFromString method)
     * @param actionElement BaseActionElement to be populated
     */
    public static void deserializeBaseActionPropertiesFromString(ParseContext context, String jsonString, BaseActionElement actionElement)
    {
        BaseActionElement baseActionElement = BaseActionElement.DeserializeBasePropertiesFromString(context, jsonString);
        CopyActionProperties(baseActionElement, actionElement);
    }

    private static void CopyCardElementProperties(BaseCardElement origin, BaseCardElement dest)
    {
        dest.SetId(origin.GetId());
        dest.SetHeight(origin.GetHeight());
        dest.SetIsVisible(origin.GetIsVisible());
        dest.SetSeparator(origin.GetSeparator());
        dest.SetSpacing(origin.GetSpacing());
        dest.SetFallbackContent(origin.GetFallbackContent());
        dest.SetFallbackType(origin.GetFallbackType());
    }

    /**
     * Deserializes the properties in all base card elements (id, height, isVisible, separator, spacing, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the Deserialize method
     * @param value JsonValue object passed down as a parameter in the Deserialize method
     * @param cardElement BaseCardElement to be populated
     */
    public static void deserializeBaseCardElementProperties(ParseContext context, JsonValue value, BaseCardElement cardElement)
    {
        BaseCardElement baseCardElement = BaseCardElement.DeserializeBaseProperties(context, value);
        CopyCardElementProperties(baseCardElement, cardElement);
    }

    /**
     * Deserializes the properties in all base card elements (id, height, isVisible, separator, spacing, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the DeserializeFromString method
     * @param jsonString Json string to be deserialized (passed down as a parameter in the DeserializeFromString method)
     * @param cardElement BaseCardElement to be populated
     */
    public static void deserializeBaseCardElementPropertiesFromString(ParseContext context, String jsonString, BaseCardElement cardElement)
    {
        BaseCardElement baseCardElement = BaseCardElement.DeserializeBasePropertiesFromString(context, jsonString);
        CopyCardElementProperties(baseCardElement, cardElement);
    }

    private static void CopyInputProperties(BaseInputElement origin, BaseInputElement dest)
    {
        CopyCardElementProperties(origin, dest);
        dest.SetIsRequired(origin.GetIsRequired());
        dest.SetErrorMessage(origin.GetErrorMessage());
        dest.SetLabel(origin.GetLabel());
    }

    /**
     * Deserializes the properties in all input elements (isRequired, errorMessage, label)
     * and the properties found in all base card elements (id, height, isVisible, separator, spacing, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the Deserialize method
     * @param value JsonValue object passed down as a parameter in the Deserialize method
     * @param inputElement BaseInputElement to be populated
     */
    public static void deserializeBaseInputProperties(ParseContext context, JsonValue value, BaseInputElement inputElement)
    {
        BaseInputElement baseInputElement = BaseInputElement.DeserializeBaseProperties(context, value);
        CopyInputProperties(baseInputElement, inputElement);
    }

    /**
     * Deserializes the properties in all input elements (isRequired, errorMessage, label)
     * and the properties found in all base card elements (id, height, isVisible, separator, spacing, fallback)
     *
     * @param context ParseContext object passed down as a parameter in the DeserializeFromString method
     * @param jsonString Json string to be deserialized (passed down as a parameter in the DeserializeFromString method)
     * @param inputElement BaseInputElement to be populated
     */
    public static void deserializeBaseInputPropertiesFromString(ParseContext context, String jsonString, BaseInputElement inputElement)
    {
        BaseInputElement baseInputElement = BaseInputElement.DeserializeBasePropertiesFromString(context, jsonString);
        CopyInputProperties(baseInputElement, inputElement);
    }

}
