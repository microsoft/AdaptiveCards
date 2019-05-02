import * as $ from "jquery";
import * as Handlebars from "handlebars";
import * as referral from "../samples/Referral.json"
import * as referralData from "../samples/Referral.data.json"
import * as AdaptiveCards from "adaptivecards";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as weather from "../samples/Weather.json";
import * as appointment from "../samples/Appointment.json";
import * as appointmentData from "../samples/Appointment.data.json";
import * as HostConfig from "../samples/HostConfig.json";

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

		referralData.forEach(item => {
			this.renderCard($("#pendingReferrals"), referral, item);
			
		})

		this.renderCard($("#appointmentCards"), appointment, appointmentData);
		this.renderCard($("#homeCards"), weather);
	}

	private renderCard(el, json, data?, actionHandler?) {
		
		let cardPayload = json;
		if(data !== undefined)
		{
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
			alert("id" + submitAction.id);
		};
		card.parse(cardPayload);
		el.append($("<div class='card'>").append(card.render()));

	}
}