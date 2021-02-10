// DO NOT EDIT - Auto generated
// Generated with swift_model.j2

import Foundation

@objcMembers
open class ACSActionsConfig: NSObject {

    public private(set) var showCard: ACSShowCardActionConfig
    public private(set) var actionsOrientation: ACSActionsOrientation
    public private(set) var actionAlignment: ACSActionAlignment
    public private(set) var buttonSpacing: NSNumber
    public private(set) var maxActions: NSNumber
    public private(set) var spacing: ACSSpacing
    public private(set) var iconPlacement: ACSIconPlacement
    public private(set) var iconSize: NSNumber

    public init(
        showCard: ACSShowCardActionConfig,
        actionsOrientation: ACSActionsOrientation,
        actionAlignment: ACSActionAlignment,
        buttonSpacing: NSNumber,
        maxActions: NSNumber,
        spacing: ACSSpacing,
        iconPlacement: ACSIconPlacement,
        iconSize: NSNumber)
    {
        self.showCard = showCard
        self.actionsOrientation = actionsOrientation
        self.actionAlignment = actionAlignment
        self.buttonSpacing = buttonSpacing
        self.maxActions = maxActions
        self.spacing = spacing
        self.iconPlacement = iconPlacement
        self.iconSize = iconSize
        
    }
}
