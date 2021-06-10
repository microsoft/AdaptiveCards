package io.adaptivecards.uitestapp.ui.test_cases;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class TestCasesViewModel extends ViewModel {

    private MutableLiveData<String> mText;

    private MutableLiveData<String> mLastClickedItem;

    public TestCasesViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("This is home fragment");
    }

    public void setLastClickedItem(String s)
    {
        if (mLastClickedItem == null)
        {
            mLastClickedItem = new MutableLiveData<>();
        }
        mLastClickedItem.setValue(s);
    }

    public LiveData<String> getText() {
        return mText;
    }

    public LiveData<String> getLastClickedItem()
    {
        return mLastClickedItem;
    }
}
