import * as Azure from "@azure/storage-blob";
import { AZURE_STORAGE_ACCOUNT_NAME, AZURE_STORAGE_SAS } from "./secrets";
import { generateUuid } from "ms-rest-js";


export class Api {

	static async init(): Promise<void> {

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
		return Api.showBlobNames(Azure.Aborter.None, Api.formsContainerURL);
	}

	static pipeline = Azure.StorageURL.newPipeline(new Azure.AnonymousCredential());
	static serviceURL = new Azure.ServiceURL(`https://${AZURE_STORAGE_ACCOUNT_NAME}.blob.core.windows.net?${AZURE_STORAGE_SAS}`, Api.pipeline);
	static formsContainerURL = Azure.ContainerURL.fromServiceURL(Api.serviceURL, "forms");
	static submittedFormsContainerURL = Azure.ContainerURL.fromServiceURL(Api.serviceURL, "submittedforms");

	static loadForm(formId: string): Promise<string> {
		return new Promise(async (resolve, reject) => {
			let blobUrl = Azure.BlockBlobURL.fromBlobURL(Azure.BlobURL.fromContainerURL(Api.formsContainerURL, formId))

			let response = await blobUrl.download(Azure.Aborter.None, 0);
			let content = await response.blobBody;
			let fr = new FileReader();

			fr.addEventListener("load", () => {

				resolve(<string>fr.result);
			});

			fr.addEventListener("error", () => {
				reject("Failed to load form");
			})

			fr.readAsText(content);
		});
	}


	private static async showBlobNames(aborter, containerURL) {

		let response;
		let marker;
		let blobs = [];

		do {
			response = await containerURL.listBlobFlatSegment(aborter, undefined, { include: ["metadata"] });
			marker = response.marker;
			for (let blob of response.segment.blobItems) {
				blobs.push(blob);
			}
		} while (marker);

		return blobs;
	}
}