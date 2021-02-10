// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSColorConfig: NSObject {

    public private(set) var defaultColor: String
    public private(set) var subtleColor: String
    public private(set) var highlightColors: ACSHighlightColorConfig

    public init(
        defaultColor: String,
        subtleColor: String,
        highlightColors: ACSHighlightColorConfig)
    {
        self.defaultColor = defaultColor
        self.subtleColor = subtleColor
        self.highlightColors = highlightColors
        
    }
}
