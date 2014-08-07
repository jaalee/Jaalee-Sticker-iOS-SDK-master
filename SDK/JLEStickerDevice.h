//
//  JLEStickerDevice.h
//  JaaleeStickerSDK
//
//  Created by jaalee on 14-4-22.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
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
 
 You do not create instances of this class directly. The JLEStickerManager object reports encountered stickers to its associated delegate object. You can use the information in a sticker object to identify which sticker device was encountered.
 
 It allows to connect with Jaalee sticker to read / write its characteristics.
 
 */

@interface JLEStickerDevice : NSObject


@property (nonatomic, weak)     id <JLEStickerDeviceDelegate>  delegate;

@property (nonatomic, strong)        CBCentralManager *manager;
/// @name Publicly available properties

/**
 *  macAddress
 *
 *  Discussion:
 *    Hardware MAC address of the sticker device.
 */

@property (nonatomic, strong)   NSString*               macAddress;

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
 *  peripheral
 *
 *    Reference of the sticker device peripheral object.
 */
@property (nonatomic, strong)   CBPeripheral*           peripheral;

/////////////////////////////////////////////////////
// properties filled when read characteristic

/// @name Properties available after connection


/**
 *  isConnected
 *
 *    Flag indicating connection status.
 */
@property (nonatomic, readonly)   BOOL                  isConnected;

/**
 *  isJaaleesticker
 *
 *    Wether the sticker is belong to Jaalee.
 */
@property (nonatomic, readonly)   BOOL                  isJaaleeSticker;

/**
 *  txPower
 *
 *    Power of signal in dBm. Value available after connection with the sticker. It takes one of the values represented by JLEStickerPower .
 */
@property (nonatomic, strong)   NSNumber*               txPower;

/**
 *  batteryLevel
 *
 *    Battery strength in %. Battery level change from 100% - 0%. Value available after connection with the sticker
 */
@property (nonatomic, strong)   NSNumber*               batteryLevel;



/// @name Connection handling methods


/**
 * Connect to particular sticker using bluetooth.
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


/**
 * Read Tx power of connected sticker (Previous connection
 * required)
 *
 * @param completion block with power value as param
 *
 * @return void
 */
- (void)readStickerTxPowerWithCompletion:(JLEPowerCompletionBlock)completion;

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
 * Change txPower of bluetooth connected sticker.
 *
 * @param txPower advertising sticker power (can take value from JLEStickerPowerLevel1 / waak to JLEStickerPowerLevel3 / strong)
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)ChangeStickerTxPower:(JLEStickerPower)txPower withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Change device name of bluetooth connected sticker.
 *
 * @param name sticker device name (lenth <= 15byte)
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)ChangeStickerDeviceName:(NSString*)name withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Change sticker data deliver interval of bluetooth connected sticker.
 *
 * @param interval Connection interval (can take value from JLConnectParameter_100 to JLConnectParameter_2000)
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)ChangeStickerDataDeliverInterval:(JaaLeeConnectParameter)interval withCompletion:(JLEBoolCompletionBlock)completion;


/**
 * Call the sticker of bluetooth connected sticker.
 *
 * @return void
 */
- (void) callJaaleeSticker;

/**
 * Enable jaalee sticker ring when disconnect.
 *
 * @return void
 */
- (void) enableJaaleeStickerRingWhenDisconnect;

/**
 * Disable jaalee sticker ring when disconnect.
 *
 * @return void
 */
- (void) disableJaaleeStickerRingWhenDisconnect;


/**
 * read jaalee sticker rssi value.
 *
 * @return void
 */
- (void) readStickerRSSIValue;

@end
