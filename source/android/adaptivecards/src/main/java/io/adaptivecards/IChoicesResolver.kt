package io.adaptivecards

import io.adaptivecards.objectmodel.BaseActionElement
import io.adaptivecards.renderer.RenderedAdaptiveCard

interface IChoicesResolver {
    fun getDynamicChoices(queryText: String
                          // choices.data
    ): List<String>
}
