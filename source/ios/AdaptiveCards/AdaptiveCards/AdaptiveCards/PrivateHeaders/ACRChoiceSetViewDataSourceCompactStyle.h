//
//  ACRChoiceSetViewDataSourceCompactStyle
//  ACRChoiceSetViewDataSourceCompactStyle.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/ChoiceInput.h>
#import <AdaptiveCards/ChoiceSetInput.h>
#import <AdaptiveCards/HostConfig.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRChoiceSetViewDataSourceCompactStyle : NSObject <UITableViewDataSource, UITableViewDelegate, UIPickerViewDataSource, UIPickerViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;
@property NSMutableDictionary *results;
@property (weak) ACRView *rootView;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const &)choiceSet
                              rootView:(ACRView *)rootView;
@end
