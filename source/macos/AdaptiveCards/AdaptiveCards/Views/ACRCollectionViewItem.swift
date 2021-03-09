import Cocoa

class ACRCollectionViewItem: NSCollectionViewItem {
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func loadView() {
        let redBox = NSView(frame: .zero)
        redBox.wantsLayer = true
        redBox.layer?.backgroundColor = .init(red: 1, green: 0, blue: 0, alpha: 1)
        view = redBox
    }
}
