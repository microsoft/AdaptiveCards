// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSLabelConfig: NSObject {

    public private(set) var inputSpacing: ACSSpacing
    public private(set) var requiredInputs: ACSInputLabelConfig
    public private(set) var optionalInputs: ACSInputLabelConfig

    public init(
        inputSpacing: ACSSpacing,
        requiredInputs: ACSInputLabelConfig,
        optionalInputs: ACSInputLabelConfig)
    {
        self.inputSpacing = inputSpacing
        self.requiredInputs = requiredInputs
        self.optionalInputs = optionalInputs
        
    }
}
