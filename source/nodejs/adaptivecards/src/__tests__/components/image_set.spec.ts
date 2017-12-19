import {ImageSet} from "../../card-elements";

test('ImageSet should be instantiated', ()=>{
    const imageSet = new ImageSet();
    expect(imageSet).toEqual(expect.anything());
})