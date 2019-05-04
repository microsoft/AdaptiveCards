import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as AdaptiveCards from "adaptivecards";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as weather from "../samples/Weather.json";
import * as HostConfig from "../samples/HostConfig.json";
import * as Api from "./api";
import { DataPaletteItem } from "adaptivecards-designer";

export class HomePage {

	constructor(private appElement: JQuery<HTMLElement>) {

	}

	private isLoaded = false;
	private html: string;

	public render(): Promise<void> {
		if (this.html) {
			return;
		}

		const homeTemplate = Handlebars.compile($('#home-template').html());
		this.html = homeTemplate({});


		this.isLoaded = true;
		return Promise.resolve();
	}

	public async show() {
		this.appElement.html(this.html);

		await this.loadReferrals();

		await this.loadAppointments();
		this.renderCard($("#homeCards"), weather);
	}

	private async loadAppointments() {
		$("#appointmentCards").empty();

		let appointments = await Api.Api.getAppointments();
		let template = await Api.Api.getTemplate("appointments");
		appointments.forEach(item => {
			this.renderCard($("#appointmentCards"), template, item);
		});
	}

	private async loadReferrals() {
		$("#pendingReferrals").empty();
		let referralData = await Api.Api.getReferrals();
		let template = await Api.Api.getTemplate("referrals");

		referralData.forEach(item => {
			this.renderCard($("#pendingReferrals"), template, item, {
				"scheduleSubmit": async (action) => {
					let timeZoneOffset = ("0" + new Date().getTimezoneOffset() / 60).slice(-2)
					let appointment: Api.Appointment = {
						patient: item.patient,
						referral: item,
						patientNeed: item.referralNeed,
						room: action.data.room,
						provider: {
							name: action.data.provider
						},
						appointmentTime: `${action.data.date}T${action.data.time}:00-${timeZoneOffset}:00`
					};
					await Api.Api.addAppointment(appointment);
					await this.loadAppointments();
				},
				"commentSubmit": (action) => alert("Add Comment " + action.data.comments)
			});
		});
	}

	private renderCard(el: JQuery<HTMLElement>, json: object, data?: object, actionMap?) {

		let cardPayload = json;
		if (data !== undefined) {
			let template = new Template(json);
			let context = new EvaluationContext();
			context.$root = data;
			cardPayload = template.expand(context)
		}

		let card = new AdaptiveCards.AdaptiveCard();
		card.hostConfig = new AdaptiveCards.HostConfig(HostConfig);
		card.onExecuteAction = (action) => {
			var submitAction = <AdaptiveCards.SubmitAction>action;
			//console.log(JSON.stringify(submitAction.data));
			if (actionMap && actionMap[submitAction.id]) {
				actionMap[submitAction.id](submitAction);
			}
		};
		card.parse(cardPayload);
		el.append($("<div class='card'>").append(card.render()));

	}
}