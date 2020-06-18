// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.provider.ContactsContract;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.CharVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSet;
import io.adaptivecards.objectmodel.SubmitAction;
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

    public static Container tryCastToContainer(BaseCardElement cardElement)
    {
        Container result = null;
        try
        {
            result = castToContainer(cardElement);
        }
        catch (Exception e) {}

        return result;
    }

    public static Container castToContainer(BaseCardElement cardElement)
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

    public static Column tryCastToColumn(BaseCardElement cardElement)
    {
        Column result = null;
        try
        {
            result = castToColumn(cardElement);
        }
        catch (Exception e) {}

        return result;
    }

    public static Column castToColumn(BaseCardElement cardElement)
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

    public static Image tryCastToImage(BaseCardElement cardElement)
    {
        Image result = null;
        try
        {
            result = castToImage(cardElement);
        }
        catch (Exception e) {}

        return result;
    }

    public static Image castToImage(BaseCardElement cardElement)
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

    public static ImageSet tryCastToImageSet(BaseCardElement cardElement)
    {
        ImageSet result = null;
        try
        {
            result = castToImageSet(cardElement);
        }
        catch (Exception e) {}

        return result;
    }

    public static ImageSet castToImageSet(BaseCardElement cardElement)
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
