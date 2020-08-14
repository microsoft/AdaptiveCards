//
//  ACRInputLabelView
//  ACRInputLabelView.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIBaseInputHandler.h"

@interface ACRInputLabelView : UIView <ACRIBaseInputHandler>
@property (weak, nonatomic) IBOutlet UILabel *errorMessage;
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) IBOutlet UIStackView *stack;
@property (strong, nonatomic) NSObject <ACRIBaseInputHandler> *dataSource;
@property BOOL isRequired;
@property BOOL hasErrorMessage;

+ (void)commonSetFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view;
+ (BOOL)commonTextUIValidate:(BOOL)isRequired hasText:(BOOL)hasText predicate:(NSPredicate *)predicate text:(NSString *)text error:(NSError *__autoreleasing *)error;

@end
