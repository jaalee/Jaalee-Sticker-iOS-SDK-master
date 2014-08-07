//
//  JLEScanSticker.h
//  Example
//
//  Created by jaalee on 14-4-23.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
//


#import "JLEStickerManager.h"

@interface JLEScanSticker : UIViewController<UIScrollViewDelegate, UITableViewDataSource, UITableViewDelegate, JLEStickerManagerDelegate>

@property (weak, nonatomic) IBOutlet UITableView *mTableView;
@end
