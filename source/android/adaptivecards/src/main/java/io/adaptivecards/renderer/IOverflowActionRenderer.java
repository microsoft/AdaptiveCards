// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.support.annotation.NonNull;
import android.view.View;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BaseActionElementVector;

/**
 * Responsible for customizing the overflow action rendering behavior.
 */
public interface IOverflowActionRenderer {

    /**
     * This implementation renders an Overflow action view.
     * @param actionElements secondary action elements list to be displayed on menu.
     * @param viewGroup container view for the rendered view to be attached (optional).
     * @param isRootLevelActions indicates action is part of root level actions or action set elements in body.
     * @return false to let the SDK render the "..." action, while true to render custom Overflow action..
     */
    boolean onRenderOverflowAction(@NonNull BaseActionElementVector actionElements, @NonNull ViewGroup viewGroup, boolean isRootLevelActions);

    /**
     * This implementation displays menu for secondary actions.
     * @param actionElements secondary action elements list displayed on the menu
     * @param view Overflow action view.
     * @return false to show the default {@link android.support.design.widget.BottomSheetDialog}, while true to display customized action menu.
     */
    boolean onDisplayOverflowActionMenu(@NonNull BaseActionElementVector actionElements, @NonNull View view);

}
