import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";
export declare abstract class BaseTeamsContainer extends Designer.HostContainer {
    renderTo(hostElement: HTMLElement): void;
}
export declare class LightTeamsContainer extends BaseTeamsContainer {
    getHostConfig(): Adaptive.HostConfig;
}
export declare class DarkTeamsContainer extends BaseTeamsContainer {
    getBackgroundColor(): string;
    getHostConfig(): Adaptive.HostConfig;
}
