package io.adaptivecards.renderer.typeaheadsearch

import android.widget.ImageView
import androidx.annotation.DrawableRes
import io.adaptivecards.R

interface ITypeAheadStateParams: ITypeAheadIconParams {
    val text: String
}

data class StartSearchingStateParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_start_search,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Start searching state",
    override val text: String = "Search Options"
): ITypeAheadStateParams

data class NoResultStateParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_ic_start_search,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "No result state",
    override val text: String = "No Results Found!"
): ITypeAheadStateParams

data class ErrorStateParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.adaptive_card_search_result_error,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Error State",
    override val text: String = "Something went wrong"
): ITypeAheadStateParams
