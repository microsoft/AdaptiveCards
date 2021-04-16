// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSContainerBleedDirectionConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSContainerBleedDirection.h"

@implementation ACSContainerBleedDirectionConvertor


+(enum ACSContainerBleedDirection) convertCpp:(AdaptiveCards::ContainerBleedDirection) containerBleedDirectionCpp
{
  switch(containerBleedDirectionCpp)
  {
    case AdaptiveCards::ContainerBleedDirection::BleedRestricted:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRestricted;
    case AdaptiveCards::ContainerBleedDirection::BleedLeft:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeft;
    case AdaptiveCards::ContainerBleedDirection::BleedRight:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRight;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftRight:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRight;
    case AdaptiveCards::ContainerBleedDirection::BleedUp:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedUp;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftUp:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftUp;
    case AdaptiveCards::ContainerBleedDirection::BleedRightUp:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightUp;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftRightUp:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRightUp;
    case AdaptiveCards::ContainerBleedDirection::BleedDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedDown;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftDown;
    case AdaptiveCards::ContainerBleedDirection::BleedRightDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightDown;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftRightDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRightDown;
    case AdaptiveCards::ContainerBleedDirection::BleedUpDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedUpDown;
    case AdaptiveCards::ContainerBleedDirection::BleedLeftUpDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftUpDown;
    case AdaptiveCards::ContainerBleedDirection::BleedRightUpDown:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightUpDown;
    case AdaptiveCards::ContainerBleedDirection::BleedAll:
      return ACSContainerBleedDirection::ACSContainerBleedDirectionBleedAll;
  }
}


+(AdaptiveCards::ContainerBleedDirection) convertObj:(enum ACSContainerBleedDirection) containerBleedDirectionObjc
{
  switch(containerBleedDirectionObjc)
  {
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRestricted:
      return AdaptiveCards::ContainerBleedDirection::BleedRestricted;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeft:
      return AdaptiveCards::ContainerBleedDirection::BleedLeft;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRight:
      return AdaptiveCards::ContainerBleedDirection::BleedRight;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRight:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftRight;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedUp:
      return AdaptiveCards::ContainerBleedDirection::BleedUp;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftUp:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftUp;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightUp:
      return AdaptiveCards::ContainerBleedDirection::BleedRightUp;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRightUp:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftRightUp;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedDown:
      return AdaptiveCards::ContainerBleedDirection::BleedDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftDown:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightDown:
      return AdaptiveCards::ContainerBleedDirection::BleedRightDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftRightDown:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftRightDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedUpDown:
      return AdaptiveCards::ContainerBleedDirection::BleedUpDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedLeftUpDown:
      return AdaptiveCards::ContainerBleedDirection::BleedLeftUpDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedRightUpDown:
      return AdaptiveCards::ContainerBleedDirection::BleedRightUpDown;
    case ACSContainerBleedDirection::ACSContainerBleedDirectionBleedAll:
      return AdaptiveCards::ContainerBleedDirection::BleedAll;
  }
}

@end
