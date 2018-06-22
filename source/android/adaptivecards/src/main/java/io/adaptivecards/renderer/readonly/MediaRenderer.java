package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.VideoView;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.Fact;
import io.adaptivecards.objectmodel.FactSet;
import io.adaptivecards.objectmodel.FactVector;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

/**
 * Created by almedina on 6/21/18.
 */

public class MediaRenderer extends BaseCardElementRenderer
{
    private MediaRenderer()
    {
    }

    public static  MediaRenderer getInstance()
    {
        if(s_instance == null)
        {
            s_instance = new MediaRenderer();
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
        Media media = null;

        if (baseCardElement instanceof Media)
        {
            media = (Media) baseCardElement;
        }
        else if ((media = Media.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Media object model.");
        }

        setSpacingAndSeparator(context, viewGroup, media.GetSpacing(), media.GetSeparator(), hostConfig, true);

        VideoView videoView = new VideoView(context);
        videoView.setTag(media);
        videoView.set


        TableLayout tableLayout = new TableLayout(context);
        tableLayout.setTag(factSet);
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
        long spacing = hostConfig.getFactSet().getSpacing();

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

            factRow.addView(createTextView(context, fact.GetTitle(), hostConfig.getFactSet().getTitle(), hostConfig, spacing, containerStyle));
            factRow.addView(createTextView(context, fact.GetValue(), hostConfig.getFactSet().getValue(), hostConfig, 0, containerStyle));
            tableLayout.addView(factRow);
        }



        return null;
    }

    private static MediaRenderer s_instance = null;
}
