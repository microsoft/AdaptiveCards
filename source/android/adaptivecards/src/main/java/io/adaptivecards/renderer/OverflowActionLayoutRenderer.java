// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LayerDrawable;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;
import android.support.annotation.AttrRes;
import android.support.annotation.ColorInt;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomSheetDialog;
import android.support.v4.app.FragmentManager;
import android.support.v4.content.ContextCompat;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.AdaptiveCardObjectModel;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Mode;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

/**
 * Responsible for rendering Overflow action layout.
 */
public class OverflowActionLayoutRenderer implements IActionLayoutRenderer {

    private static final int MARGIN = 7;
    private static final int HORIZONTAL_PADDING = 6;

    protected OverflowActionLayoutRenderer()
    {
    }

    public static OverflowActionLayoutRenderer getInstance()
    {
        if (s_instance == null) {
            s_instance = new OverflowActionLayoutRenderer();
        }

        return s_instance;
    }


    @Override
    public View renderActions(final RenderedAdaptiveCard renderedCard, final Context context, final FragmentManager fragmentManager, final ViewGroup viewGroup, final BaseActionElementVector baseActionElementList, final ICardActionHandler cardActionHandler, final HostConfig hostConfig, final RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        final IOverflowActionRenderer overflowActionRenderer = CardRendererRegistration.getInstance().getOverflowActionRenderer();

        // customized rendering
        final View customOverflowActionView = overflowActionRenderer.onRenderOverflowAction(baseActionElementList);
        if (customOverflowActionView != null)
        {
            if (!overflowActionRenderer.isRootLevelActions())
            {
                viewGroup.addView(customOverflowActionView);
            }
            renderBottomSheet(renderedCard, context, fragmentManager, viewGroup, baseActionElementList, cardActionHandler, hostConfig, renderArgs, overflowActionRenderer, customOverflowActionView);
            actionForOverflowView(overflowActionRenderer, baseActionElementList, customOverflowActionView);

            return customOverflowActionView;
        }
        else
        {
            final ImageButton overflowActionView = new ImageButton(context);
            LinearLayout.LayoutParams layoutParams;
            ActionsOrientation orientation = hostConfig.GetActions().getActionsOrientation();

            if (orientation == ActionsOrientation.Horizontal)
            {
                layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
                long spacing = hostConfig.GetActions().getButtonSpacing();
                layoutParams.rightMargin = Util.dpToPixels(context, spacing);
            }
            else
            {
                layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
            }

            layoutParams.topMargin = Util.dpToPixels(context, MARGIN);
            layoutParams.bottomMargin = Util.dpToPixels(context, MARGIN);
            overflowActionView.setPadding(Util.dpToPixels(context, HORIZONTAL_PADDING), 0, Util.dpToPixels(context, HORIZONTAL_PADDING), 0);
            overflowActionView.setImageResource(R.drawable.overlow_horizontal);
            overflowActionView.setLayoutParams(layoutParams);
            overflowActionView.setAdjustViewBounds(true);
            overflowActionView.setScaleType(ImageView.ScaleType.FIT_END);
            renderBottomSheet(renderedCard, context, fragmentManager, viewGroup, baseActionElementList, cardActionHandler, hostConfig, renderArgs, overflowActionRenderer, overflowActionView);
            actionForOverflowView(overflowActionRenderer, baseActionElementList, overflowActionView);
            applyBackgroundDrawables(context, overflowActionView);

            if (!overflowActionRenderer.isRootLevelActions())
            {
                viewGroup.addView(overflowActionView);
            }

            return overflowActionView;
        }

    }

