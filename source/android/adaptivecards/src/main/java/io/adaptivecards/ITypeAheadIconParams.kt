package io.adaptivecards

import android.widget.ImageView
import java.io.Serializable

interface ITypeAheadIconParams : Serializable {
    val drawableResourceId: Int
    val scaleType: ImageView.ScaleType
    val contentDescription: String
}

data class SearchIconParams(
    override val drawableResourceId: Int = android.R.drawable.ic_search_category_default,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field"
) : ITypeAheadIconParams

data class CrossIconParams(
    override val drawableResourceId: Int = android.R.drawable.ic_menu_close_clear_cancel,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Clear text button"
) : ITypeAheadIconParams





// <----------------------------------------------------------------------------------------------->
data class StartSearchingIconParams(
    override val drawableResourceId: Int = android.R.drawable.ic_search_category_default,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "Search Options"
) : ITypeAheadIconParams

data class NoResultIconParams(
    override val drawableResourceId: Int = android.R.drawable.ic_dialog_alert,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "No Results Found!"
) : ITypeAheadIconParams

data class ErrorIconParams(
    override val drawableResourceId: Int = android.R.drawable.ic_dialog_alert,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "Something went wrong"
) : ITypeAheadIconParams