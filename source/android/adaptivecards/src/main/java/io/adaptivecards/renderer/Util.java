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
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.objectmodel.RichTextBlock;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.objectmodel.TextBlock;
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

    public static BaseInputElement castToInputElement(BaseCardElement cardElement)
    {
        BaseInputElement baseInputElement = null;
        if (cardElement instanceof BaseInputElement)
        {
            baseInputElement = (BaseInputElement) cardElement;
        }
        else if ((baseInputElement = BaseInputElement.dynamic_cast(cardElement)) == null)
        {
            // throw new InternalError("Unable to convert BaseCardElement to BaseInputElement object model.");
        }

        return baseInputElement;
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
    public static<T extends BaseCardElement> T castTo(BaseCardElement cardElement, Class<T> cardElementType) throws Exception
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
            throw new Exception("Unable to find dynamic_cast method in " + cardElementType.getName() + ".");
        }
    }

    public static SubmitAction tryCastToSubmitAction(BaseActionElement actionElement)
    {
        SubmitAction result = null;
        try
        {
            result = castToSubmitAction(actionElement);
        }
        catch (Exception e) {}
        return result;
    }

    public static SubmitAction castToSubmitAction(BaseActionElement actionElement)
    {
        SubmitAction submitAction = null;
        if (actionElement instanceof SubmitAction)
        {
            submitAction = (SubmitAction) actionElement;
        }
        else if ((submitAction = SubmitAction.dynamic_cast(actionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to BaseInputElement object model.");
        }
        return submitAction;
    }
}
