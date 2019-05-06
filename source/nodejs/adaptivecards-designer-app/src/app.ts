import * as Navigo from "navigo";
import * as Handlebars from "handlebars";
import * as $ from "jquery";
import { FormEditor } from "./admin/form-editor";
import { HomePage } from "./home-page";
import { FormPage } from "./form-page";
import { Api } from "./api";
import "./app.css";


window.addEventListener("load", async () => {
	const appElement = $('#app');

	// Compile Handlebar Templates
	const errorTemplate = Handlebars.compile($('#error-template').html());

	var router = new Navigo();

	const homePage = new HomePage(appElement);
	const formEditor = new FormEditor(appElement);
	const formPage = new FormPage(appElement);

	router
		.on("/", async () => {
			await homePage.render();
			await homePage.show();
		})
		.on("/admin/forms", async () => {
			await formEditor.render();
			formEditor.show();
		})
		.on("/forms/:id", async (params) => {
			await formPage.render();
			formPage.show();
			await formPage.loadForm(params.id);
			router.updatePageLinks();
		})
		.on("/forms", async () => {
			await formPage.render();
			formPage.show();
			router.updatePageLinks();
		})
	.resolve();
	
	router.hooks({
		after: () => updateMenu()
	});

	$("#resetDemo").click(async () => {
		var reset = confirm("Please OK to reset the demo");
		if (reset) {
			await Api.reset();
			router.navigate("/")
			alert("Demo reset");
		}
	});


	updateMenu();

});

function updateMenu() {
	$('a', $("#menu")).removeClass("w3-teal");
	// Highlight Active Menu on Refresh/Page Reload
	const link = $(`a[href$='${window.location.pathname}']`);
	link.addClass('w3-teal');
}
