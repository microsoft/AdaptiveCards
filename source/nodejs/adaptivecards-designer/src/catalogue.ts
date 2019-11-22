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
        let cardPayloadDownloadComplete = false;
        let sampleDataDownloadComplete = false;

        if (!this.cardPayloadDownloaded) {
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
        }
        else {
            cardPayloadDownloadComplete = true;
        }

        if (this.sampleDataUrl && !this.sampleDataDownloaded) {
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

            sampleDataDownloadComplete = true;
        }

        if (cardPayloadDownloadComplete && sampleDataDownloadComplete) {
            this.downloadCompleted();
        }
    }

    get cardPayloadDownloaded(): boolean {
        return this._cardPayloadDownloaded;
    }

    get cardPayload(): string {
        return this._cardPayload;
    }

    get sampleDataDownloaded(): boolean {
        return this._sampleDataDownloaded;
    }

    get sampleData(): string {
        return this._sampleData;
    }
}

export class SampleCatalogue {
    private _entries: CatalogueEntry[] = [];
    private _isDownloaded: boolean = false;
    private _url: string;

    private downloaded() {
        this._isDownloaded = true;

        if (this.onDownloaded) {
            this.onDownloaded(this);
        }
    }

    private parse(input: any) {
        let entries: any[] = null;

        if (Array.isArray(input)) {
            entries = input;
        }
        else {
            entries = Array.isArray(input["entries"]) ? input["entries"] : null;
        }

        this._entries = [];

        if (entries != null) {
            for (let entry of entries) {
                if (typeof entry === "object") {
                    let displayName = Adaptive.parseString(entry["displayName"]);
                    let cardPayloadUrl = Adaptive.parseString(entry["cardPayloadUrl"]);

                    if (displayName && cardPayloadUrl) {
                        this._entries.push(
                            new CatalogueEntry(
                                displayName,
                                cardPayloadUrl,
                                Adaptive.parseString(entry["dataSampleUrl"])));
                    }
                }
            }
        }
    }

    onDownloaded: (sender: SampleCatalogue) => void;

    constructor(url: string = "./sample-catalogue.json") {
        this.url = url;
    }

    download() {
        if (!this.isDownloaded) {
            let downloader = new Downloader(this.url);
            downloader.onError = () => { this.downloaded(); };
            downloader.onSuccess = () => {
                if (downloader.data) {
                    try {
                        this.parse(JSON.parse(downloader.data));
                    }
                    catch (e) {
                        // Swallow the error
                    }
                }

                this.downloaded();
            };
            downloader.download();
        }
        else {
            this.downloaded();
        }
    }

    get isDownloaded(): boolean {
        return this._isDownloaded;
    }

    get entries(): CatalogueEntry[] {
        return this._entries;
    }

    get url(): string {
        return this._url;
    }

    set url(value: string) {
        if (value !== this._url) {
            this._url = value;

            this._isDownloaded = false;
        }
    }
}
