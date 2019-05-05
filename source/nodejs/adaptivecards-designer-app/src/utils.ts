import * as $ from "jquery";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as AdaptiveCards from "adaptivecards";
import * as HostConfig from "../samples/HostConfig.json";

export function toIsoString(date: Date) {
    var tzo = -date.getTimezoneOffset(),
        dif = tzo >= 0 ? '+' : '-',
        pad = function(num) {
            var norm = Math.floor(Math.abs(num));
            return (norm < 10 ? '0' : '') + norm;
        };
    return date.getFullYear() +
        '-' + pad(date.getMonth() + 1) +
        '-' + pad(date.getDate()) +
        'T' + pad(date.getHours()) +
        ':' + pad(date.getMinutes()) +
        ':' + pad(date.getSeconds()) +
        dif + pad(tzo / 60) +
        ':' + pad(tzo % 60);
}


export function renderCard(el: JQuery<HTMLElement>, json: object, data?: object, actionMap?) {

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
		if (actionMap && actionMap[submitAction.id]) {
			actionMap[submitAction.id](submitAction);
		}
	};
	card.parse(cardPayload);
	el.append($("<div class='card'>").append(card.render()));

}