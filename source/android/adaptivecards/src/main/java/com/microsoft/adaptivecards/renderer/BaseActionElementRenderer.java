package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

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
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.weight = 1;
        button.setLayoutParams(layoutParams);
        viewGroup.addView(button);
        return button;
    }
}
