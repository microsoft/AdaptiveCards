// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

import android.app.Activity
import android.content.Intent
import android.graphics.Color.parseColor
import android.graphics.drawable.Drawable
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.view.accessibility.AccessibilityEvent
import android.view.inputmethod.InputMethodManager
import android.widget.EditText
import android.widget.ImageButton
import android.widget.ProgressBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.AppCompatImageButton
import androidx.appcompat.widget.AppCompatImageView
import androidx.core.content.ContextCompat
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.RecyclerView
import io.adaptivecards.R
import io.adaptivecards.databinding.ActivityTypeAheadSearchBinding
import io.adaptivecards.renderer.ITypeAheadRenderer
import io.adaptivecards.renderer.registration.CardRendererRegistration

class TypeAheadSearchActivity : AppCompatActivity() {
    private lateinit var viewModel: TypeAheadSearchViewModel
    private lateinit var searchTextView: EditText
    private lateinit var recyclerView: RecyclerView
    private lateinit var progressBarView: ProgressBar
    private lateinit var clearTextIconView: AppCompatImageButton
    private lateinit var descriptiveImageView: AppCompatImageView
    private lateinit var descriptiveHeadingTextView: TextView
    private lateinit var descriptiveTextView: TextView
    private lateinit var submitButton: ImageButton

    private lateinit var selectedTitle: String
    private lateinit var titleList: List<String>
    private lateinit var valueList: List<String>
    private lateinit var screenTitle: String
    private lateinit var dataset: String
    private lateinit var dataType: String
    private lateinit var crossIconParams: CrossIconParams
    private lateinit var searchIconParams: SearchIconParams
    private lateinit var backIconParams: BackIconParams
    private lateinit var tickIconParams: TickIconParams
    private lateinit var startSearchingIconParams: StartSearchingStateParams
    private lateinit var errorIconParams: ErrorStateParams
    private lateinit var noResultIconParams: NoResultStateParams

    private var activityTypeAheadSearchBinding: ActivityTypeAheadSearchBinding? = null

