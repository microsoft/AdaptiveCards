// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.support.annotation.NonNull;
import android.view.View;
import android.view.ViewGroup;

import java.util.List;

import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.renderer.action.DropdownElementRenderer;

/**
 * Responsible for customizing the overflow action rendering behavior.
 */
public interface IOverflowActionRenderer {

    /**
     * This implementation renders an Overflow action view.
     *
     * @param viewGroup          container view for the rendered view to be attached.
     * @param isRootLevelActions indicates action is part of root level actions or action set elements in body.
     * @return custom rendered view or null to render the default Overflow "..." action view.
     */
    View onRenderOverflowAction(@NonNull ViewGroup viewGroup, boolean isRootLevelActions);

    /**
     * This implementation is invoked when {@link IOverflowActionRenderer#shouldDisplayCustomOverflowActionMenu()} is true, then rendered secondary view elements can be shown by the client.
     *
     * @param actionViewList list of view of rendered secondary action elements.
     * @param view           Overflow action view.
     */
    void onDisplayOverflowActionMenu(@NonNull List<View> actionViewList, @NonNull View view);


    /**
     * This implementation indicates whether to show default {@link android.support.design.widget.BottomSheetDialog} or to invoke {@link IOverflowActionRenderer#onDisplayOverflowActionMenu(List, View)} based on the returned flag.
     *
     * @return false to show the default {@link android.support.design.widget.BottomSheetDialog}, while true to display customized action menu.
     */
    boolean shouldDisplayCustomOverflowActionMenu();

}
