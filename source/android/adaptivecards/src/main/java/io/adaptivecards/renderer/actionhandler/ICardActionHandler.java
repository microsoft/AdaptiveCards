package io.adaptivecards.renderer.actionhandler;

import io.adaptivecards.objectmodel.BaseActionElement;

import java.util.Map;

public interface ICardActionHandler
{
    void onAction(BaseActionElement action, Map<String, String> inputData);
}
