// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

import android.text.Editable
import android.text.TextWatcher
import androidx.lifecycle.LifecycleCoroutineScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

/**
 * TextWatcher with debouncing capability.
 */
class DebouncingTextWatcher(
    private val coroutineScope: LifecycleCoroutineScope,
    private val onDebouncingSearchTextChange: (String) -> Unit,
    private val delayTime: Long
) : TextWatcher {
    private var debouncingSearchJob: Job? = null

    override fun afterTextChanged(s: Editable) {
        debouncingSearchJob?.cancel()
        debouncingSearchJob = coroutineScope.launch {
            delay(delayTime)
            onDebouncingSearchTextChange(s.toString())
        }
    }

    override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
    }

    override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
    }
}
