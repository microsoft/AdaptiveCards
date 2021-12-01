//
//  ACRChoiceSetViewDataSourceCompactStyle
//  ACRChoiceSetViewDataSourceCompactStyle.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRIBaseInputHandler.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/ChoiceInput.h>
#import <AdaptiveCards/ChoiceSetInput.h>
#import <AdaptiveCards/HostConfig.h>
#import <UIKit/UIKit.h>

@interface ACRChoiceSetViewDataSourceCompactStyle : NSObject <UITableViewDataSource, UITableViewDelegate, UIPickerViewDataSource, UIPickerViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;
@property NSMutableDictionary *results;
@property (weak) ACRView *rootView;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const &)choiceSet
                              rootView:(ACRView *)rootView;
@end
