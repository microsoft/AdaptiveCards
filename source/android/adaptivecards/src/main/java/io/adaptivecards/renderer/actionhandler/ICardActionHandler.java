// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.actionhandler;

import java.util.List;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.http.HttpRequestResult;

public interface ICardActionHandler
{
    void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard);
    HttpRequestResult<List<ChoiceInput>> getDynamicChoices(String queryText);
    void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard);
    void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard);
}
