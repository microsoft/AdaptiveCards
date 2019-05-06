import * as Azure from "@azure/storage-blob";
import { AZURE_STORAGE_ACCOUNT_NAME, AZURE_STORAGE_SAS } from "./secrets";
import { generateUuid } from "ms-rest-js";
//import { ListBlobsIncludeItem } from "@azure/storage-blob/typings/lib/generated/models";
import * as DefaultReferralIntakeForm from "../samples/PatientIntake.json";
import * as DefaultReferralTemplate from "../samples/Referral.json";
import * as DefaultAppointmentTemplate from "../samples/Appointment.json";
import * as DefaultPatientIntakeForm from "../samples/PatientIntake.json";
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
	blobId?: string;
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
	blobId?: string;
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

	static async reset(): Promise<void> {
		try {
			await Api.appContainerURL.create(Azure.Aborter.timeout(5000));
		}
		catch {
		}

		await Api.emptyContainer(Azure.Aborter.timeout(10000), this.appContainerURL);

		await Api.save("appSettings", AppSettings);

		await Api.save("referrals/intakeForm", DefaultReferralIntakeForm);
		await Api.save("referrals/template", DefaultReferralTemplate);
		await Api.save("appointments/template", DefaultAppointmentTemplate);
		await Api.save("patients/intakeForm", DefaultPatientIntakeForm);
		await Api.save(`referrals/${generateUuid()}`, DefaultReferralData);
	}

	static generateId() {
		return generateUuid();
	}

	static async getItems<T>(folder: string): Promise<T[]> {
		let items = await Api.listBlobs(Azure.Aborter.None, this.appContainerURL, folder);
		let response: T[] = [];
		for (let item of items) {
			if (item.name.indexOf("template") > 0 || item.name.indexOf("intakeForm") > 0)
				continue;

			let r = await Api.loadBlobAs<T>(Azure.Aborter.None, this.appContainerURL, item.name);
			response.push(r);
		}
		return response;
	}

	static async save(id: string, obj: any): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, id);
		var blob = new Blob([JSON.stringify(obj)]);

		await Azure.uploadBrowserDataToBlockBlob(Azure.Aborter.timeout(3000), blob, blobURL, {
			blobHTTPHeaders: { blobContentType: "application/json" }
		});
	}

	static async deleteItem(id: string): Promise<void> {
		const blobURL = Azure.BlockBlobURL.fromContainerURL(Api.appContainerURL, `${id}`);
		await blobURL.delete(Azure.Aborter.timeout(5000));
	}

	public static getItem(id: string): Promise<string> {
		return this.loadBlob(Azure.Aborter.timeout(3000), this.appContainerURL, id);
	}

	public static getItemAs<T>(id: string): Promise<T> {
		return this.loadBlobAs<T>(Azure.Aborter.timeout(3000), this.appContainerURL, id);
	}

	private static loadBlobAs<T>(aborter: Azure.Aborter, containerURL: Azure.ContainerURL, blob: string): Promise<T> {
		return new Promise(async (resolve, reject) => {
			let blobUrl = Azure.BlockBlobURL.fromBlobURL(Azure.BlobURL.fromContainerURL(containerURL, blob))

			let response = await blobUrl.download(Azure.Aborter.None, 0);
			let content = await response.blobBody;

			let fr = new FileReader();
			fr.addEventListener("load", () => {
				let obj = JSON.parse(<string>fr.result);
				obj.blobId = blob;
				resolve(obj);
			});
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
				if (blob.name.indexOf("template") < 0)
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