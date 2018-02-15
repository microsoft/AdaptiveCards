package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Fact;
import com.microsoft.adaptivecards.objectmodel.FactVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.FactSet;
import com.microsoft.adaptivecards.objectmodel.TextConfig;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 4/27/2017.
 */

public class FactSetRenderer extends BaseCardElementRenderer
{
    private FactSetRenderer()
    {
    }

    public static FactSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new FactSetRenderer();
        }

        return s_instance;
    }

    static TextView createTextView(Context context, String text, TextConfig textConfig, HostConfig hostConfig)
    {
        TextView textView = new TextView(context);
        textView.setText(text);

        TextBlockRenderer.setTextColor(textView, textConfig.getColor(), hostConfig, textConfig.getIsSubtle());
        TextBlockRenderer.setTextSize(textView, textConfig.getSize(), hostConfig);
        TextBlockRenderer.getInstance().setTextWeight(textView, textConfig.getWeight());
        GridLayout.LayoutParams parem = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),
                GridLayout.spec(GridLayout.UNDEFINED));
        textView.setLayoutParams(parem);
        return textView;
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
        FactSet factSet = null;
        if (baseCardElement instanceof FactSet)
        {
            factSet = (FactSet) baseCardElement;
        }
        else if ((factSet = FactSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to FactSet object model.");
        }

        GridLayout gridLayout = new GridLayout(context);
        gridLayout.setTag(factSet);
        gridLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        gridLayout.setColumnCount(2);

        FactVector factVector = factSet.GetFacts();
        long factVectorSize = factVector.size();
        for (int i = 0; i < factVectorSize; i++)
        {
            Fact fact = factVector.get(i);
            gridLayout.addView(createTextView(context, fact.GetTitle(), hostConfig.getFactSet().getTitle(), hostConfig));
            gridLayout.addView(createTextView(context, fact.GetValue(), hostConfig.getFactSet().getValue(), hostConfig));
        }

        viewGroup.addView(gridLayout);
        return gridLayout;
    }

    private static FactSetRenderer s_instance = null;
}
