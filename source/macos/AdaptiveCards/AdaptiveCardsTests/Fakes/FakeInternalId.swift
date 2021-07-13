import AdaptiveCards_bridge

class FakeInternalId: ACSInternalId {
    let fakeHashId: NSNumber
    
    init(hash: NSNumber) {
        fakeHashId = hash
    }
    
    override func hash() -> NSNumber? {
        return fakeHashId
    }
}
