// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.ui.test_cases;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.fragment.NavHostFragment;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import io.adaptivecards.uitestapp.R;

public class TestCasesFragment extends Fragment {

    private TestCasesViewModel mTestCasesViewModel;

    private NavController mNavigationController;

    private List<String> mItems;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState)
    {
        mTestCasesViewModel = new ViewModelProvider(requireActivity()).get(TestCasesViewModel.class);
        View root = inflater.inflate(R.layout.fragment_test_cases, container, false);

        Fragment fragment = requireActivity().getSupportFragmentManager().findFragmentById(R.id.nav_host_fragment);
        mNavigationController = ((NavHostFragment) fragment).getNavController();

        populateTestCaseList();

        TestCasesFragment.TestCasesAdapter<String> itemsAdapter = new TestCasesFragment.TestCasesAdapter(getContext(), android.R.layout.test_list_item, mItems);

        ListView listView = root.findViewById(R.id.test_cases_list_view);
        listView.setAdapter(itemsAdapter);

        return root;
    }

    private void populateTestCaseList() {

        try
        {
            mItems = new ArrayList<String>(Arrays.asList(getActivity().getAssets().list("")));

            // there are some extra directories retrieved, so we'll remove them
            mItems.remove("images");
            mItems.remove("webkit");
        }
        catch (IOException e)
        {
            // Raise toast
            e.printStackTrace();
        }
    }

    private class TestCasesAdapter<T> extends ArrayAdapter
    {
        public TestCasesAdapter(@NonNull Context context, int resource, List<T> itemsList)
        {
            super(context, resource, itemsList);
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent)
        {
            if (convertView == null)
            {
                convertView = getLayoutInflater().inflate(R.layout.test_case_list_item, parent, false);
            }

            Button testCaseButton = convertView.findViewById(R.id.list_item_button);

            String testCaseButtonContent = (String) getItem(position);

            // Remove the .json suffix
            String testCaseButtonText = testCaseButtonContent.substring(0, testCaseButtonContent.lastIndexOf('.'));

            testCaseButton.setText(testCaseButtonText);
            testCaseButton.setOnClickListener(new TestCasesFragment.TestCasesAdapter.TestCaseButtonClickListener(testCaseButtonContent));

            return convertView;
        }

        private class TestCaseButtonClickListener implements View.OnClickListener
        {
            String mContent;

            public TestCaseButtonClickListener(String content)
            {
                mContent = content;
            }

            @Override
            public void onClick(View v)
            {
                mTestCasesViewModel.setLastClickedItem(mContent);
                mNavigationController.navigate(R.id.navigation_rendered_card);
            }
        }
    }

}
