// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSTextConfig: NSObject {

    public private(set) var weight: ACSTextWeight
    public private(set) var size: ACSTextSize
    public private(set) var fontType: ACSFontType
    public private(set) var color: ACSForegroundColor
    public private(set) var isSubtle: Bool
    public private(set) var wrap: Bool
    public private(set) var maxWidth: NSNumber

    public init(
        weight: ACSTextWeight,
        size: ACSTextSize,
        fontType: ACSFontType,
        color: ACSForegroundColor,
        isSubtle: Bool,
        wrap: Bool,
        maxWidth: NSNumber)
    {
        self.weight = weight
        self.size = size
        self.fontType = fontType
        self.color = color
        self.isSubtle = isSubtle
        self.wrap = wrap
        self.maxWidth = maxWidth
        
    }
}
