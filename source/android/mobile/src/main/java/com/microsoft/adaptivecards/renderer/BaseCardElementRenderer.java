package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;

/**
 * Created by bekao on 2/12/2017.
 */

public interface BaseCardElementRenderer
{
    ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement);
}
