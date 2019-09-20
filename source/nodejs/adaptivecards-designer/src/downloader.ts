export class Downloader {
    private _data: string;

    private error() {
        if (this.onError) {
            this.onError(this);
        }
    }

    private success() {
        if (this.onSuccess) {
            this.onSuccess(this);
        }
    }

    onError: (sender: Downloader) => void = null;
    onSuccess: (sender: Downloader) => void = null;

    constructor(readonly url: string) {}

    download() {
        let request = new XMLHttpRequest();
        request.onerror = () => {
            this.error();
        }
        request.onload = () => {
            this._data = request.responseText;

            this.success();
        };

        try {
            request.open("GET", this.url, true);
            request.send();
        }
        catch (e) {
            this.error();
        }
    }

    get data(): string {
        return this._data;
    }
}