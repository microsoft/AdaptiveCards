import {Fact} from "../../card-elements";

test('Fact should be instantiated', ()=>{
    const fact = new Fact();
    expect(fact).toEqual(expect.anything());
})