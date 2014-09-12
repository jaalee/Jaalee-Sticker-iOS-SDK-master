//
//  JLEsticker.h
//  JaaleestickerSDK
//
//  Created by jaalee on 14-4-22.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "JLEStickerDefinitions.h"



@class JLEStickerDevice;

////////////////////////////////////////////////////////////////////
// JAALEE sticker delegate protocol


/**
 
 JLEStickerDeviceDelegate defines sticker connection delegate mathods. Connection is asynchronous operation so you need to be prepared that eg. stickerDidDisconnectWith: method can be invoked without previous action.
 
 */

@protocol JLEStickerDeviceDelegate <NSObject>

@optional

/**
 * Delegate method that indicates error in sticker connection.
 *
 * @param sticker reference to sticker object
 * @param error information about reason of error
 *
 * @return void
 */
- (void)stickerConnectionDidFail:(JLEStickerDevice*)sticker withError:(NSError*)error;

/**
 * Delegate method that indicates success in sticker connection.
 *
 * @param sticker reference to sticker object
 *
 * @return void
 */
- (void)stickerConnectionDidSucceeded:(JLEStickerDevice*)sticker;

/**
 * Delegate method that sticker did disconnect with device.
 *
 * @param sticker reference to sticker object
 * @param error information about reason of error
 *
 * @return void
 */
- (void)stickerDidDisconnect:(JLEStickerDevice*)sticker withError:(NSError*)error;


/**
 * Delegate method that sticker did update rssi with device.
 *
 * @param sticker reference to sticker object
 * @param error information about reason of error
 *
 * @return void
 */
- (void)stickerDidUpdateRssi:(JLEStickerDevice*)sticker Error:(NSError*)error;

@end

////////////////////////////////////////////////////////////////////
// Interface definition

/**
 
 You do not create instances of this class directly. The JLEstickerManager object reports encountered stickers to its associated delegate object. You can use the information in a sticker object to identify which sticker device was encountered.
 
 It allows to connect with Jaalee sticker to read / write its characteristics.
 
 */

@interface JLEStickerDevice : NSObject

- (id) initWithID:(NSString*)ID;

@property (nonatomic, weak)     id <JLEStickerDeviceDelegate>  delegate;

@property (nonatomic, strong)        CBCentralManager *manager;
/// @name Publicly available properties
/**
 *  name
 *
 *  Discussion:
 *    name of the sticker device.
 */
@property (nonatomic, strong)   NSString*               name;

/**
 *  rssi
 *
 *    Received signal strength in decibels of the specified sticker device.
 *    This value is an average of the RSSI samples collected since this sticker was last reported.
 *
 */
@property (nonatomic)           NSInteger               rssi;

/**
 *  isConnectable
 *
 *    Whether the sticker can be connected
 *
 */
@property (nonatomic)           BOOL               isConnectable;

/**
 *  isConnected
 *
 *    Flag indicating connection status.
 */
@property (nonatomic, readonly)   BOOL                  isConnected;


/**
 *  StickerID
 *
 *    The ID of jaalee sticker.
 */
@property (nonatomic, strong)   NSString*           StickerID;


/**
 *  peripheral
 *
 *    Reference of the sticker device peripheral object.
 */
@property (nonatomic, strong)   CBPeripheral*           peripheral;




/////////////////////////////////////////////////////
// @name Properties available after connection

/**
 *  isJaaleesticker
 *
 *    Wether the sticker is belong to Jaalee.
 */
@property (nonatomic, readonly)   BOOL                  isJaaleeSticker;

/**
 *  batteryLevel
 *
 *    Battery strength in %. Battery level change from 100% - 0%. Value available after connection with the sticker
 */
@property (nonatomic, strong, readonly)   NSNumber*               batteryLevel;

/**
 *  batteryLevel
 *
 *    Battery strength in %. Battery level change from 100% - 0%. Value available after connection with the sticker
 */
@property (nonatomic, strong, readonly)   NSString*               firmwareVersion;

/**
 *  macAddress
 *
 *  Discussion:
 *    Hardware MAC address of the sticker device.
 */
@property (nonatomic, strong, readonly)   NSString*               macAddress;

/**
 *  stickerState
 *
 *    The sticker state. Value available after connection with the sticker
 */
