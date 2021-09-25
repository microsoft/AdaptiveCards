// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.test_cases

import android.app.Activity
import android.content.Context
import android.content.res.AssetManager
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.ListView
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentActivity
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.NavController
import androidx.navigation.fragment.NavHostFragment
import io.adaptivecards.uitestapp.R
import java.io.IOException
import java.util.*

class TestCasesFragment : Fragment() {
    private var mTestCasesViewModel: TestCasesViewModel? = null
    private var mNavigationController: NavController? = null
    private var mItems: MutableList<String>? = null
    override fun onCreateView(inflater: LayoutInflater,
                              container: ViewGroup?, savedInstanceState: Bundle?): View? {
        mTestCasesViewModel = ViewModelProvider(requireActivity()).get(TestCasesViewModel::class.java)
        val root = inflater.inflate(R.layout.fragment_test_cases, container, false)
        val fragment = requireActivity().supportFragmentManager.findFragmentById(R.id.nav_host_fragment)
        mNavigationController = (fragment as NavHostFragment?)!!.navController
        populateTestCaseList()
        val itemsAdapter: TestCasesAdapter<Any?> = TestCasesAdapter<Any?>(requireContext(), android.R.layout.test_list_item, mItems)
        val listView = root.findViewById<ListView>(R.id.test_cases_list_view)
        listView.adapter = itemsAdapter
        return root
    }

    private fun populateTestCaseList () {
        try {
            val activity : FragmentActivity = requireActivity();
            val assets : AssetManager = activity.assets;
            val assetsList = assets.list("");

            // mItems = mutableListOf<String>(*(requireActivity().assets.list("")))

            mItems = mutableListOf<String>(*assetsList);

            // there are some extra directories retrieved, so we'll remove them
            (mItems as MutableList<String>?)?.remove("images")
            (mItems as MutableList<String>?)?.remove("webkit")
        } catch (e: IOException) {
            // Raise toast
            e.printStackTrace()
        }
    }

    private inner class TestCasesAdapter<T>(context: Context, resource: Int, itemsList: List<T>?) : ArrayAdapter<Any?>(context, resource, itemsList) {
        override fun getView(position: Int, convertView: View?, parent: ViewGroup): View? {
            var convertView = convertView
            if (convertView == null) {
                convertView = layoutInflater.inflate(R.layout.test_case_list_item, parent, false)
            }
            val testCaseButton = convertView?.findViewById<Button>(R.id.list_item_button)
            val testCaseButtonContent = getItem(position) as String

            // Remove the .json suffix
            val testCaseButtonText: String = testCaseButtonContent.substring(0, testCaseButtonContent.lastIndexOf('.'))
            testCaseButton?.text = testCaseButtonText
            testCaseButton?.setOnClickListener(TestCaseButtonClickListener(testCaseButtonContent))
            return convertView
        }

        private inner class TestCaseButtonClickListener(var mContent: String) : View.OnClickListener {
            override fun onClick(v: View) {
                mTestCasesViewModel!!.setLastClickedItem(mContent)
                mNavigationController!!.navigate(R.id.navigation_rendered_card)
            }
        }
    }
}
