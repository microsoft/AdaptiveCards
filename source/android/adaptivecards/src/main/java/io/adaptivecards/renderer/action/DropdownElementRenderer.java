// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.content.Context;
import android.os.AsyncTask;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import androidx.annotation.NonNull;
import androidx.fragment.app.FragmentManager;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

/**
 * Responsible for rendering dropdown element.
 */
public class DropdownElementRenderer extends BaseActionElementRenderer {

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
        Button button = new Button(context, null, R.style.Widget_AppCompat_Light_ActionButton_Overflow);
        SubmitAction action = Util.tryCastTo(baseActionElement, SubmitAction.class);
        if (action != null)
        {
            long actionId = Util.getViewId(button);
            renderedCard.setCardForSubmitAction(actionId, renderArgs.getContainerCardId());
        }
        button.setText(baseActionElement.GetTitle());
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        int hMargin = Util.dpToPixels(context, HORIZONTAL_MARGIN);
        int vMargin = Util.dpToPixels(context, VERTICAL_MARGIN);
        layoutParams.setMargins(hMargin, vMargin, hMargin, vMargin);
        layoutParams.gravity = Gravity.CENTER;
        button.setTextSize(TypedValue.COMPLEX_UNIT_SP, 14);
        button.setGravity(Gravity.CENTER);
        button.setTextColor(context.getResources().getColor(R.color.dropdown_text_color));
        button.setBackgroundColor(context.getResources().getColor(android.R.color.transparent));
        button.setLayoutParams(layoutParams);
        button.setMinWidth(Util.dpToPixels(context, 80));
        button.setMinimumWidth(0);

        ActionOnClickListener actionOnClickListener = new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs)
        {
            @Override
            public void onClick(View view)
            {
                try
                {
                    super.onClick(view);
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
            }
        };

        button.setOnClickListener(actionOnClickListener);
        button.setTag(BOTTOM_SHEET_TAG,viewGroup);
        setIcon(button,renderedCard,baseActionElement,hostConfig,renderArgs);
        return button;
    }

    private void setIcon(@NonNull Button button, RenderedAdaptiveCard renderedCard, BaseActionElement baseActionElement, HostConfig hostConfig, RenderArgs renderArgs){
        String iconUrl = baseActionElement.GetIconUrl();
        if (!iconUrl.isEmpty())
        {
            IconPlacement iconPlacement = hostConfig.GetActions().getIconPlacement();
            if (!renderArgs.getAllowAboveTitleIconPlacement())
            {
                iconPlacement = IconPlacement.LeftOfTitle;
                button.setMinWidth(0);
                button.setMinimumWidth(0);
            }

            ActionElementRendererIconImageLoaderAsync imageLoader = new ActionElementRendererIconImageLoaderAsync(
                renderedCard,
                button,
                hostConfig.GetImageBaseUrl(),
                iconPlacement,
                hostConfig.GetActions().getIconSize(),
                hostConfig.GetSpacing().getDefaultSpacing(),
                button.getContext()
            );
            imageLoader.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, baseActionElement.GetIconUrl());
        }

    }

    private static DropdownElementRenderer s_instance = null;

}
