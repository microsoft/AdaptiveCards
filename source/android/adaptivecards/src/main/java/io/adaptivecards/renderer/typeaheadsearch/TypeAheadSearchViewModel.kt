// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

import android.annotation.SuppressLint
import android.app.Activity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.recyclerview.widget.RecyclerView
import io.adaptivecards.R
import io.adaptivecards.objectmodel.ChoiceInput
import io.adaptivecards.renderer.SingleLiveEvent
import io.adaptivecards.renderer.http.HttpRequestResult
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.util.*
import kotlin.collections.ArrayList

class TypeAheadSearchViewModel : ViewModel() {

    private var staticChoicesCount: Int
    private var titleList: List<String>
    private var valueList: List<String>
    // TODO : Get count from host config
    private val count: Int = 15
    private val skip: Int = 0

    private lateinit var dataset: String
    private lateinit var dataType: String
    private lateinit var adapter : FilteredAdapter

    fun getAdaptor(): FilteredAdapter {
        return adapter
    }

    private val _queryText: SingleLiveEvent<String> by lazy {
        SingleLiveEvent()
    }

    private val _uiState: SingleLiveEvent<DynamicTypeAheadUiState> by lazy {
        SingleLiveEvent()
    }

    val queryText: SingleLiveEvent<String> get() = _queryText

    val uiState: SingleLiveEvent<DynamicTypeAheadUiState> get() = _uiState

    init {
        titleList = ArrayList()
        valueList = ArrayList()
        staticChoicesCount = 0
        _queryText.value = ""

        // Show start searching view by default
        _uiState.postValue(DynamicTypeAheadUiState.SearchOptions)
    }

    fun init(titles: List<String>, values: List<String>, type: String, set: String, textColor: Int, textHighlightColor: Int) {
        // get navigation params and initiate choices.data, static choices etc.
        titleList = titles
        valueList = values
        staticChoicesCount = titleList.size

        dataType = type
        dataset = set

        adapter = FilteredAdapter(titleList, valueList, textColor, textHighlightColor)
        showDefaultView()
    }

    private fun showDefaultView() {
        if (staticChoicesCount == 0) {
            _uiState.postValue(DynamicTypeAheadUiState.SearchOptions)
        }
        else {
            // Show static choices when present
            _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
        }
    }


    fun fetchDynamicOptions(queryText: String) {
        if (queryText.isEmpty()) {
            clearText()
            return
        }

        _queryText.postValue(queryText)
        _uiState.postValue(DynamicTypeAheadUiState.Loading)

        viewModelScope.launch(Dispatchers.IO) {
            val result: HttpRequestResult<List<ChoiceInput>>? = DynamicTypeAheadService.getChoicesResolver()?.getDynamicChoices(dataType, dataset, queryText, count, skip)
            withContext(Dispatchers.Main) {
                if (result != null) {
                    if (result.isSuccessful && _queryText.value.equals(queryText)) {
                        var choices: List<ChoiceInput> = result.result
                        if (choices.size > count)
                            choices = choices.subList(0, count)

                        val titles: MutableList<String> = ArrayList()
                        val values: MutableList<String> = ArrayList()
                        // save the dynamic choices as well
                        for (choice in choices) {
                            titles.add(choice.GetTitle())
                            values.add(choice.GetValue())
                        }
                        adapter.setQuery(_queryText.value)
                        adapter.setChoices(titles, values)
                        if (values.isNotEmpty())
                            _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
                        else
                            _uiState.postValue(DynamicTypeAheadUiState.NoResults)
                    } else if (_queryText.value.equals(queryText)) {
                        adapter.setQuery(_queryText.value)
                        adapter.setChoices(ArrayList(), ArrayList())
                        _uiState.postValue(DynamicTypeAheadUiState.Error(result.errorMessage))
                    }
                }
            }
        }
    }

    class FilteredAdapter (
        private var m_choices: List<String>,
        private var m_values: List<String>,
        private var textColor: Int,
        private var textHighlightColor: Int
    ) : RecyclerView.Adapter<FilteredAdapter.ViewHolder>() {

        private val delayTimeInMilliSeconds: Long = 100
        private var queryText: String = ""

        fun setQuery(query: String?) {
            if (query != null) {
                queryText = query
            }
        }

        @SuppressLint("NotifyDataSetChanged")
        fun setChoices(choices: List<String>, values: List<String>) {
            m_choices = choices
            m_values = values
            notifyDataSetChanged()
        }
        // Provide a direct reference to each of the views within a data item
        // Used to cache the views within the item layout for fast access
        inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
            // Your holder should contain and initialize a member variable
            // for any view that will be set as you render a row
            val textView: TextView = itemView.findViewById(R.id.choiceTitle)
        }

        // ... constructor and member variables
        // Usually involves inflating a layout from XML and returning the holder
        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FilteredAdapter.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            // Inflate the custom layout
            val choicesView = inflater.inflate(R.layout.adaptive_card_select_item, parent, false)
            // Return a new holder instance
            choicesView.findViewById<TextView>(R.id.choiceTitle).setTextColor(textColor)
            return ViewHolder(choicesView)
        }

        // Involves populating data into the item through holder
        override fun onBindViewHolder(viewHolder: FilteredAdapter.ViewHolder, position: Int) {
            // Get the data model based on position
            val title: String = m_choices[position]
            val value: String = m_values[position]
            // Set item views based on your views and data model
            val textView = viewHolder.textView
            textView.text = TypeAheadHelper.createHighlightedSearchResultText(
                title.lowercase(Locale.getDefault()),
                arrayOf(queryText),
                ContextCompat.getColor(textView.context, android.R.color.transparent),
                textHighlightColor
            )
            textView.setOnClickListener {
                if (it.context is Activity) {
                    it.postDelayed({
                        val activity: Activity = it.context as Activity
                        val intent = activity.intent
                        intent.putExtra("typeAheadSearchSelectedKey", title)
                        intent.putExtra("typeAheadSearchSelectedValue", value)
                        activity.setResult(Activity.RESULT_OK, intent)
                        activity.finish()
                    }, delayTimeInMilliSeconds)
                }
            }
        }

        // Returns the total count of items in the list
        override fun getItemCount(): Int {
            return m_choices.size
        }
    }

    /**
     * Clear filtered results & search bar.
     */
    fun clearText() {
        queryText.postValue("")
        //notify the property listeners
        adapter.setQuery(_queryText.value)
        adapter.setChoices(titleList, valueList)
        showDefaultView()
    }
}

sealed class DynamicTypeAheadUiState {
    object SearchOptions : DynamicTypeAheadUiState()
    object ShowingChoices : DynamicTypeAheadUiState()
    object Loading : DynamicTypeAheadUiState()
    object NoResults : DynamicTypeAheadUiState()
    class Error(val errorMessage: String?) : DynamicTypeAheadUiState()
}