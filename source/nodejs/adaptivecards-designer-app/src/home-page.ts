import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as referral from "../samples/Referral.json"
import * as AdaptiveCards from "adaptivecards";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as weather from "../samples/Weather.json";
import * as appointment from "../samples/Appointment.json";
import * as HostConfig from "../samples/HostConfig.json";
import * as Api from "./api";

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
		appointments.forEach(item => {
			this.renderCard($("#appointmentCards"), appointment, item);
		});
	}

	private async loadReferrals() {
		$("#pendingReferrals").empty();
		let referralData = await Api.Api.getReferrals();
		referralData.forEach(item => {
			this.renderCard($("#pendingReferrals"), referral, item, {
				"scheduleSubmit": async (action) => {
					let appointment: Api.Appointment = {
						patient: item.patient,
						referral: item,
						patientNeed: item.referralNeed,
						room: action.data.room,
						provider: {
							name: action.data.provider
						},
						appointmentTime: `${action.data.date}T${action.data.time}:00Z`
					};
					await Api.Api.addAppointment(appointment);
					await this.loadAppointments();
				},
				"commentSubmit": (action) => alert("Add Comment " + action.data.comments)
			});
		});
	}

	private renderCard(el, json, data?, actionMap?) {

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