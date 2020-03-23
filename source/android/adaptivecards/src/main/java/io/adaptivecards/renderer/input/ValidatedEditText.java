package io.adaptivecards.renderer.input;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;

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
            if (m_hasGainedFocus)
            {
                m_inputView.Validate();
            }

            CardRendererRegistration.getInstance().notifyInputChange(m_textInputHandler.getId(), m_textInputHandler.getInput());
        }

        private TextInputHandler m_textInputHandler;
        private ValidatedEditText m_inputView;
    }

    public ValidatedEditText(Context context) {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }

    public ValidatedEditText(Context context, Color errorColor, TextInputHandler inputHandler, IInputValidator inputValidator) {
        this(context);
        m_errorColor = errorColor;

        addTextChangedListener(new ValidatedTextWatcher(inputHandler, inputValidator, this));

        setOnFocusChangeListener(new OnFocusChangeListener() {
            @Override
            public void onFocusChange(View view, boolean b) {
                if (hasFocus())
                {
                    m_hasGainedFocus = true;
                }
            }
        });

        m_inputValidator = inputValidator;
    }

    public boolean Validate()
    {
        boolean isValid = m_inputValidator.isValid();
        if (isValid)
        {
            // Change border color to original color
            getBackground().setColorFilter(null);
        }
        else
        {
            // Change border to red
            getBackground().setColorFilter(Color.RED, PorterDuff.Mode.SRC_ATOP);
        }
        return isValid;
    }

    private Color m_errorColor = null;
    private IInputValidator m_inputValidator = null;
    private boolean m_hasGainedFocus = false;
}
