//
//  ZNPeer.h
//  ZincWallet
//
//  Created by Aaron Voisine on 10/9/13.
//  Copyright (c) 2013 Aaron Voisine <voisine@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import <Foundation/Foundation.h>
#import "NSString+Base58.h" //BITCOIN_TESTNET is defined here

#if BITCOIN_TESTNET
#define STANDARD_PORT     18333
#else // BITCOIN_TESTNET
#define STANDARD_PORT     8333
#endif // BITCOIN_TESTNET

#define NODE_NETWORK      1

@class ZNPeer;

@protocol ZNPeerDelegate<NSObject>
@optional

- (void)peerConnected:(ZNPeer *)peer;
- (void)peerDisconnected:(ZNPeer *)peer withError:(NSError *)error;

@end

typedef enum {
    disconnected = 0,
    connecting,
    connected
} peerStatus;

@interface ZNPeer : NSObject<NSStreamDelegate>

@property (nonatomic, assign) id<ZNPeerDelegate> delegate;
@property (nonatomic, readonly) peerStatus status;
@property (nonatomic, readonly) NSString *host;
@property (nonatomic, readonly) uint32_t address;
@property (nonatomic, readonly) uint16_t port;
@property (nonatomic, readonly) uint64_t services;
@property (nonatomic, readonly) uint32_t version;
@property (nonatomic, readonly) uint64_t timestamp;
@property (nonatomic, readonly) NSString *useragent;
@property (nonatomic, readonly) uint32_t lastblock;

+ (instancetype)peerWithAddress:(uint32_t)address andPort:(uint16_t)port;

- (instancetype)initWithAddress:(uint32_t)address andPort:(uint16_t)port;
- (void)connect;
- (void)sendMessage:(NSData *)message type:(NSString *)type;
- (void)sendVersionMessage;

@end
