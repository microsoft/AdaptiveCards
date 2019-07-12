import * as Adaptive from "adaptivecards";
import { Downloader } from "./downloader";

export class CatalogueEntry {
    private _cardPayload: string;
    private _cardPayloadDownloaded: boolean = false;
    private _sampleData: string;
    private _sampleDataDownloaded: boolean = false;

    private downloadCompleted() {
        if (this._cardPayloadDownloaded && this._sampleDataDownloaded && this.onDownloaded) {
            this.onDownloaded(this);
        }
    }

    sampleDataUrl?: string;

    onDownloaded: (sender: CatalogueEntry) => void = null;

    constructor(readonly displayName: string, readonly cardPayloadUrl: string, sampleDataUrl?: string) {
        this.sampleDataUrl = sampleDataUrl;
    }

    download() {
        let payloadDownloader = new Downloader(this.cardPayloadUrl);
        payloadDownloader.onSuccess = () => {
            this._cardPayload = payloadDownloader.data;
            this._cardPayloadDownloaded = true;

            this.downloadCompleted();
        }
        payloadDownloader.onError = () => {
            this._cardPayloadDownloaded = true;

            this.downloadCompleted();
        }
        payloadDownloader.download();

        if (!Adaptive.isNullOrEmpty(this.sampleDataUrl)) {
            let sampleDataDownloader = new Downloader(this.sampleDataUrl);
            sampleDataDownloader.onSuccess = () => {
                this._sampleData = sampleDataDownloader.data;
                this._sampleDataDownloaded = true;

                this.downloadCompleted();
            }
            sampleDataDownloader.onError = () => {
                this._sampleDataDownloaded = true;

                this.downloadCompleted();
            }
            sampleDataDownloader.download();
        }
        else {
            this._sampleDataDownloaded = true;

            this.downloadCompleted();
        }
    }

    get cardPayload(): string {
        return this._cardPayload;
    }

    get sampleData(): string {
        return this._sampleData;
    }
}

export function parseCatalogue(input: any): CatalogueEntry[] {
    let entries: any[] = null;

    if (Array.isArray(input)) {
        entries = input;
    }
    else {
        entries = Array.isArray(input["entries"]) ? input["entried"] : null;
    }

    let result: CatalogueEntry[] = [];

    if (entries != null) {
        for (let entry of entries) {
            if (typeof entry === "object") {
                let displayName = Adaptive.getStringValue(entry["displayName"]);
                let cardPayloadUrl = Adaptive.getStringValue(entry["cardPayloadUrl"]);

                if (!Adaptive.isNullOrEmpty(displayName) && !Adaptive.isNullOrEmpty(cardPayloadUrl)) {

                    result.push(
                        new CatalogueEntry(
                            displayName,
                            cardPayloadUrl,
                            Adaptive.getStringValue(entry["dataSampleUrl"])));
                }
            }
        }
    }

    return result;
}
