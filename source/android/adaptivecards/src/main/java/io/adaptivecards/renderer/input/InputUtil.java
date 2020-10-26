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
            }

            paragraph.append(requiredLabelSuffix);
            paragraph = RichTextBlockRenderer.setColor(paragraph, spanStart, spanStart + requiredLabelSuffix.length(), ForegroundColor.Attention, false, hostConfig, renderArgs);
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
