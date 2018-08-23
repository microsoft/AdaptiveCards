package io.adaptivecards.renderer.inputhandler;

import io.adaptivecards.renderer.RenderedAdaptiveCard;

public interface IInputWatcher {
    public void onInputChange(String id, String value);
}