@property (nonatomic, readonly)   Jaalee_Sticker_State               stickerState;

/**
 *  txPower
 *
 *    Power of signal in dBm. Value available after connection with the sticker. It takes one of the values represented by JLEstickerPower .
 */
@property (nonatomic, readonly)   JLEStickerTxPower               txPower;

/**
 *  advInterval
 *
 *    Advertising interval of the sticker. Value change from 100ms to 10000ms. Value available after connection with the sticker
 */
@property (nonatomic, strong, readonly)   NSNumber*               advInterval;

/**
 *  audioState
 *
 *    the audio state of the sticker. Value available after connection with the sticker
 */
@property (nonatomic, readonly)   Jaalee_Sticker_Audio_State      audioState;

/// @name Connection handling methods


/**
 * Connect to particular sticker using bluetooth.
 * Connection is required to change values like
 * Device name, txPower and Advertising interval.
 *
 * @return void
 */
-(void)connectToSticker;

/**
 * Disconnect device with particular sticker
 *
 * @return void
 */
-(void)disconnectSticker;


/// @name Methods for reading sticker configuration
/**
 * Read advertising interval of connected sticker (Previous connection
 * required)
 *
 * @param completion block with advertising interval value as param
 *
 * @return void
 */
- (void)readStickerAdvIntervalWithCompletion:(JLEUnsignedShortCompletionBlock)completion;


/**
 * Read battery level of connected sticker (Previous connection
 * required)
 *
 * @param completion block with battery level value as param
 *
 * @return void
 */
- (void)readStickerBatteryWithCompletion:(JLEUnsignedShortCompletionBlock)completion;


/**
 * Read device name of connected sticker (Previous connection
 * required)
 *
 * @param completion block with device name as param
 *
 * @return void
 */
- (void)readStickerDeviceNameWithCompletion:(JLEStringCompletionBlock)completion;

/**
 * Read device state of connected sticker (Previous connection
 * required)
 *
 * @param completion block with device state as param
 *
 * @return void
 */
- (void)readStickerStateWithCompletion:(JLEStickerStateCompletionBlock)completion;

/**
 * Read device audio state of connected sticker (Previous connection
 * required)
 *
 * @param completion block with device state as param
 *
 * @return void
 */
- (void)readAudioStateWithCompletion:(JLEStickerAudioStateCompletionBlock)completion;

/// @name Methods for writing sticker configuration

/**
 * Writes advertising interval (in milisec) of connected sticker.
 *
 * @param advertising interval of sticker (100 - 10000 ms)
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeStickerAdvInterval:(unsigned short)interval withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Writes txPower of bluetooth connected sticker.
 *
 * @param txPower advertising sticker power (can take value from JLEstickerPowerLevel1 / waak to JLEstickerPowerLevel11 / strong)
 
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeStickerTxPower:(JLEStickerTxPower)txPower withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Writes device name of bluetooth connected sticker.
 *
 * @param name sticker device name (lenth <= 15byte)
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeStickerDeviceName:(NSString*)name withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Writes device state of bluetooth connected sticker.
 *
 * @param state sticker device state
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void) writeStickerState:(Jaalee_Sticker_State)state withCompletion:(JLEBoolCompletionBlock)completion;

/**
 * Writes device audio state of bluetooth connected sticker.
 *
 * @param state audio state
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void) writeAudioState:(Jaalee_Sticker_Audio_State)state withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Call the sticker of bluetooth connected sticker.
 *
 * @return BOOL
 */
- (BOOL) callJaaleeSticker;

/**
 * Enable jaalee sticker ring when disconnect.
 *
 * @return void
 */
- (BOOL) enableJaaleeStickerRingWhenDisconnect;

/**
 * Disable jaalee sticker ring when disconnect.
 *
 * @return BOOL
 */
- (BOOL) disableJaaleeStickerRingWhenDisconnect;


/**
 * Delay the alarm time when disconnect,
 *
 * @param second delay time (1s-120s)
 *
 * @return BOOL
 */
- (BOOL) delayAlarmWhenDisconnect:(int)second;

/**
 * read jaalee sticker rssi value.
 *
 * @return void
 */
- (void) readStickerRSSIValue;
@end





