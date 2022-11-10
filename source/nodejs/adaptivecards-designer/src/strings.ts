import { WidgetContainer } from "./containers";

export class Strings {
    static readonly toolboxes = {
        toolPalette: {
            title: "CARD ELEMENTS"
        },
        cardEditor: {
            title: "CARD PAYLOAD EDITOR"
        },
        sampleDataEditor: {
            title: "SAMPLE DATA EDITOR"
        },
        sampleHostDataEditor: {
            title: "SAMPLE HOST DATA EDITOR"
        },
        propertySheet: {
            title: "ELEMENT PROPERTIES",
            commands: {
                bindData: {
                    displayText: () => "...",
                    accessibleText: (propertyLabel: string) => "Data Binding"
                }
            }
        },
        cardStructure: {
            title: "CARD STRUCTURE"
        },
        dataStructure: {
            title: "DATA STRUCTURE"
        }
    };
    static loadingEditor = "Loading editor...";
    static readonly widgetOverflowWarning = `[Designer] We have adjusted your card to hide overflow elements. Please ensure all card elements are contained within the proper card height per Widgets Board design guidelines. Only Carousel pagination dots can be present in the bottom ${WidgetContainer.widgetPadding}px margin of a widget.`;
}
