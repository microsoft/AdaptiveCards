// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {
    AdaptiveCard,
    ActionType,
    CardElement,
    Container,
    SerializationContext,
    ShowCardAction,
    ToggleVisibilityAction
} from "./card-elements";
import * as Enums from "./enums";
import {
    BoolProperty,
    NumProperty,
    EnumProperty,
    property,
    PropertyBag,
    SerializableObjectSchema,
    Versions,
    PixelSizeProperty
} from "./serialization";
import { GlobalRegistry } from "./registry";
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

    getForbiddenChildElements(): string[] {
        return this.forbiddenChildElements();
    }

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
            "Carousel",
            ...super.forbiddenChildElements()
        ];
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

    get hasVisibleSeparator(): boolean {
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
            this.setValue(Carousel.timerProperty, this.hostConfig.carousel.minAutoplayDelay);
        } else {
            this.setValue(Carousel.timerProperty, value);
        }
    }

    static readonly initialPageProperty = new NumProperty(Versions.v1_6, "initialPage", 0);
    @property(Carousel.initialPageProperty)
    get initialPageIndex(): number {
        return this.getValue(Carousel.initialPageProperty); 
    }

    set initialPageIndex(value: number) { 
        if (this.isValidParsedPageIndex(value)) { 
            this.setValue(Carousel.initialPageProperty, value);
        } else { 
            console.warn(Strings.errors.invalidInitialPageIndex(value));
            this.setValue(Carousel.initialPageProperty, 0); 
        }
    }

    static readonly loopProperty = new BoolProperty(Versions.v1_6, "loop", true);
    @property(Carousel.loopProperty)
    carouselLoop: boolean = true;
    
    static readonly orientationProperty = new EnumProperty(
        Versions.v1_6,
        "orientation",
        Enums.Orientation,
        Enums.Orientation.Horizontal
    );
    @property(Carousel.orientationProperty)
    carouselOrientation: Enums.Orientation = Enums.Orientation.Horizontal; 

    static readonly carouselHeightProperty = new PixelSizeProperty(
        Versions.v1_6,
        "heightInPixels"
    );
    @property(Carousel.carouselHeightProperty)
    carouselHeight?: number;
    
    private isValidParsedPageIndex(index: number) : boolean {
        return this._pages ? this.isValidPageIndex(index, this._pages.length) : false;
    }

    private isValidRenderedPageIndex(index: number) : boolean {
        return this._renderedPages ? this.isValidPageIndex(index, this._renderedPages.length) : false;
    }

    private isValidPageIndex(index: number, collectionSize: number) {
        return (collectionSize > 0 && 0 <= index && index < collectionSize);
    }

    //#endregion

    get previousEventType(): Enums.CarouselInteractionEvent {
        return this._previousEventType;
    }

    set previousEventType(eventType: Enums.CarouselInteractionEvent) {
        this._previousEventType = eventType;
    }

    private _pages: CarouselPage[] = [];
    private _renderedPages: CarouselPage[];
    private _carouselPageContainer: HTMLElement;
    private _containerForAdorners: HTMLElement;
    private _currentIndex: number = 0;
    private _previousEventType: Enums.CarouselInteractionEvent = Enums.CarouselInteractionEvent.Pagination;
    private _observer: ResizeObserver | null;
    private _carousel: Swiper | null;

    // Question: Why do we place this on the Carousel instead of the CarouselPage?
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

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        super.adjustRenderedElementSize(renderedElement);
        if (this.height == "stretch" && this._containerForAdorners !== undefined) { 
            this._containerForAdorners.style.height = "100%";
        }

        // Assign the explicit height to carouselPageContainer if given
        if (this.carouselHeight) {
            this._carouselPageContainer.style.height = this.carouselHeight + "px";
        }
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

    addPage(page: CarouselPage) {
        this._pages.push(page);
        page.setParent(this);
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

    get currentPageIndex(): number | undefined {
        return this._carousel?.realIndex;
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._pages = [];

        const jsonPages = source["pages"];
        if (Array.isArray(jsonPages)) {
            for (const item of jsonPages) {
                const page = this.createCarouselPageInstance(item, context);
                if (page) {
                    this._pages.push(page);
                }
            }
        }

        // everything is parsed do validate on initial page index
        this.validateParsing(context);
    }

    private validateParsing(context: SerializationContext) {
        if (!this.isValidParsedPageIndex(this.initialPageIndex)) {
            context.logParseEvent(
                this,
                Enums.ValidationEvent.InvalidPropertyValue,
                Strings.errors.invalidInitialPageIndex(this.initialPageIndex)
            );
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

        this.validateOrientationProperties();

        const cardLevelContainer: HTMLElement = document.createElement("div");
        cardLevelContainer.className = this.hostConfig.makeCssClassName("ac-carousel-card-level-container");

        const carouselContainer: HTMLElement = document.createElement("div");
        carouselContainer.className = this.hostConfig.makeCssClassName("swiper", "ac-carousel");
        this._carouselPageContainer = carouselContainer;

        const containerForAdorners: HTMLElement = document.createElement("div");
        containerForAdorners.className = this.hostConfig.makeCssClassName("ac-carousel-container");
        this._containerForAdorners = containerForAdorners;

        cardLevelContainer.appendChild(containerForAdorners);
        
        const navigationContainer: HTMLElement = document.createElement("div");
        navigationContainer.className = this.hostConfig.makeCssClassName("ac-carousel-navigation");
        containerForAdorners.appendChild(navigationContainer);

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
            "swiper-button-prev"
        );

        const nextElementDiv: HTMLElement = document.createElement("div");
        nextElementDiv.className = this.hostConfig.makeCssClassName(
            "swiper-button-next"
        );

        if (this.carouselOrientation === Enums.Orientation.Horizontal) {
            this.updateCssForHorizontalCarousel(prevElementDiv, nextElementDiv);
        } else {
            this.updateCssForVerticalCarousel(navigationContainer, prevElementDiv, nextElementDiv);
        }

        const pagination: HTMLElement = document.createElement("div");
        pagination.className = this.hostConfig.makeCssClassName(
            "swiper-pagination",
            "ac-carousel-pagination"
        );

        navigationContainer.appendChild(prevElementDiv);
        Utils.addCancelSelectActionEventHandler(prevElementDiv);

        navigationContainer.appendChild(pagination);
        Utils.addCancelSelectActionEventHandler(pagination);

        navigationContainer.appendChild(nextElementDiv);
        Utils.addCancelSelectActionEventHandler(nextElementDiv);

        if (this.isDesignMode()) {
            // If we are in design mode, we need to ensure these elements are in front of the peers
            prevElementDiv.style.zIndex = "20";
            nextElementDiv.style.zIndex = "20";
            pagination.style.zIndex = "20";
        }

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

        carouselContainer.tabIndex = this.isDesignMode() ? -1 : 0;

        containerForAdorners.appendChild(carouselContainer);

        // `isRtl()` will set the correct value of rtl by reading the value from the parents
        this.rtl = this.isRtl();
        this.applyRTL(pagination);

        if (!this.isDesignMode()) {
            if (this.isValidRenderedPageIndex(this.initialPageIndex)) {
                this._currentIndex = this.initialPageIndex;
            } else {
                console.warn(Strings.errors.invalidInitialPageIndex(this.initialPageIndex));
                this._currentIndex = 0
            }
        }

        this.initializeCarouselControl(
            carouselContainer,
            nextElementDiv,
            prevElementDiv,
            pagination,
            this.rtl
        );

        return this._renderedPages.length > 0 ? cardLevelContainer : undefined;
    }

    applyRTL(pagination: HTMLElement) {
        super.applyRTL(this._carouselPageContainer);
        if (this.rtl) {
            pagination.classList.add(this.hostConfig.makeCssClassName(
                "ac-carousel-pagination-rtl"
            ));
        }
    }

    validateOrientationProperties() {
        if (!this.carouselHeight) {
            this.carouselOrientation = Enums.Orientation.Horizontal;
        }
    }

    updateCssForHorizontalCarousel(
        prevElementDiv: HTMLElement,
        nextElementDiv: HTMLElement
    ) {
        prevElementDiv.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-left"
        ));
        nextElementDiv.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-right"
        ));
    }

    updateCssForVerticalCarousel(
        navigationContainer: HTMLElement,
        prevElementDiv: HTMLElement,
        nextElementDiv: HTMLElement
    ) {
        this._containerForAdorners.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-container-vertical"
        ));
        navigationContainer.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-navigation-vertical"
        ))

        prevElementDiv.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-up"
        ));
        nextElementDiv.classList.add(this.hostConfig.makeCssClassName(
            "ac-carousel-down"
        ));
    }

    private initializeCarouselControl(
        carouselContainer: HTMLElement,
        nextElement: HTMLElement,
        prevElement: HTMLElement,
        paginationElement: HTMLElement,
        rtl: boolean | undefined
    ): void {

        const nextElementAdjustedForRtl = (rtl === undefined || !rtl ? nextElement : prevElement);
        const prevElementAdjustedForRtl = (rtl === undefined || !rtl ? prevElement : nextElement);

        const prevElementAdjustedForOrientation = (Enums.Orientation.Horizontal === this.carouselOrientation) ? prevElementAdjustedForRtl : prevElement;
        const nextElementAdjustedForOrientation = (Enums.Orientation.Horizontal === this.carouselOrientation) ? nextElementAdjustedForRtl : nextElement;

        const swiperOptions: SwiperOptions = {
            loop: !this.isDesignMode() && this.carouselLoop,
            modules: [Navigation, Pagination, Scrollbar, A11y, History, Keyboard],
            pagination: {
                el: paginationElement,
                clickable: true
            },
            navigation: {
                prevEl: prevElementAdjustedForOrientation,
                nextEl: nextElementAdjustedForOrientation
            },
            a11y: {
                enabled: true
            },
            keyboard: {
                enabled: false,
                onlyInViewport: true
            },
            direction: this.carouselOrientation === Enums.Orientation.Horizontal ? "horizontal" : "vertical",
            resizeObserver: false,
            initialSlide: this._currentIndex
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

        carousel.on('navigationNext',  (swiper: Swiper) => {
            this.raiseCarouselEvent(Enums.CarouselInteractionEvent.NavigationNext);
        });

        carousel.on('navigationPrev',  (swiper: Swiper) => {
            this.raiseCarouselEvent(Enums.CarouselInteractionEvent.NavigationPrevious);
        });

        carousel.on('slideChangeTransitionEnd',  (swiper: Swiper) => {
            this.currentIndex = swiper.realIndex;
            this.raiseCarouselEvent(Enums.CarouselInteractionEvent.Pagination); 
        });

        carousel.on('autoplay',  () => {
            this.raiseCarouselEvent(Enums.CarouselInteractionEvent.Autoplay);
        });

        carousel.on('paginationRender', (swiper, paginationEl) => {
            swiper.pagination.bullets.forEach((bullet, index) => {
                bullet.addEventListener("keypress", function(event : KeyboardEvent) {
                    if (event.key == "Enter") {
                        event.preventDefault();
                        swiper.slideTo(index + 1);
                    }
                });
            });
        });

        carousel.on('destroy', () => {
            this.destroyResizeObserver();
        });

        prevElement.title = prevElement.ariaLabel ?? Strings.defaults.carouselNavigationPreviousTooltip();

        nextElement.title = nextElement.ariaLabel ?? Strings.defaults.carouselNavigationNextTooltip();

        this._carousel = carousel;

        this.createResizeObserver();
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

    slideTo(index: number) {
        this._carousel?.slideTo(index);
    }

    get carouselPageContainer() {
        return this._carouselPageContainer;
    }

    get currentIndex(): number {
        return this._currentIndex;
    }

    set currentIndex(currentIndex: number) {
        this._currentIndex = currentIndex;
    }

    private createCarouselEvent (type : Enums.CarouselInteractionEvent): CarouselEvent
    {
        let currentPageId : string | undefined;
        if (this.currentPageIndex != undefined) {
            currentPageId = this.getItemAt(this.currentPageIndex).id;
        }
        return new CarouselEvent(type, this.id, currentPageId, this.currentPageIndex);   
    }

    private raiseCarouselEvent(eventType : Enums.CarouselInteractionEvent) {
        const card = this.parent ? (this.parent.getRootElement() as AdaptiveCard) : undefined;
        const onCarouselEventHandler = 
            card && card.onCarouselEvent
                ? card.onCarouselEvent
                : AdaptiveCard.onCarouselEvent;
        // pagination event is triggered on slide transition end event 
        if (onCarouselEventHandler && eventType == Enums.CarouselInteractionEvent.Pagination) {
        // returns the event type that causes slide transition
            onCarouselEventHandler(this.createCarouselEvent(this.previousEventType));
        }
        this.previousEventType = eventType;
    }

    /// Swiper version 8 added requestAnimationFrame() call in its resize observer code
    /// The new call causes flickering issue,
    /// We've copied resize observer code from Swiper version 7 with some modifications
    private createResizeObserver() : void {

        if (!this.checkIfCarouselInValidStateForResizeEvent()) {
            return;
        }

        this._observer = new ResizeObserver((entries) => {
            const width = this._carousel?.width;
            const height = this._carousel?.height;
            let newWidth = width;
            let newHeight = height;
            entries.forEach(({ contentBoxSize, contentRect, target }) => {
            if (target && target !== this._carousel?.el) {
                return;
            }

            newWidth = contentRect
                ? contentRect.width
                : (contentBoxSize[0] || contentBoxSize).inlineSize;

            newHeight = contentRect
                ? contentRect.height
                : (contentBoxSize[0] || contentBoxSize).blockSize;
            });

            if (newWidth !== width || newHeight !== height) {
                if (this.checkIfCarouselInValidStateForResizeEvent()) {
                    this._carousel?.emit('beforeResize');
                    this._carousel?.emit('resize');
                }
            }

        });

        this._observer.observe(this._carousel?.el!);
    }

    private destroyResizeObserver(): void {
        if (this._observer && this._observer.unobserve && this._carousel?.el) {
            this._observer.unobserve(this._carousel.el);
            this._observer = null;
        }
    };

    private checkIfCarouselInValidStateForResizeEvent()
    {
        return this._carousel && !this._carousel.destroyed;
    }
}

export class CarouselEvent {
    constructor(public type : Enums.CarouselInteractionEvent,
        public carouselId : string | undefined,
        public activeCarouselPageId : string | undefined,
        public activeCarouselPageIndex : number | undefined) {}
}

GlobalRegistry.defaultElements.register(
    "Carousel",
    Carousel,
    Versions.v1_6
);

