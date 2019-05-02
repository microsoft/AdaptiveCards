import "./app.css";
import * as Navigo from "navigo";
import * as Handlebars from "handlebars";
import * as $ from "jquery";
import { FormEditor } from "./admin/form-editor";
import { HomePage } from "./home-page";
import { FormPage } from "./form-page";
import { Api } from "./api";
import * as DefaultReferralData from "../samples/Referral.data.json";


window.addEventListener("load", async () => {
	const appElement = $('#app');

	// Compile Handlebar Templates
	const errorTemplate = Handlebars.compile($('#error-template').html());

	// var root = null;
	var router = new Navigo();

	const homePage = new HomePage(appElement);
	const formEditor = new FormEditor(appElement);
	const formPage = new FormPage(appElement);

	router
		.on("/", async () => {
			await homePage.render();
			await homePage.show();
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
		.on("/admin/forms/:id", async (params) => {
			await formEditor.render();
			formEditor.show();
			await formEditor.loadForm(params.id);
			router.updatePageLinks();

		})
		.on("/admin/forms", async () => {
			await formEditor.render();
			formEditor.show();
			router.updatePageLinks();
		})
		.resolve();


	$("#resetDemo").click(async () => {
		var reset = confirm("Please OK to reset the demo");
		if (reset) {
			await Api.reset();
			alert("Demo reset");
			router.navigate("/")
		}
	});

	$("#generateReferral").click(async () => {
		var ref = DefaultReferralData;
		ref.patient.name = "Random";
		ref.patient.isInsured = false;
		await Api.addReferral(ref);
		router.navigate("/");
	});

	// Highlight Active Menu on Refresh/Page Reload
	const link = $(`a[href$='${window.location.pathname}']`);
	link.addClass('w3-teal');

	// $('a').on('click', (event) => {
	// 	// Block browser page load
	// 	event.preventDefault();

	// 	// Highlight Active Menu on Click
	// 	const target = $(event.target);
	// 	$('.w3-bar-item').removeClass('w3-teal');
	// 	target.addClass('w3-teal');

	// 	// Navigate to clicked url
	// 	const href = target.attr('href');
	// 	const path = href.substr(href.lastIndexOf('/'));
	// 	router.navigateTo(path);
	// });

});