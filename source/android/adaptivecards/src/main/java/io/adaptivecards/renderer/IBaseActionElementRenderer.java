// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import androidx.fragment.app.FragmentManager;
import android.view.ViewGroup;
import android.widget.Button;

import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.typeaheadsearch.IChoicesResolver;

public interface IBaseActionElementRenderer
{
    Button render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            ChannelAdaptor channelAdaptor,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws AdaptiveFallbackException;
}
