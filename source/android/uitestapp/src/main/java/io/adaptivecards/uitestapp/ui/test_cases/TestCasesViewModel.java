// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.test_cases;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class TestCasesViewModel extends ViewModel
{
    private MutableLiveData<String> mLastClickedItem;

    public TestCasesViewModel()
    {
        mLastClickedItem = new MutableLiveData<>();
    }

    public void setLastClickedItem(String s)
    {
        mLastClickedItem.setValue(s);
    }

    public LiveData<String> getLastClickedItem()
    {
        return mLastClickedItem;
    }
}
