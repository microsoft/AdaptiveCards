import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as referral from "../samples/Referral.json"
import * as referralData from "../samples/Referral.data.json"
import * as AdaptiveCards from "adaptivecards";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as weather from "../samples/Weather.json";
import * as appointment from "../samples/Appointment.json"

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

	public show() {
		this.appElement.html(this.html);
		let template = new Template(referral);
		let context = new EvaluationContext();
		context.$root = referralData;
		let expandedTemplatePayload = template.expand(context)
		let card = new AdaptiveCards.AdaptiveCard();
		card.parse(expandedTemplatePayload);

		card.onExecuteAction = async (action) => {
			var submitAction = <AdaptiveCards.SubmitAction>action;
			//console.log(JSON.stringify(submitAction.data));

		};

		let cardHtml = card.render();
		$("#pendingReferrals").append($("<div class='card'>").append(cardHtml));

		this.renderCard(appointment, $("#appointmentCards"));
		this.renderCard(weather, $("#homeCards"));
	}

	private renderCard(json, el) {
		let card = new AdaptiveCards.AdaptiveCard();
		card.parse(json);
		el.append($("<div class='card'>").append(card.render()));

	}
}