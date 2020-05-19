package io.adaptivecards.renderer.input;

import android.content.Context;
import android.text.SpannableStringBuilder;
import android.view.View;
import android.widget.TextView;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ErrorMessageConfig;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.InputLabelConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.renderer.layout.StretchableElementLayout;
import io.adaptivecards.renderer.layout.StretchableInputLayout;
import io.adaptivecards.renderer.readonly.RendererUtil;
import io.adaptivecards.renderer.readonly.RichTextBlockRenderer;
import io.adaptivecards.renderer.readonly.TextBlockRenderer;

public class InputUtil
{

    public static View HandleLabelAndValidation(View inputView,
                                  BaseInputElement element,
                                  boolean hasSpecificValidation,
                                  BaseInputHandler inputHandler,
                                  Context context,
                                  HostConfig hostConfig,
                                  RenderArgs renderArgs)
    {
        // as first step we must figure out if the input requires a container layout
        // it will require a container layout if:
        // it needs to be stretched
        // it contains a label
        // it needs validation (has an error message or isrequired or hasSpecificValidation)
        // Specific validation refers to validation not in all input elements, e.g. regex or min/max

        boolean mustStretch = (element.GetHeight() == HeightType.Stretch);
        boolean inputHasLabel = !element.GetLabel().isEmpty();
        boolean inputHasErrorMessage = !element.GetErrorMessage().isEmpty();
        boolean requiresValidation = (element.GetIsRequired() ||  hasSpecificValidation);
        boolean requiresSurroundingLayout =  mustStretch || inputHasLabel || inputHasErrorMessage || requiresValidation;

        if (requiresSurroundingLayout)
        {
            StretchableInputLayout stretchableinputLayout = new StretchableInputLayout(context, mustStretch);

            if (inputHasLabel)
            {
                View inputLabel = RenderInputLabel(element.GetLabel(), element.GetIsRequired(), context, hostConfig, renderArgs);
                stretchableinputLayout.setLabel(inputLabel);

                // Render spacing
                BaseCardElementRenderer.setSpacingAndSeparator(context,
                    stretchableinputLayout,
                    hostConfig.GetInputs().getInputLabels().getInputSpacing(),
                    false /* separator */,
                    hostConfig,
                    false /* horizontalLine */,
                    false /* isImageSet */);
            }

            stretchableinputLayout.setInputView(inputView);

            if (inputHasErrorMessage)
            {
                // Render spacing
                View spacing = BaseCardElementRenderer.setSpacingAndSeparator(context,
                    stretchableinputLayout,
                    hostConfig.GetInputs().getErrorMessage().getSpacing(),
                    false /* separator */,
                    hostConfig,
                    false /* horizontalLine */,
                    false /* isImageSet */);

                View errorMessage = RenderErrorMessage(element.GetErrorMessage(), context, hostConfig, renderArgs);
                errorMessage.setTag(new TagContent(null, spacing, null));
                stretchableinputLayout.setErrorMessage(errorMessage);

                BaseCardElementRenderer.setVisibility(false, errorMessage);

                inputHandler.setInputLayout(stretchableinputLayout);
            }

            return stretchableinputLayout;
        }
        else
        {
            return inputView;
        }
    }

    public static View RenderInputLabel(String label, boolean isRequired, Context context, HostConfig hostConfig, RenderArgs renderArgs)
    {
        SpannableStringBuilder paragraph = new SpannableStringBuilder();
        CharSequence text = RendererUtil.handleSpecialText(label);
        paragraph.append(text);

        InputLabelConfig inputLabelConfig;
        if (isRequired)
        {
            inputLabelConfig = hostConfig.GetInputs().getInputLabels().getRequiredInputs();
        }
        else
        {
            inputLabelConfig = hostConfig.GetInputs().getInputLabels().getOptionalInputs();
        }

        paragraph = RichTextBlockRenderer.setColor(paragraph, 0, text.length(), inputLabelConfig.getColor(), inputLabelConfig.getIsSubtle(), hostConfig, renderArgs);

        if (isRequired)
        {
            int spanStart = text.length();

            paragraph.append(" *");
            paragraph = RichTextBlockRenderer.setColor(paragraph, spanStart, spanStart + 2, ForegroundColor.Attention, false, hostConfig, renderArgs);
        }

        TextView labelView = new TextView(context);
        labelView.setText(paragraph);

        TextBlockRenderer.getInstance().setTextFormat(labelView, hostConfig, FontType.Default, inputLabelConfig.getWeight());
        TextBlockRenderer.setTextSize(labelView, FontType.Default, inputLabelConfig.getSize(), hostConfig);

        return labelView;
    }

    public static TextView RenderErrorMessage(String message, Context context, HostConfig hostConfig, RenderArgs renderArgs)
    {
        SpannableStringBuilder paragraph = new SpannableStringBuilder();
        CharSequence text = RendererUtil.handleSpecialText(message);
        paragraph.append(text);

        paragraph = RichTextBlockRenderer.setColor(paragraph, 0, text.length(), ForegroundColor.Attention, false, hostConfig, renderArgs);

        TextView errorMessageView = new TextView(context);
        errorMessageView.setText(paragraph);

        ErrorMessageConfig errorMessageConfig  = hostConfig.GetInputs().getErrorMessage();
        TextBlockRenderer.getInstance().setTextFormat(errorMessageView, hostConfig, FontType.Default, errorMessageConfig.getWeight());
        TextBlockRenderer.setTextSize(errorMessageView, FontType.Default, errorMessageConfig.getSize(), hostConfig);

        errorMessageView.setVisibility(View.GONE);

        return errorMessageView;
    }

}
