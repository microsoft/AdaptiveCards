// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input;

import android.content.Context;
import android.text.SpannableStringBuilder;
import android.view.View;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ErrorMessageConfig;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.InputLabelConfig;
import io.adaptivecards.objectmodel.TextStyle;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.readonly.RendererUtil;
import io.adaptivecards.renderer.readonly.RichTextBlockRenderer;
import io.adaptivecards.renderer.readonly.TextBlockRenderer;

public class InputUtil
{
    public static TextView RenderInputLabel(String label, boolean isRequired, Context context, HostConfig hostConfig, RenderArgs renderArgs)
    {
        SpannableStringBuilder paragraph = new SpannableStringBuilder();
        CharSequence text = RendererUtil.handleSpecialText(label);
        paragraph.append(text);

        CharSequence labelContentDescription = text;

        InputLabelConfig inputLabelConfig;
        if (isRequired)
        {
            inputLabelConfig = hostConfig.GetInputs().getLabel().getRequiredInputs();
        }
        else
        {
            inputLabelConfig = hostConfig.GetInputs().getLabel().getOptionalInputs();
        }

        paragraph = RichTextBlockRenderer.setColor(paragraph, 0, text.length(), inputLabelConfig.getColor(), inputLabelConfig.getIsSubtle(), hostConfig, renderArgs);

        if (isRequired)
        {
            int spanStart = text.length();
            String requiredLabelSuffix = inputLabelConfig.getSuffix();
            if (requiredLabelSuffix == null || requiredLabelSuffix.isEmpty())
            {
                requiredLabelSuffix = " *";

                // TalkBack should read "required" instead of "asterisk"
                labelContentDescription += " required";
            }
            else
            {
                labelContentDescription += requiredLabelSuffix;
            }

            paragraph.append(requiredLabelSuffix);
            paragraph = RichTextBlockRenderer.setColor(paragraph, spanStart, spanStart + requiredLabelSuffix.length(), ForegroundColor.Attention, false, hostConfig, renderArgs);
        }

        TextView labelView = new TextView(context);
        labelView.setText(paragraph);
        labelView.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_START);
        labelView.setContentDescription(labelContentDescription);

        TextBlockRenderer.applyTextFormat(labelView, hostConfig, TextStyle.Default, FontType.Default, inputLabelConfig.getWeight(), renderArgs);
        TextBlockRenderer.applyTextSize(labelView, hostConfig, TextStyle.Default, FontType.Default, inputLabelConfig.getSize(), renderArgs);

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
        TextBlockRenderer.applyTextFormat(errorMessageView, hostConfig, TextStyle.Default, FontType.Default, errorMessageConfig.getWeight(), renderArgs);
        TextBlockRenderer.applyTextSize(errorMessageView, hostConfig, TextStyle.Default, FontType.Default, errorMessageConfig.getSize(), renderArgs);

        errorMessageView.setVisibility(View.GONE);

        return errorMessageView;
    }

}
