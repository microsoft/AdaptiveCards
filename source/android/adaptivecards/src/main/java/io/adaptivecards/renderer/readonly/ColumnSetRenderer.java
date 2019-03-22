package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.nfc.Tag;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.ColumnSet;
import io.adaptivecards.objectmodel.ColumnVector;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;
import io.adaptivecards.renderer.IBaseCardElementRenderer;

import java.util.Vector;


public class ColumnSetRenderer extends BaseCardElementRenderer
{
    protected ColumnSetRenderer()
    {
    }

    public static ColumnSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ColumnSetRenderer();
        }

        return s_instance;
    }

    @Override
    public View render(
        RenderedAdaptiveCard renderedCard,
        Context context,
        FragmentManager fragmentManager,
        ViewGroup viewGroup,
        BaseCardElement baseCardElement,
        ICardActionHandler cardActionHandler,
        HostConfig hostConfig,
        RenderArgs renderArgs)
    {
        ColumnSet columnSet = null;
        if (baseCardElement instanceof ColumnSet)
        {
            columnSet = (ColumnSet) baseCardElement;
        }
        else if ((columnSet = ColumnSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ColumnSet object model.");
        }

        IBaseCardElementRenderer columnRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.Column.toString());
        if (columnRenderer == null)
        {
            throw new UnknownError(CardElementType.Column.toString() + " is not a registered renderer.");
        }

        setSpacingAndSeparator(context, viewGroup, columnSet.GetSpacing(), columnSet.GetSeparator(), hostConfig, true);
        ContainerStyle styleForThis = columnSet.GetStyle().swigValue() == ContainerStyle.None.swigValue() ? renderArgs.getContainerStyle() : columnSet.GetStyle();

        ColumnVector columnVector = columnSet.GetColumns();
        long columnVectorSize = columnVector.size();

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(new TagContent(columnSet));

        // Add this two for allowing children to bleed
        layout.setClipChildren(false);
        layout.setClipToPadding(false);

        if(!baseCardElement.GetIsVisible())
        {
            layout.setVisibility(View.GONE);
        }

        ContainerStyle containerStyle = renderArgs.getContainerStyle();
        for (int i = 0; i < columnVectorSize; i++) {
            Column column = columnVector.get(i);

            ColumnRenderer rendererAsColumnRenderer = null;
            if (columnRenderer instanceof ColumnRenderer)
            {
                rendererAsColumnRenderer = (ColumnRenderer)columnRenderer;
                rendererAsColumnRenderer.setIsRenderingFirstColumn(i == 0);
                rendererAsColumnRenderer.setIsRenderingLastColumn(i == (columnVectorSize - 1));
            }

            View v = columnRenderer.render(renderedCard, context, fragmentManager, layout, column, cardActionHandler, hostConfig, renderArgs);
            if (v == null)
            {
                return null;
            }
        }

        if (columnSet.GetSelectAction() != null) {
            layout.setClickable(true);
            layout.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(renderedCard, columnSet.GetSelectAction(), cardActionHandler));
        }

        if(columnSet.GetHeight() == HeightType.Stretch)
        {
            LinearLayout stretchLayout = new LinearLayout(context);
            stretchLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
            stretchLayout.setOrientation(LinearLayout.VERTICAL);

            layout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));

            stretchLayout.addView(layout);
            viewGroup.addView(stretchLayout);
        }
        else
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
            viewGroup.addView(layout);
        }

        if (columnSet.GetBleed() && (columnSet.GetCanBleed() || (styleForThis != containerStyle || columnSet.GetBackgroundImage() != null)))
        {
            long padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
            LinearLayout.LayoutParams layoutParams = (LinearLayout.LayoutParams) layout.getLayoutParams();
            layoutParams.setMargins((int)-padding, layoutParams.topMargin, (int)-padding, layoutParams.bottomMargin);
            layout.setLayoutParams(layoutParams);
        }

        if (styleForThis != containerStyle)
        {
            int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
            layout.setPadding(padding, padding, padding, padding);
            String color = styleForThis == containerStyle.Emphasis ?
                hostConfig.GetContainerStyles().getEmphasisPalette().getBackgroundColor() :
                hostConfig.GetContainerStyles().getDefaultPalette().getBackgroundColor();
            layout.setBackgroundColor(Color.parseColor(color));
        }

        return layout;
    }

    private static ColumnSetRenderer s_instance = null;
}
