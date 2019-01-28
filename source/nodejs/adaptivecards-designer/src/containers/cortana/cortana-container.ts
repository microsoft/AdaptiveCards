import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";

export class CortanaContainer extends Designer.HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("cortana-card");

        let leftSide = document.createElement("div");
        leftSide.classList.add("cortana-leftside");

        let topLeft = document.createElement("div");
        topLeft.classList.add("cortana-topleft");

        let middleLeft = document.createElement("div");
        middleLeft.classList.add("cortana-middleleft");

        let bottomLeft = document.createElement("div");
        bottomLeft.classList.add("cortana-bottomleft");

        leftSide.appendChild(topLeft);
        leftSide.appendChild(middleLeft);
        leftSide.appendChild(bottomLeft);

        let rightSide = document.createElement("div");
        rightSide.classList.add("cortana-rightside");

        let header = document.createElement("div");
        header.classList.add("cortana-header");

        let searchBox = document.createElement("div");
        searchBox.classList.add("cortana-searchbox");

        let magnifyingGlass = document.createElement("div");
        magnifyingGlass.classList.add("cortana-searchbox-magnifyingglass");

        let searchBoxMiddle = document.createElement("div");
        searchBoxMiddle.classList.add("cortana-searchbox-middle");

        let microphone = document.createElement("div");
        microphone.classList.add("cortana-searchbox-microphone");

        searchBox.appendChild(magnifyingGlass);
        searchBox.appendChild(searchBoxMiddle);
        searchBox.appendChild(microphone);

        rightSide.appendChild(header);
        rightSide.appendChild(this.cardHost);
        rightSide.appendChild(searchBox);

        let frame = document.createElement("div");
        frame.classList.add("cortana-frame");

        frame.appendChild(leftSide);
        frame.appendChild(rightSide);

        hostElement.classList.add("cortana-outer-frame");
        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
            spacing: {
                small: 3,
                default: 8,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 10
            },
            separator: {
                lineThickness: 1,
                lineColor: "#FF999999"
            },
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 13,
                default: 15,
                medium: 18,
                large: 20,
                extraLarge: 24
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#000000",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        accent: {
                            default: "#FF2E89FC",
                            subtle: "#CC2E89FC"
                        },
                        dark: {
                            default: "#FF999999",
                            subtle: "#99999999"
                        },
                        light: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        attention: {
                            default: "#CCFF0000",
                            subtle: "#99FF0000"
                        },
                        good: {
                            default: "#CC00FF00",
                            subtle: "#9900FF00"
                        },
                        warning: {
                            default: "#CCFF9800",
                            subtle: "#99FF9800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#33FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        accent: {
                            default: "#FF2E89FC",
                            subtle: "#CC2E89FC"
                        },
                        dark: {
                            default: "#FF999999",
                            subtle: "#99999999"
                        },
                        light: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        attention: {
                            default: "#CCFF0000",
                            subtle: "#99FF0000"
                        },
                        good: {
                            default: "#CC00FF00",
                            subtle: "#9900FF00"
                        },
                        warning: {
                            default: "#CCFF9800",
                            subtle: "#99FF9800"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 68,
                large: 320
            },
            actions: {
                maxActions: 5,
                spacing: Adaptive.Spacing.Default,
                buttonSpacing: 5,
                showCard: {
                    actionMode: Adaptive.ShowCardActionMode.Inline,
                    inlineTopMargin: 20
                },
                actionsOrientation: Adaptive.Orientation.Horizontal,
                actionAlignment: Adaptive.ActionAlignment.Stretch
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Adaptive.Size.Small,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Bolder,
                    wrap: true
                },
                value: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Default,
                    wrap: true,
                },
                spacing: 12
            }
        });
    }
}
