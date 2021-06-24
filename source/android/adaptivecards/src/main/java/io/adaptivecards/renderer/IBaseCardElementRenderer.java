// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.FragmentManager;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public interface IBaseCardElementRenderer
{
    View render(
            @NonNull RenderedAdaptiveCard renderedCard,
            @NonNull Context context,
            @NonNull FragmentManager fragmentManager,
            @NonNull ViewGroup viewGroup,
            @NonNull BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            @NonNull HostConfig hostConfig,
            @NonNull RenderArgs renderArgs) throws Exception;
}