    /**
     * Sets {@link View.OnClickListener} on the rendered Overflow view.
     *
     * @param overflowActionRenderer instance of IOverflowActionRenderer
     * @param baseActionElementList  secondary action elements list
     * @param overflowActionView     rendered Overflow view
     */
    private void actionForOverflowView(final IOverflowActionRenderer overflowActionRenderer, final BaseActionElementVector baseActionElementList, final View overflowActionView)
    {
        overflowActionView.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (overflowActionRenderer.shouldDisplayCustomActionMenu())
                {
                    overflowActionRenderer.onDisplayOverflowActionMenu(baseActionElementList, overflowActionView);
                }
                else if (v.getTag() instanceof BottomSheetDialog)
                {
                    ((BottomSheetDialog) v.getTag()).show();
                }
            }
        });
    }

    /**
     * Creates {@link BottomSheetDialog} when {@link IOverflowActionRenderer#shouldDisplayCustomActionMenu()} returns false.
     *
     * @param renderedCard           rendered card
     * @param context                context
     * @param fragmentManager        fragmentManger
     * @param viewGroup              root view of the action set elements
     * @param baseActionElementList  secondary action elements list
     * @param cardActionHandler      cardActionHandler
     * @param hostConfig             client configuration
     * @param renderArgs             renderArgs
     * @param overflowActionRenderer instance of IOverflowActionRenderer
     * @param overflowActionView     rendered Overflow view
     */
    private void renderBottomSheet(final RenderedAdaptiveCard renderedCard, final Context context, final FragmentManager fragmentManager, final ViewGroup viewGroup, final BaseActionElementVector baseActionElementList, final ICardActionHandler cardActionHandler, final HostConfig hostConfig, final RenderArgs renderArgs, final IOverflowActionRenderer overflowActionRenderer, final View overflowActionView)
    {
        //Make sure BottomSheet created on UI Thread.
        viewGroup.post(new Runnable()
        {
            @Override
            public void run() {
                try
                {
                    if (!overflowActionRenderer.shouldDisplayCustomActionMenu())
                    {
                        BottomSheetDialog bottomSheetDialog = renderActionSheet(renderedCard, context, fragmentManager, viewGroup, baseActionElementList, cardActionHandler, hostConfig, renderArgs);
                        overflowActionView.setTag(bottomSheetDialog);
                    }
                }
                catch (AdaptiveFallbackException e)
                {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Creates {@link BottomSheetDialog}
     *
     * @param renderedCard          rendered card
     * @param context               context
     * @param fragmentManager       fragmentManger
     * @param viewGroup             root view of the action set elements
     * @param baseActionElementList secondary action elements list
     * @param cardActionHandler     cardActionHandler
     * @param hostConfig            client configuration
     * @param renderArgs            renderArgs
     * @return created {@link BottomSheetDialog}
     * @throws AdaptiveFallbackException throws exception incase of error.
     */
    private BottomSheetDialog renderActionSheet(RenderedAdaptiveCard renderedCard, Context context, FragmentManager fragmentManager, ViewGroup viewGroup, BaseActionElementVector baseActionElementList, ICardActionHandler cardActionHandler, HostConfig hostConfig, RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        BottomSheetDialog bottomSheetDialog = new BottomSheetDialog(context, R.style.BottomSheetDialogTheme);
        LinearLayout contentLayout = new LinearLayout(context);
        contentLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        contentLayout.setOrientation(LinearLayout.VERTICAL);
        contentLayout.setGravity(Gravity.START);
        addSeparator(contentLayout);
        renderSecondaryActionElements(baseActionElementList, renderedCard, context, fragmentManager, viewGroup, contentLayout, cardActionHandler, hostConfig, renderArgs);
        bottomSheetDialog.setContentView(contentLayout);

        return bottomSheetDialog;
    }

    /**
     * Applies backgrounds drawables to the Overflow view.
     *
     * @param context context
     * @param view    drawables to be applied on view.
     */
    private void applyBackgroundDrawables(Context context, @NonNull ImageButton view)
    {
        TypedValue colorValue = new TypedValue();
        //Apply colorButtonNormal for border tp match with existing action buttons;
        int color = context.getResources().getColor(android.R.color.darker_gray);
        if (context.getTheme().resolveAttribute(android.R.attr.colorButtonNormal, colorValue, true))
        {
            color = getAttributeColor(context, R.attr.colorButtonNormal);
        }
        else if (context.getTheme().resolveAttribute(android.R.attr.colorPrimary, colorValue, true))
        {
            color = getAttributeColor(context, R.attr.colorPrimary);
        }

        ShapeDrawable shapedrawable = getShapeDrawable(context, color, 2);
        view.setColorFilter(color, PorterDuff.Mode.SRC_ATOP);
        TypedValue outValue = new TypedValue();
        context.getTheme().resolveAttribute(android.R.attr.selectableItemBackground, outValue, true);
        Drawable backGroundDrawable = ContextCompat.getDrawable(context, outValue.resourceId);
        Drawable[] layers = {backGroundDrawable, shapedrawable};
        LayerDrawable layerDrawable = new LayerDrawable(layers);
        view.setBackground(layerDrawable);
    }

    /**
     * Adds divider to the BottomSheet's content layout.
     *
     * @param linearLayout BottomSheet's root layout
     */
    private void addSeparator(@NonNull LinearLayout linearLayout)
    {
        ShapeDrawable shapedrawable = getShapeDrawable(linearLayout.getContext(), linearLayout.getContext().getResources().getColor(R.color.bottomSheet_divider_color), 1);
        linearLayout.setDividerDrawable(shapedrawable);
        linearLayout.setShowDividers(LinearLayout.SHOW_DIVIDER_MIDDLE);
    }

    /**
     * Applies border with transparent background to the Overflow View.
     *
     * @param context     context to be used for rendering
     * @param color       color of the border
     * @param strokeWidth width of tjhe border
     * @return created {@link ShapeDrawable}
     */
    private ShapeDrawable getShapeDrawable(@NonNull Context context, int color, int strokeWidth)
    {
        ShapeDrawable shapedrawable = new ShapeDrawable();
        shapedrawable.setShape(new RectShape());
        shapedrawable.getPaint().setColor(color);
        shapedrawable.getPaint().setStrokeWidth(Util.dpToPixels(context, strokeWidth));
        shapedrawable.getPaint().setStyle(Paint.Style.STROKE);
        return shapedrawable;
    }

    private void renderSecondaryActionElements(@NonNull BaseActionElementVector elementVector, RenderedAdaptiveCard renderedCard,
                                               Context context,
                                               FragmentManager fragmentManager,
                                               ViewGroup actionButtonsLayout,
                                               ViewGroup contentLayout,
                                               ICardActionHandler cardActionHandler,
                                               HostConfig hostConfig,
                                               RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();

        for (BaseActionElement actionElement : elementVector)
        {
            IBaseActionElementRenderer actionRenderer = CardRendererRegistration.getInstance().getActionRenderer(AdaptiveCardObjectModel.ModeToString(Mode.Secondary));

            try
            {
                if (actionRenderer == null)
                {
                    throw new AdaptiveFallbackException(actionElement);
                }

                if ((featureRegistration != null) && (!actionElement.MeetsRequirements(featureRegistration)))
                {
                    throw new AdaptiveFallbackException(actionElement, featureRegistration);
                }

                contentLayout.addView(actionRenderer.render(renderedCard, context, fragmentManager, actionButtonsLayout, actionElement, cardActionHandler, hostConfig, renderArgs));
            }
            catch (AdaptiveFallbackException e)
            {
                e.printStackTrace();
            }
        }
    }

    /**
     * Gets color for a given color attribute.
     *
     * @param context        context.
     * @param colorAttribute attribute name.
     * @return Id of a color resource or -1 id resource not found.
     */
    @ColorInt
    public static int getAttributeColor(Context context, @AttrRes int colorAttribute)
    {
        int[] attrs = {colorAttribute};
        TypedArray typedArray = context.obtainStyledAttributes(attrs);
        @ColorInt int color = ContextCompat.getColor(context, typedArray.getResourceId(0, -1));
        typedArray.recycle();
        return color;
    }

    private static OverflowActionLayoutRenderer s_instance = null;

    /**
     * Responsible for default Overflow rendering behavior.
     */
    public static class OverflowActionRenderer implements IOverflowActionRenderer {

        private static OverflowActionRenderer m_innerInstance = null;

        public static OverflowActionRenderer getInstance()
        {
            if (m_innerInstance == null)
            {
                m_innerInstance = new OverflowActionRenderer();
            }

            return m_innerInstance;
        }

        @Override
        public View onRenderOverflowAction(@NonNull BaseActionElementVector actionElements)
        {
            return null;
        }

        @Override
        public void onDisplayOverflowActionMenu(@NonNull BaseActionElementVector actionElements, @NonNull View view)
        {
            //default implementation.
        }

        @Override
        public boolean isRootLevelActions()
        {
            return false;
        }

        @Override
        public boolean shouldDisplayCustomActionMenu()
        {
            return false;
        }
    }
}
