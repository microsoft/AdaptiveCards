package io.adaptivecards.adaptivecardssample.CustomObjects.CardElements;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class CustomBlahRenderer extends BaseCardElementRenderer
{
    @Override
    public View render(RenderedAdaptiveCard renderedAdaptiveCard,
                       Context context,
                       FragmentManager fragmentManager,
                       ViewGroup viewGroup,
                       BaseCardElement baseCardElement,
                       ICardActionHandler cardActionHandler,
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
