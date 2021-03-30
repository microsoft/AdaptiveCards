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
     */
    void onDisplayOverflowActionMenu(@NonNull BaseActionElementVector actionElements, @NonNull View view);

    /**
     * This implementation indicates if the current "..." overflow action belongs to root level actions array. If it's false then it indicates it's ActionSet as body elements.
     * @return true for Root Level Action otherwise false.
     */
    @SuppressWarnings("BooleanMethodIsAlwaysInverted")
    boolean isRootLevelActions();

    /**
     * This implementation indicates whether to display custom action menu or not. if true then display the customized action menu otherwise display the default {@link android.support.design.widget.BottomSheetDialog}.
     * @return true displays customized action menu otherwise default {@link android.support.design.widget.BottomSheetDialog}
     */
    boolean shouldDisplayCustomActionMenu();
}
