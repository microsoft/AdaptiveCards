//
//  ACRTableRow.h
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import "AdaptiveCards.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACRColumnDefinition : NSObject

@property CGFloat numeric;
@property NSInteger baseIndex;
@property BOOL isValid;

- (instancetype)init:(CGFloat)numeric;

- (instancetype)init:(CGFloat)numeric baseIndex:(NSInteger)baseIndex;

@end

@interface ACRTableRowView : UIView

- (instancetype)init:(ACOBaseCardElement *)acoElem columnDefinitions:(NSArray<ACRColumnDefinition *> *)columnDefinition;

@end

NS_ASSUME_NONNULL_END
