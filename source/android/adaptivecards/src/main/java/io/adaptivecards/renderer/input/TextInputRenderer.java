package io.adaptivecards.renderer.input;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.support.v4.app.FragmentManager;
import android.text.Editable;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.TypedValue;
import android.view.ContextThemeWrapper;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.Sentiment;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

import io.adaptivecards.renderer.inputhandler.TextInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.TextInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextInputStyle;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;


public class TextInputRenderer extends BaseCardElementRenderer
{
    protected TextInputRenderer()
    {
    }

    public static TextInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new TextInputRenderer();
        }

        return s_instance;
    }

    protected void setTextInputStyle(EditText editText, TextInputStyle textInputStyle)
    {
        if (textInputStyle == TextInputStyle.Text)
        {
            // do nothing
        }
        else if (textInputStyle == TextInputStyle.Tel)
        {
            editText.setInputType(InputType.TYPE_CLASS_PHONE);
        }
        else if (textInputStyle == TextInputStyle.Url)
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_URI);
        }
        else if (textInputStyle == TextInputStyle.Email)
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
        }
        else
        {
            throw new IllegalArgumentException("Unknown TextInputStyle: " + textInputStyle.toString());
        }
    }

    private class EditTextTouchListener implements View.OnTouchListener
    {
        EditTextTouchListener(Object tag)
        {
            m_tag = tag;
        }

        @Override
        public boolean onTouch(View v, MotionEvent event)
        {
            // Solution taken from here: https://stackoverflow.com/questions/6123973/android-edittext-vertical-scrolling-problem
            if (v.getTag() == m_tag)
            {
                v.getParent().requestDisallowInterceptTouchEvent(true);
                switch (event.getAction() & MotionEvent.ACTION_MASK)
                {
                    case MotionEvent.ACTION_UP:
                        v.getParent().requestDisallowInterceptTouchEvent(false);
                        break;
                }
            }
            return false;
        }

        private Object m_tag = null;
    }

    protected EditText renderInternal(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ViewGroup viewGroup,
            BaseInputElement baseInputElement,
            String value,
            String placeHolder,
            final TextInputHandler textInputHandler,
            HostConfig hostConfig)
    {
        EditText editText = new EditText(context);
        textInputHandler.setView(editText);
        editText.setTag(textInputHandler);
        editText.setTextColor(Color.BLACK);
        renderedCard.registerInputHandler(textInputHandler);

        if (!TextUtils.isEmpty(value))
        {
            editText.setText(value);
        }

        if (!TextUtils.isEmpty(placeHolder))
        {
            editText.setHint(placeHolder);
        }
        editText.addTextChangedListener(new TextWatcher()
        {
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
                CardRendererRegistration.getInstance().notifyInputChange(textInputHandler.getId(), textInputHandler.getInput());
            }
        });

        TextInput textInput = (TextInput)baseInputElement;
        BaseActionElement action = textInput.GetInlineAction();
        boolean supportsInteractivity = hostConfig.getSupportsInteractivity();

        LinearLayout textInputViewGroup = null;
        if(action != null)
        {
            if (hostConfig.getActions().getShowCard().getActionMode() == ActionMode.Inline &&
                (textInput.GetInlineAction() instanceof ShowCardAction))
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Inline ShowCard not supported for InlineAction"));
            }
            else
            {
                Resources.Theme theme = context.getTheme();
                textInputViewGroup = new LinearLayout(context);
                editText.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
                textInputViewGroup.addView(editText);

                String title =  action.GetTitle(), url = action.GetIconUrl();
                TypedValue buttonStyle = new TypedValue();
                if(url != null && !url.isEmpty())
                {
                    ImageButton inlineButton = null;
                    /*
                    if(theme.resolveAttribute(R.attr.adaptiveInlineActionImage, buttonStyle, true))
                    {
                        //return createButtonWithTheme(context, buttonStyle.data);
                        Context themedContext = new ContextThemeWrapper(context, R.style.adaptiveInlineActionImage);
                        inlineButton = new ImageButton(themedContext, null, 0);
                    }
                    else*/
                    {
                        inlineButton = new ImageButton(context);
                    }

                    InlineActionIconImageLoaderAsync imageLoader =
                        new InlineActionIconImageLoaderAsync(
                            renderedCard,
                            inlineButton,
                            url,
                            editText
                        );
                    imageLoader.execute(url);
                    textInputViewGroup.addView(inlineButton);
                }
                else
                {
                    Button inlineButton = null;
                    /*
                    if(theme.resolveAttribute(R.attr.adaptiveInlineAction, buttonStyle, true))
                    {
                        Context themedContext = new ContextThemeWrapper(context, R.style.adaptiveInlineAction);
                        inlineButton = new Button(themedContext, null, 0);
                    }
                    else*/
                    {
                        inlineButton = new Button(context);
                    }
                    inlineButton.setText(title);
                    textInputViewGroup.addView(inlineButton);
                }
            }

        }
        if(baseInputElement.GetHeight() == HeightType.Stretch)
        {
            LinearLayout containerLayout = new LinearLayout(context);
            containerLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));

            containerLayout.addView(editText);
            viewGroup.addView(containerLayout);
        }
        else
        {
            if(textInputViewGroup != null)
            {
                editText.setPadding(0,0,0,0);
                viewGroup.addView(textInputViewGroup);
            }
            else
            {
                editText.setPadding(0,0,0,0);
                viewGroup.addView(editText);
            }
        }
        return editText;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Text is not allowed"));
            return null;
        }

        TextInput textInput = null;
        if (baseCardElement instanceof TextInput)
        {
            textInput = (TextInput) baseCardElement;
        }
        else if ((textInput = TextInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextInput object model.");
        }

        TextInputHandler textInputHandler = new TextInputHandler(textInput);
        setSpacingAndSeparator(context, viewGroup, textInput.GetSpacing(), textInput.GetSeparator(), hostConfig, true /* horizontal line */);
        final EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                textInput,
                textInput.GetValue(),
                textInput.GetPlaceholder(),
                textInputHandler,
                hostConfig);
        editText.setSingleLine(!textInput.GetIsMultiline());
        editText.setTag(textInput);
        if (textInput.GetIsMultiline())
        {
            editText.setLines(3);
            // Solution taken from here: https://stackoverflow.com/questions/6123973/android-edittext-vertical-scrolling-problem
            editText.setOnTouchListener(new EditTextTouchListener(textInput));

        }
        setTextInputStyle(editText, textInput.GetTextInputStyle());
        int maxLength = (int) Math.min(textInput.GetMaxLength(), Integer.MAX_VALUE);
        if (maxLength > 0)
        {
            editText.setFilters(new InputFilter[] {new InputFilter.LengthFilter(maxLength)});
        }

        return editText;
    }

    private class InlineActionIconImageLoaderAsync extends InnerImageLoaderAsync
    {
        private EditText m_editText;

        protected InlineActionIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String url, EditText editText)
        {
            super(renderedCard, containerView, url);
            m_editText = editText;
        }

        @Override
        protected void renderBitmap(Bitmap bitmap)
        {
            ImageButton button = (ImageButton) super.m_view;
            Drawable drawableIcon = new BitmapDrawable(null, bitmap);

            double editTextHeight = (m_editText.getLineHeight() + (int) m_editText.getLineSpacingExtra()) * 2.5;
            double intrinsicWidth = drawableIcon.getIntrinsicHeight();
            double scaleRatio = (editTextHeight )/ drawableIcon.getIntrinsicHeight();
            double imageWidth = scaleRatio * drawableIcon.getIntrinsicWidth();
            button.setImageDrawable(new BitmapDrawable(null, Bitmap.createScaledBitmap(bitmap, (int)imageWidth, (int)editTextHeight, false)));
        }
    }

    private static TextInputRenderer s_instance = null;
}
