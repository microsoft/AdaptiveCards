package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import android.app.Activity;
import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.ViewGroup;
import android.widget.Button;

import io.adaptivecards.adaptivecardssample.R;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class ShowCardOverrideRenderer extends BaseActionElementRenderer
{

    public ShowCardOverrideRenderer(Activity activity)
    {
        m_activity = activity;
    }

    @Override
    public Button render(RenderedAdaptiveCard renderedCard,
                         Context context,
                         FragmentManager fragmentManager,
                         ViewGroup viewGroup,
                         BaseActionElement baseActionElement,
                         ICardActionHandler cardActionHandler,
                         HostConfig hostConfig,
                         RenderArgs renderArgs)
    {
        Button button = new Button(context);

        button.setBackgroundColor(m_activity.getResources().getColor(R.color.yellowActionColor));
        button.setText(baseActionElement.GetTitle() +"(ShowCard)");

        button.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs));

        viewGroup.addView(button);
        return button;
    }

    private Activity m_activity;
}
