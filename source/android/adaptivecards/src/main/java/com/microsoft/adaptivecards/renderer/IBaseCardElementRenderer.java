package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

/**
 * Created by bekao on 2/12/2017.
 */

public interface IBaseCardElementRenderer
{
    ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostConfig hostConfig);
}
