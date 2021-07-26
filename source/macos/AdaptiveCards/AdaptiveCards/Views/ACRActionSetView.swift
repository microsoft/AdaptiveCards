import AdaptiveCards_bridge
import AppKit

protocol ACRActionSetViewDelegate: AnyObject {
    func actionSetView(_ view: ACRActionSetView, didOpenURLWith actionView: NSView, urlString: String)
    func actionSetView(_ view: ACRActionSetView, didSubmitInputsWith actionView: NSView, dataJson: String?)
    func actionSetView(_ view: ACRActionSetView, didToggleVisibilityActionWith actionView: NSView, toggleTargets: [ACSToggleVisibilityTarget])
    func actionSetView(_ view: ACRActionSetView, willShowCardWith button: NSButton)
    func actionSetView(_ view: ACRActionSetView, didShowCardWith button: NSButton)
    func actionSetView(_ view: ACRActionSetView, renderShowCardFor cardData: ACSAdaptiveCard) -> NSView
}

class ACRActionSetView: NSView, ShowCardHandlingView {
    weak var delegate: ACRActionSetViewDelegate?
    
    let orientation: NSUserInterfaceLayoutOrientation
    let alignment: NSLayoutConstraint.Attribute
    let buttonSpacing: CGFloat
    let exteriorPadding: CGFloat
    private (set) var actions: [NSView] = []
    
    private (set) var showCardsMap: [NSNumber: NSView] = [:]
    private (set) var currentShowCardItems: ShowCardItems?
    
    private (set) lazy var stackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = orientation
        view.spacing = buttonSpacing
        view.alignment = alignment
        return view
    }()
    
    private (set) lazy var showCardStackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = .vertical
        view.alignment = .leading
        view.spacing = 0
        return view
    }()
    
    init(orientation: NSUserInterfaceLayoutOrientation, alignment: NSLayoutConstraint.Attribute, buttonSpacing: CGFloat, exteriorPadding: CGFloat) {
        self.orientation = orientation
        self.alignment = alignment
        self.buttonSpacing = buttonSpacing
        self.exteriorPadding = exteriorPadding
        super.init(frame: .zero)
        initialize()
    }
    
    required init?(coder: NSCoder) {
        self.actions = []
        self.orientation = .vertical
        self.alignment = .leading
        self.buttonSpacing = 8
        self.exteriorPadding = 0
        super.init(coder: coder)
        initialize()
    }
    
    private func initialize() {
        wantsLayer = true
        layer = NoClippingLayer()
        addSubview(stackView)
        addSubview(showCardStackView)
        setupConstraints()
    }
    
    override func resizeSubviews(withOldSize oldSize: NSSize) {
        super.resizeSubviews(withOldSize: oldSize)
        guard bounds.width > 0, orientation == .horizontal, !actions.isEmpty, abs(bounds.width - oldSize.width) > 10 else { return }
        arrangeElementsIfNeeded()
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let view = superview else { return }
        widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
    }
    
    func setActions(_ actions: [NSView]) {
        self.actions = actions
        arrangeElementsIfNeeded()
    }
    
    private func setupConstraints() {
        stackView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        stackView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        stackView.topAnchor.constraint(equalTo: topAnchor, constant: 6).isActive = true
        
        showCardStackView.topAnchor.constraint(equalTo: stackView.bottomAnchor, constant: exteriorPadding).isActive = true
        showCardStackView.leadingAnchor.constraint(equalTo: stackView.leadingAnchor, constant: -exteriorPadding).isActive = true
        showCardStackView.trailingAnchor.constraint(equalTo: stackView.trailingAnchor, constant: exteriorPadding).isActive = true
        showCardStackView.bottomAnchor.constraint(equalTo: bottomAnchor, constant: exteriorPadding).isActive = true
    }
    
    private func removeElements() {
        for view in stackView.arrangedSubviews {
            view.removeFromSuperview()
        }
    }
    
    private func arrangeElementsIfNeeded() {
        switch orientation {
        case .horizontal:
            layoutHorizontally()
        case .vertical:
            layoutVertically()
        @unknown default:
            layoutVertically()
        }
    }
    
    private func renderAndAddShowCard(_ card: ACSAdaptiveCard) -> NSView {
        guard let rDelegate = delegate else {
            logError("Rendering show card failed. Delegate is nil")
            return NSView()
        }
        let cardView = rDelegate.actionSetView(self, renderShowCardFor: card)
        showCardStackView.addArrangedSubview(cardView)
        cardView.widthAnchor.constraint(equalTo: showCardStackView.widthAnchor).isActive = true
        return cardView
    }
    
    private func layoutVertically() {
        removeElements()
        actions.forEach {
            stackView.addArrangedSubview($0)
            $0.widthAnchor.constraint(equalTo: stackView.widthAnchor).isActive = true
        }
    }
    
    private func layoutHorizontally() {
        // first empty the stackview and remove all the views
        removeElements()
        var accumulatedWidth: CGFloat = 0
        
        // new child stackview for horizontal orientation
        var curview = NSStackView()
        curview.translatesAutoresizingMaskIntoConstraints = false
        curview.spacing = buttonSpacing
        
        // adding new child stackview to parent stackview and the parent stackview will align child stackview vertically
        stackView.addArrangedSubview(curview)
        stackView.orientation = .vertical
        let gravityArea: NSStackView.Gravity = stackView.alignment == .centerY ? .center: (stackView.alignment == .trailing ? .trailing: .leading)
        for view in actions {
            accumulatedWidth += view.intrinsicContentSize.width
            if accumulatedWidth > bounds.width {
                let newStackView: NSStackView = {
                    let view = NSStackView()
                    view.translatesAutoresizingMaskIntoConstraints = false
                    return view
                }()
                curview = newStackView
                curview.orientation = .horizontal
                curview.addView(view, in: gravityArea)
                curview.spacing = buttonSpacing
                accumulatedWidth = 0
                accumulatedWidth += view.intrinsicContentSize.width
                accumulatedWidth += buttonSpacing
                stackView.addArrangedSubview(curview)
            } else {
                curview.addView(view, in: gravityArea)
                accumulatedWidth += buttonSpacing
            }
        }
    }
}

