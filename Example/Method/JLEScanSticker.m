//
//  JLEScanSticker.m
//  Example
//
//  Created by jaalee on 14-4-23.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
//

#import "JLEScanSticker.h"
#import "JLEStickerDevice.h"
#import "JLEContralStickerDemo.h"

@interface JLEScanSticker ()

@property (nonatomic)        NSMutableArray *mStickerDeviceList;
@property (nonatomic)        JLEStickerManager *mStickerManager;
@property (nonatomic)        JLEStickerDevice *mStickerDevice;

@end

@implementation JLEScanSticker

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    _mStickerDeviceList = [[NSMutableArray alloc] init];
    _mStickerManager = [[JLEStickerManager alloc] init];
    _mStickerManager.delegate = self;
}


-(void)viewDidAppear:(BOOL)animated
{
    [_mStickerDeviceList removeAllObjects];
    [self.mTableView reloadData];
    [_mStickerManager startJaaleeStickersDiscovery];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark - JLEStickerConfigManager delegate

-(void)stickerManager:(JLEStickerManager *)manager didDiscoverSticker:(JLEStickerDevice *)sticker RSSI:(NSNumber *)RSSI
{
    
    for (int i = 0; i < _mStickerDeviceList.count; i++) {
        JLEStickerDevice *temp = [_mStickerDeviceList objectAtIndex:i];
        if (temp == sticker) {
            [self.mTableView reloadData];
            return;
        }
    }
    
    [_mStickerDeviceList addObject:sticker];
    [self.mTableView reloadData];
}



#pragma mark - Table view data source

-(NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section
{
	return _mStickerDeviceList.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;
{
	return 1;
}


- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"Scanning...";
}


- (UITableViewCell *)tableView:(UITableView *)tv cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell;
    
    cell = [tv dequeueReusableCellWithIdentifier:@"StickerDeviceCell"];

    UILabel *name = (UILabel*)[cell viewWithTag:1];
    UILabel *StickerID = (UILabel*)[cell viewWithTag:2];
    UILabel *rssi = (UILabel*)[cell viewWithTag:3];
    
    JLEStickerDevice *temp = [_mStickerDeviceList objectAtIndex:indexPath.row];
    
    name.text = temp.name;
    StickerID.text = temp.StickerID;
    rssi.text = [NSString stringWithFormat:@"%ld", (long)temp.rssi];
    
    
    return cell;
    
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView  deselectRowAtIndexPath:indexPath animated:YES];
    _mStickerDevice = [_mStickerDeviceList objectAtIndex:indexPath.row];
    
    [self performSegueWithIdentifier:@"ConfigDetail" sender:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ConfigDetail"])
    {
        JLEContralStickerDemo *Contral = (JLEContralStickerDemo*) segue.destinationViewController;
        Contral.mSelectStickerDevice = _mStickerDevice;
    }
}



@end
