package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Fact;
import com.microsoft.adaptivecards.objectmodel.FactVector;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.FactSet;
import com.microsoft.adaptivecards.objectmodel.TextOptions;

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

    static TextView createTextView(Context context, String text, TextOptions textOptions, HostOptions hostOptions)
    {
        TextView textView = new TextView(context);
        textView.setText(text);
        TextBlockRenderer.setTextColor(textView, textOptions.getColor(), textOptions.getIsSubtle(), hostOptions.getColors());
        TextBlockRenderer.setTextSize(textView, textOptions.getSize(), hostOptions);
        TextBlockRenderer.getInstance().setTextWeight(textView, textOptions.getWeight());
        GridLayout.LayoutParams parem = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED, 1f),
                GridLayout.spec(GridLayout.UNDEFINED, 1f));
        textView.setLayoutParams(parem);
        return textView;
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        FactSet factSet = null;
        if (baseCardElement instanceof FactSet)
        {
            factSet = (FactSet) baseCardElement;
        }
        else if ((factSet = FactSet.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        GridLayout gridLayout = new GridLayout(context);
        gridLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        gridLayout.setColumnCount(2);

        FactVector factVector = factSet.GetFacts();
        long factVectorSize = factVector.size();
        for (int i = 0; i < factVectorSize; i++)
        {
            Fact fact = factVector.get(i);
            String speak = fact.GetSpeak(); // TODO

            gridLayout.addView(createTextView(context, fact.GetTitle(), hostOptions.getFactSet().getTitle(), hostOptions));
            gridLayout.addView(createTextView(context, fact.GetValue(), hostOptions.getFactSet().getValue(), hostOptions));
        }

        viewGroup.addView(gridLayout);
        return viewGroup;
    }

    private static FactSetRenderer s_instance = null;
}
