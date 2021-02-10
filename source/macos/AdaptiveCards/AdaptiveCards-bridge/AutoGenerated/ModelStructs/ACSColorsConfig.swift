// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSColorsConfig: NSObject {

    public private(set) var defaultColor: ACSColorConfig
    public private(set) var accent: ACSColorConfig
    public private(set) var dark: ACSColorConfig
    public private(set) var light: ACSColorConfig
    public private(set) var good: ACSColorConfig
    public private(set) var warning: ACSColorConfig
    public private(set) var attention: ACSColorConfig

    public init(
        defaultColor: ACSColorConfig,
        accent: ACSColorConfig,
        dark: ACSColorConfig,
        light: ACSColorConfig,
        good: ACSColorConfig,
        warning: ACSColorConfig,
        attention: ACSColorConfig)
    {
        self.defaultColor = defaultColor
        self.accent = accent
        self.dark = dark
        self.light = light
        self.good = good
        self.warning = warning
        self.attention = attention
        
    }
}
