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
    public static<T extends BaseCardElement> T castTo(BaseCardElement cardElement, Class<T> cardElementType)
    {
        try
        {
            T castedElement = null;
            if (cardElementType.isAssignableFrom(cardElement.getClass()))
            {
                castedElement = (T)cardElement;
            }
            else
            {
                Method dynamicCastMethod = cardElementType.getMethod("dynamic_cast", BaseCardElement.class);
                if ((castedElement = (T)dynamicCastMethod.invoke(null, cardElement)) == null)
                {
                    throw new InternalError("Unable to convert " + cardElement.getClass().getName() + " to " + cardElementType.getName() + " object model.");
                }
            }
            return castedElement;
        }
        catch (Exception e)
        {
            throw new InternalError("Unable to find dynamic_cast method in " + cardElementType.getName() + ".");
        }


/*

        if (cardElement instanceof T)
        {

        }

        if (cardElementType == Column.class)
        {
            return (T)castToColumn(cardElement);
        }
        else if (cardElementType == ColumnSet.class)
        {
            return (T)castToColumnSet(cardElement);
        }
        else if (cardElementType == Container.class)
        {
            return (T)castToContainer(cardElement);
        }
        else if (cardElementType == FactSet.class)
        {
            return (T)castToFactSet(cardElement);
        }
        else if (cardElementType == Image.class)
        {
            return (T)castToImage(cardElement);
        }
        else if (cardElementType == ImageSet.class)
        {
            return (T)castToImageSet(cardElement);
        }
        else if (cardElementType == Media.class)
        {
            return (T)castToMedia(cardElement);
        }
        else if (cardElementType == RichTextBlock.class)
        {
            return (T)castToRichTextBlock(cardElement);
        }
        else if (cardElementType == TextBlock.class)
        {
            return (T)castToTextBlock(cardElement);
        }
 */
        // return (T)cardElement;
    }

    private static Column castToColumn(BaseCardElement cardElement)
    {
        Column column = null;
        if (cardElement instanceof Column)
        {
            column = (Column) cardElement;
        }
        else if ((column = Column.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Column object model.");
        }

        return column;
    }

    private static ColumnSet castToColumnSet(BaseCardElement cardElement)
    {
        ColumnSet columnSet = null;
        if (cardElement instanceof ColumnSet)
        {
            columnSet = (ColumnSet) cardElement;
        }
        else if ((columnSet = ColumnSet.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ColumnSet object model.");
        }

        return columnSet;
    }

    private static Container castToContainer(BaseCardElement cardElement)
    {
        Container container = null;
        if (cardElement instanceof Container)
        {
            container = (Container) cardElement;
        }
        else if ((container = Container.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Container object model.");
        }

        return container;
    }

    private static FactSet castToFactSet(BaseCardElement cardElement)
    {
        FactSet container = null;
        if (cardElement instanceof FactSet)
        {
            container = (FactSet) cardElement;
        }
        else if ((container = FactSet.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to FactSet object model.");
        }

        return container;
    }

    private static Image castToImage(BaseCardElement cardElement)
    {
        Image image = null;
        if (cardElement instanceof Image)
        {
            image = (Image) cardElement;
        }
        else if ((image = Image.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Image object model.");
        }

        return image;
    }

    private static ImageSet castToImageSet(BaseCardElement cardElement)
    {
        ImageSet imageSet = null;
        if (cardElement instanceof ImageSet)
        {
            imageSet = (ImageSet) cardElement;
        }
        else if ((imageSet = ImageSet.dynamic_cast(cardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ImageSet object model.");
        }

        return imageSet;
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
