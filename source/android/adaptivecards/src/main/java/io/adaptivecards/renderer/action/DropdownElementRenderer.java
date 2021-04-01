package io.adaptivecards.renderer.action;

import android.content.Context;
import android.os.AsyncTask;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomSheetBehavior;
import android.support.v4.app.FragmentManager;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

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

    private final static int VERTICAL_PADDING = 8;
    private final static int HORIZONTAL_PADDING = 16;
    private final static int TEXT_SIZE = 12;

    protected DropdownElementRenderer()
    {
    }

    public static DropdownElementRenderer getInstance()
    {
        if (s_instance == null) {
            s_instance = new DropdownElementRenderer();
        }

        return s_instance;
    }

    @Override
    public Button render(RenderedAdaptiveCard renderedCard, Context context, FragmentManager fragmentManager, ViewGroup viewGroup, BaseActionElement baseActionElement, ICardActionHandler cardActionHandler, HostConfig hostConfig, RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        Button button = new Button(context);
        SubmitAction action = Util.tryCastTo(baseActionElement, SubmitAction.class);
        if (action != null)
        {
            long actionId = Util.getViewId(button);
            renderedCard.setCardForSubmitAction(actionId, renderArgs.getContainerCardId());
        }
        button.setText(baseActionElement.GetTitle());
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        button.setLayoutParams(layoutParams);
        int verticalPadding = Util.dpToPixels(context, VERTICAL_PADDING);
        int horizontalPadding = Util.dpToPixels(context, HORIZONTAL_PADDING);
        button.setPadding(horizontalPadding, verticalPadding, horizontalPadding, verticalPadding);
        button.setGravity(Gravity.START | Gravity.CENTER_VERTICAL);
        button.setTextSize(TypedValue.COMPLEX_UNIT_SP,TEXT_SIZE);
        button.setTextColor(context.getResources().getColor(R.color.dropdown_text_color));
        button.setBackgroundColor(context.getResources().getColor(android.R.color.transparent));

        ActionOnClickListener actionOnClickListener = new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs)
        {
            @Override
            public void onClick(View view)
            {
                super.onClick(view);
                try
                {
                    //Gets  BottomSheet's behavior with deefault content view.
                    ViewParent parent = view.getParent();
                    FrameLayout bottomSheetLayout = (FrameLayout) parent.getParent();
                    BottomSheetBehavior<FrameLayout> behavior = BottomSheetBehavior.from(bottomSheetLayout);
                    behavior.setHideable(true);
                    behavior.setState(BottomSheetBehavior.STATE_HIDDEN);
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
