import * as Adaptive from "adaptivecards";
import { HostContainer } from "./host-container";

export enum ColorTheme {
    Light = "Light",
    Dark = "Dark"
}

export abstract class MultiThemeHostContainer extends HostContainer {
    private _colorTheme: ColorTheme = ColorTheme.Light;
    private _cssFileName: string;
    private _hostConfigLight: any;
    private _hostConfigDark: any;
    private _lightBackground: string;
    private _darkBackground: string;

    constructor(
        name: string,
        cssFileName: string,
        hostConfigLight: any,
        hostConfigDark: any,
        lightBackground: string,
        darkBackground: string
    ) {
        super(name);

        this._cssFileName = cssFileName;
        this._hostConfigLight = hostConfigLight;
        this._hostConfigDark = hostConfigDark;
        this._lightBackground = lightBackground;
        this._darkBackground = darkBackground;
    }

    public getCurrentStyleSheet(): string {
        return `containers/${this._cssFileName}-${this._colorTheme.toLowerCase()}.css`;
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(
            this._colorTheme === ColorTheme.Light ? this._hostConfigLight : this._hostConfigDark
        );
    }

    public getBackgroundColor(): string {
        return this._colorTheme === ColorTheme.Light ? this._lightBackground : this._darkBackground;
    }

    set colorTheme(value: ColorTheme) {
        this._colorTheme = value;
    }

    get supportsMultipleThemes(): boolean {
        return true;
    }
}
