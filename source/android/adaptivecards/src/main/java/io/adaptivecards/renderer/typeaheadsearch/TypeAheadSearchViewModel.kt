package io.adaptivecards.renderer.typeaheadsearch

import android.annotation.SuppressLint
import android.app.Activity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
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

class TypeAheadSearchViewModel : ViewModel() {

    private var totalResults: Int = 0

    private var staticChoices : MutableList<String>

    private val dataSet: String = ""

    lateinit var adapter : FilteredAdapter

    fun getAdaptor(): FilteredAdapter {
        return adapter
    }

    //    @Bindable
    //    fun getEditorTheme() = R.style.adaptiveCardEditBoxStyling

    private val _queryText: SingleLiveEvent<String> by lazy {
        SingleLiveEvent()
    }

    private val _uiState: SingleLiveEvent<DynamicTypeAheadUiState> by lazy {
        SingleLiveEvent()
    }

    val queryText: SingleLiveEvent<String> get() = _queryText

    val uiState: SingleLiveEvent<DynamicTypeAheadUiState> get() = _uiState

    init {
        staticChoices = ArrayList()
        totalResults = 0
        _queryText.value = ""

        // Show start searching view by default
        _uiState.postValue(DynamicTypeAheadUiState.SearchOptions)
    }

    // Initialize view model, adaptor in constructor or init block

    fun init(choices : MutableList<String>) {
        // get navigation params and initiate choices.data, static choices etc.
        staticChoices = choices
        totalResults = choices.size
        adapter = FilteredAdapter(choices)
        showDefaultView()
    }

    private fun showDefaultView() {
        if (staticChoices.size == 0) {
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
            var result: HttpRequestResult<List<ChoiceInput>>? = null
            DynamicTypeAheadService.getChoicesResolver()?.let {
                result = it.getDynamicChoices(queryText)
                println("Accessing async task on ${Thread.currentThread().name}")
            }

            withContext(Dispatchers.Main) {
                if (result!!.isSuccessful && _queryText.value.equals(queryText)) {
                    val choices: List<ChoiceInput> = result!!.result
                    val values: MutableList<String> = ArrayList()
                    // save the dynamic choices as well
                    for (choice in choices) {
                        values.add(choice.GetValue())
                    }
                    // TODO: Put a check to only take 10-15 choices
                    if (values.isNotEmpty())
                        _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
                    else
                        _uiState.postValue(DynamicTypeAheadUiState.NoResults)
                    adapter.setChoices(values)
                }
                else if (_queryText.value.equals(queryText)) {
                    adapter.setChoices(ArrayList())
                    _uiState.postValue(DynamicTypeAheadUiState.Error)
                }
                println("Accessing UI on ${Thread.currentThread().name}")
            }
        }

        println("Accessing main on ${Thread.currentThread().name}")
    }

    class FilteredAdapter (private var mChoices: List<String> = ArrayList()) : RecyclerView.Adapter<FilteredAdapter.ViewHolder>() {

        @SuppressLint("NotifyDataSetChanged")
        fun setChoices(choices: List<String>) {
            mChoices = choices
            notifyDataSetChanged()
        }
        // Provide a direct reference to each of the views within a data item
        // Used to cache the views within the item layout for fast access
        inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
            // Your holder should contain and initialize a member variable
            // for any view that will be set as you render a row
            val textView: TextView = itemView.findViewById(android.R.id.text1)
        }

        // ... constructor and member variables
        // Usually involves inflating a layout from XML and returning the holder
        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FilteredAdapter.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            // Inflate the custom layout
            android.R.layout.select_dialog_item
            val choicesView = inflater.inflate(R.layout.adaptive_card_select_item, parent, false)
            //            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            //                textView.setTextAppearance(android.R.attr.textAppearanceSmall)
            //            }
            // Return a new holder instance
            return ViewHolder(choicesView)
        }

        // Involves populating data into the item through holder
        override fun onBindViewHolder(viewHolder: FilteredAdapter.ViewHolder, position: Int) {
            // Get the data model based on position
            val choice: String = mChoices[position]
            // Set item views based on your views and data model
            val textView = viewHolder.textView
            textView.text = choice
            textView.setOnClickListener {
                if (it.context is Activity) {
                    it.postDelayed({
                        val activity: Activity = it.context as Activity
                        val intent = activity.intent
                        intent.putExtra("typeAheadSearchSelectedKey", choice)
                        activity.setResult(Activity.RESULT_OK, intent)
                        activity.finish()
                    }, 100)
                }
            }
        }

        // Returns the total count of items in the list
        override fun getItemCount(): Int {
            return mChoices.size
        }
    }

    /**
     * Clear filtered results & search bar.
     */
    fun clearText() {
        queryText.postValue("")
        //notify the property listeners
        adapter.setChoices(staticChoices)
        showDefaultView()
    }
}

sealed class DynamicTypeAheadUiState {
    object SearchOptions : DynamicTypeAheadUiState()
    object ShowingChoices : DynamicTypeAheadUiState()
    object Loading : DynamicTypeAheadUiState()
    object NoResults : DynamicTypeAheadUiState()
    object Error : DynamicTypeAheadUiState()
}
