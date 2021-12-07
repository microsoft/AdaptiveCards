// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {
    ActionType,
    CardElement,
    Container,
    SerializationContext,
    ShowCardAction,
    ToggleVisibilityAction
} from "./card-elements";
import * as Enums from "./enums";
import {
    NumProperty,
    property,
    PropertyBag,
    SerializableObjectSchema,
    Versions
} from "./serialization";
import { GlobalRegistry, ElementSingletonBehavior } from "./registry";
import { TypeErrorType, ValidationEvent } from "./enums";
import { Strings } from "./strings";
import {
    Swiper,
    A11y,
    Autoplay,
    History,
    Keyboard,
    Navigation,
    Pagination,
    Scrollbar,
    SwiperOptions
} from "swiper";
import * as Utils from "./utils";
import { GlobalSettings } from "./shared";

// Note: to function correctly, consumers need to have CSS from swiper/css, swiper/css/pagination, and
// swiper/css/navigation

export class CarouselPage extends Container {
    //#region Schema
    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        // `style`, `bleed`, `isVisible` are not supported in CarouselPage
        schema.remove(Container.styleProperty);
        schema.remove(Container.bleedProperty);
        schema.remove(Container.isVisibleProperty);
    }
    //#endregion

    protected internalRender(): HTMLElement | undefined {
        const carouselSlide: HTMLElement = document.createElement("div");
        carouselSlide.className = this.hostConfig.makeCssClassName("swiper-slide");
        // `isRtl()` will set the correct value of rtl by reading the value from the parents
        this.rtl = this.isRtl();
        const renderedElement = super.internalRender();
        Utils.appendChild(carouselSlide, renderedElement);
        return carouselSlide;
    }

    getForbiddenActionTypes(): ActionType[] {
        return [ShowCardAction, ToggleVisibilityAction];
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this.setShouldFallback(false);
    }

    protected shouldSerialize(_context: SerializationContext): boolean {
        return true;
    }

    getJsonTypeName(): string {
        return "CarouselPage";
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class Carousel extends Container {
    //#region Schema
    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        // `style`, `bleed`, `isVisible` are not supported in Carousel
        schema.remove(Container.styleProperty);
        schema.remove(Container.bleedProperty);
        schema.remove(Container.isVisibleProperty);
    }

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
        } else {
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
        } else {
            return undefined;
        }
    }

    getLastVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedPages?.length > 0) {
            return this._renderedPages[this._renderedPages.length - 1];
        } else {
            return undefined;
        }
    }

    get currentPageId(): string | undefined {
        if (this._carousel?.slides?.length) {
            const activeSlide = this._carousel.slides[this._carousel.activeIndex] as HTMLElement;
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

        const carouselContainer: HTMLElement = document.createElement("div");
        carouselContainer.className = this.hostConfig.makeCssClassName("swiper", "ac-carousel");

        const containerForAdorners: HTMLElement = document.createElement("div");
        containerForAdorners.className = this.hostConfig.makeCssClassName("ac-carousel-container");

        cardLevelContainer.appendChild(containerForAdorners);

        const carouselWrapper: HTMLElement = document.createElement("div");
        carouselWrapper.className = this.hostConfig.makeCssClassName(
            "swiper-wrapper",
            "ac-carousel-card-container"
        );
        carouselWrapper.style.display = "flex";

        switch (this.getEffectiveVerticalContentAlignment()) {
            case Enums.VerticalAlignment.Top:
                carouselWrapper.style.alignItems = "flex-start";
                break;
            case Enums.VerticalAlignment.Bottom:
                carouselWrapper.style.alignItems = "flex-end";
                break;
            default:
                carouselWrapper.style.alignItems = "center";
                break;
        }

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
            carouselWrapper.style.minHeight = "-webkit-min-content";
        }

        const prevElementDiv: HTMLElement = document.createElement("div");
        prevElementDiv.className = this.hostConfig.makeCssClassName(
            "swiper-button-prev",
            "ac-carousel-left"
        );
        containerForAdorners.appendChild(prevElementDiv);

        const nextElementDiv: HTMLElement = document.createElement("div");
        nextElementDiv.className = this.hostConfig.makeCssClassName(
            "swiper-button-next",
            "ac-carousel-right"
        );
        containerForAdorners.appendChild(nextElementDiv);

        const pagination: HTMLElement = document.createElement("div");
        pagination.className = this.hostConfig.makeCssClassName(
            "swiper-pagination",
            "ac-carousel-pagination"
        );
        containerForAdorners.appendChild(pagination);

        const requestedNumberOfPages: number = Math.min(
            this._pages.length,
            this.hostConfig.carousel.maxCarouselPages
        );
        if (this._pages.length > this.hostConfig.carousel.maxCarouselPages) {
            console.warn(Strings.errors.tooManyCarouselPages);
        }

        if (this._pages.length > 0) {
            for (let i = 0; i < requestedNumberOfPages; i++) {
                const page = this._pages[i];
                const renderedItem = this.isElementAllowed(page) ? page.render() : undefined;
                renderedItem?.classList.add("ac-carousel-page");
                renderedItem?.children[0]?.classList.add("ac-carousel-page-container");

                if (renderedItem) {
                    Utils.appendChild(carouselWrapper, renderedItem);
                    this._renderedPages.push(page);
                }
            }
        }

        carouselContainer.appendChild(carouselWrapper);

        carouselContainer.tabIndex = 0;

        containerForAdorners.appendChild(carouselContainer);

        // `isRtl()` will set the correct value of rtl by reading the value from the parents
        this.rtl = this.isRtl();
        this.applyRTL(carouselContainer);

        this.initializeCarouselControl(
            carouselContainer,
            nextElementDiv,
            prevElementDiv,
            pagination,
            this.rtl
        );

        cardLevelContainer.addEventListener(
            "keydown",
            (_event) => {
                // we don't need to check which key was pressed, we only need to reinit swiper once, then remove this event listener
                const activeIndex = this._carousel?.activeIndex;
                this.initializeCarouselControl(
                    carouselContainer,
                    nextElementDiv,
                    prevElementDiv,
                    pagination,
                    this.rtl
                );
                if (activeIndex) {
                    this._carousel?.slideTo(activeIndex);
                }
            },
            { once: true }
        );

        return this._renderedPages.length > 0 ? cardLevelContainer : undefined;
    }

    private _carousel?: Swiper;

    private initializeCarouselControl(
        carouselContainer: HTMLElement,
        nextElement: HTMLElement,
        prevElement: HTMLElement,
        paginationElement: HTMLElement,
        rtl: boolean | undefined
    ): void {
        const swiperOptions: SwiperOptions = {
            loop: true,
            modules: [Navigation, Pagination, Scrollbar, A11y, History, Keyboard],
            pagination: {
                el: paginationElement,
                clickable: true
            },
            navigation: {
                prevEl: rtl === undefined || !rtl ? prevElement : nextElement,
                nextEl: rtl === undefined || !rtl ? nextElement : prevElement
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
            swiperOptions.modules?.push(Autoplay);
            swiperOptions.autoplay = { delay: this.timer, pauseOnMouseEnter: true };
        }

        const carousel: Swiper = new Swiper(carouselContainer, swiperOptions);

        // While the 'pauseOnMouseEnter' option should resume autoplay on
        // mouse exit it doesn't do it, so adding custom events to handle it

        carouselContainer.addEventListener("mouseenter", function (_event) {
            carousel.autoplay?.stop();
        });

        carouselContainer.addEventListener("mouseleave", function (_event) {
            carousel.autoplay?.start();
        });

        this._carousel = carousel;
    }

    private createCarouselPageInstance(
        source: any,
        context: SerializationContext
    ): CarouselPage | undefined {
        return context.parseCardObject<CarouselPage>(
            this,
            source,
            this.forbiddenChildElements(),
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "CarouselPage" ? new CarouselPage() : undefined;
            },
            (typeName: string, _errorType: TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName)
                );
            }
        );
    }
}

GlobalRegistry.defaultElements.register(
    "Carousel",
    Carousel,
    Versions.v1_6,
    ElementSingletonBehavior.Only
);
