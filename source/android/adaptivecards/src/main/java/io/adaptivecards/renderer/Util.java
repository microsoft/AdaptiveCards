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

    public static int dpToPixels(Context context, long dp)
    {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        int returnVal = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, metrics);
        return returnVal;
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
     *
     * @param cardElement
     * @param cardElementType
     * @param <T>
     * @return
     */
    public static<T extends BaseCardElement> boolean isOfType(BaseCardElement cardElement, Class<T> cardElementType)
    {
        return (tryCastTo(cardElement, cardElementType) != null);
    }

    /**
     *
     * @param cardElement
     * @param cardElementType
     * @param <T>
     * @return
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
     *
     * @param cardElement
     * @param cardElementType
     * @param <T>
     * @return
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
     *
     * @param actionElement
     * @param actionElementType
     * @param <T>
     * @return
     */
    public static<T extends BaseActionElement> boolean isOfType(BaseActionElement actionElement, Class<T> actionElementType)
    {
        return (tryCastTo(actionElement, actionElementType) != null);
    }

    /**
     *
     * @param actionElement
     * @param actionElementType
     * @param <T>
     * @return
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
     *
     * @param actionElement
     * @param actionElementType
     * @param <T>
     * @return
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

    public static void deserializeBaseActionProperties(ParseContext context, JsonValue value, BaseActionElement actionElement)
    {
        BaseActionElement baseActionElement = BaseActionElement.ExtractBaseProperties(context, value);
        CopyActionProperties(baseActionElement, actionElement);
    }

    public static void deserializeBaseActionPropertiesFromString(ParseContext context, String jsonString, BaseActionElement actionElement)
    {
        BaseActionElement baseActionElement = BaseActionElement.ExtractBasePropertiesFromString(context, jsonString);
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

    public static void deserializeBaseCardElementProperties(ParseContext context, JsonValue value, BaseCardElement cardElement)
    {
        BaseCardElement baseCardElement = BaseCardElement.ExtractBaseProperties(context, value);
        CopyCardElementProperties(baseCardElement, cardElement);
    }

    public static void deserializeBaseCardElementPropertiesFromString(ParseContext context, String jsonString, BaseCardElement cardElement)
    {
        BaseCardElement baseCardElement = BaseCardElement.ExtractBasePropertiesFromString(context, jsonString);
        CopyCardElementProperties(baseCardElement, cardElement);
    }

    private static void CopyInputProperties(BaseInputElement origin, BaseInputElement dest)
    {
        CopyCardElementProperties(origin, dest);
        dest.SetIsRequired(origin.GetIsRequired());
        dest.SetErrorMessage(origin.GetErrorMessage());
        dest.SetLabel(origin.GetLabel());
    }

    public static void deserializeBaseInputProperties(ParseContext context, JsonValue value, BaseInputElement inputElement)
    {
        BaseInputElement baseInputElement = BaseInputElement.ExtractBaseProperties(context, value);
        CopyInputProperties(baseInputElement, inputElement);
    }

    public static void deserializeBaseInputPropertiesFromString(ParseContext context, String jsonString, BaseInputElement inputElement)
    {
        BaseInputElement baseInputElement = BaseInputElement.ExtractBasePropertiesFromString(context, jsonString);
        CopyInputProperties(baseInputElement, inputElement);
    }

}
