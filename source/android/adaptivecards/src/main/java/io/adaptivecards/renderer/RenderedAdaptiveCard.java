// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.view.View;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.InternalId;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class RenderedAdaptiveCard {

    private View view;
    private Vector<AdaptiveWarning> warnings;
    private Vector<IInputHandler> handlers;
    private AdaptiveCard adaptiveCard;

    private Map<Long, Long> submitActionCard;
    private Map<Long, Vector<IInputHandler>> inputsInCard;
    private Map<Long, Long> parentCardForCard;
    private Map<String, String> prevalidatedInputs;

    private long m_lastClickedAction;

    protected RenderedAdaptiveCard(AdaptiveCard adaptiveCard)
    {
        this.warnings = new Vector<>();
        this.handlers = new Vector<>();
        this.adaptiveCard = adaptiveCard;

        this.submitActionCard = new HashMap<>();
        this.inputsInCard = new HashMap<>();
        this.parentCardForCard = new HashMap<>();
        this.prevalidatedInputs = new HashMap<>();
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

    public void registerInputHandler(IInputHandler handler, long cardId)
    {
        if (!inputsInCard.containsKey(cardId))
        {
            inputsInCard.put(cardId, new Vector<IInputHandler>());
        }
        inputsInCard.get(cardId).add(handler);

        handlers.add(handler);
    }

    public Map<String, String> getInputs()
    {
        return prevalidatedInputs;
    }

    public void setParentToCard(long cardId, long parentCardId)
    {
        parentCardForCard.put(cardId, parentCardId);
    }

    public void setCardForSubmitAction(long actionId, long parentCardId)
    {
        submitActionCard.put(actionId, parentCardId);
    }

    private Vector<IInputHandler> getInputsToValidate()
    {
        Long cardId = submitActionCard.get(m_lastClickedAction);
        Vector<IInputHandler> inputHandlers = new Vector<>();

        while ((cardId != null) && (cardId != View.NO_ID))
        {
            Vector<IInputHandler> handlersInCard = inputsInCard.get(cardId);

            if (handlersInCard != null)
            {
                inputHandlers.addAll(handlersInCard);
            }

            cardId = parentCardForCard.get(cardId);
        }

        return inputHandlers;
    }

    public boolean areInputsValid()
    {
        boolean allInputsAreValid = true;
        boolean hasSetFocusToElement = false;
        Map<String, String> validatedInputs = new HashMap<>();

        Vector<IInputHandler> inputsToValidate = getInputsToValidate();

        for(IInputHandler i : inputsToValidate)
        {
            // This variable is calculated out of the assignment as optimizations may make this code
            // not execute if allInputsAreValid is set to true
            allInputsAreValid &= i.isValid();

            // We populate the validated inputs only if all inputs are valid, otherwise, just save time
            if (allInputsAreValid)
            {
                validatedInputs.put(i.getId(), i.getInput());
            }

            if (!allInputsAreValid && !hasSetFocusToElement)
            {
                BaseInputHandler baseInputHandler = (BaseInputHandler) i;
                baseInputHandler.setFocusToView();
                hasSetFocusToElement = true;
            }
        }

        if (allInputsAreValid)
        {
            prevalidatedInputs = validatedInputs;
        }

        return allInputsAreValid;
    }

    public AdaptiveCard getAdaptiveCard()
    {
        return adaptiveCard;
    }

    public void setView(View view)
    {
        this.view = view;
    }

    protected void setLastClickedAction(View view)
    {
        m_lastClickedAction = Util.getViewId(view);
    }

    public void registerSubmitableAction(View renderedAction, RenderArgs renderArgs)
    {
        long actionId = Util.getViewId(renderedAction);
        setCardForSubmitAction(actionId, renderArgs.getContainerCardId());
    }

}
