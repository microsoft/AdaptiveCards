import {Fact} from "../../src/card-elements";

test('Fact should be instantiated', ()=>{
    const fact = new Fact();
    expect(fact).toEqual(expect.anything());
})