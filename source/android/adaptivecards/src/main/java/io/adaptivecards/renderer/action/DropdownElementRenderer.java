// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import androidx.fragment.app.FragmentManager;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

/**
 * Responsible for rendering dropdown element.
 */
public class DropdownElementRenderer implements IBaseActionElementRenderer {

    private final static int HORIZONTAL_MARGIN = 12;
    private final static int VERTICAL_MARGIN = 10;



    protected DropdownElementRenderer()
    {
    }

    public static DropdownElementRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new DropdownElementRenderer();
        }

        return s_instance;
    }

    @Override
    public Button render(RenderedAdaptiveCard renderedCard, Context context, FragmentManager fragmentManager, ViewGroup viewGroup, BaseActionElement baseActionElement, ICardActionHandler cardActionHandler, HostConfig hostConfig, RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        IBaseActionElementRenderer actionRenderer = CardRendererRegistration.getInstance().getActionRenderer(baseActionElement.GetElementTypeString());
        FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();
        if (actionRenderer == null)
        {
            throw new AdaptiveFallbackException(baseActionElement);
        }

        if ((featureRegistration != null) && (!baseActionElement.MeetsRequirements(featureRegistration)))
        {
            throw new AdaptiveFallbackException(baseActionElement, featureRegistration);
        }

        //Remove button so it does not get added to the default viewGroup.
        Button button = actionRenderer.render(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs);
        viewGroup.removeView(button);

        Button dropDownItem = new Button(context, null, R.style.Widget_AppCompat_Light_ActionButton_Overflow);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        int hMargin = Util.dpToPixels(context, HORIZONTAL_MARGIN);
        int vMargin = Util.dpToPixels(context, VERTICAL_MARGIN);
        layoutParams.setMargins(hMargin, vMargin, hMargin, vMargin);
        layoutParams.gravity = Gravity.CENTER;
        dropDownItem.setText(button.getText());
        dropDownItem.setTextSize(TypedValue.COMPLEX_UNIT_SP, 14);
        dropDownItem.setGravity(Gravity.CENTER);
        dropDownItem.setTextColor(context.getResources().getColor(R.color.dropdown_text_color));
        dropDownItem.setBackgroundColor(context.getResources().getColor(android.R.color.transparent));
        dropDownItem.setLayoutParams(layoutParams);
        dropDownItem.setMinWidth(Util.dpToPixels(context, 80));
        dropDownItem.setMinimumWidth(0);

        dropDownItem.post(() ->
        {
            Drawable[] drawables;

            if((drawables = button.getCompoundDrawablesRelative()) !=null)
            {
                dropDownItem.setCompoundDrawablePadding(button.getCompoundDrawablePadding());
                dropDownItem.setCompoundDrawablesRelativeWithIntrinsicBounds(drawables[0], drawables[1], drawables[2], drawables[3]);
            }

        });

        dropDownItem.setOnClickListener(view ->
        {
            button.performClick();
            try
            {
                if (view.getParent() instanceof ViewGroup && ((ViewGroup) view.getParent()).getTag() instanceof PopupWindow)
                {
                    PopupWindow popupWindow = (PopupWindow) ((ViewGroup) view.getParent()).getTag();
                    popupWindow.dismiss();
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        });
        button.setTag(BaseActionElementRenderer.PARENT_DROPDOWN_TAG, viewGroup);

        return dropDownItem;
    }

    private static DropdownElementRenderer s_instance = null;

}
