// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSFontTypeDefinition: NSObject {

    public private(set) var fontFamily: String
    public private(set) var fontSizes: ACSFontSizesConfig
    public private(set) var fontWeights: ACSFontWeightsConfig

    public init(
        fontFamily: String,
        fontSizes: ACSFontSizesConfig,
        fontWeights: ACSFontWeightsConfig)
    {
        self.fontFamily = fontFamily
        self.fontSizes = fontSizes
        self.fontWeights = fontWeights
        
    }
}
