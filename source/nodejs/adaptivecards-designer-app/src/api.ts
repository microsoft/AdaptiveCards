import * as Azure from "@azure/storage-blob";
import { AZURE_STORAGE_ACCOUNT_NAME, AZURE_STORAGE_SAS } from "./secrets";
import { generateUuid } from "ms-rest-js";
//import { ListBlobsIncludeItem } from "@azure/storage-blob/typings/lib/generated/models";
import * as DefaultReferralTemplate from "../samples/Referral.json";
import * as DefaultAppointmentTemplate from "../samples/Appointment.json";
import * as DefaultReferralData from "../samples/Referral.data.json";
import * as AppSettings from "../samples/app.json";

export interface Contact {
	name: string;
	photo?: string;
	contact?: ContactMethod[];
}

export interface Patient extends Contact {
	isInsured: boolean;
}
export interface Appointment {
	patient: Patient;
	referral?: Referral;
	appointmentTime: string;
	provider: Provider;
	room: string;
	patientNeed: string;
}

export interface Provider extends Contact {
}

export interface ContactMethod {
	name: string;
	number: string;
}
export interface Referral {
	patient: Patient;
	referredBy: Provider;
	referredTo: Provider;
	referralNeed: string;
	comments: string;
	requestedDate: string;
}

export class Api {

	static pipeline = Azure.StorageURL.newPipeline(new Azure.AnonymousCredential());
	static serviceURL = new Azure.ServiceURL(`https://${AZURE_STORAGE_ACCOUNT_NAME}.blob.core.windows.net?${AZURE_STORAGE_SAS}`, Api.pipeline);
	static formsContainerURL = Azure.ContainerURL.fromServiceURL(Api.serviceURL, "forms");
	static submittedFormsContainerURL = Azure.ContainerURL.fromServiceURL(Api.serviceURL, "submittedforms");
	static appContainerURL = Azure.ContainerURL.fromServiceURL(Api.serviceURL, "appcontainer");

	static async reset(): Promise<void>{ 
		try {
			await Api.appContainerURL.create(Azure.Aborter.timeout(5000));
		}
		catch {
		}

		await Api.emptyContainer(Azure.Aborter.timeout(10000), this.appContainerURL);

		await Api.saveAppSettings(AppSettings);

		await Api.saveTemplate("referrals", DefaultReferralTemplate);
		await Api.saveTemplate("appointments", DefaultAppointmentTemplate);
		await Api.addReferral(DefaultReferralData);
	}


	static async init(): Promise<void> {

	

		//await Api.addReferral(newRef);
		//let referrals = await Api.getReferrals();


		// await Api.addReferral(referral)
		// await Api.updateReferral(referral)
		// await Api.deleteReferral(referral)

		// await Api.getAppointments()
		// await Api.addAppointment(referral)
		// await Api.updateAppointment(appointment)
		// await Api.deleteAppointment(appointment)

		try {
			await Api.formsContainerURL.create(Azure.Aborter.timeout(5000));
		}
		catch (e) {
		}

		try {
			await Api.submittedFormsContainerURL.create(Azure.Aborter.timeout(5000));
		}
		catch (e) {
		}
	}

	static async getReferrals(): Promise<Referral[]> {
		let referrals = await Api.listBlobs(Azure.Aborter.None, this.appContainerURL, "referrals");
		let response: Referral[] = [];
		for (let referral of referrals) {
			let r = await Api.loadBlobAs<Referral>(Azure.Aborter.None, this.appContainerURL, referral.name);
			response.push(r);
		}
		return response;
	}

	static async getAppointments(): Promise<Appointment[]> {
		let referrals = await Api.listBlobs(Azure.Aborter.None, this.appContainerURL, "appointments");
		let response: Appointment[] = [];
		for (let referral of referrals) {
			let r = await Api.loadBlobAs<Appointment>(Azure.Aborter.None, this.appContainerURL, referral.name);
			response.push(r);
		}
		return response;
	}

	static async getTemplate(id: string): Promise<object> {
		return await Api.loadBlobAs<object>(Azure.Aborter.None, this.appContainerURL, `${id}/template`);
	}

