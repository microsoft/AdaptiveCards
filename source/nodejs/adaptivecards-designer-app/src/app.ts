// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as monaco from "monaco-editor";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";
import * as ACTemplating from "adaptivecards-templating";
import * as Adaptive from "adaptivecards";
import "adaptivecards-designer/dist/adaptivecards-designer.css";
import "./app.css";

// Uncomment below if you plan to use an empty hostContainers array
// import "adaptivecards-designer/dist/adaptivecards-defaulthost.css";

window.onload = function() {
    ACTemplating.GlobalSettings.getUndefinedFieldValueSubstitutionString = (path: string) => { return "<" + path + " is undefined>" };

    ACDesigner.GlobalSettings.showVersionPicker = true;
    ACDesigner.GlobalSettings.enableDataBindingSupport = true;
    ACDesigner.GlobalSettings.showDataStructureToolbox = false;
    ACDesigner.GlobalSettings.showSampleDataEditorToolbox = true;

    // Uncomment to configure default toolbox titles
    /*
    ACDesigner.Strings.toolboxes.cardEditor.title = "Custom title";
    ACDesigner.Strings.toolboxes.cardStructure.title = "Custom title";
    ACDesigner.Strings.toolboxes.dataStructure.title = "Custom title";
    ACDesigner.Strings.toolboxes.propertySheet.title = "Custom title";
    ACDesigner.Strings.toolboxes.sampleDataEditor.title = "Custom title";
    ACDesigner.Strings.toolboxes.toolPalette.title = "Custom title";
    */

	ACDesigner.CardDesigner.onProcessMarkdown = (text: string, result: { didProcess: boolean, outputHtml: string }) => {
		result.outputHtml = new markdownit().render(text);
		result.didProcess = true;
	}

	if (!ACDesigner.SettingsManager.isLocalStorageAvailable) {
		console.log("Local storage is not available.");
    }

    // Uncomment to disable (de)serialization of a specific property
    /*
    Adaptive.CardElement.requiresProperty.isSerializationEnabled = false;
    */

    // Uncomment to add/remove properties to/from the renderer's schema
    /*
    Adaptive.SerializableObject.onRegisterCustomProperties = (sender: Adaptive.SerializableObject, schema: Adaptive.SerializableObjectSchema) => {
        if (sender instanceof Adaptive.TextBlock) {
            schema.remove(Adaptive.TextBlock.heightProperty);
        }
    }
    */
    
    // Uncomment to add/remove properties to/from the designer's property sheet
    /*
    ACDesigner.DesignerPeer.onPopulatePropertySheet = (sender: ACDesigner.DesignerPeer, propertySheet: ACDesigner.PropertySheet) => {
        if (sender instanceof ACDesigner.TextBlockPeer) {
            propertySheet.remove(ACDesigner.TextBlockPeer.maxLinesProperty);
        }
    }
    */

	let designer = new ACDesigner.CardDesigner(ACDesigner.defaultMicrosoftHosts);
	designer.sampleCatalogueUrl = window.location.origin + "/sample-catalogue.json";
	designer.attachTo(document.getElementById("designerRootHost"));

    /* Uncomment to test a custom palette item example
    let exampleSnippet = new ACDesigner.SnippetPaletteItem("Custom", "Example");
    exampleSnippet.snippet = {
        type: "ColumnSet",
        columns: [
            {
                width: "auto",
                items: [
                    {
                        type: "Image",
                        size: "Small",
                        style: "Person",
                        url: "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
                    }
                ]
            },
            {
                width: "stretch",
                items: [
                    {
                        type: "TextBlock",
                        text: "John Doe",
                        weight: "Bolder",
                        wrap: true
                    },
                    {
                        type: "TextBlock",
                        spacing: "None",
                        text: "Additional information",
                        wrap: true
                    }
                ]
            }
        ]
    };

    designer.customPaletteItems = [ exampleSnippet ];
    */

    designer.monacoModuleLoaded(monaco);

    let sampleData = {
        title: "Publish Adaptive Card Schema",
        description: "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
        creator: {
            name: "Matt Hidinger",
            profileImage: "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
        },
        createdUtc: "2017-02-14T06:08:39Z",
        viewUrl: "https://adaptivecards.io",
        properties: [
            { key: "Board", value: "Adaptive Cards" },
            { key: "List", value: "Backlog" },
            { key: "Assigned to", value: "Matt Hidinger" },
            { key: "Due date", value: "Not set" }
        ]
    };

    let sampleDataStructure: ACDesigner.IData = {
        valueType: "Object",
        fields: [
            {
                name: "title",
                displayName: "Title",
                valueType: "String",
                sampleValue: "Publish Adaptive Card Schema"
            },
            {
                name: "description",
                displayName: "Description",
                valueType: "String",
                sampleValue: "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation."
            },
            {
                name: "creator",
                displayName: "Creator",
                valueType: "Object",
                fields: [
                    {
                        name: "name",
                        displayName: "Name",
                        valueType: "String",
                        sampleValue: "Matt Hidinger"
                    },
                    {
                        name: "profileImage",
                        displayName: "Profile image URL",
                        valueType: "String",
                        sampleValue: "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
                    }
                ]
            },
            {
                name: "createdUtc",
                displayName: "Date created",
                valueType: "String",
                sampleValue: "2017-02-14T06:08:39Z"
            },
            {
                name: "viewUrl",
                displayName: "View URL",
                valueType: "String",
                sampleValue: "https://adaptivecards.io"
            },
            {
                name: "properties",
                displayName: "Properties",
                valueType: "Array",
                itemType: {
                    valueType: "Object",
                    fields: [
                        {
                            name: "key",
                            displayName: "Key",
                            valueType: "String",
                            sampleValue: "Sample key"
                        },
                        {
                            name: "value",
                            displayName: "Value",
                            valueType: "String",
                            sampleValue: "Sample value"
                        }
                    ]
                }
            }
        ]
    };

    /*
	let sampleData = {
		firstName: "John",
		lastName: "Doe",
		age: 45,
		isMarried: true,
		address: {
			street: "1234 555th Ave NE",
			city: "Redmond",
			state: "WA",
			countryOrRegion: "USA"
		},
		children: [
			{
				firstName: "Jennifer",
				lastName: "Doe",
				age: 9
			},
			{
				firstName: "James",
				lastName: "Doe",
				age: 13
			}
		]
    };

    let sampleDataStructure: ACDesigner.IData = {
        valueType: "Object",
        fields: [
            {
                name: "firstName",
                displayName: "First name",
                valueType: "String",
                sampleValue: "John"
            },
            {
                name: "lastName",
                displayName: "Last name",
                valueType: "String",
                sampleValue: "Doe"
            },
            {
                name: "age",
                displayName: "Age",
                valueType: "Number",
                sampleValue: 36
            },
            {
                name: "isMarried",
                displayName: "Married",
                valueType: "Boolean",
                sampleValue: false
            },
            {
                name: "address",
                displayName: "Address",
                valueType: "Object",
                fields: [
                    {
                        name: "street",
                        displayName: "Street",
                        valueType: "String",
                        sampleValue: "1234 555th Ave NE"
                    },
                    {
                        name: "city",
                        displayName: "City",
                        valueType: "String",
                        sampleValue: "Redmond"
                    },
                    {
                        name: "state",
                        displayName: "State",
                        valueType: "String",
                        sampleValue: "WA"
                    },
                    {
                        name: "countryOrRegion",
                        displayName: "Country/region",
                        valueType: "String",
                        sampleValue: "USA"
                    }
                ]
            },
            {
                name: "children",
                displayName: "Children",
                valueType: "Array",
                itemType: {
                    valueType: "Object",
                    fields: [
                        {
                            name: "firstName",
                            displayName: "First name",
                            valueType: "String",
                            sampleValue: "Jennifer"
                        },
                        {
                            name: "lastName",
                            displayName: "Last name",
                            valueType: "String",
                            sampleValue: "Doe"
                        },
                        {
                            name: "age",
                            displayName: "Age",
                            valueType: "Number",
                            sampleValue: 13
                        }
                    ]
                }
            }
        ]
    };
    */

	designer.dataStructure = ACDesigner.FieldDefinition.parse(sampleDataStructure);
    // designer.lockDataStructure = true;
    designer.sampleData = sampleData;
    designer.bindingPreviewMode = ACDesigner.BindingPreviewMode.SampleData;
}
