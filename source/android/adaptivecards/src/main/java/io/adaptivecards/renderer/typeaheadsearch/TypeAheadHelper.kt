package io.adaptivecards.renderer.typeaheadsearch

import android.graphics.Typeface
import android.text.Html
import android.text.SpannableString
import android.text.SpannableStringBuilder
import android.text.Spanned
import android.text.style.BackgroundColorSpan
import android.text.style.ForegroundColorSpan
import android.text.style.StyleSpan
import androidx.annotation.ColorInt
import java.util.*
import java.util.regex.PatternSyntaxException

object TypeAheadHelper {
    fun createHighlightedSearchResultText(
        text: String?, highlightTexts: Array<String>?, @ColorInt backgroundColor: Int,
        @ColorInt highlightTextColor: Int
    ): Spanned {
        if (text != null && text.isEmpty()) {
            return SpannableString("")
        }
        val lowerCaseHighlightTexts: MutableList<String> = ArrayList()
        if (highlightTexts != null) {
            for (highlightText in highlightTexts) {
                if (highlightText.isNotBlank() && highlightText.isNotEmpty()) {
                    lowerCaseHighlightTexts.add(highlightText.lowercase(Locale.getDefault()))
                }
            }
        }
        return if (lowerCaseHighlightTexts.size == 0) {
            Html.fromHtml(text)
        } else try {
            val spannableText = SpannableStringBuilder(text)
            for (lowerQuery in lowerCaseHighlightTexts) {
                highlightSpannableText(
                    spannableText,
                    lowerQuery,
                    backgroundColor,
                    highlightTextColor
                )
            }
            spannableText
        } catch (ignored: PatternSyntaxException) {
            // as the user can input any string - it might lead to an invalid regex. in such case - do not highlight
            Html.fromHtml(text)
        } catch (ignored: IndexOutOfBoundsException) {
            // in rare cases the index can be out of bound when setting span. in such case - do not highlight
            Html.fromHtml(text)
        }
    }

    private fun highlightSpannableText(
        spannableText: SpannableStringBuilder, lowerQuery: String, @ColorInt backgroundColor: Int,
        @ColorInt highlightTextColor: Int
    ) {
        val lowerText = spannableText.toString().lowercase(Locale.getDefault())
        val length = lowerQuery.length
        var idx = lowerText.indexOf(lowerQuery)
        while (idx != -1) {
            val span = StyleSpan(Typeface.BOLD)
            spannableText.setSpan(span, idx, idx + length, Spanned.SPAN_EXCLUSIVE_EXCLUSIVE)
            spannableText.setSpan(
                BackgroundColorSpan(backgroundColor),
                idx,
                idx + length,
                Spanned.SPAN_EXCLUSIVE_EXCLUSIVE
            )
            if (highlightTextColor != 0) {
                spannableText.setSpan(
                    ForegroundColorSpan(highlightTextColor),
                    idx,
                    idx + length,
                    Spanned.SPAN_EXCLUSIVE_EXCLUSIVE
                )
            }
            idx = lowerText.indexOf(lowerQuery, idx + 1)
        }
    }
}