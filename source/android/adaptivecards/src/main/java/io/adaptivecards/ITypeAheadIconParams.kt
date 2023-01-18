package io.adaptivecards

import android.widget.ImageView
import androidx.annotation.DrawableRes
import java.io.Serializable

interface ITypeAheadIconParams : Serializable {
    val drawableResourceId: Int
    val scaleType: ImageView.ScaleType
    val contentDescription: String
}

data class SearchIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.ic_baseline_search_24,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field"
) : ITypeAheadIconParams

data class CrossIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.ic_cross_mark,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Clear text button",
) : ITypeAheadIconParams





// <----------------------------------------------------------------------------------------------->
data class StartSearchingIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.ic_search,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "Search Options"
) : ITypeAheadIconParams

data class NoResultIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.ic_search,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "No Results Found!"
) : ITypeAheadIconParams

data class ErrorIconParams(
    @DrawableRes override val drawableResourceId: Int = R.drawable.ic_search,
    override val scaleType: ImageView.ScaleType = ImageView.ScaleType.FIT_START,
    override val contentDescription: String = "Search Field",
    val text: String = "Something went wrong"
) : ITypeAheadIconParams