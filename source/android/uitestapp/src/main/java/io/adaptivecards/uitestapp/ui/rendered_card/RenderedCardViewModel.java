package io.adaptivecards.uitestapp.ui.rendered_card;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class RenderedCardViewModel extends ViewModel {

    private MutableLiveData<String> mText;

    public RenderedCardViewModel()
    {
        mText = new MutableLiveData<>();
        mText.setValue("This is where the adaptive card should be rendered");
    }

    public LiveData<String> getText() {
        return mText;
    }
}
