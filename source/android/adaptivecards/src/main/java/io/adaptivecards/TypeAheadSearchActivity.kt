package io.adaptivecards

import android.os.Bundle
import android.view.View
import android.view.accessibility.AccessibilityEvent
import android.widget.EditText
import android.widget.ImageView
import android.widget.ProgressBar
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.coroutineScope
import androidx.recyclerview.widget.RecyclerView
import io.adaptivecards.databinding.ActivityTypeAheadSearchBinding

class TypeAheadSearchActivity : AppCompatActivity() {
    private lateinit var viewModel: TypeAheadSearchViewModel
    private lateinit var searchTextView: EditText
    private lateinit var progressView: ProgressBar
    private lateinit var recyclerView: RecyclerView
    //private lateinit var stateLayout: StateLayout
    //private lateinit var clearIcon: IconView
    //private lateinit var searchOptionsView: View

    private var errorBinding = null
    private var emptyBinding = null
    private var loadingBinding = null

    private lateinit var crossIconParams: CrossIconParams
    private lateinit var searchIconParams: SearchIconParams
    private lateinit var startSearchingIconParams: StartSearchingIconParams
    private lateinit var errorIconParams: ErrorIconParams
    private lateinit var noResultIconParams: NoResultIconParams


    private var activityTypeAheadSearchBinding: ActivityTypeAheadSearchBinding? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val intent = intent
        val launchParams = intent.getSerializableExtra("launchParams")
        viewModel = ViewModelProvider(this)[TypeAheadSearchViewModel::class.java]
        val choices : MutableList<String> = ArrayList()
        if (launchParams is TypeAheadSearchLaunchParams) {
            launchParams.staticChoices?.let { staticChoices -> staticChoices.forEach { choices.add(it) } }
            crossIconParams = launchParams.crossIconParams
            searchIconParams = launchParams.searchIconParams
            startSearchingIconParams = launchParams.startSearchingIconParams
            errorIconParams = launchParams.errorIconParams
            noResultIconParams = launchParams.noResultIconParams
        }
        // pass choices data, host communication interface
        viewModel.init(choices)
        activityTypeAheadSearchBinding = ActivityTypeAheadSearchBinding.inflate(layoutInflater)
        activityTypeAheadSearchBinding?.let { activityTypeAheadSearchBinding ->
            searchTextView = activityTypeAheadSearchBinding.typeAheadSearchQuery
            //progressView = activityTypeAheadSearchBinding.progressBar
//            loadingBinding = activityTypeAheadSearchBinding.customOverlayView
//            emptyBinding = activityTypeAheadSearchBinding.customEmptyView
//            errorBinding = activityTypeAheadSearchBinding.customErrorView

            //activityTypeAheadSearchBinding.customErrorView

            recyclerView = activityTypeAheadSearchBinding.searchResultsList
            activityTypeAheadSearchBinding.viewModel = viewModel

            if (launchParams is TypeAheadSearchLaunchParams) {
                activityTypeAheadSearchBinding.clearTextIcon.setBackgroundResource(launchParams.crossIconParams.drawableResourceId)
                activityTypeAheadSearchBinding.searchIcon.setBackgroundResource(launchParams.searchIconParams.drawableResourceId)
            }
        }

        val observer = Observer<Boolean?> { loading ->
            loading?.let {
                if (it) {
                    //.visibility = View.VISIBLE
                    recyclerView.visibility = View.GONE
                    activityTypeAheadSearchBinding?.let { binding ->
                        //binding.customErrorView.rootView.visibility = View.GONE
                        //binding.customEmptyView.rootView.visibility = View.GONE
                        //binding.customOverlayView.rootView.visibility = View.VISIBLE
                    }
//                    emptyBinding.root.visibility = View.GONE
//                    errorBinding.root.visibility = View.GONE
//
//                    loadingBinding.root.visibility = View.VISIBLE
                    }
                else {
                    //progressView.visibility = View.GONE
                    recyclerView.visibility = View.VISIBLE
                    activityTypeAheadSearchBinding?.let { binding ->
                        //binding.customErrorView?.rootView.visibility = View.GONE
                        //binding.customEmptyView?.rootView.visibility = View.GONE
                        //binding.customOverlayView.rootView.visibility = View.GONE
                    }
//                    emptyBinding.root.visibility = View.GONE
//                    errorBinding.root.visibility = View.GONE
//
//                    loadingBinding.root.visibility = View.GONE
                }
            }
            takeIf { loading }?.let {
                //progressView.announceForAccessibility("Loading Options")
            }
//            if (!loading && viewModel.state.type != ViewStateType.ERROR && viewModel.state.type != ViewStateType.EMPTY) {
//                //stateLayout.announceForAccessibility(String.format(resources.getString(R.string.results_found), viewModel.totalResults))
//            }
        }


