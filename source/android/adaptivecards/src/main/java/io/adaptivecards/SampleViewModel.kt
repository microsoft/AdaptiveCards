package io.adaptivecards

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.lifecycle.ViewModel
import androidx.recyclerview.widget.RecyclerView

class SampleViewModel : ViewModel() {

    // Initialize view model, adaptor in constructor or init block

    fun init(choices : MutableList<String>) {
        // get navigation params and initiate choices.data, static choices etc.
        totalResults = choices.size
        adapter = FilteredAdapter(choices)
    }


//    val rvContacts = findViewById<View>(R.id.rvContacts) as RecyclerView
//    // Initialize contacts
//    contacts = Contact.createContactsList(20)
//    // Create adapter passing in the sample user data
//    val adapter = ContactsAdapter(contacts)
//    // Attach the adapter to the recyclerview to populate items
//    rvContacts.adapter = adapter
//    // Set layout manager to position the items
//    rvContacts.layoutManager = LinearLayoutManager(this)

    //private var mChoiceList: List<TypeAheadSearch.Item>? = null

    private var totalResults: Int = 0

    //private var mResultsDataCancellationToken: CancellationToken? = null

    private var mSelectedItemsSet: Set<String>? = null

    private var mIsMultiSelect = false

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

    val isLoading: SingleLiveEvent<Boolean> get() = _isLoading

    init {
        totalResults = 0
        _isLoading.value = false
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
        }

        // Returns the total count of items in the list
        override fun getItemCount(): Int {
            return mChoices.size
        }
    }

}