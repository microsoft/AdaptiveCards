// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.actionhandler;

import java.util.List;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.renderer.RenderedAdaptiveCard;

public interface ICardActionHandler
{
    void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard);
    List<String> getDynamicChoices2(String queryText);
    void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard);
    void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard);
}
