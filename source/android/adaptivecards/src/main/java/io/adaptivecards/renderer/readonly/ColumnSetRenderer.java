package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
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

        for (int i = 0; i < columnVectorSize; i++) {
            Column column = columnVector.get(i);
            columnRenderer.render(renderedCard, context, fragmentManager, layout, column, cardActionHandler, hostConfig, containerStyle);
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

        return layout;
    }

    private static ColumnSetRenderer s_instance = null;
}
