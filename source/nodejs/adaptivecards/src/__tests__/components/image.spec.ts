import {Image} from "../../card-elements";

test('Image should be instantiated', ()=>{
    const image = new Image();
    expect(image).toEqual(expect.anything());
})