import AdaptiveCards_bridge
import AppKit

struct ACRBleedDirection: OptionSet {
    let rawValue: UInt
    
    static let ACRBleedRestricted = ACRBleedDirection(rawValue: 0 << 0)
    static let ACRBleedToLeadingEdge = ACRBleedDirection(rawValue: 1 << 0)
    static let ACRBleedToTrailingEdge = ACRBleedDirection(rawValue: 1 << 1)
    static let ACRBleedToTopEdge = ACRBleedDirection(rawValue: 1 << 2)
    static let ACRBleedToBottomEdge = ACRBleedDirection(rawValue: 1 << 3)
    static let ACRBleedToAll: ACRBleedDirection = [.ACRBleedToBottomEdge, .ACRBleedToLeadingEdge, .ACRBleedToTrailingEdge, .ACRBleedToTopEdge]
}