extension ACRActionSetView: ShowCardTargetHandlerDelegate {
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard) {
        guard let cardId = showCard.getInternalId()?.hash() else {
            logError("Card InternalID is nil")
            return
        }
        
        func manageShowCard(with id: NSNumber) {
            let cardView = showCardsMap[id] ?? renderAndAddShowCard(showCard)
            showCardsMap[cardId] = cardView
            currentShowCardItems = (cardId, button, cardView)
            cardView.isHidden = false
            return
        }
        
        delegate?.actionSetView(self, willShowCardWith: button)
        if button.state == .on {
            if let currentCardItems = currentShowCardItems {
                // Has a current open or closed showCard
                if currentCardItems.id == cardId {
                    // current card needs to be shown
                    currentCardItems.showCard.isHidden = false
                } else {
                    // different card needs to shown
                    currentCardItems.showCard.isHidden = true
                    currentCardItems.button.state = .off
                    manageShowCard(with: cardId)
                }
            } else {
                manageShowCard(with: cardId)
            }
        } else {
            currentShowCardItems?.showCard.isHidden = true
        }
        delegate?.actionSetView(self, didShowCardWith: button)
    }
    
    func handleOpenURLAction(actionView: NSView, urlString: String) {
        delegate?.actionSetView(self, didOpenURLWith: actionView, urlString: urlString)
    }
    
    func handleSubmitAction(actionView: NSView, dataJson: String?) {
        delegate?.actionSetView(self, didSubmitInputsWith: actionView, dataJson: dataJson)
    }
    
    func handleToggleVisibilityAction(actionView: NSView, toggleTargets: [ACSToggleVisibilityTarget]) {
        delegate?.actionSetView(self, didToggleVisibilityActionWith: actionView, toggleTargets: toggleTargets)
    }
}
