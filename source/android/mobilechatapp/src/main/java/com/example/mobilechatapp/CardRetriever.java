// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.content.Context;
import android.content.res.AssetManager;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class CardRetriever
{

    private CardRetriever()
    {
    }

    public void setFilesReadListener(IFilesReadListener filesReadListener)
    {
        m_filesReadListener = filesReadListener;
    }

    private boolean isJsonFile(String fileName)
    {
        return fileName.endsWith(".json");
    }

    public void populateCardJsons(Context context)
    {
        s_cardJsons = Collections.synchronizedList(new ArrayList<Card>());
        final AssetManager assetManager = context.getAssets();
        try
        {
            String[] files = assetManager.list("");
            int fileCount = files.length;
            for(String fileName : files)
            {
                if(!isJsonFile(fileName))
                {
                    fileCount--;
                }
            }

            m_filesReadListener.setFilesCount(fileCount);
            for(String fileName : files)
            {
                if(isJsonFile(fileName))
                {
                    new CardReaderTask(fileName, assetManager, this).execute();
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    public static CardRetriever getInstance()
    {
        if(s_instance == null)
        {
            s_instance = new CardRetriever();
        }
        return s_instance;
    }

    public Card getCard(int i)
    {
        return s_cardJsons.get(i);
    }

    public Card getRandomCard()
    {
        return getCard(Utils.getRandom(0, s_cardJsons.size()));
    }

    // This search shall be pretty much basic:
    // We should receive something similar to "(all[default] | random | number)? (all[default] | Elemennt Type Name)?"
    public List<Card> searchCards(String query)
    {
        List<Card> results = new ArrayList<>();
        String[] parts = query.trim().split(" ");
        int partsLength = parts.length;
        if(partsLength == 0)
        {
            results = getAllCards();
        }
        else
        {
            String secondSection = parts[partsLength - 1].toLowerCase();
            FirstSectionValue firstSectionValue = parseFirstSection(parts[0]);
            SecondSectionValue secondSectionValue = parseSecondSection(secondSection);

            int cardNumber = 0;
            if(firstSectionValue == FirstSectionValue.number)
            {
                cardNumber = Utils.parseSafeNumber(parts[0]);
            }

            if (partsLength == 1)
            {
                if(firstSectionValue != FirstSectionValue.notUnderstood)
                {
                    if (firstSectionValue == FirstSectionValue.random)
                    {
                        results.add(getRandomCard());
                    }
                    else if(firstSectionValue == FirstSectionValue.number)
                    {
                        results.add(getCard(cardNumber));
                    }
                    else
                    {
                        results = getAllCards();
                    }
                }
                else if (secondSectionValue != SecondSectionValue.notUnderstood)
                {
                    results = searchAllByType(secondSection);
                }
                else
                {
                    // Not understood in any way, what let's do nothing
                }
            }
            else // As of this time we only care that the Card has a given element type in it
            {
                if(firstSectionValue == FirstSectionValue.random)
                {
                    if( secondSectionValue == SecondSectionValue.elementTypeName )
                    {
                        List<Card> cards = searchAllByType(secondSection);
                        results.add( cards.get(Utils.getRandom(0, cards.size())) );
                    }
                    else
                    {
                        results.add(getRandomCard());
                    }
                }
                else if( firstSectionValue == FirstSectionValue.number )
                {
                    if( secondSectionValue == SecondSectionValue.elementTypeName )
                    {
                        List<Card> cards = searchAllByType(secondSection);
                        results.add(cards.get(cardNumber));
                    }
                    else
                    {
                        results.add(getCard(cardNumber));
                    }
                }
                else if( firstSectionValue == FirstSectionValue.all && secondSectionValue == SecondSectionValue.all )
                {
                    results = getAllCards();
                }
            }
        }

        return results;
    }

    private List<Card> searchAllByType(String elementType)
    {
        List<Card> allCards = getAllCards();
        List<Card> validCards = new ArrayList<>();

        elementType = elementType.toLowerCase();
        for(Card card : allCards)
        {
            if( card.ContainsElementType(elementType) )
            {
                validCards.add(card);
            }
        }

        return validCards;
    }

    private FirstSectionValue parseFirstSection(String firstSectionString)
    {
        if(firstSectionString == null)
        {
            return FirstSectionValue.notUnderstood;
        }

        if( firstSectionString.isEmpty() )
        {
            return FirstSectionValue.all;
        }

        FirstSectionValue value = FirstSectionValue.notUnderstood;
        if( firstSectionString.compareToIgnoreCase("all") == 0 )
        {
            value = FirstSectionValue.all;
        }
        else if( (firstSectionString.compareToIgnoreCase("random") == 0) ||
                (firstSectionString.compareToIgnoreCase("R") == 0 ) )
        {
            value = FirstSectionValue.random;
        }
        else
        {
            try
            {
                Integer.parseInt(firstSectionString);
                value = FirstSectionValue.number;
            }
            catch (Exception e) { /* Do nothing, it just isn's a number */ }
        }

        return value;
    }

    private SecondSectionValue parseSecondSection(String secondSectionString)
    {
        if(secondSectionString == null)
        {
            return SecondSectionValue.notUnderstood;
        }

        if(secondSectionString.isEmpty())
        {
            return SecondSectionValue.all;
        }

        if(s_cardElements.contains(secondSectionString))
        {
            return SecondSectionValue.elementTypeName;
        }

        return SecondSectionValue.notUnderstood;
    }

    public List<Card> getAllCards()
    {
        return s_cardJsons;
    }

    public void registerExistingCardElementType(String elementType)
    {
        s_cardElements.add(elementType);
    }

    public Set<String> getCardElements()
    {
        return s_cardElements;
    }

    public void addCard(Card card)
    {
        s_cardJsons.add(card);
        m_filesReadListener.updateFilesCompletion();
    }

    private IFilesReadListener m_filesReadListener = null;
    private static List<Card> s_cardJsons = null;
    private static CardRetriever s_instance = null;
    private static Set<String> s_cardElements = new TreeSet<>();
    private enum FirstSectionValue { all, random, number, notUnderstood }
    private enum SecondSectionValue { all, elementTypeName, notUnderstood }

}
