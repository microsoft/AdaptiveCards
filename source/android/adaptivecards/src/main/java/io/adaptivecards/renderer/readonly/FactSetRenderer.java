// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.os.Build;
import android.text.SpannableString;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import androidx.fragment.app.FragmentManager;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.Fact;
import io.adaptivecards.objectmodel.FactSet;
import io.adaptivecards.objectmodel.FactSetTextConfig;
import io.adaptivecards.objectmodel.FactVector;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextStyle;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

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

    static TextView createTextView(Context context, CharSequence text, FactSetTextConfig textConfig, HostConfig hostConfig, long spacing, ContainerStyle containerStyle, RenderArgs renderArgs)
    {
        TextView textView = new TextView(context);
        textView.setText(text);

        TextBlockRenderer.applyTextColor(textView, hostConfig, TextStyle.Default, textConfig.getColor(), textConfig.getIsSubtle(), containerStyle, renderArgs);
        TextBlockRenderer.applyTextSize(textView, hostConfig, TextStyle.Default, FontType.Default, textConfig.getSize(), renderArgs);
        TextBlockRenderer.applyTextFormat(textView, hostConfig, TextStyle.Default, FontType.Default, textConfig.getWeight(), renderArgs);
        textView.setOnTouchListener(new TextBlockRenderer.TouchTextView(new SpannableString(text)));
        textView.setSingleLine(!textConfig.getWrap());
        textView.setMaxWidth(Util.dpToPixels(context, textConfig.getMaxWidth()));
        textView.setEllipsize(TextUtils.TruncateAt.END);
        textView.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_START);
        textView.setPaddingRelative(0, 0, (int)spacing,0);

        // FactSets TextViews are wrapped under multiple ViewGroups, and further nesting like
        // having FactSets cards view under RecyclerViews is making Android accessibility services
        // to skip factset data for talkBack (sometimes). So marking these TextViews as important for
        // accessibility explicitly/
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            textView.setScreenReaderFocusable(true);
        } else {
            textView.setFocusable(true);
        }
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
            RenderArgs renderArgs) throws Exception
    {
        FactSet factSet = Util.castTo(baseCardElement, FactSet.class);

        TableLayout tableLayout = new TableLayout(context);
        tableLayout.setTag(new TagContent(factSet));

        tableLayout.setColumnShrinkable(1, true);
        HeightType height = factSet.GetHeight();

        FactVector factVector = factSet.GetFacts();
        long factVectorSize = factVector.size();

        long spacing = hostConfig.GetFactSet().getSpacing();

        int validFacts = 0;

        for (int i = 0; i < factVectorSize; i++)
        {
            Fact fact = factVector.get(i);
            DateTimeParser parser = new DateTimeParser(fact.GetLanguage());

            String titleWithFormattedDates = parser.GenerateString(fact.GetTitleForDateParsing());
            String valueWithFormattedDates = parser.GenerateString(fact.GetValueForDateParsing());

            if (!titleWithFormattedDates.isEmpty() || !valueWithFormattedDates.isEmpty())
            {
                TableRow factRow = new TableRow(context);

                if (height == HeightType.Stretch)
                {
                    factRow.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.MATCH_PARENT, 1));
                }
                else
                {
                    factRow.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.WRAP_CONTENT));
                }

                factRow.addView(createTextView(context, RendererUtil.handleSpecialText(titleWithFormattedDates), hostConfig.GetFactSet().getTitle(), hostConfig, spacing, renderArgs.getContainerStyle(), renderArgs));
                factRow.addView(createTextView(context, RendererUtil.handleSpecialText(valueWithFormattedDates), hostConfig.GetFactSet().getValue(), hostConfig, 0, renderArgs.getContainerStyle(), renderArgs));
                tableLayout.addView(factRow);
                validFacts++;
           }
        }

        if (validFacts == 0)
        {
            return null;
        }

        viewGroup.addView(tableLayout);
        return tableLayout;
    }

    private static FactSetRenderer s_instance = null;
}
