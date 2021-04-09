@testable import AdaptiveCards

class FakeRootView: ACRView {
    init() {
        super.init(style: .default, hostConfig: FakeHostConfig.make(), renderConfig: .default)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
