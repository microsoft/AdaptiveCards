package com.microsoft.adaptivecards.renderer.actionhandler;

import com.microsoft.adaptivecards.objectmodel.SubmitAction;

import java.util.Map;

/**
 * Created by bekao on 6/30/2017.
 */

public interface ISubmitActionHandler
{
    void onSubmit(SubmitAction submitAction, Map<String, String> keyValueMap);
}
