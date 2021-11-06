// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ActionType, CardElement, Container, ContainerBase, SerializationContext, ShowCardAction, ToggleVisibilityAction } from "./card-elements";
import { NumProperty, property, PropertyBag, Versions } from "./serialization";
import { GlobalRegistry, ElementSingletonBehavior } from "./registry";
import { TypeErrorType, ValidationEvent } from "./enums";
import { Strings } from "./strings";
import { Swiper, A11y, Autoplay, History, Keyboard, Navigation, Pagination, Scrollbar, SwiperOptions } from "swiper";
import * as Utils from "./utils";
import { GlobalSettings } from "./shared";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css/navigation";

export class CarouselPage extends Container {
    //#region Schema

    //#endregion

    protected internalRender(): HTMLElement | undefined {
        const swiperSlide: HTMLElement = document.createElement("div");
        swiperSlide.className = this.hostConfig.makeCssClassName("swiper-slide");

        const renderedElement = super.internalRender();
        Utils.appendChild(swiperSlide, renderedElement);
        return swiperSlide;
    }

    getForbiddenActionTypes(): ActionType[] {
        return [ShowCardAction, ToggleVisibilityAction]
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this.setShouldFallback(false);
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    getJsonTypeName(): string {
        return "CarouselPage";
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class Carousel extends ContainerBase {
    //#region Schema

    static readonly timerProperty = new NumProperty(Versions.v1_6, "timer", undefined);
    @property(Carousel.timerProperty)
    get timer(): number | undefined {
        let timer = this.getValue(Carousel.timerProperty);

        if (timer && timer < this.hostConfig.carousel.minAutoplayDelay) {
            console.warn(Strings.errors.tooLittleTimeDelay);
            timer = this.hostConfig.carousel.minAutoplayDelay;
        }

        return timer;
    }

    set timer(value: number | undefined) {
        if (value && value < this.hostConfig.carousel.minAutoplayDelay) {
            console.warn(Strings.errors.tooLittleTimeDelay);
            this.timer = this.hostConfig.carousel.minAutoplayDelay;
        }
        else {
            this.timer = value;
        }
    }

    //#endregion

    private _pages: CarouselPage[] = [];
    private _renderedPages: CarouselPage[];

    protected forbiddenChildElements(): string[] {
        return [
            ToggleVisibilityAction.JsonTypeName,
            ShowCardAction.JsonTypeName,
            "Media",
            "ActionSet",
            "Input.Text",
            "Input.Date",
            "Input.Time",
            "Input.Number",
            "Input.ChoiceSet",
            "Input.Toggle",
            ...super.forbiddenChildElements()
        ];
    }

    getJsonTypeName(): string {
        return "Carousel";
    }

    getItemCount(): number {
        return this._pages.length;
    }

    getItemAt(index: number): CardElement {
        return this._pages[index];
    }

    removeItem(item: CardElement): boolean {
        if (item instanceof CarouselPage) {
            const itemIndex = this._pages.indexOf(item);

            if (itemIndex >= 0) {
                this._pages.splice(itemIndex, 1);

                item.setParent(undefined);

                this.updateLayout();

                return true;
            }
        }

        return false;
    }

    getFirstVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedPages?.length > 0) {
            return this._renderedPages[0];
        }
        else {
            return undefined;
        }
    }

    getLastVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedPages?.length > 0) {
            return this._renderedPages[this._renderedPages.length - 1];
        }
        else {
            return undefined;
        }
    }

    get currentPageId(): string | undefined {
        if (this._swiper?.slides?.length) {
            const activeSlide = this._swiper.slides[this._swiper.activeIndex] as HTMLElement;
            return activeSlide.id;
        }
        return undefined;
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._pages = [];
        this._renderedPages = [];

        const jsonPages = source["pages"];
        if (Array.isArray(jsonPages)) {
            for (const item of jsonPages) {
                const page = this.createCarouselPageInstance(item, context);
                if (page) {
                    this._pages.push(page);
                }
            }
        }
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        context.serializeArray(target, "pages", this._pages);
    }

    protected internalRender(): HTMLElement | undefined {
        this._renderedPages = [];

        if (this._pages.length <= 0) {
            return undefined;
        }

        const cardLevelContainer: HTMLElement = document.createElement("div");

        const containerForAdorners: HTMLElement = document.createElement("div");
        containerForAdorners.className = this.hostConfig.makeCssClassName("ac-carousel-container");
        cardLevelContainer.appendChild(containerForAdorners);

        const swiperContainer: HTMLElement = document.createElement("div");
        swiperContainer.className = this.hostConfig.makeCssClassName("swiper", "ac-carousel");

        const swiperWrapper: HTMLElement = document.createElement("div");
        swiperWrapper.className = this.hostConfig.makeCssClassName("swiper-wrapper", "ac-carousel-card-container");
        swiperWrapper.style.display = "flex";

        if (GlobalSettings.useAdvancedCardBottomTruncation) {
            // Forces the container to be at least as tall as its content.
            //
            // Fixes a quirk in Chrome where, for nested flex elements, the
            // inner element's height would never exceed the outer element's
            // height. This caused overflow truncation to break -- containers
            // would always be measured as not overflowing, since their heights
            // were constrained by their parents as opposed to truly reflecting
            // the height of their content.
            //
            // See the "Browser Rendering Notes" section of this answer:
            // https://stackoverflow.com/questions/36247140/why-doesnt-flex-item-shrink-past-content-size
            swiperWrapper.style.minHeight = '-webkit-min-content';
        }

        const prevElementDiv: HTMLElement = document.createElement("div");
        prevElementDiv.className = this.hostConfig.makeCssClassName("swiper-button-prev", "ac-carousel-left");
        containerForAdorners.appendChild(prevElementDiv);

        const nextElementDiv: HTMLElement = document.createElement("div");
        nextElementDiv.className = this.hostConfig.makeCssClassName("swiper-button-next", "ac-carousel-right");
        containerForAdorners.appendChild(nextElementDiv);

        const pagination: HTMLElement = document.createElement("div");
        pagination.className = this.hostConfig.makeCssClassName("swiper-pagination", "ac-carousel-pagination");
        containerForAdorners.appendChild(pagination);

        const requestedNumberOfPages: number = Math.min(this._pages.length, this.hostConfig.carousel.maxCarouselPages);
        if (this._pages.length > this.hostConfig.carousel.maxCarouselPages) {
            console.warn(Strings.errors.tooManyCarouselPages);
        }

        if (this._pages.length > 0) {
            for (let i = 0; i < requestedNumberOfPages; i++) {
                const page = this._pages[i];
                const renderedItem = this.isElementAllowed(page) ? page.render() : undefined;
                renderedItem?.classList.add("ac-carousel-page");

                if (renderedItem) {
                    Utils.appendChild(swiperWrapper, renderedItem);
                    this._renderedPages.push(page);
                }
            }
        }

        swiperContainer.appendChild(swiperWrapper as HTMLElement);

        containerForAdorners.appendChild(swiperContainer);

        this.initializeCarouselControl(swiperContainer, nextElementDiv, prevElementDiv, pagination);

        cardLevelContainer.onfocus = () => {
            if (!this._isSwiperInitialized) {
                this._isSwiperInitialized = true;
                this._swiper?.destroy();
                this.initializeCarouselControl(swiperContainer, nextElementDiv, prevElementDiv, pagination);
            }
        };

        return this._renderedPages.length > 0 ? cardLevelContainer : undefined;
    }

    private _swiper?: Swiper;
    private _isSwiperInitialized = false;

    private initializeCarouselControl(swiperContainer: HTMLElement, nextElement: HTMLElement, prevElement: HTMLElement, paginationElement: HTMLElement): void {
        const swiperOptions: SwiperOptions = {
            loop: true,
            modules: [
                Navigation,
                Pagination,
                Scrollbar,
                A11y,
                History,
                Keyboard,
                Autoplay
            ],
            pagination: {
                el: paginationElement,
                clickable: true
            },
            navigation: {
                prevEl: prevElement,
                nextEl: nextElement
            },
            a11y: {
                enabled: true
            },
            keyboard: {
                enabled: true,
                onlyInViewport: true
            }
        };

        if (this.timer && !this.isDesignMode()) {
            swiperOptions.autoplay = { delay: this.timer, pauseOnMouseEnter: true };
        }

        const swiper: Swiper = new Swiper(swiperContainer, swiperOptions);

        // While the 'pauseOnMouseEnter' option should resume autoplay on
        // mouse exit it doesn't do it, so adding custom events to handle it
        swiperContainer.onmouseenter = function () {
            swiper.autoplay.stop();
        };

        swiperContainer.onmouseleave = function () {
            swiper.autoplay.start();
        };

        this._swiper = swiper;
    }

    private createCarouselPageInstance(source: any, context: SerializationContext): CarouselPage | undefined {
        return context.parseCardObject<CarouselPage>(
            this,
            source,
            this.forbiddenChildElements(),
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "CarouselPage" ? new CarouselPage() : undefined;
            },
            (typeName: string, errorType: TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName));
            }
        )
    }
}

GlobalRegistry.defaultElements.register("Carousel", Carousel, Versions.v1_6, ElementSingletonBehavior.Only);
