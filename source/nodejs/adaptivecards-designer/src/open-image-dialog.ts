import { Dialog } from "./dialog";

export class FetchManager {
    private headers = {
        "Content-Type": "application/json",
        "Access-Control-Allow-Origin": "*",
    };

    async getSampleImages() {
        const option = {
            method: "GET",
            headers: this.headers,
        };
        try {
            const sampleImages = await fetch(
                process.env.PIC_TO_CARD_PREDICTION_API + "/get_card_templates",
                option
            );
            return await sampleImages.json();
        } catch (err) {
            console.log(err.message);
        }
    }

    async getPredictedData(imageContent, isTemplateBindingEnabled) {
        const options = {
            method: "POST",
            headers: this.headers,
            body: JSON.stringify({
                image: imageContent.split(",")[1],
            }),
        };
        try {
            const endPoint = isTemplateBindingEnabled
                ? "/predict_json?format=template"
                : "/predict_json";
            const picResponse = await fetch(
                process.env.PIC_TO_CARD_PREDICTION_API + endPoint,
                options
            );
            return await picResponse.json();
        } catch (err) {
            console.log(err.message);
        }
    }
}

export class OpenImageDialog extends Dialog {
    private _renderedElement: HTMLElement;
    private _imageElement: HTMLElement;
    private _buttonContainer: HTMLElement;
    private _inputTemplate: HTMLElement;
    private _uploadedImage: string =
        "data:image/png;base64,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";
    private _predictedCardJSON: predictedCardJSON;
    private fetchManager: FetchManager;
    private isTemplateOptionChecked: boolean = false;
    private allowedImageSize = 2; // In MB

    constructor() {
        super();
        this.fetchManager = new FetchManager();
    }

    private setContent(element: HTMLElement) {
        this._renderedElement.appendChild(element);
    }

    private removeContent(element: HTMLElement) {
        this._renderedElement.removeChild(element);
    }

    private renderTitle(): HTMLElement {
        const title = document.createElement("div");
        title.className = "acd-image-title";
        title.innerText = "Upload your own card design";
        return title;
    }

    private renderTitleContent(): HTMLElement {
        const content = document.createElement("div");
        content.className = "acd-image-title-content";
        content.innerText =
            "Design your cards and upload it as a png, or jpeg and see it magically convert to a functioning adaptive card";
        return content;
    }

    private renderUploadedImage(): HTMLElement {
        this._imageElement = document.createElement("img");
        this._imageElement.className = "acd-image-placeholder";
        this._imageElement.setAttribute("src", this._uploadedImage);
        return this._imageElement;
    }

    private renderUploadButton(type: string): HTMLElement {
        this._buttonContainer = document.createElement("div");
        this._buttonContainer.className = "acd-upload-button-container";
        const fileNote = document.createElement("div");
        fileNote.className = "acd-image-file-note";
        fileNote.innerHTML =
            "By using the upload feature you agree to our <a href='../privacy' target='_blank'><span class='link'> image usage policy</spanl></a>";
        type !== "file" &&
            this._buttonContainer.appendChild(this.renderCheckbox());
        this._buttonContainer.appendChild(
            type === "file"
                ? this.createFileButton()
                : this.createActionButton()
        );
        this._buttonContainer.appendChild(fileNote);
        return this._buttonContainer;
    }

    private renderCheckbox() {
        const checkboxContainer = document.createElement("div");
        checkboxContainer.className = "acd-checkbox-container";
        const inputElement = <HTMLInputElement>document.createElement("INPUT");
        inputElement.className = "acd-checkbox-element";
        inputElement.setAttribute("id", "template-option");
        inputElement.setAttribute("type", "checkbox");
        inputElement.onclick = () => {
            const checkbox = document.getElementById(
                "template-option"
            ) as HTMLInputElement;
            this.isTemplateOptionChecked = checkbox.checked ? true : false;
        };
        const customCheckboxElement = <HTMLInputElement>(
            document.createElement("SPAN")
        );
        customCheckboxElement.className = "acd-custom-checkbox";
        checkboxContainer.appendChild(inputElement);
        checkboxContainer.appendChild(customCheckboxElement);
        checkboxContainer.appendChild(this.renderLabelText());
        return checkboxContainer;
    }

    private renderLabelText() {
        const labelElement = <HTMLInputElement>document.createElement("LABEL");
        labelElement.className = "acd-label-element";
        labelElement.setAttribute("for", "template-option");
        labelElement.innerText =
            "Create adaptive card along with sample template binding";
        return labelElement;
    }

    private checkFileSize(file) {
        const filesize = parseInt((file.size / 1024 / 1024).toFixed(4)); // MB
        return filesize < this.allowedImageSize;
    }

    private createFileButton() {
        const inputElement = <HTMLInputElement>document.createElement("INPUT");
        inputElement.className = "acd-file-type";
        inputElement.setAttribute("type", "file");
        inputElement.setAttribute("button-name", "Browse File");
        inputElement.setAttribute("accept", "image/*");
        inputElement.onchange = () => {
            if (this.checkFileSize(inputElement.files[0])) {
                const reader = new FileReader();
                reader.readAsDataURL(inputElement.files[0]);
                reader.onload = () => this.renderImage(reader.result);
                reader.onerror = (error) => console.log(error);
            } else {
                this._inputTemplate.removeChild(this._buttonContainer);
                this._inputTemplate.appendChild(
                    this.renderUploadButton("file")
                );
                this.geneareteErrorText(
                    "Invalid file size. Try image under 2 MB"
                );
                this._uploadedImage =
                    "data:image/png;base64,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";
                this._imageElement.setAttribute("src", this._uploadedImage);
            }
        };

        return inputElement;
    }

