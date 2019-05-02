import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";
import "adaptivecards-designer/dist/adaptivecards-designer.css";
import * as $ from "jquery";
import * as Handlebars from "handlebars";
import { Api } from "../api";

export class FormEditor {

	constructor(private appElement: JQuery<HTMLElement>) {

	}

	private designer: ACDesigner.CardDesigner;
	private isLoaded = false;
	private html: string;

	public async render(): Promise<void> {
		if (this.html) {
			return;
		}


		// Comment to disable preview features (data binding)
		ACDesigner.GlobalSettings.previewFeaturesEnabled = true;

		ACDesigner.CardDesigner.onProcessMarkdown = (text: string, result: { didProcess: boolean, outputHtml: string }) => {
			result.outputHtml = new markdownit().render(text);
			result.didProcess = true;
		}

		let hostContainers: Array<ACDesigner.HostContainer> = [];
		hostContainers.push(new ACDesigner.WebChatContainer("ContosoMedical", "../../containers/webchat-container.css"));

		this.designer = new ACDesigner.CardDesigner(hostContainers);
		this.designer.assetPath = "/";
		this.designer.sampleCatalogueUrl = window.location.origin + "/sample-catalogue.json";
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker).isVisible = false;
		//designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.CopyJSON).isVisible = false;

		let saveButton = new ACDesigner.ToolbarButton(
			"saveButton",
			"Save",
			null,
			(sender) => { this.saveCard(); });
		saveButton.separator = true;
		this.designer.toolbar.insertElementAfter(saveButton, ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker);


		let items = await Api.getForms();

		const formEditorTemplate = Handlebars.compile($('#form-editor-template').html());

		this.html = formEditorTemplate({ items: items });
		this.isLoaded = true;
	}

	public show() {
		this.appElement.html(this.html);
		this.designer.attachTo(document.getElementById("designerRootHost"));

		this.designer.jsonEditorToolbox.collapse();

		this.designer.monacoModuleLoaded(monaco);


	}

	public async loadForm(formId: string) {
		let json = await Api.loadForm(formId);
		this.designer.setCard(JSON.parse(json));

		/* Uncomment to test a custom palette item example */
		let exampleSnippet = new ACDesigner.SnippetPaletteItem("Data Fields", "Patient Referrer");
		exampleSnippet.snippet = {
			"type": "Input.Text"
		};

		this.designer.customPaletteItems = [exampleSnippet];
	}

	private async saveCard() {

		await Api.saveCard(this.designer.getCard());
		alert("Saved!");

	}


	private loadSampleData() {
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
}
