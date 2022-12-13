package io.adaptivecards.renderer;

import android.os.AsyncTask;

import androidx.annotation.NonNull;

import java.util.List;

import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestResult;

public abstract class DynamicChoicesServiceAsync extends AsyncTask<String, Void, HttpRequestResult<List<ChoiceInput>>> {

    public DynamicChoicesServiceAsync(ICardActionHandler cardActionHandler) {
        this.cardActionHandler = cardActionHandler;
    }

    @Override
    protected HttpRequestResult<List<ChoiceInput>> doInBackground(String... args) {
        // put null check
        return cardActionHandler.getDynamicChoices(args[0]);
    }

    @Override
    protected void onPostExecute(HttpRequestResult<List<ChoiceInput>> result)
    {
        if (result.isSuccessful())
        {
            List<ChoiceInput> choices = result.getResult();
            onSuccessfulPostExecute(choices);
//            Bitmap image = result.getResult();
//            if(image != null) {
//                image = styleBitmap(image);
//                image.setDensity(DisplayMetrics.DENSITY_DEFAULT);
//            }
//            onSuccessfulPostExecute(image);
        }
        else
        {
            onFailurePostExecute();
            //m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
        }
    }

    public abstract void onSuccessfulPostExecute(@NonNull List<ChoiceInput> choices);

    public abstract void onFailurePostExecute();

    private ICardActionHandler cardActionHandler;
}
