package io.adaptivecards.renderer.inputhandler;

import java.util.Map;

public interface IInputHandler
{
    Exception validate();
    Exception getData(Map<String, String> data);
}
