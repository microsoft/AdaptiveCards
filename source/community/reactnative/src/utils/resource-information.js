/**
 * This holds the media resource details.
 */
export default class ResourceInformation {
    url = "";
    mimeType = "";

    constructor(urlString, mimeTypeString) {
        this.url = urlString;
        this.mimeType = mimeTypeString;
    }
}
