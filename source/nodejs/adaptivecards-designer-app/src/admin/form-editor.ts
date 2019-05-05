import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";
import "adaptivecards-designer/dist/adaptivecards-designer.css";
import "../app.css";
import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as Api from "../api";
import * as ReferralSampleData from "../../samples/Referral.data.json";
import * as AppointmentSampleData from "../../samples/Appointment.data.json";
import * as Adaptive from "adaptivecards";
import { AdaptiveCardPeer } from "adaptivecards-designer";
import { ContosoHostContainer, CheckInAction, CheckInActionPeer} from "../host-container";

export class FormEditor {

	constructor(private appElement: JQuery<HTMLElement>) {

	}

	private designer: ACDesigner.CardDesigner;
	private isLoaded = false;
	private html: string;
	private formId?: string;

	private templates = {
		patients: {
			metadata: {
				displayname: "Patient Intake Template"
			},
		},
		referrals: {
			sampleData: ReferralSampleData,
			metadata: {
				displayname: "Referral Template"
			},
		},
		appointments: {
			sampleData: AppointmentSampleData,
			metadata: {
				displayname: "Appiontment Template"
			}
		}
	};

	public async render(): Promise<void> {
		if (this.html) {
			return;
		}


		// Comment to disable preview features (data binding)
		ACDesigner.GlobalSettings.previewFeaturesEnabled = true;
		ACDesigner.CardDesignerSurface.actionPeerRegistry.registerPeer(CheckInAction, CheckInActionPeer, "Actions", "acd-icon-actionCheckin");

		Adaptive.AdaptiveCard.useBuiltInInputValidation = true;
		Adaptive.AdaptiveCard.displayInputValidationErrors = true;

		ACDesigner.CardDesigner.onProcessMarkdown = (text: string, result: { didProcess: boolean, outputHtml: string }) => {
			result.outputHtml = new markdownit().render(text);
			result.didProcess = true;
		}

		let hostContainers: Array<ACDesigner.HostContainer> = [];
		hostContainers.push(new ContosoHostContainer("ContosoMedical", "../../containers/webchat-container.css"));

		this.designer = new ACDesigner.CardDesigner(hostContainers);
		
		this.designer.assetPath = "/";
		this.designer.sampleCatalogueUrl = window.location.origin + "/sample-catalogue.json";
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker).isVisible = false;
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.OpenPayload).isVisible = false;
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.NewCard).isVisible = false;
		//designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.CopyJSON).isVisible = false;

		let saveButton = new ACDesigner.ToolbarButton(
			"saveButton",
			"Save",
			"acd-icon-save",
			(sender) => { this.saveCard(); });
		saveButton.separator = true;
		this.designer.toolbar.insertElementAfter(saveButton, ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker);

		const formEditorTemplate = Handlebars.compile($('#form-editor-template').html());

		this.html = formEditorTemplate({ items: this.templates });
		this.isLoaded = true;
	}

	public show() {
		this.appElement.html(this.html);
		Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Contoso.Action.CheckIn", () => { return new CheckInAction(); });

	}

	public async loadForm(formId: string) {
		this.formId = formId;
		let json = await Api.Api.getTemplate(formId);

		this.designer.attachTo(document.getElementById("designerRootHost"));
		this.designer.setCard(json);


		//this.designer.jsonEditorToolbox.collapse();

		this.designer.monacoModuleLoaded(monaco);
		this.designer.sampleData = this.templates[formId].sampleData;
		this.designer.dataStructure = ACDesigner.FieldDefinition.create(this.templates[formId].sampleData);
		//this.designer.designerSurface.rootPeer
		/* Uncomment to test a custom palette item example */
		let exampleSnippet = new ACDesigner.SnippetPaletteItem("Actions", "Action.PatientIntake");
		exampleSnippet.snippet = {
			"type": "Action.PatientIntake"
		};

		this.designer.customPaletteItems = [exampleSnippet];
	}

	private async saveCard() {

		await Api.Api.saveTemplate(this.formId, this.designer.getCard());
		alert("Saved!");

	}
}
