declare namespace ColorString {
    function get(colorString: string): { model: 'rgb' | 'hsl' | 'hwb', value: number[] };
}

declare namespace ColorString.get {
    function hsl(colorString: string): number[];
    function hwb(colorString: string): number[];
    function rgb(colorString: string): number[];
}

declare namespace ColorString.to {
    function hex(value: number[]): string;
    function hsl(value: number[]): string;
    function hwb(value: number[]): string;
    function keyword(value: number[]): string;
    function rgb(value: number[]): string;
}

declare namespace ColorString.to.rgb {
    function percent(value: number[]): string;
}

declare module "color-string" {
    export = ColorString;
}