        val observer1 = Observer<String?> { queryText ->
            val imageView = findViewById<ImageView>(R.id.clear_text_icon)
            if (queryText.isNullOrEmpty()) {
                imageView.visibility = View.GONE
            }
            else
                imageView.visibility = View.VISIBLE
        }

        //viewModel.isLoading.observe(this, observer)
        viewModel.uiState.observe(this, ::processState)
        viewModel.queryText.observe(this, observer1)

        with(searchTextView) {
            // request focus to the SearchBarView for accessibility once the activity is open.
            isFocusable = true
            sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED)
            //KeyboardUtilities.showKeyboard(this)
            addTextChangedListener(
                DebouncingTextWatcher(
                    lifecycle.coroutineScope,
                    { s: String ->
                        viewModel.fetchDynamicOptions(s)
                    },
                    250 // pass host config value here
                )
            )
        }

        activityTypeAheadSearchBinding?.clearTextIcon?.setBackgroundResource(crossIconParams.drawableResourceId)
        activityTypeAheadSearchBinding?.clearTextIcon?.setOnClickListener { viewModel.clearText().also { searchTextView.text.clear() } }

        setContentView(activityTypeAheadSearchBinding?.root)
    }

    private fun processState(dynamicTypeAheadUiState: DynamicTypeAheadUiState?) {
        when (dynamicTypeAheadUiState) {
            is DynamicTypeAheadUiState.SearchOptions -> {
                recyclerView.visibility = View.GONE
                activityTypeAheadSearchBinding?.let {
                    //it.emptyImage.visibility = View.VISIBLE
                    //it.emptyMessage.visibility = View.VISIBLE
                    it.customOverlayView.visibility = View.GONE
                    it.customErrorView.visibility = View.VISIBLE
                    val imageView = findViewById<ImageView>(R.id.error_image)
                    imageView.apply {
                        setBackgroundResource(searchIconParams.drawableResourceId)
                    }
                }
            }
            is DynamicTypeAheadUiState.ShowingChoices -> {
                //progressView.visibility = View.GONE
                recyclerView.visibility = View.VISIBLE
                activityTypeAheadSearchBinding?.let {
                    //it.emptyImage.visibility = View.GONE
                    //it.emptyMessage.visibility = View.GONE
                    it.customOverlayView.visibility = View.GONE
                    it.customErrorView.visibility = View.GONE
                }
            }
            is DynamicTypeAheadUiState.Loading -> {
                //progressView.visibility = View.VISIBLE
                recyclerView.visibility = View.GONE
                activityTypeAheadSearchBinding?.let {
                    //it.emptyImage.visibility = View.GONE
                    //it.emptyMessage.visibility = View.GONE
                    it.customOverlayView.visibility = View.VISIBLE
                    it.customErrorView.visibility = View.GONE
                }
            }
            is DynamicTypeAheadUiState.NoResults -> {
                //progressView.visibility = View.GONE
                recyclerView.visibility = View.GONE
                activityTypeAheadSearchBinding?.let {
                    //it.emptyImage.visibility = View.VISIBLE
                    //it.emptyMessage.visibility = View.VISIBLE
                    it.customOverlayView.visibility = View.GONE
                    it.customErrorView.visibility = View.VISIBLE
                    val imageView = findViewById<ImageView>(R.id.error_image)
                    imageView.apply { setBackgroundResource(noResultIconParams.drawableResourceId) }
                }
            }
            is DynamicTypeAheadUiState.Error -> {
                //progressView.visibility = View.GONE
                recyclerView.visibility = View.GONE
                activityTypeAheadSearchBinding?.let {
                    //it.emptyImage.visibility = View.VISIBLE
                    //it.emptyMessage.visibility = View.VISIBLE
                    it.customOverlayView.visibility = View.GONE
                    it.customErrorView.visibility = View.VISIBLE
                    val imageView = findViewById<ImageView>(R.id.error_image)
                    imageView.apply { setBackgroundResource(errorIconParams.drawableResourceId) }
                }
            }
        }
    }

// onDestroyView
//    override fun onDestroy() {
//        super.onDestroy()
//        activityTypeAheadSearchBinding = null
//    }
}