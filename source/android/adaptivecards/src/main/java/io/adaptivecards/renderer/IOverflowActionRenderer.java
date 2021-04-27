// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;


import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;

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
     * @param menuItemList       list of view of rendered secondary action elements.
     * @param isRootLevelActions indicates action is part of root level actions or action set elements in body.
     * @return custom rendered view or null to render the default Overflow "..." action view.
     */
    default View onRenderOverflowAction(@NonNull ViewGroup viewGroup, @NonNull List<View> menuItemList, boolean isRootLevelActions)
    {
        return null;
    }

    /**
     * This implementation is invoked when Overflow action view ("...") is pressed and rendered secondary view elements will be shown.
     *
     * @param menuItemList list of view of rendered secondary action elements.
     * @param view           Overflow action view.
     * @return false will show the elements in default {@link android.widget.PopupWindow}, while true indicates client can customize the display behaviour.
     */
    default boolean onDisplayOverflowActionMenu(@NonNull List<View> menuItemList, @NonNull View view)
    {
        return false;
    }


    /**
     * This implementation indicates whether to add the excess elements (i.e id primary elements exceeds the MaxActions) to the secondary elements or not.
     *
     * @return false not to add the excess elements to the secondary elements, otherwise true.
     */
    default boolean shouldAllowMoreThanMaxActionsInOverflowMenu()
    {
        return false;
    }
}