	static async saveAppSettings(appSettings): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, "appSettings");
		var blob = new Blob([JSON.stringify(appSettings)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}

	static async saveTemplate(id: string, template: object): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, `${id}/template`);
		var blob = new Blob([JSON.stringify(template)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}


	static async addReferral(referral: Referral): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, `referrals/${generateUuid()}`);
		var blob = new Blob([JSON.stringify(referral)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}

	static async addAppointment(appointment: Appointment): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, `appointments/${generateUuid()}`);
		var blob = new Blob([JSON.stringify(appointment)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}

	static async submitForm(id: any, data: Object): Promise<void> {

		data["formId"] = id;
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.submittedFormsContainerURL, `${generateUuid()}`);
		var blob = new Blob([JSON.stringify(data)]);

		// Store the submmited form data into the blob metadata
		let dict: { [propertyName: string]: string; } = {};
		for (var key in data) {
			if (data.hasOwnProperty(key)) {
				dict[key] = data[key];
			}
		}

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			metadata: dict,
			blobHTTPHeaders: { blobContentType: "application/json" }
		});

	}

	static async saveCard(card: object): Promise<void> {

		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.formsContainerURL, `${generateUuid()}`);
		var blob = new Blob([JSON.stringify(card)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			metadata: {
				"displayName": "My Card"
			},
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}

	static getForms() {
		return Api.listBlobs(Azure.Aborter.None, Api.formsContainerURL, "forms");
	}

	static async getSubmmitedForms() {
		var submittedForms = await Api.listBlobs(Azure.Aborter.None, Api.submittedFormsContainerURL, "submittedforms");
		submittedForms.filter(m => m.metadata["formid"] === "a8021bbc-684a-440f-984e-9b8813f86b04")
	}


	static loadForm(formId: string): Promise<string> {
		return Api.loadBlob(Azure.Aborter.timeout(3000), Api.formsContainerURL, formId);
	}

	private static loadBlobAs<T>(aborter: Azure.Aborter, containerURL: Azure.ContainerURL, blob: string): Promise<T> {
		return new Promise(async (resolve, reject) => {
			let blobUrl = Azure.BlockBlobURL.fromBlobURL(Azure.BlobURL.fromContainerURL(containerURL, blob))

			let response = await blobUrl.download(Azure.Aborter.None, 0);
			let content = await response.blobBody;

			let fr = new FileReader();
			fr.addEventListener("load", () => resolve(JSON.parse(<string>fr.result)));
			fr.addEventListener("error", () => reject("Failed to load form"));
			fr.readAsText(content);
		});
	}

	private static loadBlob(aborter: Azure.Aborter, containerURL: Azure.ContainerURL, blob: string): Promise<string> {
		return new Promise(async (resolve, reject) => {
			let blobUrl = Azure.BlockBlobURL.fromBlobURL(Azure.BlobURL.fromContainerURL(containerURL, blob))

			let response = await blobUrl.download(Azure.Aborter.None, 0);
			let content = await response.blobBody;

			let fr = new FileReader();
			fr.addEventListener("load", () => resolve(<string>fr.result));
			fr.addEventListener("error", () => reject("Failed to load form"));
			fr.readAsText(content);
		});
	}

	private static async listBlobs(aborter: Azure.Aborter, containerURL: any, folder: string) {

		let response;
		let marker;
		let blobs = [];

		do {
			response = await containerURL.listBlobFlatSegment(aborter, undefined, { prefix: `${folder}/`, include: ["metadata"] });
			marker = response.marker;
			for (let blob of response.segment.blobItems) {
				if(blob.name.indexOf("template") < 0)
					blobs.push(blob);
			}
		} while (marker);

		return blobs;
	}

	private static async emptyContainer(aborter: Azure.Aborter, containerURL: any): Promise<void> {
		let response;
		let marker;

		do {
			response = await containerURL.listBlobFlatSegment(aborter);
			marker = response.marker;
			for (let blob of response.segment.blobItems) {
				let blobUrl = Azure.BlobURL.fromContainerURL(containerURL, blob.name);
				await blobUrl.delete(Azure.Aborter.None);
			}
		} while (marker);
	}
}