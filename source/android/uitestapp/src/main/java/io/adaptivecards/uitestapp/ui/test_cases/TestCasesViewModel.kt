// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.test_cases

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class TestCasesViewModel : ViewModel() {
    private val mLastClickedItem: MutableLiveData<String>

    fun setLastClickedItem(s: String) {
        mLastClickedItem.value = s
    }

    val lastClickedItem: LiveData<String>
        get() = mLastClickedItem

    init {
        mLastClickedItem = MutableLiveData()
    }
}
