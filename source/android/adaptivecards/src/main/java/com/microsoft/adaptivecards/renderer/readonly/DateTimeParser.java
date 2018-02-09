package com.microsoft.adaptivecards.renderer.readonly;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.TextBlockText;
import com.microsoft.adaptivecards.objectmodel.TextSection;
import com.microsoft.adaptivecards.objectmodel.TextSectionFormat;
import com.microsoft.adaptivecards.objectmodel.TextSectionVector;

import java.util.Locale;
import java.util.Date;
import java.text.SimpleDateFormat;

public class DateTimeParser {


    public DateTimeParser(String language){
        m_language = new Locale(language);
    }

    public String GenerateString(TextBlockText text){
        String parsedString = new String();
        TextSectionVector textSections = text.GetString();
        long textSectionLength = textSections.size();

        for(int i = 0; i < textSectionLength; ++i){
            TextSection ts = textSections.get(i);
            // Java complains of the enum not being a constant type, so have to do this with if elses
            if(ts.GetFormat() == TextSectionFormat.Time){
                SimpleDateFormat timeFormat = new SimpleDateFormat("hh:mm aaa");
                String time = timeFormat.format(FormatTime(ts.GetHour(), ts.GetMinute()));
                parsedString += time;
            } else {
                Date dateToParse = FormatDate(ts.GetYear(), ts.GetMonth(), ts.GetDay());
                if (ts.GetFormat() == TextSectionFormat.DateCompact) {
                    SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
                    parsedString += dateFormat.format(dateToParse);
                } else {
                    if (ts.GetFormat() == TextSectionFormat.DateShort) {
                        SimpleDateFormat localizedFormat = new SimpleDateFormat("E, M d, y", m_language);
                        parsedString += localizedFormat.format(dateToParse);
                    } else {
                        if (ts.GetFormat() == TextSectionFormat.DateLong) {
                            SimpleDateFormat localizedFormat = new SimpleDateFormat("E, M d, y", m_language);
                            parsedString += localizedFormat.format(dateToParse);
                        } else {
                            parsedString += ts.GetOriginalText();
                        }
                    }
                }
            }
        }

        return parsedString;
    }

    private Date FormatTime(int hour, int minute)
    {
        SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");
        try {
            return timeFormat.parse(hour + ":" + minute);
        } catch (Exception e){
            return new Date(); // I dont know, return today, the method shouldnt fail after all
        }
    }

    private Date FormatDate(int year, int month, int day){
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/mm/yyyy");
        try{
            return dateFormat.parse(day + "/" + month + "/" + year);
        } catch(Exception e){
            return new Date();
        }
    }

    private Locale m_language;

}
