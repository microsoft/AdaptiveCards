package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

/**
 * Created by bekao on 7/1/2017.
 */

public abstract class BaseActionElementRenderer implements IBaseActionElementRenderer
{
    public Button renderButton(
            Context context,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            HostConfig hostConfig)
    {
        Button button = new Button(context);
        button.setText(baseActionElement.GetTitle());
        button.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        viewGroup.addView(button);
        return button;
    }
}
