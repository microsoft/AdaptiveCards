// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
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
