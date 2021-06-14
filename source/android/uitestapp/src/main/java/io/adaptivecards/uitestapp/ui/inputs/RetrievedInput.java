// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.inputs;

import androidx.annotation.Nullable;

public class RetrievedInput
{
    private String mId;
    private String mValue;

    public RetrievedInput(String id, String value)
    {
        mId = id;
        mValue = value;
    }

    public String getId()
    {
        return mId;
    }

    public String getValue()
    {
        return mValue;
    }

    @Override
    public boolean equals(@Nullable Object obj)
    {
        if (obj instanceof RetrievedInput)
        {
            RetrievedInput cmp = (RetrievedInput) obj;
            return (mId.compareToIgnoreCase(cmp.getId()) == 0)
                && (mValue.compareToIgnoreCase(cmp.getValue()) == 0);
        }

        return false;
    }
}
