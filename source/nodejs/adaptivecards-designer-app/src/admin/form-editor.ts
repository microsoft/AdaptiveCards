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
import { ContosoHostContainer, CheckInAction, CheckInActionPeer } from "../host-container";
import * as Utils from "../utils";

export class FormEditor {

	constructor(private appElement: JQuery<HTMLElement>) {

	}

	private designer: ACDesigner.CardDesigner;
	private isLoaded = false;
	private html: string;
	private formId?: string;

	private templates = [
		{
			id: "patients",
			metadata: {
				displayname: "Patient Intake Template"
			},
		},
		{
			id: "referrals",
			sampleData: ReferralSampleData,
			metadata: {
				displayname: "Referral Template"
			},
		},
		{
			id: "appointments",
			sampleData: AppointmentSampleData,
			metadata: {
				displayname: "Appiontment Template"
			}
		}
	];

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
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker).isVisible = false;
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.OpenPayload).isVisible = false;
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.NewCard).isVisible = false;
		this.designer.toolbar.getElementById(ACDesigner.CardDesigner.ToolbarCommands.CopyJSON).isVisible = false;

		let saveButton = new ACDesigner.ToolbarButton(
			"saveButton",
			"Save",
			"acd-icon-save",
			() => { this.saveCard(); });
		saveButton.separator = true;
		this.designer.toolbar.insertElementBefore(saveButton, ACDesigner.CardDesigner.ToolbarCommands.HostAppPicker);

		let closeButton = new ACDesigner.ToolbarButton(
			"closeButton",
			"X",
			"acd-icon-close",
			() => { this.hideDesigner() });
		closeButton.separator = true;
		this.designer.toolbar.insertElementAfter(closeButton, ACDesigner.CardDesigner.ToolbarCommands.FullScreen);


		const formEditorTemplate = Handlebars.compile($('#form-editor-template').html());

		this.templates.forEach(async t => {
			var tCard = await Api.Api.getTemplate(t.id)
			Utils.renderCard($(`#cardContainer-${t.id}`), tCard, t.sampleData);
			$(`#editCard-${t.id}`).click(() => {
				this.showDesigner();
				
				this.designer.setCard(tCard);
				this.designer.sampleData = t.sampleData;
				this.designer.dataStructure = ACDesigner.FieldDefinition.create(t.sampleData);
				
			});
		});
		this.html = formEditorTemplate({ items: this.templates });

		this.isLoaded = true;
	}

	public show() {
		this.appElement.html(this.html);
		Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Contoso.Action.CheckIn", () => { return new CheckInAction(); });
		this.designer.attachTo(document.getElementById("designerRootHost"));
		this.designer.monacoModuleLoaded(monaco);
	
		//this.designer.setCard(json);


		//this.designer.jsonEditorToolbox.collapse();

	

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
		this.hideDesigner();
		alert("Saved!");

	}

	private showDesigner() {
		$("#designerContainer").css("height", "100%");
	}

	/* Close */
	private hideDesigner() {
		$("#designerContainer").css("height", "0%");
	}
}
