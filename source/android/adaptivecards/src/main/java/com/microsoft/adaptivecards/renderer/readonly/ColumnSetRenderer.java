package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.ContainerStyle;
import com.microsoft.adaptivecards.renderer.action.ActionElementRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.Column;
import com.microsoft.adaptivecards.objectmodel.ColumnSet;
import com.microsoft.adaptivecards.objectmodel.ColumnVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.registration.CardRendererRegistration;
import com.microsoft.adaptivecards.renderer.IBaseCardElementRenderer;

import java.util.Vector;


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

        ColumnVector columnVector = columnSet.GetColumns();
        long columnVectorSize = columnVector.size();
        LinearLayout layout = new LinearLayout(context);
        layout.setTag(columnSet);
        layout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        for (int i = 0; i < columnVectorSize; i++)
        {
            Column column = columnVector.get(i);
            columnRenderer.render(context, fragmentManager, layout, column, inputActionHandlerList, cardActionHandler, hostConfig, containerStyle);
        }

        if (columnSet.GetSelectAction() != null)
        {
            layout.setClickable(true);
            layout.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(columnSet.GetSelectAction(),inputActionHandlerList, cardActionHandler));
        }

        viewGroup.addView(layout);
        return layout;
    }

    private static ColumnSetRenderer s_instance = null;
}
