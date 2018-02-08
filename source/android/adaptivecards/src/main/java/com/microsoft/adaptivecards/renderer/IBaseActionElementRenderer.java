package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.ViewGroup;
import android.widget.Button;

import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

import java.util.Vector;

public interface IBaseActionElementRenderer
{
    Button render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            Vector<IInputHandler> inputHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig);
}
