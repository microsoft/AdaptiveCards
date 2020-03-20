package io.adaptivecards.renderer.inputhandler.validation;

import android.view.View;

import java.util.List;

public interface IInputValidator
{
    boolean isValid();

    void setViewForValidation(View v);
    List<View> getViewsForValidation();
}
