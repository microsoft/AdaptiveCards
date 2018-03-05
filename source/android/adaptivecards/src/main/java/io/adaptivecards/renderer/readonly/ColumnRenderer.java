package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Vector;
import java.util.Locale;

public class ColumnRenderer extends BaseCardElementRenderer
{
    private ColumnRenderer()
    {
    }

    public static ColumnRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ColumnRenderer();
        }

        return s_instance;
    }

    @Override
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
        Column column;
        if (baseCardElement instanceof Column)
        {
            column = (Column) baseCardElement;
        }
        else if ((column = Column.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to FactSet object model.");
        }

        LinearLayout.LayoutParams layoutParams;
        setSpacingAndSeparator(context, viewGroup, column.GetSpacing(), column.GetSeparator(), hostConfig, false);

        ContainerStyle styleForThis = column.GetStyle().swigValue() == ContainerStyle.None.swigValue() ? containerStyle : column.GetStyle();
        View returnedView = CardRendererRegistration.getInstance().render(context, fragmentManager, null, column, column.GetItems(), inputActionHandlerList, cardActionHandler, hostConfig, styleForThis);
        if (styleForThis.swigValue() != containerStyle.swigValue())
        {
            int padding = Util.dpToPixels(context, hostConfig.getSpacing().getPaddingSpacing());
            returnedView.setPadding(padding, padding, padding, padding);
            String color = styleForThis.swigValue() == containerStyle.Emphasis.swigValue() ?
                    hostConfig.getContainerStyles().getEmphasisPalette().getBackgroundColor() :
                    hostConfig.getContainerStyles().getDefaultPalette().getBackgroundColor();
            returnedView.setBackgroundColor(Color.parseColor(color));
        }

        String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());

        if (TextUtils.isEmpty(columnSize) || columnSize.equals(g_columnSizeStretch))
        {
            layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
            layoutParams.weight = 1;
            returnedView.setLayoutParams(layoutParams);
        }
        else if (columnSize.equals(g_columnSizeAuto))
        {
            layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
            returnedView.setLayoutParams(layoutParams);
        }
        else
        {
            try
            {
                float columnWeight = Float.parseFloat(columnSize);
                layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
                layoutParams.width = 0;
                layoutParams.weight = columnWeight;
                returnedView.setLayoutParams(layoutParams);
            }
            catch (NumberFormatException numFormatExcep)
            {
                throw new IllegalArgumentException("Column Width (" + column.GetWidth() + ") is not a valid weight ('auto', 'stretch', <integer>).");
            }
        }

        if (column.GetSelectAction() != null)
        {
            returnedView.setClickable(true);
            returnedView.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(column.GetSelectAction(),inputActionHandlerList, cardActionHandler));
        }

        viewGroup.addView(returnedView);
        return returnedView;
    }

    private static ColumnRenderer s_instance = null;
    private final String g_columnSizeAuto = "auto";
    private final String g_columnSizeStretch = "stretch";
}
