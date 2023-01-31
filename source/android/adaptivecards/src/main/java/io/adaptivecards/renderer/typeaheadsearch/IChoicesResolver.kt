package io.adaptivecards.renderer.typeaheadsearch

import io.adaptivecards.objectmodel.ChoiceInput
import io.adaptivecards.renderer.http.HttpRequestResult

interface IChoicesResolver {
    fun getDynamicChoices(type: String,
                          dataset: String,
                          value: String,
                          count: Int?,
                          skip: Int?
    ): HttpRequestResult<List<ChoiceInput>>
}