package io.adaptivecards.uitestapp.ui.rendered_card;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import java.util.List;

import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput;

public class RenderedCardViewModel extends ViewModel
{
    private MutableLiveData<List<RetrievedInput>> mInputs;

    public RenderedCardViewModel()
    {
        mInputs = new MutableLiveData<>();
    }

    public MutableLiveData<List<RetrievedInput>> getInputs()
    {
        return mInputs;
    }
}
