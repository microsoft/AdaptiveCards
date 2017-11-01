import {ImageSet} from "../../src/card-elements";

test('ImageSet should be instantiated', ()=>{
    const imageSet = new ImageSet();
    expect(imageSet).toEqual(expect.anything());
})