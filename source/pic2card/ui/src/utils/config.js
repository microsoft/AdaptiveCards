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
                        subtle: "#767676"
                    },
                    accent: {
                        default: "#0063B1",
                        subtle: "#0063B1"
                    },
                    attention: {
                        default: "#FF0000",
                        subtle: "#DDFF0000"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#c3ab23",
                        subtle: "#DDc3ab23"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#F0F0F0",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#767676"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#FF0000",
                        subtle: "#DDFF0000"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#c3ab23",
                        subtle: "#DDc3ab23"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
    },
    webChat: {
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
                fontFamily: "Calibri, sans-serif",
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
                        subtle: "#767676"
                    },
                    accent: {
                        default: "#0063B1",
                        subtle: "#0063B1"
                    },
                    attention: {
                        default: "#FF0000",
                        subtle: "#DDFF0000"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#c3ab23",
                        subtle: "#DDc3ab23"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#F0F0F0",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#767676"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#FF0000",
                        subtle: "#DDFF0000"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#c3ab23",
                        subtle: "#DDc3ab23"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
                        default: "#54a254",
                        subtle: "#DD54a254"
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
            maxActions: 100,
            spacing: "default",
            buttonSpacing: 8,
            showCard: {
                actionMode: "inline",
                inlineTopMargin: 8
            },
            actionsOrientation: "vertical",
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
    },
    microsoftTeamslight: {
        choiceSetInputValueSeparator: ",",
        supportsInteractivity: true,
        spacing: {
            small: 8,
            default: 12,
            medium: 16,
            large: 20,
            extraLarge: 24,
            padding: 16
        },
        separator: {
            lineThickness: 1,
            lineColor: "#EEEEEE"
        },
        imageSizes: {
            small: 32,
            medium: 52,
            large: 100
        },
        fontTypes: {
            default: {
                fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 14,
                    large: 18,
                    extraLarge: 24
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
                    medium: 14,
                    large: 18,
                    extraLarge: 24
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
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                },
                backgroundColor: "#ffffff"
            },
            emphasis: {
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                },
                backgroundColor: "#fff9f8f7"
            },
            accent: {
                backgroundColor: "#C7DEF9",
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                }
            },
            good: {
                backgroundColor: "#CCFFCC",
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                }
            },
            attention: {
                backgroundColor: "#FFC5B2",
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                }
            },
            warning: {
                backgroundColor: "#FFE2B2",
                foregroundColors: {
                    default: {
                        default: "#ff252424",
                        subtle: "#bf252424"
                    },
                    dark: {
                        default: "#252424",
                        subtle: "#bf252424"
                    },
                    light: {
                        default: "#ffffff",
                        subtle: "#fff3f2f1"
                    },
                    accent: {
                        default: "#6264a7",
                        subtle: "#8b8cc7"
                    },
                    good: {
                        default: "#92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#f8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#c4314b",
                        subtle: "#e5c4314b"
                    }
                }
            }
        },
        actions: {
            maxActions: 6,
            spacing: "Default",
            buttonSpacing: 8,
            showCard: {
                actionMode: "Inline",
                inlineTopMargin: 16,
                style: "emphasis"
            },
            preExpandSingleShowCardAction: false,
            actionsOrientation: "Horizontal",
            actionAlignment: "Left"
        },
        adaptiveCard: {
            allowCustomStyle: false
        },
        imageSet: {
            imageSize: "Medium",
            maxImageHeight: 100
        },
        factSet: {
            title: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Bolder",
                warp: true
            },
            value: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Default",
                warp: true
            },
            spacing: 16
        }
    },
    microsoftTeamsDark: {
        choiceSetInputValueSeparator: ",",
        supportsInteractivity: true,
        spacing: {
            small: 8,
            default: 12,
            medium: 16,
            large: 20,
            extraLarge: 24,
            padding: 16
        },
        separator: {
            lineThickness: 1,
            lineColor: "#EEEEEE"
        },
        fontTypes: {
            default: {
                fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 14,
                    large: 18,
                    extraLarge: 24
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
                    medium: 14,
                    large: 18,
                    extraLarge: 24
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            }
        },
        imageSizes: {
            small: 32,
            medium: 52,
            large: 100
        },
        containerStyles: {
            default: {
                foregroundColors: {
                    default: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                },
                backgroundColor: "#ff2d2c2c"
            },
            emphasis: {
                foregroundColors: {
                    default: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                },
                backgroundColor: "#ff292828"
            },
            accent: {
                backgroundColor: "#C7DEF9",
                foregroundColors: {
                    default: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                }
            },
            good: {
                backgroundColor: "#CCFFCC",
                foregroundColors: {
                    default: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                }
            },
            attention: {
                backgroundColor: "#FFC5B2",
                foregroundColors: {
                    default: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                }
            },
            warning: {
                backgroundColor: "#FFE2B2",
                foregroundColors: {
                    default: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    dark: {
                        default: "#ff201f1f",
                        subtle: "#ff2d2c2c"
                    },
                    light: {
                        default: "#ffffffff",
                        subtle: "#bfffffff"
                    },
                    accent: {
                        default: "#ffa6a7dc",
                        subtle: "#ff8b8cc7"
                    },
                    good: {
                        default: "#ff92c353",
                        subtle: "#e592c353"
                    },
                    warning: {
                        default: "#fff8d22a",
                        subtle: "#e5f8d22a"
                    },
                    attention: {
                        default: "#ffd74654",
                        subtle: "#e5d74654"
                    }
                }
            }
        },
        actions: {
            maxActions: 6,
            spacing: "Default",
            buttonSpacing: 8,
            showCard: {
                actionMode: "Inline",
                inlineTopMargin: 16,
                style: "emphasis"
            },
            preExpandSingleShowCardAction: false,
            actionsOrientation: "Horizontal",
            actionAlignment: "Left"
        },
        adaptiveCard: {
            allowCustomStyle: false
        },
        imageSet: {
            imageSize: "Medium",
            maxImageHeight: 100
        },
        factSet: {
            title: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Bolder",
                warp: true
            },
            value: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Default",
                warp: true
            },
            spacing: 16
        }
    },
    cortanaSkillsDark: {
        spacing: {
            small: 4,
            default: 8,
            medium: 12,
            padding: 16,
            large: 20,
            extraLarge: 32
        },
        separator: {
            lineThickness: 1,
            lineColor: "#505050"
        },
        imageSizes: {
            small: 32,
            medium: 48,
            large: 96
        },
        fontTypes: {
            default: {
                fontFamily: "Segoe UI, Tahoma, Geneva, Verdana, sans-serif",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 16,
                    large: 18,
                    extraLarge: 24
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            },
            monospace: {
                fontFamily: "Courier New, Courier, monospace",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 16,
                    large: 18,
                    extraLarge: 24
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            }
        },
        fontSizes: {
            small: 12,
            default: 14,
            medium: 16,
            large: 18,
            extraLarge: 24
        },
        fontWeights: {
            lighter: 200,
            default: 400,
            bolder: 600
        },
        containerStyles: {
            default: {
                backgroundColor: "#222222",
                foregroundColors: {
                    default: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#2F2F2F",
                foregroundColors: {
                    default: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            },
            accent: {
                backgroundColor: "#1B3345",
                foregroundColors: {
                    default: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            },
            good: {
                backgroundColor: "#92C353",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#415725"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#415725"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#EBF4E0"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            },
            attention: {
                backgroundColor: "#D74553",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#601F25"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#601F25"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#F7DEE0"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            },
            warning: {
                backgroundColor: "#F8D22A",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#6F5E12"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#6F5E12"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#FDF7D9"
                    },
                    accent: {
                        default: "#82C7FF",
                        subtle: "#3AA0F3"
                    },
                    good: {
                        default: "#92C353",
                        subtle: "#498205"
                    },
                    warning: {
                        default: "#F8D22A",
                        subtle: "#C19C00"
                    },
                    attention: {
                        default: "#D74553",
                        subtle: "#D13438"
                    }
                }
            }
        },
        actions: {
            maxActions: 5,
            spacing: "Default",
            buttonSpacing: 12,
            showCard: {
                actionMode: "Inline",
                inlineTopMargin: 16,
                style: "Emphasis"
            },
            preExpandSingleShowCardAction: false,
            actionsOrientation: "Horizontal",
            actionAlignment: "Stretch",
            iconSize: 20,
            iconPlacement: "leftOfTitle"
        },
        imageSet: {
            imageSize: "Medium",
            maxImageHeight: 100
        },
        factSet: {
            title: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Bolder",
                warp: true,
                maxWidth: 150
            },
            value: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Default",
                wrap: true
            },
            spacing: 12
        }
    },
    cortanaSkillsLight: {
        spacing: {
            small: 4,
            default: 8,
            medium: 12,
            padding: 16,
            large: 20,
            extraLarge: 32
        },
        separator: {
            lineThickness: 1,
            lineColor: "#E6E6E6"
        },
        imageSizes: {
            small: 32,
            medium: 48,
            large: 96
        },
        fontTypes: {
            default: {
                fontFamily: "Segoe UI, Tahoma, Geneva, Verdana, sans-serif",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 16,
                    large: 18,
                    extraLarge: 24
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            },
            monospace: {
                fontFamily: "Courier New, Courier, monospace",
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 16,
                    large: 18,
                    extraLarge: 24
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                }
            }
        },
        fontSizes: {
            small: 12,
            default: 14,
            medium: 16,
            large: 18,
            extraLarge: 24
        },
        fontWeights: {
            lighter: 200,
            default: 400,
            bolder: 600
        },
        containerStyles: {
            default: {
                backgroundColor: "#ffffff",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#F2F2F2",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            },
            accent: {
                backgroundColor: "#E5F1FA",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#737373"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D2D2D2"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            },
            good: {
                backgroundColor: "#107C10",
                foregroundColors: {
                    default: {
                        default: "#FFFFFF",
                        subtle: "#D4E7D4"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#073707"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#D4E7D4"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            },
            attention: {
                backgroundColor: "#C50F1F",
                foregroundColors: {
                    default: {
                        default: "#FFFFFF",
                        subtle: "#F4D4D7"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#58060D"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#F4D4D7"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            },
            warning: {
                backgroundColor: "#FCE100",
                foregroundColors: {
                    default: {
                        default: "#000000",
                        subtle: "#716500"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#716500"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#FEF9D2"
                    },
                    accent: {
                        default: "#0078D4",
                        subtle: "#004D8C"
                    },
                    good: {
                        default: "#107C10",
                        subtle: "#0B6A0B"
                    },
                    warning: {
                        default: "#CA5010",
                        subtle: "#8E562E"
                    },
                    attention: {
                        default: "#C50F1F",
                        subtle: "#A80000"
                    }
                }
            }
        },
        actions: {
            maxActions: 5,
            spacing: "Default",
            buttonSpacing: 12,
            showCard: {
                actionMode: "Inline",
                inlineTopMargin: 16,
                style: "Emphasis"
            },
            preExpandSingleShowCardAction: false,
            actionsOrientation: "Horizontal",
            actionAlignment: "Stretch",
            iconSize: 20,
            iconPlacement: "leftOfTitle"
        },
        imageSet: {
            imageSize: "Medium",
            maxImageHeight: 100
        },
        factSet: {
            title: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Bolder",
                wrap: true,
                maxWidth: 150
            },
            value: {
                size: "Default",
                color: "Default",
                isSubtle: false,
                weight: "Default",
                wrap: true
            },
            spacing: 12
        }
    }
};
