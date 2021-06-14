package io.adaptivecards.uitestapp.ui.inputs;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import java.util.ArrayList;
import java.util.List;

import io.adaptivecards.uitestapp.R;
import io.adaptivecards.uitestapp.ui.rendered_card.RenderedCardViewModel;

public class InputsFragment extends Fragment {

    private InputsViewModel mInputsViewModel;

    private RenderedCardViewModel mRenderedCardViewModel;

    private List<RetrievedInput> mRetrievedInputs;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        mInputsViewModel = new ViewModelProvider(requireActivity()).get(InputsViewModel.class);
        mRenderedCardViewModel = new ViewModelProvider(requireActivity()).get(RenderedCardViewModel.class);
        mRetrievedInputs = new ArrayList<RetrievedInput>();

        View root = inflater.inflate(R.layout.fragment_inputs, container, false);

        InputsFragment.InputsAdapter<String> itemsAdapter = new InputsFragment.InputsAdapter(getContext(), android.R.layout.test_list_item, mRetrievedInputs);
        final ListView listView = root.findViewById(R.id.inputs_list_view);
        listView.setAdapter(itemsAdapter);

        mRenderedCardViewModel.getInputs().observe(getViewLifecycleOwner(), new Observer<List<RetrievedInput>>() {
            @Override
            public void onChanged(List<RetrievedInput> retrievedInputs)
            {
                mRetrievedInputs = retrievedInputs;
                listView.setAdapter(new InputsFragment.InputsAdapter(getContext(), android.R.layout.test_list_item, mRetrievedInputs));
            }
        });

        return root;
    }

    private class InputsAdapter<T> extends ArrayAdapter
    {
        public InputsAdapter(@NonNull Context context, int resource, List<T> itemsList)
        {
            super(context, resource, itemsList);
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent)
        {
            if (convertView == null)
            {
                convertView = getLayoutInflater().inflate(R.layout.inputs_list_item, parent, false);
            }

            RetrievedInput retrievedInput = (RetrievedInput) getItem(position);

            TextView inputIdTextView = convertView.findViewById(R.id.text_input_id);
            inputIdTextView.setText(retrievedInput.getId());

            TextView inputValueTextView = convertView.findViewById(R.id.text_input_value);
            inputValueTextView.setText(retrievedInput.getValue());

            return convertView;
        }
    }

}
