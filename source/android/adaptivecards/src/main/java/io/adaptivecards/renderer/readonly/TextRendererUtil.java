// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.graphics.Typeface;
import android.view.View;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextStyle;
import io.adaptivecards.objectmodel.TextWeight;
import io.adaptivecards.renderer.RenderArgs;

public class TextRendererUtil
{
    private static Map<String, Typeface> customTypefaces = new HashMap<>();
    private static HashSet<String> systemFonts = null;
    private static HashSet<String> monospaceSystemFonts = null;
    private static Map<String, Typeface> systemTypefaces = new HashMap<>();
    private static Map<String, String> lightSystemFonts = null;

    public static void registerCustomTypeface(String name, Typeface typeface) {

        customTypefaces.put(name, typeface);
    }

    static boolean fontHasLightVersion(String fontFamily)
    {
        if (lightSystemFonts == null)
        {
            lightSystemFonts = new HashMap<>();

            // Retrieved list of family fonts from here, there's little to no documentation of valid font names
            // https://android.googlesource.com/platform/frameworks/base/+/master/data/fonts/fonts.xml
            lightSystemFonts.put("sans-serif", "sans-serif-light");
            lightSystemFonts.put("arial", "sans-serif-light");
            lightSystemFonts.put("helvetica", "sans-serif-light");
            lightSystemFonts.put("tahoma", "sans-serif-light");
            lightSystemFonts.put("verdana", "sans-serif-light");

            lightSystemFonts.put("sans-serif-condensed", "sans-serif-condensed-light");
        }

        return lightSystemFonts.containsKey(fontFamily);
    }

    static boolean fontExistsInSystem(String fontFamily)
    {
        if (systemFonts == null)
        {
            systemFonts = new HashSet<>();

            systemFonts.add("sans-serif");
            systemFonts.add("arial");
            systemFonts.add("helvetica");
            systemFonts.add("tahoma");
            systemFonts.add("verdana");
            systemFonts.add("sans-serif-condensed");
            systemFonts.add("serif");
            systemFonts.add("times");
            systemFonts.add("times new roman");
            systemFonts.add("palatino");
            systemFonts.add("georgia");
            systemFonts.add("baskerville");
            systemFonts.add("goudy");
            systemFonts.add("fantasy");
            systemFonts.add("ITC Stone Serif");
            systemFonts.add("casual");
            systemFonts.add("cursive");
            systemFonts.add("sans-serif-smallcaps");
            systemFonts.add("source-sans-pro");
        }

        return systemFonts.contains(fontFamily);
    }

    static boolean fontIsMonospace(String fontFamily)
    {
        if (monospaceSystemFonts == null)
        {
            // This should render as monospace
            monospaceSystemFonts = new HashSet<>();
            monospaceSystemFonts.add("sans-serif-monospace");
            monospaceSystemFonts.add("monaco");
            monospaceSystemFonts.add("serif-monospace");
            monospaceSystemFonts.add("courier");
            monospaceSystemFonts.add("courier new");
        }

        return monospaceSystemFonts.contains(fontFamily);
    }

    static Typeface getSystemTypeface(String fontName)
    {
        if (!systemTypefaces.containsKey(fontName))
        {
            systemTypefaces.put(fontName, Typeface.create(fontName, Typeface.NORMAL));
        }

        return systemTypefaces.get(fontName);
    }

    static int getTextAlignment(HorizontalAlignment textAlignment)
    {
        int alignment;
        if (textAlignment == HorizontalAlignment.Center)
        {
            alignment = View.TEXT_ALIGNMENT_CENTER;
        }
        else if (textAlignment == HorizontalAlignment.Left)
        {
            alignment = View.TEXT_ALIGNMENT_VIEW_START;
        }
        else if (textAlignment == HorizontalAlignment.Right)
        {
            alignment = View.TEXT_ALIGNMENT_VIEW_END;
        }
        else
        {
            throw new IllegalArgumentException("Invalid text alignment: " + textAlignment.toString());
        }

        return alignment;
    }

    static TextSize computeTextSize(HostConfig hostConfig, TextStyle declaredStyle, TextSize declaredSize, RenderArgs renderArgs)
    {
        if (declaredSize != null)
        {
            return declaredSize;
        }
        if (declaredStyle == TextStyle.Heading)
        {
            return hostConfig.GetTextStyles().getHeading().getSize();
        }
        if (declaredStyle == null && renderArgs != null && renderArgs.isColumnHeader())
        {
            return hostConfig.GetTextStyles().getColumnHeader().getSize();
        }
        return TextSize.Default;
    }

    static ForegroundColor computeTextColor(HostConfig hostConfig, TextStyle declaredStyle, ForegroundColor declaredColor, RenderArgs renderArgs)
    {
        if (declaredColor != null)
        {
            return declaredColor;
        }
        if (declaredStyle == TextStyle.Heading)
        {
            return hostConfig.GetTextStyles().getHeading().getColor();
        }
        if (declaredStyle == null && renderArgs != null && renderArgs.isColumnHeader())
        {
            return hostConfig.GetTextStyles().getColumnHeader().getColor();
        }
        return ForegroundColor.Default;
    }