    // TODO: Get delay value from host config here
    private val delayTimeInMilliSeconds: Long = 250
    private var backgroundColor: Int = parseColor("#FFFFFF")
    private var foregroundColor: Int = parseColor("#212121")
    private var primaryColor: Int = parseColor("#0F6CBD")
    private var secondaryColor: Int = parseColor("#FFFFFF")

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)
        menuInflater.inflate(R.menu.menu_modal_screen, menu)
        menu?.let {
            val menuItem = menu.findItem(R.id.action_submit)
            submitButton = menuItem.actionView as ImageButton
            val tickIconDrawable: Drawable? = ContextCompat.getDrawable(this, tickIconParams.drawableResourceId)
            tickIconDrawable?.setTint(secondaryColor)
            if (tickIconDrawable != null)
                submitButton.setImageDrawable(tickIconDrawable)
            else
                submitButton.setImageResource(tickIconParams.drawableResourceId)
            submitButton.background = null
            submitButton.setOnClickListener {
                onOptionsItemSelected(menuItem)
            }
            submitButton.contentDescription = tickIconParams.contentDescription
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
            val intent = Intent()
            intent.putExtra("typeAheadSearchSelectedKey", "")
            intent.putExtra("typeAheadSearchSelectedValue", "")
            setResult(Activity.RESULT_OK, intent)
            finish()
            return true
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val intent = intent
        val launchParams = intent.getSerializableExtra("launchParams")
        viewModel = ViewModelProvider(this)[TypeAheadSearchViewModel::class.java]
        if (launchParams is TypeAheadSearchLaunchParams) {
            selectedTitle = launchParams.selectedTitle
            titleList = launchParams.titleList
            valueList = launchParams.valueList
            dataset = launchParams.dataset
            dataType = launchParams.choicesDataType
            foregroundColor = launchParams.foregroundColor
            backgroundColor = launchParams.backgroundColor
        }

        val typeAheadParams: ITypeAheadRenderer? = CardRendererRegistration.getInstance().typeAheadRenderer
        if (typeAheadParams != null) {
            crossIconParams = typeAheadParams.getCrossIconParams()
            searchIconParams = typeAheadParams.getSearchIconParams()
            tickIconParams = typeAheadParams.getTickIconParams()
            backIconParams = typeAheadParams.getBackIconParams()
            screenTitle = typeAheadParams.getScreenTitle()

            startSearchingIconParams = typeAheadParams.getStartSearchingStateParams()
            errorIconParams = typeAheadParams.getErrorStateParams()
            noResultIconParams = typeAheadParams.getNoResultStateParams()
            primaryColor = typeAheadParams.getPrimaryColor()
            secondaryColor = typeAheadParams.getSecondaryColor()
        }
        else {
            crossIconParams = CrossIconParams()
            searchIconParams = SearchIconParams()
            tickIconParams = TickIconParams()
            backIconParams = BackIconParams()
            screenTitle = ""

            startSearchingIconParams = StartSearchingStateParams()
            errorIconParams = ErrorStateParams()
            noResultIconParams = NoResultStateParams()
        }

        // pass choices data, host communication interface
        viewModel.init(titleList, valueList, dataType, dataset, foregroundColor, primaryColor)

        // set theme
        layoutInflater.context.setTheme(R.style.adaptiveCardTypeAheadStyling)

        activityTypeAheadSearchBinding = ActivityTypeAheadSearchBinding.inflate(layoutInflater)
        activityTypeAheadSearchBinding?.let { activityTypeAheadSearchBinding ->
            searchTextView = activityTypeAheadSearchBinding.typeAheadSearchQuery
            recyclerView = activityTypeAheadSearchBinding.searchResultsList
            progressBarView = activityTypeAheadSearchBinding.customOverlayView
            clearTextIconView = activityTypeAheadSearchBinding.clearTextIcon
            descriptiveImageView = activityTypeAheadSearchBinding.errorImage
            descriptiveHeadingTextView = activityTypeAheadSearchBinding.errorHeadingText
            descriptiveTextView = activityTypeAheadSearchBinding.errorMsgDescription
            activityTypeAheadSearchBinding.viewModel = viewModel
        }

        val processClearTextIconVisibility = Observer<String?> { queryText ->
            clearTextIconView.visibility = if (queryText.isNullOrEmpty()) View.GONE else View.VISIBLE
        }

        viewModel.uiState.observe(this, ::processState)
        viewModel.queryText.observe(this, processClearTextIconVisibility)

        clearTextIconView.setBackgroundResource(crossIconParams.drawableResourceId)
        clearTextIconView.contentDescription = crossIconParams.contentDescription
        clearTextIconView.setOnClickListener { viewModel.clearText().also { searchTextView.text.clear() } }
        activityTypeAheadSearchBinding?.searchIcon?.setBackgroundResource(searchIconParams.drawableResourceId)

        with(searchTextView) {
            // request focus to the SearchBarView for accessibility once the activity is open.
            isFocusable = true
            sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED)
            addTextChangedListener(
                DebouncingTextWatcher(
                    lifecycleScope,
                    { s: String ->
                        viewModel.fetchDynamicOptions(s)
                    },
                    delayTimeInMilliSeconds
                )
            )
            setText(selectedTitle)
            showKeyboard(this)
        }

        activityTypeAheadSearchBinding?.toolbar?.let {
            setSupportActionBar(it)
        }

        val backIconDrawable: Drawable? = ContextCompat.getDrawable(this, backIconParams.drawableResourceId)
        backIconDrawable?.setTint(secondaryColor)
        supportActionBar?.let { actionBar ->
            actionBar.setDisplayHomeAsUpEnabled(true)
            if (backIconDrawable != null)
                actionBar.setHomeAsUpIndicator(backIconDrawable)
            else
                actionBar.setHomeAsUpIndicator(backIconParams.drawableResourceId)
            actionBar.setHomeActionContentDescription(backIconParams.contentDescription)
            actionBar.title = screenTitle
        }

        activityTypeAheadSearchBinding?.let {
            it.constraintLayout.setBackgroundColor(backgroundColor)

            it.appbar.setBackgroundColor(primaryColor)
            it.toolbar.setBackgroundColor(primaryColor)
            it.customOverlayView.indeterminateDrawable.setTint(primaryColor)

            it.toolbar.setTitleTextColor(secondaryColor)
            it.searchIcon.background?.setTint(secondaryColor)
            it.clearTextIcon.background?.setTint(secondaryColor)
            it.typeAheadSearchQuery.setTextColor(secondaryColor)
            it.typeAheadSearchQuery.setHintTextColor(secondaryColor)

            it.errorHeadingText.setTextColor(foregroundColor)
            it.errorMsgDescription.setTextColor(foregroundColor)
        }

        setContentView(activityTypeAheadSearchBinding?.root)
    }

    private fun showKeyboard(view: View): Boolean {
        view.requestFocus()
        val imm = view.context.getSystemService(INPUT_METHOD_SERVICE) as InputMethodManager
        return imm.showSoftInput(view, InputMethodManager.SHOW_FORCED)
    }

    private fun processState(dynamicTypeAheadUiState: DynamicTypeAheadUiState?) {
        when (dynamicTypeAheadUiState) {
            is DynamicTypeAheadUiState.SearchOptions -> {
                recyclerView.visibility = View.GONE
                progressBarView.visibility = View.GONE
                descriptiveImageView.setImageResource(startSearchingIconParams.drawableResourceId)
                descriptiveHeadingTextView.text = startSearchingIconParams.text
                descriptiveTextView.text = startSearchingIconParams.message
                descriptiveImageView.visibility = View.VISIBLE
                descriptiveHeadingTextView.visibility = View.VISIBLE
                descriptiveTextView.visibility = View.VISIBLE
                showKeyboard(searchTextView)
            }
            is DynamicTypeAheadUiState.ShowingChoices -> {
                progressBarView.visibility = View.GONE
                descriptiveImageView.visibility = View.GONE
                descriptiveHeadingTextView.visibility = View.GONE
                descriptiveTextView.visibility = View.GONE
                recyclerView.visibility = View.VISIBLE
            }
            is DynamicTypeAheadUiState.Loading -> {
                recyclerView.visibility = View.GONE
                descriptiveImageView.visibility = View.GONE
                descriptiveHeadingTextView.visibility = View.GONE
                descriptiveTextView.visibility = View.GONE
                progressBarView.visibility = View.VISIBLE
            }
            is DynamicTypeAheadUiState.NoResults -> {
                recyclerView.visibility = View.GONE
                progressBarView.visibility = View.GONE
                descriptiveImageView.setImageResource(noResultIconParams.drawableResourceId)
                descriptiveHeadingTextView.text = noResultIconParams.text
                descriptiveTextView.text = noResultIconParams.message
                descriptiveImageView.visibility = View.VISIBLE
                descriptiveHeadingTextView.visibility = View.VISIBLE
                descriptiveTextView.visibility = View.VISIBLE
            }
            is DynamicTypeAheadUiState.Error -> {
                recyclerView.visibility = View.GONE
                progressBarView.visibility = View.GONE
                descriptiveImageView.setImageResource(errorIconParams.drawableResourceId)
                descriptiveHeadingTextView.text = errorIconParams.text
                descriptiveTextView.text = dynamicTypeAheadUiState.errorMessage ?: errorIconParams.message
                descriptiveImageView.visibility = View.VISIBLE
                descriptiveHeadingTextView.visibility = View.VISIBLE
                descriptiveTextView.visibility = View.VISIBLE
            }
        }
    }
}
