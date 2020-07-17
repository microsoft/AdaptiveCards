// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;


public interface IInputHandler
{
    String getId();
    String getInput();
    void setInput(String input);

    boolean isValid();
    void setFocusToView();
}
