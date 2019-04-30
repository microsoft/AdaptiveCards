// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";
import * as Azure from "@azure/storage-blob";
import { AZURE_STORAGE_ACCOUNT_NAME, AZURE_STORAGE_SAS } from "./secrets";
import { generateUuid } from "ms-rest-js";
import "adaptivecards-designer/dist/adaptivecards-designer.css";
import "./app.css";

const card = `{
    "type": "AdaptiveCard",
    "body": [
        {
            "type": "TextBlock",
            "size": "Large",
            "text": "Please complete this referral request",
            "wrap": true
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Patient Name"
        },
        {
            "type": "Input.Text",
            "id": "PatientName",
            "placeholder": "Placeholder text"
        },
        {
            "type": "Input.Toggle",
            "id": "HasInsurance",
            "title": "Does this patient have insurance?",
            "value": "false"
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Referring To"
        },
        {
            "type": "Input.Text",
            "id": "DoctorName",
            "placeholder": "Placeholder text"
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Referral Need"
        },
        {
            "type": "Input.Text",
            "id": "ReferralNeed",
            "placeholder": "Placeholder text"
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Are you the referring physician?"
        },
        {
            "type": "Input.ChoiceSet",
            "id": "Rating",
            "placeholder": "Placeholder text",
            "choices": [
                {
                    "title": "Yes",
                    "value": "yes"
                },
                {
                    "title": "No",
                    "value": "no"
                }
            ],
            "style": "expanded"
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Requested Date for Appointment"
        },
        {
            "type": "Input.Date",
            "id": "RequestedDate"
        },
        {
            "type": "TextBlock",
            "color": "Accent",
            "text": "Any notes we should add for the doctor?"
        },
        {
            "type": "Input.Text",
            "id": "Notes",
            "placeholder": "Let us know!",
            "isMultiline": true
        }
    ],
    "actions": [
        {
            "type": "Action.Submit",
            "id": "Submit",
            "title": "Submit Referral"
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.0"
}`;

const pipeline = Azure.StorageURL.newPipeline(new Azure.AnonymousCredential());
const serviceURL = new Azure.ServiceURL(`https://${AZURE_STORAGE_ACCOUNT_NAME}.blob.core.windows.net?${AZURE_STORAGE_SAS}`, pipeline);
let designer: ACDesigner.CardDesigner;



function saveCard() {

	// List containers

	// Create a container
	//   const containerName = `newcontainer${new Date().getTime()}`;
	//   const containerURL = Azure.ContainerURL.fromServiceURL(serviceURL, containerName);
	//   await containerURL.create(Azure.Aborter.None);

	const containerURL = Azure.ContainerURL.fromServiceURL(serviceURL, "newcontainer1556579201786");

	const blobURL = Azure.BlockBlobURL.fromContainerURL(containerURL, `${generateUuid()}.json`);

	let card = designer.getCard();

	var blob = new Blob([JSON.stringify(card)]);

	Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {blobHTTPHeaders: { blobContentType: "application/json"}})
	alert("Saved!");

}

window.onload = async function () {

	let marker;
	do {
		const listContainersResponse = await serviceURL.listContainersSegment(
			Azure.Aborter.None,
			marker
		);

		marker = listContainersResponse.nextMarker;
		for (const container of listContainersResponse.containerItems) {
			console.log(`Container: ${container.name}`);
		}
	} while (marker);

	// Comment to disable preview features (data binding)
	ACDesigner.GlobalSettings.previewFeaturesEnabled = false;

	ACDesigner.CardDesigner.onProcessMarkdown = (text: string, result: { didProcess: boolean, outputHtml: string }) => {
		result.outputHtml = new markdownit().render(text);
		result.didProcess = true;
	}

	let hostContainers: Array<ACDesigner.HostContainer> = [];
	hostContainers.push(new ACDesigner.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"));

	designer = new ACDesigner.CardDesigner(hostContainers);
	designer.sampleCatalogueUrl = window.location.origin + "/sample-catalogue.json";
	designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker).isVisible = false;
	//designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.CopyJSON).isVisible = false;

	let saveButton = new ACDesigner.ToolbarButton(
        "saveButton",
        "Save",
        null,
        (sender) => { saveCard(); });
    saveButton.separator = true;
    designer.toolbar.insertElementAfter(saveButton, ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker);
 


	designer.attachTo(document.getElementById("designerRootHost"));

	designer.jsonEditorToolbox.collapse();

	designer.setCard(JSON.parse(card));


	/* Uncomment to test a custom palette item example */
	let exampleSnippet = new ACDesigner.SnippetPaletteItem("Data Fields", "Patient Referrer");
	exampleSnippet.snippet = {
		"type": "Input.Text"
	};

	designer.customPaletteItems = [exampleSnippet];


	designer.monacoModuleLoaded(monaco);

}

function loadSampleData()
{
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

	// designer.dataStructure = ACDesigner.FieldDefinition.create(sampleData);
	// designer.sampleData = sampleData;
}