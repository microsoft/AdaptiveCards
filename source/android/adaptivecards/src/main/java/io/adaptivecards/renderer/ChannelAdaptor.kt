package io.adaptivecards.renderer

import io.adaptivecards.renderer.actionhandler.ICardActionHandler
import io.adaptivecards.renderer.typeaheadsearch.IChoicesResolver

class ChannelAdaptor private constructor(builder: Builder) {
    val cardActionHandler: ICardActionHandler?
    val choicesResolver: IChoicesResolver?

    init {
        this.cardActionHandler = builder.cardActionHandler
        this.choicesResolver = builder.choicesResolver
    }

    class Builder {
        var cardActionHandler: ICardActionHandler? = null
            private set
        var choicesResolver: IChoicesResolver? = null
            private set

        fun actionHandler(cardActionHandler: ICardActionHandler) = apply { this.cardActionHandler = cardActionHandler }
        fun choicesResolver(choicesResolver: IChoicesResolver) = apply { this.choicesResolver = choicesResolver }
        fun build() = ChannelAdaptor(this)
    }
}