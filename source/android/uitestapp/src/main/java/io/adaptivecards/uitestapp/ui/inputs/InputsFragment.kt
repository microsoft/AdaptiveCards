// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.inputs

import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import io.adaptivecards.uitestapp.R
import io.adaptivecards.uitestapp.ui.rendered_card.RenderedCardViewModel
import java.util.*

class InputsFragment : Fragment() {
    private var mInputsViewModel: InputsViewModel? = null
    private var mRenderedCardViewModel: RenderedCardViewModel? = null
    private var mRetrievedInputs: List<RetrievedInput?>? = null
    override fun onCreateView(inflater: LayoutInflater,
                              container: ViewGroup?, savedInstanceState: Bundle?): View? {
        mInputsViewModel = ViewModelProvider(requireActivity()).get(InputsViewModel::class.java)
        mRenderedCardViewModel = ViewModelProvider(requireActivity()).get(RenderedCardViewModel::class.java)
        mRetrievedInputs = ArrayList()
        val root = inflater.inflate(R.layout.fragment_inputs, container, false)
        val itemsAdapter: InputsAdapter<Any?> = InputsAdapter<Any?>(requireContext(), android.R.layout.test_list_item, mRetrievedInputs)
        val listView = root.findViewById<ListView>(R.id.inputs_list_view)
        listView.adapter = itemsAdapter
        mRenderedCardViewModel!!.inputs.observe(viewLifecycleOwner, { retrievedInputs ->
            mRetrievedInputs = retrievedInputs
            listView.adapter = InputsAdapter<Any?>(requireContext(), android.R.layout.test_list_item, mRetrievedInputs)
        })
        return root
    }

    private inner class InputsAdapter<T>(context: Context, resource: Int, itemsList: List<T>?) : ArrayAdapter<Any?>(context, resource, itemsList!!) {
        override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
            var convertView: View? = convertView
            if (convertView == null) {
                convertView = layoutInflater.inflate(R.layout.inputs_list_item, parent, false)
            }
            val retrievedInput = getItem(position) as RetrievedInput?
            val inputIdTextView = convertView?.findViewById<TextView>(R.id.text_input_id)
            inputIdTextView?.text = retrievedInput!!.id
            val inputValueTextView = convertView?.findViewById<TextView>(R.id.text_input_value)
            inputValueTextView?.text = retrievedInput.value
            return convertView!!
        }
    }
}
