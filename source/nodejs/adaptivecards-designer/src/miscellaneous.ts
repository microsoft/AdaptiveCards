// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";

export interface IPoint {
	x: number;
	y: number;
}

export class Rect {
	top: number;
	right: number;
	bottom: number;
	left: number;

	constructor(top: number = 0, right: number = 0, bottom: number = 0, left: number = 0) {
		this.top = top;
		this.right = right;
		this.bottom = bottom;
		this.left = left;
	}

	union(otherRect: Rect) {
		this.top = Math.min(this.top, otherRect.top);
		this.left = Math.min(this.left, otherRect.left);
		this.bottom = Math.max(this.bottom, otherRect.bottom);
		this.right = Math.max(this.right, otherRect.right);
	}

	isInside(point: IPoint): boolean {
		return point.x >= this.left && point.x <= this.right && point.y >= this.top && point.y <= this.bottom;
	}

	get width(): number {
		return this.right - this.left;
	}

	get height(): number {
		return this.bottom - this.top;
	}
}

export class Utils {
	public static isAbsoluteUrl(urlString: string): boolean {
		return urlString.indexOf('http://') === 0
		|| urlString.indexOf('https://') === 0;
	}

	public static joinPaths(...args: string[]) {
		return args.map(
			(part, i) => {
				if (!part) {
					part = "";
				}

				if (i === 0) {
					return part.trim().replace(/[\/]*$/g, '')
				} else {
					return part.trim().replace(/(^[\/]*|[\/]*$)/g, '')
				}
			}).filter(x => x.length).join('/')
	}
}

export var defaultHostConfig = new Adaptive.HostConfig(
    {
        preExpandSingleShowCardAction: true,
        supportsInteractivity: true,
        spacing: {
            small: 10,
            default: 20,
            medium: 30,
            large: 40,
            extraLarge: 50,
            padding: 20
        },
        separator: {
            lineThickness: 1,
            lineColor: "#EEEEEE"
        },
        textAlign: {
            right: "right"
        },
        imageSizes: {
            small: 40,
            medium: 80,
            large: 160
        },
        fontStyles: {
            default: {
                fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 17,
                    large: 21,
                    extraLarge: 26
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            },
            monospace: {
                fontFamily: "'Courier New', Courier, monospace",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 17,
                    large: 21,
                    extraLarge: 26
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            }
        },
        containerStyles: {
            default: {
                backgroundColor: "#f9f9f9",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#08000000",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            accent: {
                backgroundColor: "#C7DEF9",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            good: {
                backgroundColor: "#CCFFCC",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            attention: {
                backgroundColor: "#FFC5B2",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            warning: {
                backgroundColor: "#FFE2B2",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            }
        },
        actions: {
            maxActions: 5,
            spacing: Adaptive.Spacing.Default,
            buttonSpacing: 10,
            showCard: {
                actionMode: Adaptive.ShowCardActionMode.Inline,
                inlineTopMargin: 16
            },
            actionsOrientation: Adaptive.Orientation.Horizontal,
            actionAlignment: Adaptive.ActionAlignment.Left
        },
        adaptiveCard: {
            allowCustomStyle: true
        },
        imageSet: {
            imageSize: Adaptive.Size.Medium,
            maxImageHeight: 100
        },
        factSet: {
            title: {
                color: Adaptive.TextColor.Default,
                size: Adaptive.TextSize.Default,
                isSubtle: false,
                weight: Adaptive.TextWeight.Bolder,
                wrap: true,
                maxWidth: 150,
            },
            value: {
                color: Adaptive.TextColor.Default,
                size: Adaptive.TextSize.Default,
                isSubtle: false,
                weight: Adaptive.TextWeight.Default,
                wrap: true,
            },
            spacing: 10
        }
    }
);

defaultHostConfig.cssClassNamePrefix = "default";
