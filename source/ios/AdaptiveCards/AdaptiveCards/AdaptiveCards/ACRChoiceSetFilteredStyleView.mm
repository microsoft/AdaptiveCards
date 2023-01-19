//
//  ACRChoiceSetTypeaheadStyleView.cpp
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 16/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACRChoiceSetFilteredStyleView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOBundle.h"
#import "ACRActionDelegate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ChoicesData.h"
#import "ACRInputLabelView.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import "UtiliOS.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRTypeaheadSearchViewController.h"
#include "ACRTypeaheadSearchParameters.h"

using namespace AdaptiveCards;

@implementation ACRChoiceSetFilteredStyleView {
    ACOFilteredDataSource *_filteredDataSource;
    ACOFilteredListStateManager *_stateManager;
    ACOChoiceSetCompactStyleValidator *_validator;
    ACOHostConfig *_hostConfig;
    ACOBaseCardElement *_inputElem;
    NSString *_inputLabel;
    __weak ACRView *_rootView;
    UIButton *_navigationButton;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)hostConfig
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        _rootView = rootView;
        _inputElem = acoElem;
        _hostConfig = hostConfig;
        _validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElem dataSource:_filteredDataSource];

        // configure UITextField
        self.delegate = self;
        self.placeholder = _validator.placeHolder;
        self.allowsEditingTextAttributes = NO;
        self.text = _validator.userInitialChoice;

        // configure AdaptiveCards input handler
        self.id = [NSString stringWithCString:choiceSet->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.isRequired = _validator.isRequired;
        self.hasValidationProperties = self.isRequired;
        self.accessibilityTraits = UIAccessibilityTraitButton;
        
        _navigationButton = [UIButton buttonWithType:UIButtonTypeCustom];
        self.showFilteredListControl = _navigationButton;
        [_navigationButton addTarget:self action:@selector(launchFullScreenTypeaheadSearchView) forControlEvents:UIControlEventTouchUpInside];
        self.rightView = _navigationButton;
        self.rightViewMode = UITextFieldViewModeAlways;
        self.showFilteredListControl = _navigationButton;
        
        auto inputLabel = choiceSet->GetLabel();
        _inputLabel = (!inputLabel.empty()) ? [NSString stringWithCString:inputLabel.c_str() encoding:NSUTF8StringEncoding] : @"";

        ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
        if (renderer && [renderer respondsToSelector:@selector(configure:rootView:baseCardElement:hostConfig:)]) {
            // configure input UI
            [renderer configure:self rootView:rootView baseCardElement:acoElem hostConfig:hostConfig];
        }
    }
    return self;
}

-(void)launchFullScreenTypeaheadSearchView
{
    UIViewController *rootViewController = traverseResponderChainForUIViewController(_rootView);
    std::shared_ptr<BaseCardElement> elem = [_inputElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    std::shared_ptr<ChoicesData> choicesData = choiceSet->GetChoicesData();
    
    if (rootViewController &&
        choicesData->GetChoicesDataType().compare((AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::DataQuery))) == 0 ) {
        ACRTypeaheadZeroStateParams *zeroStateParams = [[ACRTypeaheadZeroStateParams alloc] initWithtitle:@"Search options" subtitle:nil];
        ACRTypeaheadOfflineStateParams *offlineStateParams = [[ACRTypeaheadOfflineStateParams alloc] initWithtitle:@"the device is offline" subtitle:nil];
        ACRTypeaheadNoResultsStateParams *noResultStateParams = [[ACRTypeaheadNoResultsStateParams alloc] initWithtitle:@"No results" subtitle:nil];
        ACRTypeaheadErrorStateParams *errorStateParams = [[ACRTypeaheadErrorStateParams alloc] initWithtitle:@"Something went wrong" subtitle:nil];
        ACRTypeaheadStateAllParameters *typeaheadParams = [[ACRTypeaheadStateAllParameters alloc] initWithzeroStateParams:zeroStateParams
                                                                                                         errorStateParams:errorStateParams
                                                                                                       noResultStateParams:noResultStateParams
                                                                                                        offlineStateParams:offlineStateParams];
        
        ACRTypeaheadSearchViewController *controller = [[ACRTypeaheadSearchViewController alloc] initWithInputChoiceSet:_inputElem rootView:_rootView hostConfig:nil choiceSetDelegate:self searchStateParams:typeaheadParams];
        UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:controller];
        navController.modalPresentationStyle = UIModalPresentationFullScreen;
        [rootViewController presentViewController:navController animated:YES completion:nil];
    }
}
- (void)navigateToTypeaheadSearchView:(UIButton *)button
{
    [self launchFullScreenTypeaheadSearchView];
}

#pragma mark - UITextFieldDelegate Methods

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    // launch the new view controller here
    [self launchFullScreenTypeaheadSearchView];
    return NO;
}

/// configures position of showFilteredListControl
- (CGRect)rightViewRectForBounds:(CGRect)bounds
{
    CGRect newBounds = [super rightViewRectForBounds:bounds];
    newBounds.origin.x = newBounds.origin.x - self.layoutMargins.right;
    return newBounds;
}

#pragma mark - ACRIBaseInputHandler Methods

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    self.accessibilityLabel = view.accessibilityLabel;
    if (shouldBecomeFirstResponder) {
        UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, self);
    } else {
        [view resignFirstResponder];
    }
}

- (BOOL)validate:(NSError **)error
{
    return [_validator isValid:self.text];
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = [_validator getValue:self.text];
}

#pragma mark - ACRChoiceSetTypeaheadSearchDelegate Methods

- (void)updateSelectedChoiceInTextField:(NSString *)text {
    self.text = text;
}

-(NSString *)getSelectedText {
    return self.text;
}

@synthesize hasValidationProperties;
@synthesize hasVisibilityChanged;
@synthesize isRequired;
@synthesize id;

@end

