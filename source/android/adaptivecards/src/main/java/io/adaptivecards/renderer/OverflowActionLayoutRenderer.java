// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Paint;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LayerDrawable;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import androidx.annotation.NonNull;
import androidx.fragment.app.FragmentManager;

import java.util.ArrayList;
import java.util.List;

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

    private static final int OVERFLOW_BUTTON_WIDTH = 48;
    private static final int OVERFLOW_BUTTON_TEXT_SIZE = 18;
    private static final String OVERFLOW_TEXT = "•••";
    private static final int POPUP_CONTENT_SEPARATOR_STROKE_WIDTH = 1;
    private static final int POPUP_CONTENT_SEPARATOR_BORDER_WIDTH = 2;

    protected OverflowActionLayoutRenderer()
    {
    }

    public static OverflowActionLayoutRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new OverflowActionLayoutRenderer();
        }

        return s_instance;
    }


    @Override
    public View renderActions(final RenderedAdaptiveCard renderedCard, final Context context, final FragmentManager fragmentManager, final ViewGroup viewGroup, final BaseActionElementVector baseActionElementList, final ICardActionHandler cardActionHandler, final HostConfig hostConfig, final RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        final IOverflowActionRenderer overflowActionRenderer = CardRendererRegistration.getInstance().getOverflowActionRenderer();
        final List<View> menuItemList = renderSecondaryActionElements(baseActionElementList, renderedCard, context, fragmentManager, viewGroup, cardActionHandler, hostConfig, renderArgs);

        View overflowActionView = null;
        try
        {
            if (overflowActionRenderer == null || (overflowActionView = overflowActionRenderer.onRenderOverflowAction(viewGroup, menuItemList, renderArgs.isRootLevelActions())) == null) {
                overflowActionView = renderDefaultOverflowAction(context, viewGroup, hostConfig);
            }
            final LinearLayout contentLayout = new LinearLayout(context);
            contentLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
            contentLayout.setOrientation(LinearLayout.VERTICAL);
            setDrawables(contentLayout);
            overflowActionView.setOnClickListener(new OverflowActionOnClickListener(contentLayout, overflowActionRenderer, menuItemList, renderArgs.isRootLevelActions()));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        return overflowActionView;
    }

    /**
     * Renders default Overflow(...) action view
     *
     * @param context    context for the view to be rendered
     * @param viewGroup  Container view for the view to be attached
     * @param hostConfig hostConfig
     * @return rendered view
     */
    private Button renderDefaultOverflowAction(@NonNull Context context, @NonNull ViewGroup viewGroup, @NonNull HostConfig hostConfig)
    {
        final Button overflowActionView = new Button(context);
        LinearLayout.LayoutParams layoutParams;
        final ActionsOrientation orientation = hostConfig.GetActions().getActionsOrientation();

        final int width = Util.dpToPixels(context, OVERFLOW_BUTTON_WIDTH);
        if (orientation == ActionsOrientation.Horizontal)
        {
            layoutParams = new LinearLayout.LayoutParams(width, LinearLayout.LayoutParams.MATCH_PARENT);
            long spacing = hostConfig.GetActions().getButtonSpacing();
            layoutParams.setMarginEnd(Util.dpToPixels(context, spacing));
        }
        else
        {
            layoutParams = new LinearLayout.LayoutParams(width, LinearLayout.LayoutParams.MATCH_PARENT);
        }

        overflowActionView.setText(OVERFLOW_TEXT);
        overflowActionView.setMinWidth(0);
        overflowActionView.setMinimumWidth(0);
        overflowActionView.setGravity(Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL);
        overflowActionView.setLayoutParams(layoutParams);
        overflowActionView.setTextSize(TypedValue.COMPLEX_UNIT_SP, OVERFLOW_BUTTON_TEXT_SIZE);
        viewGroup.addView(overflowActionView);

        return overflowActionView;
    }

    /**
     * Adds divider and background to the content layout.
     *
     * @param linearLayout BottomSheet's root layout
     */
    private void setDrawables(@NonNull LinearLayout linearLayout)
    {
        ColorDrawable colorDrawable = new ColorDrawable(linearLayout.getContext().getResources().getColor(android.R.color.white));
        Drawable borderDrawable = getShapeDrawable(linearLayout.getContext(), linearLayout.getContext().getResources().getColor(R.color.menu_border_color), POPUP_CONTENT_SEPARATOR_BORDER_WIDTH);
        linearLayout.setBackground(new LayerDrawable(new Drawable[]{colorDrawable, borderDrawable}));
        linearLayout.setDividerDrawable(getShapeDrawable(linearLayout.getContext(), linearLayout.getContext().getResources().getColor(R.color.menu_divider_color), POPUP_CONTENT_SEPARATOR_STROKE_WIDTH));
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

    /**
     * Class responsible handling action event for Overflow view.
     */
    private static final class OverflowActionOnClickListener implements View.OnClickListener
    {

        private final LinearLayout contentLayout;
        private final IOverflowActionRenderer overflowActionRenderer;
        private final List<View> menuItemViewList;
        private PopupWindow popupWindow;
        private int contentWidth;
        private int contentHeight;
        private boolean isRootLevelActions;

        public OverflowActionOnClickListener(LinearLayout contentLayout, IOverflowActionRenderer overflowActionRenderer, List<View> menuItemViewList, boolean isRootLevelActions)
        {
            this.contentLayout = contentLayout;
            this.overflowActionRenderer = overflowActionRenderer;
            this.menuItemViewList = menuItemViewList;
            this.isRootLevelActions = isRootLevelActions;
        }

        @Override
        public void onClick(View v) {

            if (overflowActionRenderer == null || !overflowActionRenderer.onDisplayOverflowActionMenu(menuItemViewList, v, isRootLevelActions))
            {
                // Add & measure PopupWindow.
                if (popupWindow == null)
                {
                    for (View child : menuItemViewList)
                    {
                        contentLayout.addView(child);
                    }
                    contentLayout.measure(View.MeasureSpec.makeMeasureSpec(0, View.MeasureSpec.UNSPECIFIED), View.MeasureSpec.makeMeasureSpec(0, View.MeasureSpec.UNSPECIFIED));
                    contentWidth = contentLayout.getMeasuredWidth();
                    contentHeight = contentLayout.getMeasuredHeight();
                    popupWindow = new PopupWindow(contentLayout, LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT, true);
                    popupWindow.setBackgroundDrawable(new ColorDrawable());
                    contentLayout.setTag(popupWindow);
                }

                int[] location = new int[2];
                v.getLocationOnScreen(location);
                int xPos = location[0];
                int yPos = location[1];
                int screenHeight = v.getContext().getResources().getDisplayMetrics().heightPixels;
                int screenWidth = v.getContext().getResources().getDisplayMetrics().widthPixels;
                int gravity = Gravity.BOTTOM | Gravity.END;
                int yOffset = 0;
                //If content can not be shown in the bottom, then show in on the top of view.
                if (yPos + contentHeight + v.getHeight() > screenHeight)
                {
                    yOffset = -v.getHeight() - contentHeight - contentLayout.getPaddingBottom();
                }
                //If content can not be shown on the right, then set gravity to start of the view.
                if (xPos + contentWidth + v.getWidth() > screenWidth)
                {
                    gravity = Gravity.START | Gravity.TOP;
                }

                popupWindow.showAsDropDown(v, 0, yOffset, gravity);
            }
        }
    }

    private List<View> renderSecondaryActionElements(@NonNull BaseActionElementVector elementVector, RenderedAdaptiveCard renderedCard,
                                               Context context,
                                               FragmentManager fragmentManager,
                                               ViewGroup actionButtonsLayout,
                                               ICardActionHandler cardActionHandler,
                                               HostConfig hostConfig,
                                               RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        final List<View> menuItemViewList = new ArrayList<>();
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

                menuItemViewList.add(actionRenderer.render(renderedCard, context, fragmentManager, actionButtonsLayout, actionElement, cardActionHandler, hostConfig, renderArgs));
            }
            catch (AdaptiveFallbackException e)
            {
                e.printStackTrace();
            }
        }

        return menuItemViewList;
    }

    private static OverflowActionLayoutRenderer s_instance = null;
}
