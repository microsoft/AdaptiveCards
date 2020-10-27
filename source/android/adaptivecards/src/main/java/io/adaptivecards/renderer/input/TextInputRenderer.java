// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.text.Editable;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.TypedValue;
import android.view.ContextThemeWrapper;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseInputElement;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

import io.adaptivecards.renderer.input.customcontrols.ValidatedEditText;
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
        EditTextTouchListener(EditText editText)
        {
            m_editText = editText;
        }

        @Override
        public boolean onTouch(View v, MotionEvent event)
        {
            // Solution taken from here: https://stackoverflow.com/questions/6123973/android-edittext-vertical-scrolling-problem
            if (m_editText.hasFocus())
            {
                v.getParent().requestDisallowInterceptTouchEvent(true);
                switch (event.getAction() & MotionEvent.ACTION_MASK)
                {
                    case MotionEvent.ACTION_SCROLL:
                        v.getParent().requestDisallowInterceptTouchEvent(false);
                        break;
                }
            }
            return false;
        }

        private EditText m_editText = null;
    }

    private class EditTextKeyListener implements View.OnKeyListener
    {
        EditTextKeyListener(Object tag, ICardActionHandler actionHandler,
                            RenderedAdaptiveCard renderedCard, BaseActionElement action) {
            m_tag = tag;
            m_cardActionHandler = actionHandler;
            m_renderedAdaptiveCard = renderedCard;
            m_action = action;
        }

        @Override
        public boolean onKey(View view, int i, KeyEvent keyEvent) {
            if(view.getTag() == m_tag) {
                if(keyEvent.getAction() == KeyEvent.ACTION_DOWN && i == KeyEvent.KEYCODE_ENTER &&
                    m_action.GetElementType() == ActionType.Submit)
                {
                    m_cardActionHandler.onAction(m_action, m_renderedAdaptiveCard);
                    return true;
                }
            }
            return false;
        }

        private Object m_tag = null;
        private ICardActionHandler m_cardActionHandler;
        private RenderedAdaptiveCard m_renderedAdaptiveCard = null;
        private BaseActionElement m_action = null;
    }

    private class UnvalidatedTextWatcher implements TextWatcher
    {

        public UnvalidatedTextWatcher(TextInputHandler inputHandler)
        {
            m_textInputHandler = inputHandler;
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
            CardRendererRegistration.getInstance().notifyInputChange(m_textInputHandler.getId(), m_textInputHandler.getInput());
        }

        private TextInputHandler m_textInputHandler;
    }

    protected EditText renderInternal(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ViewGroup viewGroup,
            BaseInputElement baseInputElement,
            String value,
            String placeHolder,
            final TextInputHandler textInputHandler,
            HostConfig hostConfig,
            TagContent tagContent,
            RenderArgs renderArgs,
            boolean hasSpecificValidation)
    {
        EditText editText = null;

        if (baseInputElement.GetIsRequired() || hasSpecificValidation)
        {
            editText = new ValidatedEditText(context, getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));
        }
        else
        {
            editText = new EditText(context);
            editText.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
            // editText.addTextChangedListener(new UnvalidatedTextWatcher(textInputHandler));
        }

        editText.setFocusable(true);
        textInputHandler.setView(editText);
        renderedCard.registerInputHandler(textInputHandler, renderArgs.getContainerCardId());

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

        LinearLayout textInputViewGroup = null;

        if (baseInputElement instanceof TextInput)
        {
            TextInput textInput = (TextInput) baseInputElement;

            BaseActionElement action = textInput.GetInlineAction();

            if (action != null)
            {
                if ((hostConfig.GetActions().getShowCard().getActionMode() == ActionMode.Inline) &&
                    (action.GetElementType() == ActionType.ShowCard))
                {
                    renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Inline ShowCard not supported for InlineAction"));
                }
                else
                {
                    textInputViewGroup = new LinearLayout(context);
                    textInputViewGroup.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
                    editText.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
                    textInputViewGroup.addView(editText);

                    Resources.Theme theme = context.getTheme();
                    TypedValue buttonStyle = new TypedValue();

                    String url = action.GetIconUrl();
                    if (url != null && !url.isEmpty())
                    {
                        ImageButton inlineButton = null;
                        // check for style from resources
                        if (theme.resolveAttribute(R.attr.adaptiveInlineActionImage, buttonStyle, true))
                        {
                            Context themedContext = new ContextThemeWrapper(context, R.style.adaptiveInlineActionImage);
                            inlineButton = new ImageButton(themedContext, null, 0);
                        }
                        else
                        {
                            inlineButton = new ImageButton(context);
                            inlineButton.setBackgroundColor(Color.TRANSPARENT);
                            inlineButton.setPadding(16, 0, 0, 8);
                        }

                        InlineActionIconImageLoaderAsync imageLoader =
                                new InlineActionIconImageLoaderAsync(
                                        renderedCard,
                                        inlineButton,
                                        url,
                                        editText);

                        imageLoader.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, url);

                        if (Util.isOfType(action, SubmitAction.class) || action.GetElementType() == ActionType.Custom)
                        {
                            renderedCard.setCardForSubmitAction(Util.getViewId(inlineButton), renderArgs.getContainerCardId());
                        }

                        textInputViewGroup.addView(inlineButton, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, 0));
                    }
                    else
                    {
                        String title = action.GetTitle();
                        Button inlineButton = null;
                        // check for styles from references
                        if (theme.resolveAttribute(R.attr.adaptiveInlineAction, buttonStyle, true))
                        {
                            Context themedContext = new ContextThemeWrapper(context, R.style.adaptiveInlineAction);
                            inlineButton = new Button(themedContext, null, 0);
                        }
                        else
                        {
                            inlineButton = new Button(context);
                            inlineButton.setBackgroundColor(Color.TRANSPARENT);
                            inlineButton.setTextColor(Color.BLACK);
                            inlineButton.setPadding(16, 0, 0, 8);
                        }
                        inlineButton.setText(title);

                        if (Util.isOfType(action, SubmitAction.class) || action.GetElementType() == ActionType.Custom)
                        {
                            renderedCard.setCardForSubmitAction(Util.getViewId(inlineButton), renderArgs.getContainerCardId());
                        }

                        textInputViewGroup.addView(inlineButton, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, 0));
                    }
                    textInputViewGroup.setGravity(Gravity.CENTER);
                }
            }
        }


        View returnableView = editText;
        if (textInputViewGroup != null)
        {
            returnableView = textInputViewGroup;
        }

        viewGroup.addView(returnableView);

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
            RenderArgs renderArgs) throws Exception
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Text is not allowed"));
            return null;
        }

        TextInput textInput = Util.castTo(baseCardElement, TextInput.class);

        TextInputHandler textInputHandler = new TextInputHandler(textInput);
        TagContent tagContent = new TagContent(textInput, textInputHandler);
        final EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                textInput,
                textInput.GetValue(),
                textInput.GetPlaceholder(),
                textInputHandler,
                hostConfig,
                tagContent,
                renderArgs,
                !textInput.GetRegex().isEmpty());

        editText.setSingleLine(!textInput.GetIsMultiline());
        editText.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), editText);

        BaseActionElement action = textInput.GetInlineAction();

        if (textInput.GetIsMultiline())
        {
            editText.setLines(3);

            // Solution taken from here: https://stackoverflow.com/questions/6123973/android-edittext-vertical-scrolling-problem
            editText.setOnTouchListener(new EditTextTouchListener(editText));
        }
        else if (action != null)
        {
            // Add KeyListener if it's single line and action is submit, so when user touches enter key,
            // submit action will get triggered.
            editText.setOnKeyListener(new EditTextKeyListener(textInput, cardActionHandler, renderedCard, action));
        }

        setTextInputStyle(editText, textInput.GetTextInputStyle());
        int maxLength = (int) Math.min(textInput.GetMaxLength(), Integer.MAX_VALUE);
        if (maxLength > 0)
        {
            editText.setFilters(new InputFilter[] {new InputFilter.LengthFilter(maxLength)});
        }

        if (action != null)
        {
            // adds click listeners to buttons; it iterates through subviews, and grabs the button
            // this way is cleaner than modifying interface to accept a cardActionHandler
            // the subViewGroup has two child views
            View subView = viewGroup.getChildAt(viewGroup.getChildCount() - 1 );
            if (subView instanceof ViewGroup)
            {
                ViewGroup subViewGroup = (ViewGroup) subView;
                for (int index = 0; index < subViewGroup.getChildCount(); ++index)
                {
                    View view = subViewGroup.getChildAt(index);
                    if (view instanceof Button || view instanceof ImageButton)
                    {
                        view.setOnClickListener(new ActionElementRenderer.SelectActionOnClickListener(renderedCard, action, cardActionHandler));
                    }
                }
            }
        }
        return editText;
    }

    private class InlineActionIconImageLoaderAsync extends InnerImageLoaderAsync
    {
        private EditText m_editText;

        protected InlineActionIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String url, EditText editText)
        {
            super(renderedCard, containerView, url, containerView.getResources().getDisplayMetrics().widthPixels);
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
