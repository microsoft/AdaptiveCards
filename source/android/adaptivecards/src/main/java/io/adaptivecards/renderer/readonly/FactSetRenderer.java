// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.SpannableString;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.Fact;
import io.adaptivecards.objectmodel.FactVector;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.FactSet;
import io.adaptivecards.objectmodel.TextConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;

public class FactSetRenderer extends BaseCardElementRenderer
{
    protected FactSetRenderer()
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

    static TextView createTextView(Context context, CharSequence text, TextConfig textConfig, HostConfig hostConfig, long spacing, ContainerStyle containerStyle)
    {
        TextView textView = new TextView(context);
        textView.setText(text);

        TextBlockRenderer.setTextColor(textView, textConfig.getColor(), hostConfig, textConfig.getIsSubtle(), containerStyle);
        TextBlockRenderer.setTextSize(textView, FontType.Default, textConfig.getSize(), hostConfig);
        TextBlockRenderer.getInstance().setTextFormat(textView, hostConfig, FontType.Default, textConfig.getWeight());
        textView.setOnTouchListener(new TextBlockRenderer.TouchTextView(new SpannableString(text)));
        textView.setSingleLine(!textConfig.getWrap());
        textView.setMaxWidth(Util.dpToPixels(context, textConfig.getMaxWidth()));
        textView.setEllipsize(TextUtils.TruncateAt.END);

        textView.setPaddingRelative(0, 0, (int)spacing,0);
        return textView;
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
        FactSet factSet = null;
        if (baseCardElement instanceof FactSet)
        {
            factSet = (FactSet) baseCardElement;
        }
        else if ((factSet = FactSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to FactSet object model.");
        }

        View separator = setSpacingAndSeparator(context, viewGroup, factSet.GetSpacing(), factSet.GetSeparator(), hostConfig, true);

        TableLayout tableLayout = new TableLayout(context);
        tableLayout.setTag(new TagContent(factSet, separator, viewGroup));

        setVisibility(baseCardElement.GetIsVisible(), tableLayout);

        tableLayout.setColumnShrinkable(1, true);
        HeightType height = factSet.GetHeight();

        if(height == HeightType.Stretch)
        {
            tableLayout.setLayoutParams(new TableLayout.LayoutParams(TableLayout.LayoutParams.WRAP_CONTENT, TableLayout.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            tableLayout.setLayoutParams(new TableLayout.LayoutParams(TableLayout.LayoutParams.WRAP_CONTENT, TableLayout.LayoutParams.WRAP_CONTENT));
        }

        FactVector factVector = factSet.GetFacts();
        long factVectorSize = factVector.size();
        long spacing = hostConfig.GetFactSet().getSpacing();

        for (int i = 0; i < factVectorSize; i++)
        {
            Fact fact = factVector.get(i);
            TableRow factRow = new TableRow(context);

            if( height == HeightType.Stretch )
            {
                factRow.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.MATCH_PARENT, 1));
            }
            else
            {
                factRow.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.WRAP_CONTENT));
            }

            DateTimeParser parser = new DateTimeParser(fact.GetLanguage());

            // Handle Title
            String titleWithFormattedDates = parser.GenerateString(fact.GetTitleForDateParsing());
            factRow.addView(createTextView(context, RendererUtil.handleSpecialText(titleWithFormattedDates), hostConfig.GetFactSet().getTitle(), hostConfig, spacing, renderArgs.getContainerStyle()));

            // Handle Value
            String valueWithFormattedDates = parser.GenerateString(fact.GetValueForDateParsing());
            factRow.addView(createTextView(context, RendererUtil.handleSpecialText(valueWithFormattedDates), hostConfig.GetFactSet().getValue(), hostConfig, 0, renderArgs.getContainerStyle()));

            tableLayout.addView(factRow);
        }

        viewGroup.addView(tableLayout);
        return tableLayout;
    }

    private static FactSetRenderer s_instance = null;
}
