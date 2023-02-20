// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer

import io.adaptivecards.renderer.typeaheadsearch.*

interface ITypeAheadRenderer {
    fun getSearchIconParams(): SearchIconParams? {
        return SearchIconParams()
    }

    fun getCrossIconParams(): CrossIconParams? {
        return CrossIconParams()
    }

    fun getTickIconParams(): TickIconParams? {
        return TickIconParams()
    }

    fun getBackIconParams(): BackIconParams? {
        return BackIconParams()
    }

    fun getStartSearchingStateParams(): StartSearchingStateParams? {
        return StartSearchingStateParams()
    }

    fun getErrorStateParams(): ErrorStateParams? {
        return ErrorStateParams()
    }

    fun getNoResultStateParams(): NoResultStateParams? {
        return NoResultStateParams()
    }

    fun getScreenTitle(): String? {
        return ""
    }
}