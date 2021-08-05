//
//  ACRTableCellRenderer
//  ACRTableCellRenderer.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableCellRenderer.h"

@implementation ACRTableCellRenderer

+ (ACRTableCellRenderer *)getInstance
{
    static ACRTableCellRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTableCell;
}

@end
