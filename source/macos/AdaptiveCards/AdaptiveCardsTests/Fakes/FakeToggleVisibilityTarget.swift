import AdaptiveCards_bridge

class FakeToggleVisibilityTarget: ACSToggleVisibilityTarget {
    var elementId: String?
    var isVisible: ACSIsVisible = .isVisibleToggle
    
    override func getElementId() -> String? {
        return elementId
    }
    
    override func getIsVisible() -> ACSIsVisible {
        return isVisible
    }
}

extension FakeToggleVisibilityTarget {
    static func make(elementId: String = "", isVisible: ACSIsVisible = .isVisibleToggle) -> FakeToggleVisibilityTarget {
        let target = FakeToggleVisibilityTarget()
        target.elementId = elementId
        target.isVisible = isVisible
        return target
    }
}
