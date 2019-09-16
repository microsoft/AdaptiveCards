// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.content.res.AssetManager;
import android.os.AsyncTask;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class CardReaderTask extends AsyncTask<Void, Void, Card> {
    public CardReaderTask(String fileName, AssetManager assetManager, CardRetriever cardRetriever)
    {
        m_fileName = fileName;
        m_assetManager = assetManager;
        m_cardRetriever = cardRetriever;
    }

    private String readFile(String fileName, AssetManager assetManager) throws IOException
    {
        final int length = 128;
        byte[] buffer = new byte[length];

        int readBytes;
        InputStream inputStream = assetManager.open(fileName);
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        while((readBytes = inputStream.read(buffer, 0, length)) > 0)
        {
            outputStream.write(buffer, 0, readBytes);
        }
        return outputStream.toString();
    }

    @Override
    protected Card doInBackground(Void... voids)
    {
        try
        {
            Card parsedCard = new Card(m_fileName, readFile(m_fileName, m_assetManager));
            return parsedCard;
        }
        catch (Exception e)
        {
            return null;
        }
    }

    @Override
    protected void onPostExecute(Card card)
    {
        m_cardRetriever.addCard(card);
    }

    private String m_fileName;
    private AssetManager m_assetManager;
    private CardRetriever m_cardRetriever;
}
