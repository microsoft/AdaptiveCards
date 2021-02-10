// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSContainerStyleDefinition: NSObject {

    public private(set) var backgroundColor: String
    public private(set) var borderColor: String
    public private(set) var borderThickness: NSNumber
    public private(set) var foregroundColors: ACSColorsConfig

    public init(
        backgroundColor: String,
        borderColor: String,
        borderThickness: NSNumber,
        foregroundColors: ACSColorsConfig)
    {
        self.backgroundColor = backgroundColor
        self.borderColor = borderColor
        self.borderThickness = borderThickness
        self.foregroundColors = foregroundColors
        
    }
}
