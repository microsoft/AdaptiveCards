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
     * @param parent view to be the parent of the rendered view if attachToRoot is true.
     * @return rendered view.
     */
    View onRenderOverflowAction(@NonNull BaseActionElementVector actionElements, @NonNull ViewGroup parent);

    /**
     * This implementation displays menu for secondary actions.
     * @param actionElements secondary action elements list displayed on the menu
     * @param view Overflow action view.
     * @return default {@link android.support.design.widget.BottomSheetDialog} will be shown if returned false.
     */
    boolean onDisplayOverflowActionMenu(@NonNull BaseActionElementVector actionElements, @NonNull View view);

    /**
     * This implementation indicates if the current "..." overflow action belongs to root level actions array. If it's false then it indicates it's ActionSet as body elements.
     * @return true
     */
    boolean isRootLevelActions();
}
