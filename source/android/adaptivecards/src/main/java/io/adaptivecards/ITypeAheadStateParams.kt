package io.adaptivecards

import android.widget.ImageView

interface ITypeAheadStateParams: ITypeAheadIconParams {
    val text: String
}

data class StartSearchingStateParams(
    override val drawableResourceId: Int = android.R.drawable.ic_search_category_default,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Start searching state",
    override val text: String = "Search Options"
): ITypeAheadStateParams

data class NoResultStateParams(
    override val drawableResourceId: Int = android.R.drawable.ic_dialog_alert,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "No result state",
    override val text: String = "No Results Found!"
): ITypeAheadStateParams

data class ErrorStateParams(
    override val drawableResourceId: Int = android.R.drawable.ic_dialog_alert,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Error State",
    override val text: String = "Something went wrong"
): ITypeAheadStateParams