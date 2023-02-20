package io.adaptivecards.adaptivecardssample.CustomObjects.CardElements;

import android.content.Context;
import androidx.fragment.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.ChannelAdaptor;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;

public class CustomBlahRenderer extends BaseCardElementRenderer
{
    @Override
    public View render(RenderedAdaptiveCard renderedAdaptiveCard,
                       Context context,
                       FragmentManager fragmentManager,
                       ViewGroup viewGroup,
                       BaseCardElement baseCardElement,
                       ChannelAdaptor channelAdaptor,
                       HostConfig hostConfig,
                       RenderArgs renderArgs)
    {
        TextView textView = new TextView(context);

        CustomCardElement element = (CustomCardElement) baseCardElement.findImplObj();

        textView.setText(element.getSecretString());

        textView.setAllCaps(true);

        viewGroup.addView(textView);

        return textView;
    }
}
