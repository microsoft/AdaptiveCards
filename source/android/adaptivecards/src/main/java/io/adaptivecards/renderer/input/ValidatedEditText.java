package io.adaptivecards.renderer.input;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;

import io.adaptivecards.renderer.inputhandler.TextInputHandler;
import io.adaptivecards.renderer.inputhandler.validation.IInputValidator;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

@SuppressLint("AppCompatCustomView")
public class ValidatedEditText extends EditText
{
    private class ValidatedTextWatcher implements TextWatcher
    {

        public ValidatedTextWatcher(TextInputHandler inputHandler, IInputValidator inputValidator, ValidatedEditText inputView)
        {
            m_textInputHandler = inputHandler;
            m_inputValidator = inputValidator;
            m_inputView = inputView;
        }

        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after)
        {
        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count)
        {
        }

        @Override
        public void afterTextChanged(Editable s)
        {
            m_inputView.Validate();
            CardRendererRegistration.getInstance().notifyInputChange(m_textInputHandler.getId(), m_textInputHandler.getInput());
        }

        private TextInputHandler m_textInputHandler;
        private ValidatedEditText m_inputView;
    }


    public ValidatedEditText(Context context) {
        super(context);
    }

    public ValidatedEditText(Context context, IInputValidator inputValidator) {
        super(context);
        addTextChangedListener(new ValidatedTextWatcher(null, inputValidator, this));
        m_inputValidator = inputValidator;
    }

    public boolean Validate()
    {
        boolean isValid = m_inputValidator.isValid();
        GradientDrawable inputBorder = (GradientDrawable)getBackground();

        if (isValid)
        {
            // Change border color to green or whatever
            inputBorder.setStroke(4, Color.TRANSPARENT);
        }
        else
        {
            // Change border to red
            inputBorder.setStroke(4, Color.RED);
        }

        invalidate();

        return isValid;
    }

    private IInputValidator m_inputValidator = null;
}
