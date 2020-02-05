// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import io.adaptivecards.objectmodel.DateTimePreparsedToken;
import io.adaptivecards.objectmodel.DateTimePreparsedTokenFormat;
import io.adaptivecards.objectmodel.DateTimePreparsedTokenVector;
import io.adaptivecards.objectmodel.DateTimePreparser;

import java.text.ParsePosition;
import java.util.Locale;
import java.util.Date;
import java.text.SimpleDateFormat;

public class DateTimeParser {

    public DateTimeParser(String language){
        m_language = new Locale(language);
    }

    public String GenerateString(DateTimePreparser text){
        String parsedString = new String();
        DateTimePreparsedTokenVector textSections = text.GetTextTokens();
        long textSectionLength = textSections.size();

        for(int i = 0; i < textSectionLength; ++i){
            DateTimePreparsedToken ts = textSections.get(i);
            // Java complains of the enum not being a constant type, so have to do this with if elses
            Date dateToParse = FormatDate(ts.GetYear(), ts.GetMonth(), ts.GetDay());
            if (ts.GetFormat() == DateTimePreparsedTokenFormat.DateCompact) {
                SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
                parsedString += dateFormat.format(dateToParse);
            } else {
                if (ts.GetFormat() == DateTimePreparsedTokenFormat.DateShort) {
                    SimpleDateFormat localizedFormat = new SimpleDateFormat("EEE, MMM dd, yyyy", m_language);
                    parsedString += localizedFormat.format(dateToParse);
                } else {
                    if (ts.GetFormat() == DateTimePreparsedTokenFormat.DateLong) {
                        SimpleDateFormat localizedFormat = new SimpleDateFormat("EEEE, MMMM dd, yyyy", m_language);
                        parsedString += localizedFormat.format(dateToParse);
                    } else {
                        parsedString += ts.GetText();
                    }
                }
            }
        }

        return parsedString;
    }

    private Date FormatDate(int year, int month, int day){
        SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
        try{
            String rawDate = (month + 1) + "/" + day + "/" + year;
            return dateFormat.parse(rawDate, new ParsePosition(0));
        } catch(Exception e){
            return new Date();
        }
    }

    private Locale m_language;

}
