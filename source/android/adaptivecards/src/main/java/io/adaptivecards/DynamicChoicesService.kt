package io.adaptivecards

import android.os.AsyncTask
import io.adaptivecards.objectmodel.ChoiceInput
import io.adaptivecards.renderer.DynamicChoicesServiceAsync
import io.adaptivecards.renderer.actionhandler.ICardActionHandler

object DynamicChoicesService {
    private var cardActionHandler: ICardActionHandler? = null

    fun setICardActionHandler(actionHandler: ICardActionHandler?) {
        cardActionHandler = actionHandler
    }

    fun removeICardActionHandler() {
        cardActionHandler = null
    }

    fun getICardActionHandler(): ICardActionHandler? {
        return cardActionHandler
    }

    fun getDynamicChoices(queryText: String, onSuccess: (choices: MutableList<String>) -> Unit, onFailure: () -> Unit) {
        val dynamicChoicesServiceImpl = DynamicChoicesServiceAsyncImpl(onSuccess, onFailure)
        dynamicChoicesServiceImpl.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, queryText)
    }

    class DynamicChoicesServiceAsyncImpl(
        private val onSuccess: (choices: MutableList<String>) -> Unit,
        private val onFailure: () -> Unit
    ): DynamicChoicesServiceAsync(cardActionHandler) {
        override fun onSuccessfulPostExecute(choices: MutableList<ChoiceInput>) {
            var values: MutableList<String> = ArrayList()
            // save the dynamic choices as well
            for (choice in choices) {
                values.add(choice.GetValue())
            }
            onSuccess(values)
            // adapter.setChoices(choices)
        }

        override fun onFailurePostExecute() {
            onFailure()
        }
    }
}