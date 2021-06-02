import AppKit

class BundleUtils {
    static func getImage(_ imageName: String, ofType: String) -> NSImage? {
        let bundle = Bundle(for: self)
        guard let path = bundle.path(forResource: imageName, ofType: ofType) else {
            logError("AdaptiveCards: Image named '\(imageName)' Not Found")
            return nil
        }
        return NSImage(byReferencing: URL(fileURLWithPath: path))
    }
    
    static func loadNibNamed(_ nibName: String, owner: NSView) {
        let bundle = Bundle(for: self)
        guard bundle.loadNibNamed(nibName, owner: owner, topLevelObjects: nil) else {
            logError("AdaptiveCards: Bundle of '\(nibName)' is nil")
            return
        }
    }
}
