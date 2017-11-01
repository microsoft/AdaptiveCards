import {DateInput} from "../../src/card-elements";

test('DateInput should be instantiated', ()=>{
    const dateInput = new DateInput();
    expect(dateInput).toEqual(expect.anything());
})