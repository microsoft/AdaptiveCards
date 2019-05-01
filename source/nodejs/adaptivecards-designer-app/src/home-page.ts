import * as $ from "jquery";
import * as Handlebars from "handlebars";

export class HomePage {

	public render() {
		const homeTemplate = Handlebars.compile($('#home-template').html());
		let html = homeTemplate({});
		return html;
	}
}