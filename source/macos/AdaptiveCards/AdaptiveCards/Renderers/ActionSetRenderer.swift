import AdaptiveCards_bridge
import AppKit

class ActionSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = ActionSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let actionSet = element as? ACSActionSet else {
            logError("Element is not of type ACSActionSet")
            return NSView()
        }
        
        let actionSetView = ACRActionSetView()
        actionSetView.translatesAutoresizingMaskIntoConstraints = false
        let adaptiveActionHostConfig = hostConfig.getActions()
        
        if let orientation = adaptiveActionHostConfig?.actionsOrientation, orientation == .horizontal {
            actionSetView.orientation = .horizontal
        } else {
            actionSetView.orientation = .vertical
            let alignment = actionSetView.alignment
            if let actionAlignment = adaptiveActionHostConfig?.actionAlignment {
                switch actionAlignment {
                case .center:
                    actionSetView.alignment = .centerX
                case .left:
                    actionSetView.alignment = .leading
                case .right:
                    actionSetView.alignment = .trailing
                default:
                    actionSetView.alignment = alignment
                }
            }
        }
        
        var accumulatedWidth: CGFloat = 0, maxWidth: CGFloat = 0
        guard !actionSet.getActions().isEmpty else {
            logInfo("Actions in ActionSet is empty")
            return actionSetView
        }
        
        var actionsToRender: Int = 0
        if let maxActionsToRender = adaptiveActionHostConfig?.maxActions, let uMaxActionsToRender = maxActionsToRender as? Int {
            actionsToRender = min(uMaxActionsToRender, actionSet.getActions().count)
            if actionSet.getActions().count > uMaxActionsToRender {
                logError("WARNING: Some actions were not rendered due to exceeding the maximum number \(uMaxActionsToRender) actions are allowed")
            }
        }
        
        for index in 0..<actionsToRender {
            let action = actionSet.getActions()[index]
            let renderer = RendererManager.shared.actionRenderer(for: action.getType())
            if let curView = rootView as? ACRView {
                let view = renderer.render(action: action, with: hostConfig, style: style, rootView: curView, parentView: rootView, inputs: [])
                
                actionSetView.addArrangedSubView(view)
                if actionSetView.orientation == .vertical {
                    view.widthAnchor.constraint(equalTo: actionSetView.widthAnchor).isActive = true
                }
                accumulatedWidth += view.intrinsicContentSize.width
                maxWidth = max(maxWidth, view.intrinsicContentSize.width)
                actionSetView.actions.append(view)
            }
        }
        
        var contentWidth = accumulatedWidth
        if let spacing = adaptiveActionHostConfig?.buttonSpacing {
            actionSetView.spacing = CGFloat(truncating: spacing)
            actionSetView.elementSpacing = CGFloat(truncating: spacing)
            if actionSetView.orientation == .horizontal {
                contentWidth += CGFloat(truncating: spacing) * CGFloat(actionsToRender - 1)
            } else {
                contentWidth = maxWidth
            }
        }
        
        actionSetView.totalWidth = CGFloat(contentWidth)
        return actionSetView
    }
}
