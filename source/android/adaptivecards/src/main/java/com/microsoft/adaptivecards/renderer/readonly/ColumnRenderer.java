package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridLayout;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.Column;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Vector;
import java.util.Locale;

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
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        throw new InternalError("Default renderer unsupported by Column Renderer.");
    }

    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Column column,
            int index,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        GridLayout.LayoutParams layoutParams = new GridLayout.LayoutParams();
        BaseCardElementVector baseCardElementVector = column.GetItems();
        View returnedView = CardRendererRegistration.getInstance().render(context, fragmentManager, null, column, baseCardElementVector, inputActionHandlerList, hostConfig);
        String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
        if (TextUtils.isEmpty(columnSize) || columnSize.equals(g_columnSizeAuto))
        {
            //GridLayout.LayoutParams layoutParams = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index));
            layoutParams.columnSpec = GridLayout.spec(index);
            returnedView.setLayoutParams(layoutParams);
        }
        else if (columnSize.equals(g_columnSizeStretch))
        {
            //GridLayout.LayoutParams layoutParams = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index, 1f));
            layoutParams.columnSpec = GridLayout.spec(index, 1f);
            returnedView.setLayoutParams(layoutParams);
        }
        else
        {
            try
            {
                int columnWeight = Integer.parseInt(columnSize);
                //GridLayout.LayoutParams layoutParams = new GridLayout.LayoutParams(GridLayout.spec(0), GridLayout.spec(index, (float)columnWeight));
                layoutParams.columnSpec = GridLayout.spec(index, (float)columnWeight);
                returnedView.setLayoutParams(layoutParams);
            }
            catch (NumberFormatException numFormatExcep)
            {
                throw new IllegalArgumentException("Column Width (" + column.GetWidth() + ") is not a valid weight ('auto', 'stretch', <integer>).");
            }
        }

        viewGroup.addView(returnedView);
        return returnedView;
    }

    private static ColumnRenderer s_instance = null;
    private final String g_columnSizeAuto = "auto";
    private final String g_columnSizeStretch = "stretch";
}
