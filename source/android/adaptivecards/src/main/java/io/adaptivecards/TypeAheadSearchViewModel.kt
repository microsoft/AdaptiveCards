package io.adaptivecards

import android.annotation.SuppressLint
import android.app.Activity
import android.os.AsyncTask
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.lifecycle.ViewModel
import androidx.recyclerview.widget.RecyclerView
import io.adaptivecards.objectmodel.ChoiceInput
import io.adaptivecards.renderer.DynamicChoicesServiceAsync

class TypeAheadSearchViewModel : ViewModel() {

    // Initialize view model, adaptor in constructor or init block

    fun init(choices : MutableList<String>) {
        // get navigation params and initiate choices.data, static choices etc.
        staticChoices = choices
        totalResults = choices.size
        adapter = FilteredAdapter(choices)
        if (totalResults == 0)
            _uiState.postValue(DynamicTypeAheadUiState.SearchOptions)
    }

    //private var mChoiceList: List<TypeAheadSearch.Item>? = null

    private var totalResults: Int = 0

    //private var mResultsDataCancellationToken: CancellationToken? = null

    private var mSelectedItemsSet: Set<String>? = null

    private var mIsMultiSelect = false

    private var staticChoices : MutableList<String>

    //private val mDataSet: TypeAheadSearch.DataSet? = null

    lateinit var adapter : FilteredAdapter

    //    @Bindable
    //    private var mQueryText: String = ""
    //
    //    private var mIsSearchInvoked = false
    //
    //    @Bindable
    //    private var mShouldShowLoading = MutableLiveData(false)
    //
    //    @Bindable
    //    private var mTypeAheadTitle: String = ""

    //***** -- Data Binding Methods -- *****

    fun getAdaptor(): FilteredAdapter {
        return adapter
    }

    private val _isLoading: SingleLiveEvent<Boolean> by lazy {
        SingleLiveEvent()
    }

    private val _queryText: SingleLiveEvent<String> by lazy {
        SingleLiveEvent()
    }

    val isLoading: SingleLiveEvent<Boolean> get() = _isLoading

    private val _uiState: SingleLiveEvent<DynamicTypeAheadUiState> by lazy {
        SingleLiveEvent()
    }

    val queryText: SingleLiveEvent<String> get() = _queryText

    val uiState: SingleLiveEvent<DynamicTypeAheadUiState> get() = _uiState

    init {
        staticChoices = ArrayList()
        totalResults = 0
        _isLoading.value = false
        _queryText.value = ""
        _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
    }

    fun fetchDynamicOptions(queryText: String) {
        _queryText.postValue(queryText)
        if (queryText.isEmpty()) {
            //clear search box text and dynamic choices
            //return ArrayList()
            adapter.setChoices(staticChoices)
            return
        }

        _isLoading.postValue(true)
        _uiState.postValue(DynamicTypeAheadUiState.Loading)

        DynamicChoicesService.getDynamicChoices(
            queryText,
            {
                if (it.size > 0)
                    _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
                else
                    _uiState.postValue(DynamicTypeAheadUiState.NoResults)
                adapter.setChoices(it)
                _isLoading.postValue(false)
            },
            {
                adapter.setChoices(ArrayList())
                _isLoading.postValue(false)
                _uiState.postValue(DynamicTypeAheadUiState.Error)
            }
        )

//        val dynamicChoicesServiceImpl = DynamicChoicesServiceImpl(
//            {
//                if (it.size > 0)
//                    _uiState.postValue(DynamicTypeAheadUiState.ShowingChoices)
//                else
//                    _uiState.postValue(DynamicTypeAheadUiState.NoResults)
//                adapter.setChoices(it)
//                _isLoading.postValue(false)
//            },
//            {
//                adapter.setChoices(ArrayList())
//                _isLoading.postValue(false)
//                _uiState.postValue(DynamicTypeAheadUiState.Error)
//            }
//        )
//        dynamicChoicesServiceImpl.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, queryText)
        //val newChoices: List<String>? = DynamicChoicesService.getDynamicChoices(queryText)
        //val newChoices: List<String> =  CardRendererRegistration.getInstance().cardActionHandler.getDynamicChoices(queryText)
        //newChoices?.let { adapter.setChoices(it) }
        //adapter.setChoices(newChoices)
        //return newChoices;
        // call the host
        // get dynamic choices and return to the UI
        //return ArrayList()
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
            android.R.drawable.ic_dialog_alert
            android.R.drawable.stat_notify_error
            android.R.drawable.ic_menu_search
            android.R.drawable.ic_search_category_default
            val choicesView = inflater.inflate(android.R.layout.select_dialog_item, parent, false)
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

//    class DynamicChoicesServiceImpl(
//        private val onSuccess: (choices: MutableList<String>) -> Unit,
//        private val onFailure: () -> Unit
//    ): DynamicChoicesServiceAsync(DynamicChoicesService.getICardActionHandler()) {
//        override fun onSuccessfulPostExecute(choices: MutableList<ChoiceInput>) {
//            var values: MutableList<String> = ArrayList()
//            // save the dynamic choices as well
//            for (choice in choices) {
//                values.add(choice.GetValue())
//            }
//            onSuccess(values)
//           // adapter.setChoices(choices)
//        }
//
//        override fun onFailurePostExecute() {
//            onFailure()
//        }
//    }

    //***** -- end -- *****
    /**
     * Clear filtered results & search bar.
     */
    fun clearText() {
//        if (mResultsDataCancellationToken != null) {
//            mResultsDataCancellationToken.cancel()
//            mResultsDataCancellationToken = null
//            stopScenarioOnCancel()
//        }
        queryText.postValue("")
        //notify the property listeners
        adapter.setChoices(ArrayList())
        _isLoading.postValue(false)
        _uiState.postValue(DynamicTypeAheadUiState.SearchOptions)
    }
}

sealed class DynamicTypeAheadUiState {
    object SearchOptions : DynamicTypeAheadUiState()
    object ShowingChoices : DynamicTypeAheadUiState()
    object Loading : DynamicTypeAheadUiState()
    object NoResults : DynamicTypeAheadUiState()
    object Error : DynamicTypeAheadUiState()
//    class InstallationFailure(val appInstallData: String) : AppInstallationUiState()
//    object Dismiss : AppInstallationUiState()
//    class InstallationSuccess(val appInstallData: String) : AppInstallationUiState()
}
