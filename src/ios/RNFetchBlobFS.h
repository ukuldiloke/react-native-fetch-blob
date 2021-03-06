//
//  RNFetchBlobFS.h
//  RNFetchBlob
//
//  Created by Ben Hsieh on 2016/6/6.
//  Copyright © 2016年 suzuri04x2. All rights reserved.
//

#ifndef RNFetchBlobFS_h
#define RNFetchBlobFS_h

#import <Foundation/Foundation.h>
#import "RCTBridgeModule.h"
@import AssetsLibrary;

@interface RNFetchBlobFS : NSObject <NSStreamDelegate>  {
    NSOutputStream * outStream;
    NSInputStream * inStream;
    RCTResponseSenderBlock callback;
    RCTBridge * bridge;
    Boolean isOpen;
    NSString * encoding;
    int bufferSize;
    BOOL appendData;
    NSString * taskId;
    NSString * path;
    NSString * streamId;
}

@property (nonatomic) NSOutputStream * outStream;
@property (nonatomic) NSInputStream * inStream;
@property (strong, nonatomic) RCTResponseSenderBlock callback;
@property (nonatomic) RCTBridge * bridge;
@property (nonatomic) NSString * encoding;
@property (nonatomic) NSString * taskId;
@property (nonatomic) NSString * path;
@property (nonatomic) int bufferSize;
@property (nonatomic) NSString * streamId;
@property (nonatomic) BOOL appendData;

// get dirs
+ (NSString *) getTempPath;
+ (NSString *) getCacheDir;
+ (NSString *) getDocumentDir;
+ (NSString *) getTempPath:(NSString*)taskId withExtension:(NSString *)ext;
+ (NSString *) getPathOfAsset:(NSString *)assetURI;
+ (void) getPathFromUri:(NSString *)uri completionHandler:(void(^)(NSString * path, ALAssetRepresentation *asset)) onComplete;

// fs methods
+ (RNFetchBlobFS *) getFileStreams;
+ (BOOL) mkdir:(NSString *) path;
+ (NSDictionary *) stat:(NSString *) path error:(NSError **) error;
+ (BOOL) exists:(NSString *) path;
+ (void) writeFileArray:(NSString *)path data:(NSArray *)data append:(BOOL)append resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject;
+ (void) writeFile:(NSString *)path encoding:(NSString *)encoding data:(NSString *)data append:(BOOL)append resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject;
+ (void) readFile:(NSString *)path encoding:(NSString *)encoding resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject onComplete:(void (^)(NSData * content))onComplete;
+ (void) readAssetFile:(NSData *)assetUrl completionBlock:(void(^)(NSData * content))completionBlock failBlock:(void(^)(NSError * err))failBlock;
+ (void)slice:(NSString *)path
         dest:(NSString *)dest
        start:(nonnull NSNumber *)start
          end:(nonnull NSNumber *)end
        encode:(NSString *)encode
     resolver:(RCTPromiseResolveBlock)resolve
     rejecter:(RCTPromiseRejectBlock)reject;
//+ (void) writeFileFromFile:(NSString *)src toFile:(NSString *)dest append:(BOOL)append;

// constructor
- (id) init;
- (id)initWithCallback:(RCTResponseSenderBlock)callback;
- (id)initWithBridgeRef:(RCTBridge *)bridgeRef;

// file stream
- (void) openWithDestination;
- (NSString *)openWithPath:(NSString *)destPath encode:(nullable NSString *)encode appendData:(BOOL)append;
- (void) startAssetReadStream:(NSData *)assetUrl;

// file stream write data
- (void)write:(NSData *) chunk;
- (void)writeEncodeChunk:(NSString *) chunk;
- (void)readWithPath:(NSString *)path useEncoding:(NSString *)encoding bufferSize:(int) bufferSize;

- (void) closeInStream;
- (void) closeOutStream;

@end

#endif /* RNFetchBlobFS_h */
