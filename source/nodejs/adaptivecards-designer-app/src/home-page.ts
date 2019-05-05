import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as AdaptiveCards from "adaptivecards";
import * as weather from "../samples/Weather.json";
import * as Api from "./api";
import * as Utils from "./utils";

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
		AdaptiveCards.AdaptiveCard.actionTypeRegistry.unregisterType("Contoso.Action.CheckIn");

		this.appElement.html(this.html);

		await this.loadReferrals();

		await this.loadAppointments();
		Utils.renderCard($("#homeCards"), weather);
	}

	private async loadAppointments() {
		$("#appointmentCards").empty();

		let appointments = await Api.Api.getAppointments();
		let template = await Api.Api.getTemplate("appointments");
		appointments.forEach(item => {
			Utils.renderCard($("#appointmentCards"), template, item);
		});
	}

	private async loadReferrals() {
		$("#pendingReferrals").empty();
		let referralData = await Api.Api.getReferrals();
		let template = await Api.Api.getTemplate("referrals");

		referralData.forEach(item => {
			Utils.renderCard($("#pendingReferrals"), template, item, {
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

}