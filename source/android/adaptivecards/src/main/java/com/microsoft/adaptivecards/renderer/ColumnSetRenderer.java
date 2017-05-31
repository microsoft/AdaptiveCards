package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.Column;
import com.microsoft.adaptivecards.objectmodel.ColumnSet;
import com.microsoft.adaptivecards.objectmodel.ColumnVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

/**
 * Created by bekao on 4/27/2017.
 */

public class ColumnSetRenderer extends BaseCardElementRenderer
{
    private ColumnSetRenderer()
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

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostConfig hostConfig)
    {
        ColumnSet columnSet = null;
        if (baseCardElement instanceof ColumnSet)
        {
            columnSet = (ColumnSet) baseCardElement;
        }
        else if ((columnSet = ColumnSet.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        IBaseCardElementRenderer columnRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.Column.toString());
        if (columnRenderer == null)
        {
            throw new UnknownError(CardElementType.Column.toString() + " is not a registered renderer.");
        }

        ColumnVector columnVector = columnSet.GetColumns();
        long columnVectorSize = columnVector.size();
        GridLayout gridLayout = new GridLayout(context);
        gridLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        for (int i = 0; i < columnVectorSize; i++)
        {
            Column column = columnVector.get(i);
            //setSeparationConfig(context, gridLayout, columnSet.GetSeparationStyle(), hostConfig.getContainer().getSeparation(), hostConfig.getStrongSeparation(), false /* horizontal line */);
            ((ColumnRenderer)columnRenderer).render(context, gridLayout, column, i, hostConfig);
        }

        viewGroup.addView(gridLayout);
        return viewGroup;
    }

    private static ColumnSetRenderer s_instance = null;
}
