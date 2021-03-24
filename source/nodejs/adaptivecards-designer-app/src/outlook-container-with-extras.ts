import { OutlookContainer } from "adaptivecards-designer";
import * as Extras from "adaptivecards-extras";

export class OutlookContainerWithExtras extends OutlookContainer {
    public initialize() {
        super.initialize();

        this.elementsRegistry.register("Table", Extras.Table);
    }
}