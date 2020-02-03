// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public interface IActionLayoutRenderer {
    public View renderActions(RenderedAdaptiveCard renderedCard,
                              Context context,
                              FragmentManager fragmentManager,
                              ViewGroup viewGroup,
                              BaseActionElementVector baseActionElementList,
                              ICardActionHandler cardActionHandler,
                              HostConfig hostConfig,
                              RenderArgs renderArgs) throws AdaptiveFallbackException;
}
