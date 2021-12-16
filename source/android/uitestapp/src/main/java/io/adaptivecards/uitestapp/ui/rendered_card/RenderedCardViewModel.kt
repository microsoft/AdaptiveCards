// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.rendered_card

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput

import androidx.test.espresso.idling.CountingIdlingResource

class RenderedCardViewModel : ViewModel() {
    val inputs: MutableLiveData<List<RetrievedInput>>
    val idlingResource: MutableLiveData<CountingIdlingResource>

    init {
        inputs = MutableLiveData()
        idlingResource = MutableLiveData(CountingIdlingResource("filteredChoiceSetIdlingResource"))
    }
}
