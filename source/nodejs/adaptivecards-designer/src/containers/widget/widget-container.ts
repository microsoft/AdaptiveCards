// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { MultiThemeHostContainer } from "../multi-theme-host-container";
import * as hostConfigLight from "../../hostConfigs/widget-light.json";
import * as hostConfigDark from "../../hostConfigs/widget-dark.json";

export enum ContainerSize {
    Small = "Small",
    Medium = "Medium",
    Large = "Large"
}

export class WidgetContainer extends MultiThemeHostContainer {
    private _containerSize: ContainerSize;
    private _outerFrame: HTMLDivElement;

    constructor(size: ContainerSize) {
        super(
            "Widgets Board",
            "widget-container",
            hostConfigLight,
            hostConfigDark,
            "#D2D2D2",
            "#616161"
        );
        this._containerSize = size;
    }
    
    static readonly widgetPadding: number = 16;

    public initialize(): void {
        super.initialize();
        Adaptive.GlobalSettings.removePaddingFromContainersWithBackgroundImage = true;
    }

    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.remove(
            "widget-small-card",
            "widget-medium-card",
            "widget-large-card"
        );
        this.cardHost.classList.add(`widget-${this._containerSize.toLowerCase()}-card`);
        this._outerFrame = document.createElement("div");
        this._outerFrame.classList.add("widget-outer-container");
        this._outerFrame.classList.add(`widget-${this._containerSize.toLowerCase()}-container`);

        const header = document.createElement("div");
        header.className = "widget-header";
        this._outerFrame.appendChild(header);

        const headerText = document.createElement("p");
        headerText.className = "widget-header-text";
        headerText.textContent = "Widget Header";
        header.appendChild(headerText);

        const moreButton = document.createElement("div");
        moreButton.className = "widget-header-more-button";
        moreButton.setAttribute("role", "button");
        moreButton.tabIndex = 0;
        header.appendChild(moreButton);

        const innerFrame = document.createElement("div");
        innerFrame.className = "widget-inner-container";
        innerFrame.appendChild(this.cardHost);

        this._outerFrame.appendChild(innerFrame);
        hostElement.appendChild(this._outerFrame);
    }

    public requiresOverflowStyling(): boolean {
        const renderedCard = document.getElementsByClassName("ac-adaptiveCard")[0] as HTMLElement;

        const cardHeight = renderedCard.getBoundingClientRect().height;
        const widgetHeight = this.cardHost.getBoundingClientRect().height;
        
        if (cardHeight > widgetHeight) {
            this.applyWidgetOverflowStyling(renderedCard);
            return true;
        }
        return false;
    }

    private applyWidgetOverflowStyling(renderedCard: HTMLElement) {
        renderedCard.style.height = "100%";

        const cardElementsWrapper = this.addCardElementsWrapper(renderedCard);
        cardElementsWrapper.classList.add("no-overflow");

        const carouselElements = renderedCard.getElementsByClassName("ac-carousel-container");

        for (let i = 0; i < carouselElements.length; i++) {
            const currentCarousel = carouselElements[i] as HTMLElement;

            const carouselRect = currentCarousel.getBoundingClientRect();
            const wrapperRect = cardElementsWrapper.getBoundingClientRect();

            // pagination will be in the bottom 16px of a carousel
            const paginationTop = carouselRect.bottom - 16;
            const paginationBottom = carouselRect.bottom;

            const paginationOverlapsBoundary = ((paginationBottom >= wrapperRect.bottom) && (paginationBottom < (wrapperRect.bottom + WidgetContainer.widgetPadding)) ||
                                                (paginationTop >= wrapperRect.bottom) && (paginationTop < (wrapperRect.bottom + WidgetContainer.widgetPadding)));

            if (paginationOverlapsBoundary) {
                // Hide overflow on the cardElement instead of the wrapper since pagination dots are in the margin
                renderedCard.classList.add("no-overflow");
                cardElementsWrapper.classList.remove("no-overflow");

                // Add the padding to the carousel if the pagination dots are in the margin
                currentCarousel.style.marginBottom = WidgetContainer.widgetPadding + "px";
                break;
            }
        }
    }
    
    private addCardElementsWrapper(parentElement: Element): HTMLElement {
        const cardElementsWrapper = document.createElement("div");
        cardElementsWrapper.classList.add("ac-card-elements-wrapper");

        Array.from(parentElement.children).forEach((child) => {
            cardElementsWrapper.appendChild(child);
        })

        parentElement.appendChild(cardElementsWrapper);
        return cardElementsWrapper;
    }
    
    public adjustStyleForBackground() {
        this._outerFrame.classList.remove(
            "widget-small-container-no-border",
            "widget-medium-container-no-border",
            "widget-large-container-no-border"
        );

        const renderedCard = document.getElementsByClassName("ac-adaptiveCard")[0] as HTMLElement;
        if (renderedCard.style.backgroundImage) {
            // If there is a background image present, we should remove the border
            this._outerFrame.classList.add(`widget-${this._containerSize.toLowerCase()}-container-no-border`);
        }
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_6;
    }

    get isFixedHeight(): boolean {
        return true;
    }

    set containerSize(value: ContainerSize) {
        this._containerSize = value;
    }

    get supportsMultipleSizes(): boolean {
        return true;
    }

    static get supportedContainerSizes(): string[] {
        return Object.values(ContainerSize);
    }
}
