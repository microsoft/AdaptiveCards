package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.text.TextUtils;
import android.view.ViewGroup;
import android.widget.GridLayout;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.Column;

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

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions) { return viewGroup; }
    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, int index, HostOptions hostOptions)
    {
        Column column = null;
        if (baseCardElement instanceof Column)
        {
            column = (Column) baseCardElement;
        }
        else if ((column = Column.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        BaseCardElementVector baseCardElementVector = column.GetItems();
        ViewGroup returnedViewGroup = CardRendererRegistration.getInstance().render(context, null,baseCardElementVector, hostOptions);
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
