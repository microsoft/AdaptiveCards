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

    /**
     * Registers an input handler with the card where it is located.
     * @param handler Input handler to be registered
     * @param renderArgs RenderArgs passed as parameter in the render method
     */
    public void registerInputHandler(IInputHandler handler, RenderArgs renderArgs)
    {
        registerInputHandler(handler, renderArgs.getContainerCardId());
    }

    /**
     * Registers an input handler with the card where it is located.
     * @param handler Input handler to be registered.
     * @param cardId Card id where the input is located. This value can be retrieved from RenderArgs.getContainerCardId()
     */
    public void registerInputHandler(IInputHandler handler, long cardId)
    {
        if (!inputsInCard.containsKey(cardId))
        {
            inputsInCard.put(cardId, new Vector<IInputHandler>());
        }
        inputsInCard.get(cardId).add(handler);

        handlers.add(handler);
    }

    /**
     * Retrieves the map of validated inputs. The map entries contain the input id as key and the retrieved value.
     * @return A populated map of the retrieved inputs if the input validation succeeded, an empty map otherwise.
     */
    public Map<String, String> getInputs()
    {
        return prevalidatedInputs;
    }

    /**
     * Sets a hierarchical relation between two cards. A card 'P' contains another card 'C' if 'C' is located
     * in a ShowCard action in the 'actions' section of the card or in an ActionSet in card 'P'.
     * @param cardId Card contained by parent card.
     * @param parentCardId Card that contains the child card.
     */
    public void setParentToCard(long cardId, long parentCardId)
    {
        parentCardForCard.put(cardId, parentCardId);
    }

    /**
     * Sets a hierarchical relation between an action and a card. A card 'C' contains an action 'A' if 'A' is located
     * in the 'actions' section of the card or in an ActionSet in card 'C'.
     * @param actionId Id for the action contained in the card.
     * @param parentCardId Id for the container card
     */
    public void setCardForSubmitAction(long actionId, long parentCardId)
    {
        submitActionCard.put(actionId, parentCardId);
    }

    private Vector<IInputHandler> getInputsToValidate(long clickedActionId)
    {
        Long cardId = submitActionCard.get(clickedActionId);
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

    protected boolean areInputsValid(long actionId)
    {
        boolean allInputsAreValid = true;
        boolean hasSetFocusToElement = false;
        Map<String, String> validatedInputs = new HashMap<>();

        Vector<IInputHandler> inputsToValidate = getInputsToValidate(actionId);

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

    /**
     * Registers an action so input retrieval can be performed when the action is clicked
     * @param renderedAction View where the action listener has been set
     * @param renderArgs RenderArgs passed as a parameter from the render method
     */
    public void registerSubmitableAction(View renderedAction, RenderArgs renderArgs)
    {
        long actionId = Util.getViewId(renderedAction);
        setCardForSubmitAction(actionId, renderArgs.getContainerCardId());
    }

    protected boolean isActionSubmitable(View action)
    {
        long actionId = action.getId();
        return submitActionCard.containsKey(actionId);
    }

}
