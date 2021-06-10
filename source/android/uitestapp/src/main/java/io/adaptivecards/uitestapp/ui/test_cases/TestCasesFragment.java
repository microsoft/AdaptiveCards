package io.adaptivecards.uitestapp.ui.test_cases;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import java.util.ArrayList;
import java.util.List;

import io.adaptivecards.uitestapp.R;
import io.adaptivecards.uitestapp.ui.inputs.InputsFragment;

public class TestCasesFragment extends Fragment {

    private TestCasesViewModel testCasesViewModel;

    private List<String> items;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState)
    {
        testCasesViewModel = new ViewModelProvider(requireActivity()).get(TestCasesViewModel.class);
        View root = inflater.inflate(R.layout.fragment_test_cases, container, false);

        items = new ArrayList<String>();
        for(int i = 0; i < 5; ++i)
        {
            items.add("" + i);
        }

        TestCasesFragment.TestCasesAdapter<String> itemsAdapter = new TestCasesFragment.TestCasesAdapter(getContext(), android.R.layout.test_list_item, items);

        ListView listView = root.findViewById(R.id.test_cases_list_view);
        listView.setAdapter(itemsAdapter);

        return root;
    }

    private class TestCasesAdapter<T> extends ArrayAdapter
    {
        private List<T> m_testCaseList = null;

        public TestCasesAdapter(@NonNull Context context, int resource, List<T> itemsList)
        {
            super(context, resource, itemsList);
            m_testCaseList = itemsList;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent)
        {
            if (convertView == null)
            {
                convertView = getLayoutInflater().inflate(R.layout.test_case_list_item, parent, false);
            }

            Button testCaseButton = convertView.findViewById(R.id.list_item_button);
            String testCaseButtonContent = getItem(position).toString();
            testCaseButton.setText(testCaseButtonContent);
            testCaseButton.setOnClickListener(new TestCasesFragment.TestCasesAdapter.TestCaseButtonClickListener(testCaseButtonContent));

            return convertView;
        }

        private class TestCaseButtonClickListener implements View.OnClickListener
        {
            String m_content;

            public TestCaseButtonClickListener(String content)
            {
                m_content = content;
            }

            @Override
            public void onClick(View v)
            {
                testCasesViewModel.setLastClickedItem(m_content);
            }
        }
    }


}
