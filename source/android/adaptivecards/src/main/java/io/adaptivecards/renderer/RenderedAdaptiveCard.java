// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.view.View;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class RenderedAdaptiveCard {

    private View view;
    private Vector<AdaptiveWarning> warnings;
    private Vector<IInputHandler> handlers;
    private AdaptiveCard adaptiveCard;

    protected RenderedAdaptiveCard(AdaptiveCard adaptiveCard)
    {
        this.warnings = new Vector<>();
        this.handlers = new Vector<>();
        this.adaptiveCard = adaptiveCard;
    }

    public View getView()
    {
        return view;
    }

    public void addWarning(AdaptiveWarning warning)
    {
        warnings.add(warning);
    }

    public Vector<AdaptiveWarning> getWarnings()
    {
        return warnings;
    }

    public void registerInputHandler(IInputHandler handler)
    {
        handlers.add(handler);
    }

    public Map<String, String> getInputs()
    {
        HashMap<String, String> input = new HashMap<>();
        for(IInputHandler i : handlers)
        {
            input.put(i.getId(), i.getInput());
        }
        return input;
    }

    public void setInputs(Map<String, String> inputs)
    {
        if (inputs == null || inputs.isEmpty())
        {
            return;
        }
        //Iterate over all handlers
        for (IInputHandler handler: handlers)
        {
            if (inputs.containsKey(handler.getId()))
            {
                handler.setInput(inputs.get(handler.getId()));
            }
        }
    }

    public AdaptiveCard getAdaptiveCard()
    {
        return adaptiveCard;
    }

    public void setView(View view) {
        this.view = view;
    }
}
