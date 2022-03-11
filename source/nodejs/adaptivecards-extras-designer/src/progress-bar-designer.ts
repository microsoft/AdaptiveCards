// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { TypedCardElementPeer, NumberPropertyEditor, PropertySheet, PropertySheetCategory, StringPropertyEditor } from "adaptivecards-designer";
import { ProgressBar } from "@microsoft/adaptivecards-extras";

export class ProgressBarPeer extends TypedCardElementPeer<ProgressBar> {
    static readonly titleProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "title", "Title", true);
    static readonly valueProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "value", "Value", 0);

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ProgressBarPeer.titleProperty,
            ProgressBarPeer.valueProperty);
    }
}
