@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ChoiceSetInputRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var choiceSetInput: FakeChoiceSetInput!
    private var choiceSetInputRenderer: ChoiceSetInputRenderer!
    private var choices: [ACSChoiceInput] = []
    private var button: FakeChoiceInput!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        choiceSetInput = .make()
        choiceSetInputRenderer = ChoiceSetInputRenderer()
        button = .make()
        choices.append(button)
    }
    
    func testRendererSetChoiceStyle() {
        choiceSetInput = .make(choices: choices, choiceSetStyle: .compact)
        
        let choiceSetCompactView = renderChoiceSetCompactView()
        XCTAssertEqual(choiceSetCompactView.type, .compact)
        
        choiceSetInput = .make(choices: choices, choiceSetStyle: .expanded)
        
        let choiceSetView = renderChoiceSetView()
        XCTAssertEqual(choiceSetView.isRadioGroup, true)
    }
    
    func testRendererIsMultiSelect() {
        button = .make(title: "Blue", value: "2")
        choices.append(button)
        choiceSetInput = .make(isMultiSelect: true, value: "1,2", choices: choices)
        
        let choiceSetView = renderChoiceSetView()
        
        XCTAssertEqual(choiceSetView.isRadioGroup, false)
    }
    
    func testRendererSetsWrap() {
        // test wrap for radio button
        choiceSetInput = .make(isMultiSelect: false, value: "1", choices: choices, wrap: true)
        
        let choiceSetRadioView = renderChoiceSetView()
        XCTAssertEqual(choiceSetRadioView.wrap, true)
        
        // test wrap for check button
        choiceSetInput = .make(isMultiSelect: true, value: "1,2", choices: choices, wrap: true)
        
        let choiceSetCheckView = renderChoiceSetView()
        XCTAssertEqual(choiceSetCheckView.wrap, true)
    }
    
    private func renderChoiceSetView() -> ACRChoiceSetView {
        let view = choiceSetInputRenderer.render(element: choiceSetInput, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRChoiceSetView)
        guard let choiceSetView = view as? ACRChoiceSetView else { fatalError() }
        return choiceSetView
    }
    
    private func renderChoiceSetCompactView() -> ACRChoiceSetCompactView {
        let view = choiceSetInputRenderer.render(element: choiceSetInput, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRChoiceSetCompactView)
        guard let choiceSetCompactView = view as? ACRChoiceSetCompactView else { fatalError() }
        return choiceSetCompactView
    }
}

