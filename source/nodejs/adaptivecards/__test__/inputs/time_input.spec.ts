import {TimeInput} from "../../src/card-elements";

test('TimeInput should be instantiated', ()=>{
    const timeInput = new TimeInput();
    expect(timeInput).toEqual(expect.anything());
})