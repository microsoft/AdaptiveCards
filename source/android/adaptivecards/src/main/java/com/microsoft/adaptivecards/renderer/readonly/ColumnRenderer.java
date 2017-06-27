package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.text.TextUtils;
import android.view.ViewGroup;
import android.widget.GridLayout;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.Column;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.CardRendererRegistration;

/**
 * Created by bekao on 4/27/2017.
 */

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
    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostConfig hostConfig)
    {
        throw new InternalError("Default renderer unsupported by Column Renderer.");
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, Column column, int index, HostConfig hostConfig)
    {
        BaseCardElementVector baseCardElementVector = column.GetItems();
        ViewGroup returnedViewGroup = CardRendererRegistration.getInstance().render(context, null, column, baseCardElementVector, hostConfig);
        String columnSize = column.GetSize().toLowerCase();
        if (TextUtils.isEmpty(columnSize) || columnSize.equals(g_columnSizeAuto))
        {
            GridLayout.LayoutParams param = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index));
            returnedViewGroup.setLayoutParams(param);
        }
        else if (columnSize.equals(g_columnSizeStretch))
        {
            GridLayout.LayoutParams param = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index, 1f));
            returnedViewGroup.setLayoutParams(param);
        }
        else
        {
            try
            {
                int columnWeight = Integer.parseInt(columnSize);
                GridLayout.LayoutParams param = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index, (float)columnWeight));
                returnedViewGroup.setLayoutParams(param);
            }
            catch (NumberFormatException numFormatExcep)
            {
                throw new IllegalArgumentException("Column Size (" + column.GetSize() + ") is not a valid weight ('auto', 'stretch', <integer>).");
            }
        }

        viewGroup.addView(returnedViewGroup);
        return viewGroup;
    }

    private static ColumnRenderer s_instance = null;
    private final String g_columnSizeAuto = "auto";
    private final String g_columnSizeStretch = "stretch";
}
