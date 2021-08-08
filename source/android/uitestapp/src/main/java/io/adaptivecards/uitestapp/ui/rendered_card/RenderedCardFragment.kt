// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.rendered_card

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import io.adaptivecards.objectmodel.*
import io.adaptivecards.renderer.AdaptiveCardRenderer
import io.adaptivecards.renderer.RenderedAdaptiveCard
import io.adaptivecards.renderer.actionhandler.ICardActionHandler
import io.adaptivecards.uitestapp.R
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput
import io.adaptivecards.uitestapp.ui.test_cases.TestCasesViewModel
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.util.*

class RenderedCardFragment : Fragment(), ICardActionHandler {
    private var mRenderedCardViewModel: RenderedCardViewModel? = null
    private var mTestCasesViewModel: TestCasesViewModel? = null
    private var mCardContainer: LinearLayout? = null
    override fun onCreateView(inflater: LayoutInflater,
                              container: ViewGroup?, savedInstanceState: Bundle?): View? {
        mRenderedCardViewModel = ViewModelProvider(requireActivity()).get(RenderedCardViewModel::class.java)
        mTestCasesViewModel = ViewModelProvider(requireActivity()).get(TestCasesViewModel::class.java)
        val root = inflater.inflate(R.layout.fragment_rendered_card, container, false)
        mCardContainer = root.findViewById(R.id.layout_cardContainer)
        mTestCasesViewModel!!.lastClickedItem.observe(viewLifecycleOwner,
                TestCaseObserver(this))
        return root
    }

    override fun onAction(actionElement: BaseActionElement, renderedAdaptiveCard: RenderedAdaptiveCard) {
        val actionType = actionElement.GetElementType()
        if (actionType == ActionType.Submit) {
            val keyValueMap = renderedAdaptiveCard.inputs
            val retrievedInputList: MutableList<RetrievedInput> = ArrayList()
            for ((key, value) in keyValueMap) {
                retrievedInputList.add(RetrievedInput(key!!, value!!))
            }
            mRenderedCardViewModel!!.inputs.value = retrievedInputList
        }
    }

    override fun onMediaPlay(mediaElement: BaseCardElement, renderedAdaptiveCard: RenderedAdaptiveCard) {}
    override fun onMediaStop(mediaElement: BaseCardElement, renderedAdaptiveCard: RenderedAdaptiveCard) {}
    private inner class TestCaseObserver(var m_cardActionHandler: ICardActionHandler) : Observer<String> {
        override fun onChanged(testCase: String) {
            activity!!.title = testCase
            val adaptiveCardContents = readAdaptiveCardJson(testCase)
            renderCard(adaptiveCardContents)
        }

        private fun renderCard(adaptiveCardContents: String?) {
            try {
                val parseResult = AdaptiveCard.DeserializeFromString(adaptiveCardContents,
                        AdaptiveCardRenderer.VERSION)
                mCardContainer!!.removeAllViews()
                val renderedCard = AdaptiveCardRenderer.getInstance().render(context,
                        activity!!.supportFragmentManager,
                        parseResult.GetAdaptiveCard(),
                        m_cardActionHandler,
                        HostConfig())
                mCardContainer!!.addView(renderedCard.view)
            } catch (ex: Exception) {
            }
        }

        private fun readAdaptiveCardJson(testCase: String): String? {
            try {
                val cardContents = requireActivity().assets.open(testCase).bufferedReader().use {
                    it.readText()
                }
                return cardContents
            } catch (ioExcep: IOException) {
            }
            return null
        }
    }
}
