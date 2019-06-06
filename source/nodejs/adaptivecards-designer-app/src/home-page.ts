import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as AdaptiveCards from "adaptivecards";
import * as weather from "../samples/Weather.json";
import * as Api from "./api";
import * as Utils from "./utils";
import * as DefaultReferralData from "../samples/Referral.data.json";
import * as faker from "faker";
import * as StockTemplate from "../samples/StockUpdate.json";
import * as DefaultStockData from "../samples/StockUpdate.data.json";
import * as AppSettings from "../samples/app.json";

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

		$("#generateReferral").click(async () => {
			var ref = DefaultReferralData;
			ref.patient.name = faker.name.findName();
			
			ref.patient.isInsured = Math.random() < 0.5;
			await Api.Api.save(`referrals/${Api.Api.generateId()}`, ref);
			await this.loadReferrals();
		});
		this.loadReferrals();

		this.loadAppointments();

		this.loadCustomCards();
	}
	

	private loadCustomCards() {

		for(let card of AppSettings.homeCards) {
			$.getJSON(card.templateUrl, templateRes => {
				$.getJSON(card.dataUrl, dataRes => {
					Utils.renderCard($("#homeCards"), templateRes, dataRes);
				})
			});
		}
	}

	private async loadAppointments() {
		$("#appointmentCards").empty();

		let appointments = await Api.Api.getItems<Api.Appointment>("appointments");
		let template = await Api.Api.getItemAs<object>("appointments/template");
		appointments.forEach(item => {
			Utils.renderCard($("#appointmentCards"), template, item, {
				"cancelSubmit": async () => {
					await Api.Api.deleteItem(item.blobId);
					await this.loadAppointments();
				}
			});
		});
	}

	private async loadReferrals() {
		$("#pendingReferrals").empty();
		let referralData = await Api.Api.getItems<Api.Referral>("referrals");
		let template = await Api.Api.getItemAs<object>("referrals/template");

		referralData.forEach(referral => {
			Utils.renderCard($("#pendingReferrals"), template, referral, {
				"scheduleSubmit": async (action) => {
					let timeZoneOffset = ("0" + new Date().getTimezoneOffset() / 60).slice(-2)
					let appointment: Api.Appointment = {
						patient: referral.patient,
						referral: referral,
						patientNeed: referral.referralNeed,
						room: action.data.room,
						provider: {
							name: action.data.provider
						},
						appointmentTime: `${action.data.date}T${action.data.time}:00-${timeZoneOffset}:00`
					};
					await Api.Api.save(`appointments/${Api.Api.generateId()}`, appointment);
					await Api.Api.deleteItem(referral.blobId);
					await this.loadReferrals();
					await this.loadAppointments();
				},
				"commentSubmit": (action) => alert("Add Comment " + action.data.comments)
			});
		});
	}

}