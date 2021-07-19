import AdaptiveCards_bridge

class FakeActionsConfig: ACSActionsConfig {
    static func make(showCard: ACSShowCardActionConfig = FakeShowCardActionConfig.make(),
                     actionsOrientation: ACSActionsOrientation = .vertical,
                     actionAlignment: ACSActionAlignment = .left,
                     buttonSpacing: NSNumber = 0,
                     maxActions: NSNumber = 0,
                     spacing: ACSSpacing = .default,
                     iconPlacement: ACSIconPlacement = .aboveTitle,
                     iconSize: NSNumber = 0) -> ACSActionsConfig {
        return ACSActionsConfig(showCard: showCard,
                                actionsOrientation: actionsOrientation,
                                actionAlignment: actionAlignment,
                                buttonSpacing: buttonSpacing,
                                maxActions: maxActions,
                                spacing: spacing,
                                iconPlacement: iconPlacement,
                                iconSize: iconSize)
    }
}

class FakeShowCardActionConfig: ACSShowCardActionConfig {
    static func make(actionMode: ACSActionMode = .inline,
                     style: ACSContainerStyle = .default,
                     inlineTopMargin: NSNumber = 0) -> ACSShowCardActionConfig {
        return ACSShowCardActionConfig(actionMode: actionMode,
                                       style: style,
                                       inlineTopMargin: inlineTopMargin)
    }
}
