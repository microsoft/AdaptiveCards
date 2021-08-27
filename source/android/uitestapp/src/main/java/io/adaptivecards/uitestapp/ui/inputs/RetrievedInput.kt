// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.inputs

class RetrievedInput(val id: String, val value: String) {
    override fun equals(obj: Any?): Boolean {
        if (obj is RetrievedInput) {
            val cmp = obj
            return (id.compareTo(cmp.id, ignoreCase = true) == 0
                    && value.compareTo(cmp.value, ignoreCase = true) == 0)
        }
        return false
    }
}
