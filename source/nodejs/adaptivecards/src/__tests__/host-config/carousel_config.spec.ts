// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CarouselConfig } from "../../host-config";

test("CarouselConfig should parse valid json", () => {
    const carouselJson = {
        maxCarouselPages: 10,
        minAutoplayDelay: 50
    };
    const carouselConfig = new CarouselConfig(carouselJson);

    expect(carouselConfig.maxCarouselPages).toEqual(10);
    expect(carouselConfig.minAutoplayDelay).toEqual(50);
});

test("CarouselConfig can be parsed", () => {
    const carouselJson = {
        maxCarouselPages: 10,
        minAutoplayDelay: 50
    };
    const carouselConfig = new CarouselConfig(carouselJson);

    expect(carouselConfig.toJSON()).toEqual(carouselJson);
});
