// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

import androidx.annotation.DrawableRes
import io.adaptivecards.R
import java.io.Serializable

interface ITypeAheadIconParams : Serializable {
    val drawableResourceId: Int
    val contentDescription: String
}

data class SearchIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_baseline_search_24,
    override val contentDescription: String = "Search Field"
) : ITypeAheadIconParams

data class CrossIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_cross_mark,
    override val contentDescription: String = "Clear text button",
) : ITypeAheadIconParams

data class BackIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_left_arrow,
    override val contentDescription: String = "Back button",
) : ITypeAheadIconParams

data class TickIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_tick_mark,
    override val contentDescription: String = "Done button",
) : ITypeAheadIconParams