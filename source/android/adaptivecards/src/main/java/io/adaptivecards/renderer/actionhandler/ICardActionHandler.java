package io.adaptivecards.renderer.actionhandler;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.renderer.RenderedAdaptiveCard;

public interface ICardActionHandler
{
    void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard);
}
