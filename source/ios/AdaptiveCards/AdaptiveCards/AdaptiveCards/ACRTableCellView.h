//
//  ACRTableCell.h
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "AdaptiveCards.h"

NS_ASSUME_NONNULL_BEGIN

@interface ACRTableCellDefinition : NSObject

//@property ACRWidth width;

- (instancetype)init:(ACRHorizontalAlignment) horizontalAlignment;

@end

@interface ACRTableCellView : UIView

@property CGFloat spacing;

- (instancetype)init:(UIView *)content cellDefinition:(ACRTableCellDefinition *)definition;

@end

NS_ASSUME_NONNULL_END