    private geneareteErrorText(text: string) {
        const errorContent = document.createElement("div");
        errorContent.className = "acd-error-text";
        errorContent.innerText = text;
        this._buttonContainer.appendChild(errorContent);
    }

    private onCardFailure(spinnerElement) {
        this.removeContent(spinnerElement);
        this._inputTemplate.removeChild(this._buttonContainer);
        this._inputTemplate.appendChild(this.renderUploadButton("file"));
        this.geneareteErrorText("Failed to generate card for selected Image");
    }

    createActionButton() {
        const uploadButton = document.createElement("INPUT");
        uploadButton.className = "acd-card-button";
        uploadButton.setAttribute("type", "BUTTON");
        uploadButton.setAttribute("button-name", "Convert to Adaptive Cards");
        uploadButton.setAttribute("value", "Convert to Adaptive Cards");
        uploadButton.onclick = () => {
            let spinnerElement = this.loadSpinner();
            this.setContent(spinnerElement);
            this.fetchManager
                .getPredictedData(
                    this._uploadedImage,
                    this.isTemplateOptionChecked
                )
                .then((res) => {
                    if (res.error) {
                        this.onCardFailure(spinnerElement);
                    } else {
                        this._predictedCardJSON = res.card_json;
                        this.close();
                    }
                });
        };

        return uploadButton;
    }

    private loadSpinner() {
        let spinnerHostElement = document.createElement("div");
        spinnerHostElement.className = "acd-spinner-host";
        let spinnerElement = document.createElement("div");
        spinnerElement.className = "acd-spinner acd-image-spinner";
        spinnerHostElement.appendChild(spinnerElement);
        return spinnerHostElement;
    }

    private renderImage(imageContent) {
        this._imageElement.setAttribute("src", imageContent);
        this._uploadedImage = imageContent;
        this._inputTemplate.removeChild(this._buttonContainer);
        this._inputTemplate.appendChild(this.renderUploadButton("action"));
    }

    private renderUploadControl(): HTMLElement {
        this._inputTemplate = document.createElement("div");
        this._inputTemplate.className = "acd-upload-control";
        this._inputTemplate.appendChild(this.renderUploadedImage());
        this._inputTemplate.appendChild(this.renderUploadButton("file"));
        return this._inputTemplate;
    }

    private renderUploadContainer(): HTMLElement {
        const uploadTemplate = document.createElement("div");
        uploadTemplate.className = "acd-image-file-container";
        uploadTemplate.appendChild(this.renderUploadControl());
        return uploadTemplate;
    }

    private renderImageContainer(): HTMLElement {
        let template = document.createElement("div");
        template.className = "acd-image-upload-container";
        template.appendChild(this.renderTitle());
        template.appendChild(this.renderTitleContent());
        template.appendChild(this.renderUploadContainer());
        return template;
    }

    private renderSampleTemplate() {
        let sampleImageTemplate = document.createElement("div");
        sampleImageTemplate.className = "acd-sample-image-container";
        sampleImageTemplate.style.flexDirection = "column";
        let spinnerElement = document.createElement("div");
        spinnerElement.className = "acd-spinner";
        spinnerElement.style.width = "28px";
        spinnerElement.style.height = "28px";
        const message = document.createElement("div");
        message.className = "acd-dialog-message";
        message.innerText = "Loading Sample Images...";
        message.style.marginTop = "10px";
        sampleImageTemplate.appendChild(spinnerElement);
        sampleImageTemplate.appendChild(message);

        this.fetchManager.getSampleImages().then((res) => {
            const imageTitle = document.createElement("div");
            imageTitle.innerText = "Choose from our Sample Images";
            imageTitle.style.marginLeft = "15px";
            imageTitle.className = "acd-image-title";
            sampleImageTemplate.style.flexDirection = "row";
            sampleImageTemplate.removeChild(spinnerElement);
            sampleImageTemplate.removeChild(message);
            sampleImageTemplate.appendChild(imageTitle);
            const imageContainer = document.createElement("div");
            imageContainer.className = "acd-sample-list";
            for (let template of res.templates) {
                let sampleImage = new ImageItem(template);
                sampleImage.onClick = (selectedImage: string) => {
                    this.renderImage(selectedImage);
                };
                imageContainer.appendChild(sampleImage.render());
            }
            sampleImageTemplate.appendChild(imageContainer);
        });
        return sampleImageTemplate;
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.className = "acd-pic2card-container";
        const poweredByContainer = document.createElement("div");
        poweredByContainer.className = "acd-poweredby-title";
        poweredByContainer.innerHTML =
            "Powered By <a class='poweredby-link' href='https://www.imaginea.com/' target='_blank'><span class='link'>Imaginea</spanl></a>";
        const container = document.createElement("div");
        container.className = "acd-sample-container";

        container.appendChild(this.renderImageContainer());
        container.appendChild(this.renderSampleTemplate());
        this.setContent(poweredByContainer);
        this.setContent(container);

        return this._renderedElement;
    }

    get predictedCardJSON(): predictedCardJSON {
        return this._predictedCardJSON;
    }
}

export class ImageItem {
    constructor(readonly template: string) {}
    onClick: (template: string) => void;
    render(): HTMLElement {
        const imagePlaceholder = <HTMLImageElement>(
            document.createElement("img")
        );
        imagePlaceholder.className = "acd-sample-image";
        imagePlaceholder.setAttribute(
            "src",
            "data:image/png;base64," + this.template
        );
        imagePlaceholder.onclick = (event) => {
            this.onClick((event.target as HTMLImageElement).src);
        };
        return imagePlaceholder;
    }
}
export interface predictedCardJSON {
    card: {};
    data: {};
}
