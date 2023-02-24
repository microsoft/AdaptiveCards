// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer

import io.adaptivecards.renderer.typeaheadsearch.*

interface ITypeAheadRenderer {
    fun getSearchIconParams(): SearchIconParams

    fun getCrossIconParams(): CrossIconParams

    fun getTickIconParams(): TickIconParams

    fun getBackIconParams(): BackIconParams

    fun getStartSearchingStateParams(): StartSearchingStateParams

    fun getErrorStateParams(): ErrorStateParams

    fun getNoResultStateParams(): NoResultStateParams

    fun getScreenTitle(): String

    fun getPrimaryColor(): Int

    fun getSecondaryColor(): Int
}