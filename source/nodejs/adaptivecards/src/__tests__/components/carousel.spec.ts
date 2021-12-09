// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard, SerializationContext, TextBlock } from "../../card-elements";
import { Carousel, CarouselPage } from "../../carousel";
import { ValidationEvent } from "../../enums";
import { CarouselConfig } from "../../host-config";

describe("carousels", () => {
    describe("when default constructed", () => {
        const defaultCarousel = new Carousel();

        it("should have reasonable default values", () => {
            expect(defaultCarousel.getJsonTypeName()).toBe("Carousel");
            expect(defaultCarousel.getItemCount()).toEqual(0);
            expect(defaultCarousel.getAllInputs()).toStrictEqual([]);
            expect(defaultCarousel.timer).toBeUndefined();
            expect(defaultCarousel.asString()).toBe(""); // expected?
        });
    });

    describe("when parsed from a valid object", () => {
        const tinyTimer = 42;

        const carouselTheJson = {
            "type": "Carousel",
            "timer": tinyTimer,
            "pages": [
                {
                    "type": "CarouselPage",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "page one"
                        }
                    ]
                },
                {
                    // note: implicit "type" here, for fun!
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "page two"
                        }
                    ]
                }
            ]
        };

        const carouselConfig = new CarouselConfig();
        expect(carouselConfig.minAutoplayDelay).toBeGreaterThan(tinyTimer);

        const context = new SerializationContext();

        let carouselTheObject: Carousel;

        it("shouldn't throw exceptions", () => {
            carouselTheObject = context.parseElement(
                undefined,
                carouselTheJson,
                [],
                false,
                true
            ) as Carousel;
        });

        it("should have all of its expected properties and child elements", () => {
            expect(carouselTheObject.timer).toEqual(carouselConfig.minAutoplayDelay);
            expect(carouselTheObject.getItemCount()).toBe(2);
            for (let i = 0; i < carouselTheObject.getItemCount(); i++) {
                const currentPage = carouselTheObject.getItemAt(i) as CarouselPage;
                expect(currentPage.getJsonTypeName()).toBe("CarouselPage");
                expect(currentPage.getItemCount()).toBe(1);
                expect(currentPage.getItemAt(0)).toBeInstanceOf(TextBlock);
                let theTextBlock = currentPage.getItemAt(0) as TextBlock;
                expect(theTextBlock.text).toMatch(/^page /);
            }
        });

        it("shouldn't allow anything in pages but CarouselPages", () => {
            const incorrectTypeCarousel = {
                "type": "Carousel",
                "pages": [
                    {
                        "type": "this ain't it"
                    }
                ]
            };

            let incorrectTypeParsed = context.parseElement(
                undefined,
                incorrectTypeCarousel,
                [],
                false,
                true
            ) as Carousel;
            expect(incorrectTypeParsed.getItemCount()).toBe(0);
            expect(context.eventCount).toBe(1);
            expect(context.getEventAt(0).event).toBe(ValidationEvent.ElementTypeNotAllowed);
        });
    });

    describe("certain elements", () => {
        it("shouldn't be allowed within a Carousel", () => {
            const carouselCard = {
                "type": "AdaptiveCard",
                "body": {
                    "type": "Carousel",
                    "pages": [
                        {
                            "items": [
                                {
                                    "type": "Input.Text",
                                    "label": "gottem"
                                }
                            ]
                        }
                    ]
                },
                "actions": [
                    {
                        "type": "Action.ToggleVisibility",
                        "title": "wooo!"
                    }
                ]
            };

            let context = new SerializationContext();
            let theCard = new AdaptiveCard();
            theCard.parse(carouselCard, context);
            expect(theCard.getItemCount()).toBe(1);

            let carouselElement = theCard.getItemAt(0) as Carousel;
            expect(carouselElement).toBeDefined();
            expect(carouselElement.getItemCount()).toEqual(1);

            let carouselPage = carouselElement.getItemAt(0) as CarouselPage;
            expect(carouselPage).toBeDefined();
            expect(carouselPage.getItemCount()).toBe(0);

            expect(theCard.getActionCount()).toBe(0);

            expect(context.eventCount).toBe(2);
        });
    });
});

describe("carousel pages", () => {
    it("shouldn't be parseable outside of a Carousel", () => {
        const context = new SerializationContext();
        const pageObject = {
            "type": "CarouselPage",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "unthinkable!"
                }
            ]
        };
        expect(context.parseElement(undefined, pageObject, [], false)).toBeUndefined();
        expect(context.eventCount).toBe(1);
        expect(context.getEventAt(0).event).toBe(ValidationEvent.UnknownElementType);
    });
});
