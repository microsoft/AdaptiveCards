package com.microsoft.adaptivecards.renderer.actionhandler;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.ShowCardAction;

/**
 * Created by bekao on 7/1/2017.
 */

public interface IShowCardActionHandler
{
    void onShowCard(ShowCardAction showCardAction, AdaptiveCard adaptiveCard);
}
