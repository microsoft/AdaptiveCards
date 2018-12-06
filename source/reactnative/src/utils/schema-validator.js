import React from 'react';
import * as Utils from '../utils/util';

export class schemaValidator {
        
    static validateSchema( json ) {
        if (!Utils.isNullOrEmpty(json)) {
            let props = Object.keys(json);
           
        }
}


    /**
     * @description Parse an Array of components
     * @param {Array} componentArray - Json
     */
    parseRegistryComponents = ( componentArray ) => {
        const parsedElement = [];
        if (!componentArray)
             return parsedElement;
        componentArray.map((element, index) => {
            const Element = this.getComponentOfType(element.type);
            if (Element) {
                //let keys = Object.keys(json);
              
                parsedElement.push(<Element json={element} key={`${element.type}-${index}-${this.generateNumber()}`} />);
            } else {
                let error = {"type":"ParseError", "error": `Unknown Type ${element.type} encountered`};        
                this.props.onParseError(error);
               return null;
              }
          });
          return parsedElement;
    }

}
