//
//  JLEStickerDefinitions.h
//  JaaleeStickerSDK
//
//  Created by jaalee on 14-4-22.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef enum : char
{
    JLEStickerTxPowerLevel1 = 4,
    JLEStickerTxPowerLevel2 = 0,
    JLEStickerTxPowerLevel3 = -4,
    JLEStickerTxPowerLevel4 = -6,
    JLEStickerTxPowerLevel5 = -8,
    JLEStickerTxPowerLevel6 = -12,
    JLEStickerTxPowerLevel7 = -16,
    JLEStickerTxPowerLevel8 = -20,
    JLEStickerTxPowerLevel9 = -23,
    JLEStickerTxPowerLevel10 = -30,
    JLEStickerTxPowerLevel11 = -40
} JLEStickerTxPower;

typedef NS_ENUM(NSInteger, Jaalee_Sticker_State) {
    STICKER_STATE_ENABLE = 0,
    STICKER_STATE_DISABLE,
    STICKER_STATE_UNKNOWN
};

typedef NS_ENUM(NSInteger, Jaalee_Sticker_Audio_State) {
    STICKER_AUDIO_STATE_ENABLE = 0,
    STICKER_AUDIO_STATE_ENABLE_WHEN_START,
    STICKER_AUDIO_STATE_ENABLE_WHEN_TAP,
    STICKER_AUDIO_STATE_DISABLE,
    STICKER_AUDIO_STATE_UNKNOWN
};


typedef void(^JLECompletionBlock) (NSError* error);
typedef void(^JLEUnsignedShortCompletionBlock) (unsigned short value, NSError* error);
typedef void(^JLEPowerCompletionBlock) (JLEStickerTxPower value, NSError* error);
typedef void(^JLEBoolCompletionBlock) (BOOL value, NSError* error);
typedef void(^JLEStringCompletionBlock) (NSString* value, NSError* error);
typedef void(^JLEStickerStateCompletionBlock) (Jaalee_Sticker_State value, NSError* error);
typedef void(^JLEStickerAudioStateCompletionBlock) (Jaalee_Sticker_Audio_State value, NSError* error);

////////////////////////////////////////////////////////////////////
// Interface definition

@interface JLEStickerDefinitions : NSObject

@end
