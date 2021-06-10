package io.adaptivecards.uitestapp.ui.inputs;

import android.content.Context;
import android.content.Intent;
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

import io.adaptivecards.uitestapp.MainActivityUITestApp;
import io.adaptivecards.uitestapp.R;
import io.adaptivecards.uitestapp.RenderCardUiTestAppActivity;

public class InputsFragment extends Fragment {

    private InputsViewModel inputsViewModel;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        inputsViewModel =
            new ViewModelProvider(this).get(InputsViewModel.class);
        View root = inflater.inflate(R.layout.fragment_rendered_card, container, false);
        final TextView textView = root.findViewById(R.id.text_dashboard);
        inputsViewModel.getText().observe(getViewLifecycleOwner(), new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText(s);
            }
        });

        return root;
    }

}
