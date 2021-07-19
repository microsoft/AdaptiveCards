import AdaptiveCards_bridge
import AppKit

extension ACSIconPlacement {
    var imagePosition: NSControl.ImagePosition {
        switch self {
        case .aboveTitle: return .imageAbove
        case .leftOfTitle: return .imageLeft
        @unknown default: return .imageLeft
        }
    }
}

extension ACSBaseActionElement {
    var hasValidIcon: Bool {
        guard let iconUrl = getIconUrl() else { return false }
        return !iconUrl.isEmpty
    }
}
