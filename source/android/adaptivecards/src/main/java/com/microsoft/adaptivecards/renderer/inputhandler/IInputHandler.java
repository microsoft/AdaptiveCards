package com.microsoft.adaptivecards.renderer.inputhandler;

import java.util.Map;

/**
 * Created by bekao on 6/30/2017.
 */

public interface IInputHandler
{
    Exception validate();
    Exception getData(Map<String, String> data);
}
