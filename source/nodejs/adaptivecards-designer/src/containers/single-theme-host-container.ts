import { HostContainer } from "./host-container";

export abstract class SingleThemeHostContainer extends HostContainer {
    private _styleSheet: string;

    constructor(name: string, styleSheet: string) {
        super(name);
        this._styleSheet = styleSheet;
    }

    public getCurrentStyleSheet(): string {
        return this._styleSheet;
    }
}
