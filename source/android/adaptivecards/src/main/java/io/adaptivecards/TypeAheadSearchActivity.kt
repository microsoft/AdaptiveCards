package io.adaptivecards

import android.content.Context
import android.graphics.Color
import android.graphics.drawable.Drawable
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.view.accessibility.AccessibilityEvent
import android.widget.*
import androidx.annotation.ColorRes
import androidx.annotation.DrawableRes
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
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
    private lateinit var backIconParams: BackIconParams
    private lateinit var tickIconParams: TickIconParams
    private lateinit var startSearchingIconParams: StartSearchingIconParams
    private lateinit var errorIconParams: ErrorIconParams
    private lateinit var noResultIconParams: NoResultIconParams


    private var activityTypeAheadSearchBinding: ActivityTypeAheadSearchBinding? = null

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)
        menuInflater.inflate(R.menu.menu_modal_screen, menu)
        menu?.let {
            val menuItem = menu.findItem(R.id.action_submit)
            val submitButton = menuItem.actionView as ImageButton
            submitButton.setImageResource(tickIconParams.drawableResourceId)
            //submitButton.setImageDrawable(resources.getDrawable(R.drawable.ic_tick_mark))
            submitButton.background = null
            submitButton.setOnClickListener {
                onOptionsItemSelected(menuItem)
            }
            //val padding = resources.getDimensionPixelSize(12dp) / 2
            //btn.setPadding(padding, padding, padding, padding)
            submitButton.contentDescription = menuItem.title
            submitButton.isEnabled = true
            submitButton.imageAlpha = 255
            submitButton.importantForAccessibility = View.IMPORTANT_FOR_ACCESSIBILITY_YES
        }
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (item.itemId == android.R.id.home) {
            onBackPressed()
            return true
        } else if (item.itemId == R.id.action_submit) {
            //onSubmitClicked()
            onBackPressed()
            return true
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val intent = intent
        baseContext.theme
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
            tickIconParams = launchParams.tickIconParams
            backIconParams = launchParams.backIconParams
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
            // is it required ?
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

            //val toolbar = findViewById<Toolbar>(R.id.toolbar)

//            val backImageView = findViewById<ImageView>(R.id.back_icon)
//            backImageView.apply {
//                setBackgroundResource(android.R.drawable.ic_menu_revert)
//            }

//            val tickImageView = findViewById<ImageView>(R.id.tick_icon)
//            tickImageView.apply {
//                setBackgroundResource(android.R.drawable.ic_input_add)
//            }
        }


        val observer1 = Observer<String?> { queryText ->
            val imageView = findViewById<ImageView>(R.id.clearTextIcon)
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

        activityTypeAheadSearchBinding?.toolbar?.let { setSupportActionBar(it) }

        supportActionBar?.let { actionBar ->
            actionBar.setDisplayHomeAsUpEnabled(true)
            actionBar.setHomeAsUpIndicator(backIconParams.drawableResourceId)
            actionBar.title = "Search"
        }

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
                        //backgroundTintMode = PorterDuff.Mode.SRC_ATOP
                        //setBackgroundColor(Color.parseColor("#C8C8C8"))
                    }
                    val textView = findViewById<TextView>(R.id.error_msg_text)
                    textView.text = "Search Options"
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
                    imageView.setImageResource(noResultIconParams.drawableResourceId)
                    //imageView.setImageDrawable(resources.getDrawable(R.drawable.ic_illustration_generic_error))
//                    imageView.apply {
//                        setBackgroundResource(noResultIconParams.drawableResourceId)
//                        backgroundTintMode = PorterDuff.Mode.SRC_ATOP
//                        //setBackgroundColor(Color.parseColor("#C8C8C8"))
//                    }
                    val textView = findViewById<TextView>(R.id.error_msg_text)
                    textView.text = noResultIconParams.text
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
                    imageView.apply {
                        setBackgroundResource(errorIconParams.drawableResourceId)
//                        val unwrappedDrawable: Drawable? =
//                            AppCompatResources.getDrawable(context, errorIconParams.drawableResourceId)
//                        unwrappedDrawable?.let { wrappedDrawable ->
//                            DrawableCompat.wrap(
//                                wrappedDrawable
//                            )
//                            DrawableCompat.setTint(wrappedDrawable, Color.BLUE)
//                            setImageDrawable(wrappedDrawable)
//                        }

                    }
                    val textView = findViewById<TextView>(R.id.error_msg_text)
                    textView.text = errorIconParams.text
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