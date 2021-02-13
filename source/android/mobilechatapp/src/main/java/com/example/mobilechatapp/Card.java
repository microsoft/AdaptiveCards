// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.view.View;

import java.io.IOException;
import java.lang.annotation.ElementType;
import java.util.HashSet;
import java.util.Set;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.ColumnSet;
import io.adaptivecards.objectmodel.ColumnVector;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSet;
import io.adaptivecards.objectmodel.ImageVector;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.objectmodel.ParseResult;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.renderer.AdaptiveCardRenderer;

/**
 * Created by almedina on 8/17/2018.
 */

public class Card
{

    public Card(String filename, String fullCard)
    {
        m_filename = filename;
        fillElementTypes(fullCard);
    }

    private void fillElementTypes(String fullCardString)
    {
        m_elementTypes = new HashSet<>();

        try
        {
            ParseContext context = new ParseContext(null, null);
            m_parsedCard = AdaptiveCard.DeserializeFromString(fullCardString, AdaptiveCardRenderer.VERSION, context);
            if(m_parsedCard != null)
            {
                fillElementTypes(m_parsedCard.GetAdaptiveCard());
            }
        }
        catch (Exception e)
        {
            m_exceptionDetailMessage = e.getMessage();
        }

        // Register all the types found into the bigger dictionary of existing element types
        for(String elementType : m_elementTypes)
        {
            CardRetriever.getInstance().registerExistingCardElementType(elementType);
        }
    }

    private void fillElementTypes(AdaptiveCard adaptiveCard)
    {
        if(adaptiveCard == null)
        {
            return;
        }

        fillElementTypes(adaptiveCard.GetBody());
        fillElementTypes(adaptiveCard.GetActions());
    }

    private void fillElementTypes(BaseCardElementVector elements)
    {
        if(elements == null)
        {
            return;
        }

        final int elementsInCardCount = (int)elements.size();
        for(int i = 0; i < elementsInCardCount; i++)
        {
            BaseCardElement element = elements.get(i);
            addElementToElementTypes(element.GetElementTypeString());
            fillElementTypes(element);
        }
    }

    private void fillElementTypes(BaseCardElement containerElement)
    {
        if(containerElement.GetElementType() == CardElementType.ColumnSet)
        {
            ColumnSet columnSet = null;
            if (containerElement instanceof ColumnSet)
            {
                columnSet = (ColumnSet)containerElement;
            }
            else if ((columnSet = ColumnSet.dynamic_cast(containerElement)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            fillElementTypes(columnSet);
        }
        else if(containerElement.GetElementType() == CardElementType.Container)
        {
            Container container = null;
            if (containerElement instanceof Container)
            {
                container = (Container) containerElement;
            }
            else if ((container = Container.dynamic_cast(containerElement)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            fillElementTypes(container);
        }
        else if(containerElement.GetElementType() == CardElementType.ImageSet)
        {
            ImageSet imageSet = null;
            if (containerElement instanceof ImageSet)
            {
                imageSet = (ImageSet) containerElement;
            }
            else if ((imageSet = ImageSet.dynamic_cast(containerElement)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            fillElementTypes(imageSet);
        }
    }

    private void fillElementTypes(Container container)
    {
        if(container == null)
        {
            return;
        }

        fillElementTypes(container.GetItems());
    }

    private void fillElementTypes(ColumnSet columnSet)
    {
        if(columnSet == null)
        {
            return;
        }

        ColumnVector columns = columnSet.GetColumns();
        final int columnsCount = (int)columns.size();
        for(int i = 0; i < columnsCount; i++)
        {
            Column column = columns.get(i);
            addElementToElementTypes(column.GetElementTypeString());
            fillElementTypes(column.GetItems());
        }
    }

    private void fillElementTypes(ImageSet imageSet)
    {
        if(imageSet == null)
        {
            return;
        }

        ImageVector imageVector = imageSet.GetImages();
        if(!imageVector.isEmpty())
        {
            addElementToElementTypes(imageVector.get(0).GetElementTypeString());
        }
    }

    private void fillElementTypes(BaseActionElementVector actions)
    {
        final int actionsCount = (int)actions.size();
        for(int i = 0; i < actionsCount; i++)
        {
            BaseActionElement action = actions.get(i);
            addElementToElementTypes(action.GetElementTypeString());

            if(action.GetElementType() == ActionType.ShowCard)
            {
                ShowCardAction showCardAction = null;
                if (action instanceof ShowCardAction)
                {
                    showCardAction = (ShowCardAction) action;
                }
                else if ((showCardAction = ShowCardAction.dynamic_cast(action)) == null)
                {
                    throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
                }

                fillElementTypes(showCardAction.GetCard());
            }
        }
    }

    public ParseResult getParsedCard()
    {
        return m_parsedCard;
    }

    public String getFileName()
    {
        return m_filename;
    }

    public String getExceptionDetailMessage()
    {
        return m_exceptionDetailMessage;
    }

    private void addElementToElementTypes(String elementType)
    {
        m_elementTypes.add(elementType.toLowerCase());
    }

    public boolean ContainsElementType(String elementType)
    {
        return m_elementTypes.contains(elementType);
    }

    private ParseResult m_parsedCard;
    private Set<String> m_elementTypes;
    private String m_filename;
    private String m_exceptionDetailMessage;
}
