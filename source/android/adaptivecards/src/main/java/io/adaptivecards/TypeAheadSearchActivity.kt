package io.adaptivecards

import android.os.Bundle
import android.text.Editable
import android.view.View
import android.view.accessibility.AccessibilityEvent
import android.widget.EditText
import android.widget.ProgressBar
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.coroutineScope
import io.adaptivecards.databinding.ActivityTypeAheadSearchBinding

class TypeAheadSearchActivity : AppCompatActivity() {
    private lateinit var viewModel: TypeAheadSearchViewModel
    private lateinit var searchTextView: EditText
    private lateinit var progressView: ProgressBar
    //private lateinit var stateLayout: StateLayout
    //private lateinit var clearIcon: IconView
    //private lateinit var searchOptionsView: View


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val intent = intent
        val launchParams = intent.getSerializableExtra("launchParams")
        viewModel = ViewModelProvider(this)[TypeAheadSearchViewModel::class.java]
        val choices : MutableList<String> = ArrayList()
        if (launchParams is TypeAheadSearchLaunchParams) {
            launchParams.staticChoices?.let { staticChoices -> staticChoices.forEach { choices.add(it) } }
        }
        // pass choices data, host communication interface
        viewModel.init(choices)
        val binding = ActivityTypeAheadSearchBinding.inflate(layoutInflater)
        searchTextView = binding.typeAheadSearchQuery
        progressView = binding.progressBar
        binding.viewModel = viewModel

        val observer = Observer<Boolean?> { loading ->
            takeIf { loading }?.let {
                progressView.announceForAccessibility("Loading Options")
            }
//            if (!loading && viewModel.state.type != ViewStateType.ERROR && viewModel.state.type != ViewStateType.EMPTY) {
//                //stateLayout.announceForAccessibility(String.format(resources.getString(R.string.results_found), viewModel.totalResults))
//            }
        }
        viewModel.isLoading.observe(this, observer)

        with(searchTextView) {
            // request focus to the SearchBarView for accessibility once the activity is open.
            isFocusable = true
            sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED)
            //KeyboardUtilities.showKeyboard(this)
            addTextChangedListener(
                DebouncingTextWatcher(
                    lifecycle.coroutineScope,
                    { s: String? ->
                        viewModel.fetchDynamicOptions(s)
                    },
                    250 // pass host config value here
                )
            )
        }

        setContentView(binding.root)
    }
}