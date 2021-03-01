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
}
