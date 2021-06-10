package io.adaptivecards.uitestapp.ui.rendered_card;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import io.adaptivecards.uitestapp.R;
import io.adaptivecards.uitestapp.ui.test_cases.TestCasesViewModel;

public class RenderedCardFragment extends Fragment {

    private RenderedCardViewModel renderedCardViewModel;

    private TestCasesViewModel testCasesViewModel;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        renderedCardViewModel =
            new ViewModelProvider(this).get(RenderedCardViewModel.class);

        testCasesViewModel = new ViewModelProvider(requireActivity()).get(TestCasesViewModel.class);

        View root = inflater.inflate(R.layout.fragment_rendered_card, container, false);

        final TextView textView = root.findViewById(R.id.text_dashboard);

        /*
        renderedCardViewModel.getText().observe(getViewLifecycleOwner(), new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText(s);
            }
        });
         */

        testCasesViewModel.getLastClickedItem().observe(getViewLifecycleOwner(), new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText("Test case clicked " + s);
            }
        });

        return root;
    }
}
