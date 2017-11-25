import { BackgroundImage } from "../../src/card-elements";

test('BackgroundImage should be instantiated', () => {
    const backgroundImage = new BackgroundImage();
    expect(backgroundImage).toEqual(expect.anything());
})