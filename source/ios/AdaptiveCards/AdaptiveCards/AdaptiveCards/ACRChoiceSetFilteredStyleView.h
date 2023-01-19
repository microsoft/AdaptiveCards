//
//  ACRChoiceSetTypeaheadStyleView.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 16/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOHostConfig.h"
#import "ACRIBaseInputHandler.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

@protocol ACRChoiceSetFilteredDelegate <NSObject>
- (void)updateSelectedChoiceInTextField:(NSString *)text;
- (NSString *)getSelectedText;
@end

@interface ACRChoiceSetFilteredStyleView : UITextField <UITextFieldDelegate, ACRIBaseInputHandler, ACRChoiceSetFilteredDelegate>

@property (weak) UIView *showFilteredListControl;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)hostConfig;

@end
