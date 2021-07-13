//
//  AdaptiveCardsTests.swift
//  AdaptiveCardsTests
//
//  Created by aksc on 13/01/21.
//

@testable import AdaptiveCards
import XCTest

class AdaptiveCardsTests: XCTestCase {
    private var delegate: FakeAdaptiveCardActionDelegate!
    private var resourceResolver: FakeResourceResolver!
    
    override func setUp() {
        super.setUp()
        delegate = FakeAdaptiveCardActionDelegate()
        resourceResolver = FakeResourceResolver()
    }
    
    func testRetainCycles() {
        let bundle = Bundle(for: type(of: self))
        let fileNames = ["ActivityUpdate", "ActionSetSample", "ImageGallery", "Agenda"]
        let jsons = fileNames.map { NSDataAsset(name: $0 + ".json", bundle: bundle)!.data }
                        .map { String(data: $0, encoding: .utf8)! }
        
        let hostConfigData = NSDataAsset(name: "HostConfig.json", bundle: bundle)!.data
        let hostConfigJSON = String(data: hostConfigData, encoding: .utf8)!
        
        let hostConfig = try! AdaptiveCard.parseHostConfig(from: hostConfigJSON).get()
        let cards = jsons.map { AdaptiveCard.from(jsonString: $0).getAdaptiveCard()! }
        
        weak var weakCard1: NSView?
        weak var weakCard2: NSView?
        weak var weakCard3: NSView?
        weak var weakCard4: NSView?
        
        var blockExecuted = false
        autoreleasepool {
            let card1 = AdaptiveCard.render(card: cards[0], with: hostConfig, width: 432, actionDelegate: delegate, resourceResolver: resourceResolver)
            let card2 = AdaptiveCard.render(card: cards[1], with: hostConfig, width: 432, actionDelegate: delegate, resourceResolver: resourceResolver)
            let card3 = AdaptiveCard.render(card: cards[2], with: hostConfig, width: 432, actionDelegate: delegate, resourceResolver: resourceResolver)
            let card4 = AdaptiveCard.render(card: cards[3], with: hostConfig, width: 432, actionDelegate: delegate, resourceResolver: resourceResolver)
            
            // Simulate show card action
            guard let showCardButton = card1.buttonInHierachy(withTitle: "Set due date") else {
                XCTFail()
                return
            }
            showCardButton.performClick()
            
            weakCard1 = card1
            weakCard2 = card2
            weakCard3 = card3
            weakCard4 = card4
            
            XCTAssertNotNil(weakCard1)
            XCTAssertNotNil(weakCard2)
            XCTAssertNotNil(weakCard3)
            XCTAssertNotNil(weakCard4)
            
            blockExecuted = true
        }
        
        XCTAssertTrue(blockExecuted)
        XCTAssertNil(weakCard1)
        XCTAssertNil(weakCard2)
        XCTAssertNil(weakCard3)
        XCTAssertNil(weakCard4)
    }
    
    func testPerformanceExample() throws {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
}
