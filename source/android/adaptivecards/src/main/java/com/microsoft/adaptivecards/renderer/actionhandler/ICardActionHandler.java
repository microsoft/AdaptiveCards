package com.microsoft.adaptivecards.renderer.actionhandler;

import com.microsoft.adaptivecards.objectmodel.BaseActionElement;

import java.util.Map;

public interface ICardActionHandler
{
    void onAction(BaseActionElement action, Map<String, String> inputData);
}
