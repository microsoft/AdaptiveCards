export interface IPoint {
    x: number;
    y: number;
}
export declare class Rect {
    top: number;
    right: number;
    bottom: number;
    left: number;
    constructor(top?: number, right?: number, bottom?: number, left?: number);
    union(otherRect: Rect): void;
    isInside(point: IPoint): boolean;
    readonly width: number;
    readonly height: number;
}
