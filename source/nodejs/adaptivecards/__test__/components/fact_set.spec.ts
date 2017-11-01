import {FactSet} from "../../src/card-elements";

test('FactSet should be instantiated', ()=>{
    const factSet = new FactSet();
    expect(factSet).toEqual(expect.anything());
})