    static TextWeight computeTextWeight(HostConfig hostConfig, TextStyle declaredStyle, TextWeight declaredWeight, RenderArgs renderArgs)
    {
        if (declaredWeight != null)
        {
            return declaredWeight;
        }
        if (declaredStyle == TextStyle.Heading)
        {
            return hostConfig.GetTextStyles().getHeading().getWeight();
        }
        if (declaredStyle == null && renderArgs != null &&  renderArgs.isColumnHeader())
        {
            return hostConfig.GetTextStyles().getColumnHeader().getWeight();
        }
        return TextWeight.Default;
    }

    static boolean computeIsSubtle(HostConfig hostConfig, TextStyle declaredStyle, Boolean declaredIsSubtle, RenderArgs renderArgs)
    {
        if (declaredIsSubtle != null)
        {
            return declaredIsSubtle;
        }
        if (declaredStyle == TextStyle.Heading)
        {
            return hostConfig.GetTextStyles().getHeading().getIsSubtle();
        }
        if (declaredStyle == null && renderArgs != null &&  renderArgs.isColumnHeader())
        {
            return hostConfig.GetTextStyles().getColumnHeader().getIsSubtle();
        }
        return false;
    }

    static FontType computeFontType(HostConfig hostConfig, TextStyle declaredStyle, FontType declaredFontType, RenderArgs renderArgs)
    {
        if (declaredFontType != null)
        {
            return declaredFontType;
        }
        if (declaredStyle == TextStyle.Heading)
        {
            return hostConfig.GetTextStyles().getHeading().getFontType();
        }
        if (declaredStyle == null && renderArgs != null &&  renderArgs.isColumnHeader())
        {
            return hostConfig.GetTextStyles().getColumnHeader().getFontType();
        }
        return FontType.Default;
    }

    static long getTextSize(FontType type, TextSize textSize, HostConfig hostConfig)
    {
        return hostConfig.GetFontSize(type, textSize);
    }

    static String cleanFontFamilyName(String fontFamily)
    {
        String fontFamilyName = fontFamily.trim();
        if (!fontFamilyName.isEmpty() && fontFamilyName.charAt(0) == '\'')
        {
            fontFamilyName = fontFamilyName.replace("'", "");

        }
        fontFamilyName = fontFamilyName.toLowerCase();

        return fontFamilyName;
    }

    static Typeface getTextFormat(HostConfig hostConfig, FontType type, boolean isLightWeigthed)
    {
        String[] fontFamilies = hostConfig.GetFontFamily(type).split(",");

        if (hostConfig.GetFontFamily().isEmpty() && type == FontType.Monospace)
        {
            return Typeface.MONOSPACE;
        }

        for (String fontFamily : fontFamilies)
        {
            fontFamily = cleanFontFamilyName(fontFamily);
            String lightFontFamily = fontFamily + "-light";

            if (customTypefaces.containsKey(fontFamily))
            {
                return customTypefaces.get(fontFamily);
            }
            else if (isLightWeigthed && customTypefaces.containsKey(lightFontFamily))
            {
                return customTypefaces.get(lightFontFamily);
            }
            else if (!isLightWeigthed && fontExistsInSystem(fontFamily))
            {
                return getSystemTypeface(fontFamily);
            }
            else if (isLightWeigthed && fontHasLightVersion(fontFamily))
            {
                return getSystemTypeface(lightSystemFonts.get(fontFamily));
            }
            else if (fontFamily.isEmpty() && type == FontType.Monospace || fontIsMonospace(fontFamily))
            {
                return Typeface.MONOSPACE;
            }
        }

        // If the font was not found but it was requested as light, default to sans-serif-light
        if (isLightWeigthed)
        {
            return getSystemTypeface("sans-serif-light");
        }

        return Typeface.create((String) null, Typeface.NORMAL);
    }

    static String getTextColor(ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        return hostConfig.GetForegroundColor(containerStyle, foregroundColor, isSubtle);
    }

    static String getHighlightColor(ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        return hostConfig.GetHighlightColor(containerStyle, foregroundColor, isSubtle);
    }

    static int getTextWeight(TextWeight textWeight)
    {
        int weight;
        if (textWeight == TextWeight.Default)
        {
            weight = Typeface.NORMAL;
        }
        else if (textWeight == TextWeight.Bolder)
        {
            weight = Typeface.BOLD;
        }
        else if (textWeight == TextWeight.Lighter)
        {
            weight = Typeface.NORMAL;
        }
        else
        {
            throw new IllegalArgumentException("Invalid text weight: " + textWeight.toString());
        }

        return weight;
    }

}
