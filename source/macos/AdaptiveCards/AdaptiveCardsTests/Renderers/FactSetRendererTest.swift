@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class FactSetRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var factSet: FakeFactSet!
    private var factSetRenderer: FactSetRenderer!
    
    override func setUpWithError() throws {
        hostConfig = .make()
        factSet = .make()
        factSetRenderer = FactSetRenderer()
    }
    
    func testSingleFact() {
        var factArray: [FakeFacts] = []
        let fakeFact = FakeFacts()
        fakeFact.setTitle("Title Exists")
        fakeFact.setValue("Value Exists too")
        fakeFact.setLanguage("")
        factArray.append(fakeFact)
        factSet = .make(factArray: factArray)
        let factsRendered = factSet.getFacts()
        
        let factView = renderFactSet()
        let renderedFacts = factView.subviews
        guard let titleStack = renderedFacts[0] as? NSStackView else { return }
        guard let valueStack = renderedFacts[1] as? NSStackView else { return }
        
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            guard let titleView = elem as? ACRFactTextField else { return }
            let valueArray = valueStack.arrangedSubviews
            guard let valueView = valueArray[index] as? ACRFactTextField else { return }
            XCTAssertEqual(factsRendered[index].getTitle(), titleView.plainTextValue)
            XCTAssertEqual(factsRendered[index].getValue(), valueView.plainTextValue)
        }
    }
    
    func testOnlyTitle() {
        var factArray: [FakeFacts] = []
        let fakeFact = FakeFacts()
        fakeFact.setTitle("Only Title")
        fakeFact.setValue("")
        fakeFact.setLanguage("")
        factArray.append(fakeFact)
        factSet = .make(factArray: factArray)
        let factsRendered = factSet.getFacts()
        
        let factView = renderFactSet()
        let renderedFacts = factView.subviews
        guard let titleStack = renderedFacts[0] as? NSStackView else { return }
        guard let valueStack = renderedFacts[1] as? NSStackView else { return }
        
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            guard let titleView = elem as? ACRFactTextField else { return }
            let valueArray = valueStack.arrangedSubviews
            guard let valueView = valueArray[index] as? ACRFactTextField else { return }
            XCTAssertEqual(factsRendered[index].getTitle(), titleView.plainTextValue)
            XCTAssertEqual(factsRendered[index].getValue(), valueView.plainTextValue)
        }
    }
    
    func testOnlyValue() {
        var factArray: [FakeFacts] = []
        let fakeFact = FakeFacts()
        fakeFact.setTitle("")
        fakeFact.setValue("Value Only")
        fakeFact.setLanguage("")
        factArray.append(fakeFact)
        factSet = .make(factArray: factArray)
        let factsRendered = factSet.getFacts()
        
        let factView = renderFactSet()
        let renderedFacts = factView.subviews
        guard let titleStack = renderedFacts[0] as? NSStackView else { return }
        guard let valueStack = renderedFacts[1] as? NSStackView else { return }
        
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            guard let titleView = elem as? ACRFactTextField else { return }
            let valueArray = valueStack.arrangedSubviews
            guard let valueView = valueArray[index] as? ACRFactTextField else { return }
            XCTAssertEqual(factsRendered[index].getTitle(), titleView.plainTextValue)
            XCTAssertEqual(factsRendered[index].getValue(), valueView.plainTextValue)
        }
    }
    
    func testMultipleFacts() {
        var factArray: [FakeFacts] = []
        //First Fact
        let fakeFact1 = FakeFacts()
        fakeFact1.setTitle("Title1")
        fakeFact1.setValue("Value1")
        fakeFact1.setLanguage("")
        factArray.append(fakeFact1)
        // Second Fact
        let fakeFact2 = FakeFacts()
        fakeFact2.setTitle("Title2")
        fakeFact2.setValue("Value2")
        fakeFact2.setLanguage("")
        factArray.append(fakeFact2)
        factSet = .make(factArray: factArray)
        let factsRendered = factSet.getFacts()
        
        let factView = renderFactSet()
        let renderedFacts = factView.subviews
        guard let titleStack = renderedFacts[0] as? NSStackView else { return }
        guard let valueStack = renderedFacts[1] as? NSStackView else { return }
        
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            guard let titleView = elem as? ACRFactTextField else { return }
            let valueArray = valueStack.arrangedSubviews
            guard let valueView = valueArray[index] as? ACRFactTextField else { return }
            XCTAssertEqual(factsRendered[index].getTitle(), titleView.plainTextValue)
            XCTAssertEqual(factsRendered[index].getValue(), valueView.plainTextValue)
        }
    }
    
    func testMarkdownInFact() {
        var factArray: [FakeFacts] = []
        let fakeFact = FakeFacts()
        fakeFact.setTitle("Title Exists")
        fakeFact.setValue("Value *Exists* **too**")
        fakeFact.setLanguage("")
        factArray.append(fakeFact)
        factSet = .make(factArray: factArray)
        let factsRendered = factSet.getFacts()
        
        let factView = renderFactSet()
        let renderedFacts = factView.subviews
        guard let titleStack = renderedFacts[0] as? NSStackView else { return }
        guard let valueStack = renderedFacts[1] as? NSStackView else { return }
        
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            guard let titleView = elem as? ACRFactTextField else { return }
            let valueArray = valueStack.arrangedSubviews
            guard let valueView = valueArray[index] as? ACRFactTextField else { return }
            XCTAssertEqual(factsRendered[index].getTitle(), titleView.plainTextValue)
            XCTAssertEqual("Value Exists too", valueView.plainTextValue)
        }
    }
    
    private func renderFactSet() -> NSView {
        let view = factSetRenderer.render(element: factSet, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        return view
    }
}
