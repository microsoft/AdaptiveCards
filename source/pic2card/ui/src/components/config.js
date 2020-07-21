export default {
    adaptiveHostConfig: {
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
            lineColor: "#EEEEEE"
        },
        supportsInteractivity: true,
        fontTypes: {
            default: {
                fontFamily:
                    "'Segoe UI', 'Roboto', 'Oxygen', 'Ubuntu', 'Cantarell', 'Fira Sans', 'Droid Sans', 'Helvetica Neue', sans-serif",
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
                backgroundColor: "#FFFFFF",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#6f6f6f"
                    },
                    accent: {
                        default: "#0063B1",
                        subtle: "#0063B1"
                    },
                    attention: {
                        default: "#ED0000",
                        subtle: "#DDED0000"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#B75C00",
                        subtle: "#DDB75C00"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#F9F9F9",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#6f6f6f"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#ED0000",
                        subtle: "#DDED0000"
                    },
                    good: {
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#B75C00",
                        subtle: "#DDB75C00"
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
        imageSizes: {
            small: 40,
            medium: 80,
            large: 160
        },
        actions: {
            maxActions: 5,
            spacing: "default",
            buttonSpacing: 8,
            showCard: {
                actionMode: "inline",
                inlineTopMargin: 8
            },
            actionsOrientation: "horizontal",
            actionAlignment: "stretch"
        },
        adaptiveCard: {
            allowCustomStyle: false
        },
        imageSet: {
            imageSize: "medium",
            maxImageHeight: 100
        },
        factSet: {
            title: {
                color: "default",
                size: "default",
                isSubtle: false,
                weight: "bolder",
                wrap: true,
                maxWidth: 150
            },
            value: {
                color: "default",
                size: "default",
                isSubtle: false,
                weight: "default",
                wrap: true
            },
            spacing: 8
        }
    }
};
