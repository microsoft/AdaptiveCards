import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";
import "adaptivecards-designer/dist/adaptivecards-designer.css";
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
	private currentTemplateId?: string;

	private templates = [
		{
			id: "referrals/intakeForm",
			htmlId: "referrals-intakeForm",
			sampleData: {},
			metadata: {
				displayname: "Referral Intake Form"
			},
		},
		{
			id: "referrals/template",
			htmlId: "referrals-template",
			sampleData: ReferralSampleData,
			metadata: {
				displayname: "Referral"
			},
		},
		{
			id: "appointments/template",
			htmlId: "appointments-template",
			sampleData: AppointmentSampleData,
			metadata: {
				displayname: "Appointment"
			}
		},
		{
			id: "patients/intakeForm",
			htmlId: "patients-intakeForm",
			sampleData: {},
			metadata: {
				displayname: "Patient Intake Form"
			},
		},

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
		hostContainers.push(new ContosoHostContainer());

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


		this.html = formEditorTemplate({ items: this.templates });

		this.isLoaded = true;
	}

	public refresh(id?: string): Promise<void> {
		return new Promise(async resolve => {

			for (let t of this.templates) {
				// if (id && t.id !== id)
				// 	continue;

				try {
					let cardContainer = $(`#cardContainer-${t.htmlId}`);
					cardContainer.empty();
					let tCard = await Api.Api.getItemAs<object>(t.id);
					Utils.renderCard(cardContainer, tCard, t.sampleData);
					$(`#editCard-${t.htmlId}`).click(() => {

						this.currentTemplateId = t.id;
						this.designer.setCard(tCard);
						this.designer.sampleData = t.sampleData;
						this.designer.dataStructure = ACDesigner.FieldDefinition.create(t.sampleData);

						this.showDesigner();

					});
				} catch (ex) {
					console.error(ex.message);
					continue;
				}
			}
			resolve();
		});
	}

	public show() {
		this.appElement.html(this.html);
		Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Contoso.Action.CheckIn", () => { return new CheckInAction(); });
		this.designer.attachTo(document.getElementById("designerRootHost"));
		this.designer.monacoModuleLoaded(monaco);
		this.refresh();

		//this.designer.setCard(json);


		this.designer.jsonEditorToolbox.collapse();



		//this.designer.designerSurface.rootPeer
		/* Uncomment to test a custom palette item example */
		let exampleSnippet = new ACDesigner.SnippetPaletteItem("Actions", "Action.PatientIntake");
		exampleSnippet.snippet = {
			"type": "Action.PatientIntake"
		};

		this.designer.customPaletteItems = [exampleSnippet];
	}

	private async saveCard() {

		await Api.Api.save(this.currentTemplateId, this.designer.getCard());
		await this.refresh(this.currentTemplateId);
		this.hideDesigner();
		this.currentTemplateId = null;
	}

	private showDesigner() {
		$("#designerContainer").show();
	}

	private hideDesigner() {
		$("#designerContainer").hide();
	}
}
