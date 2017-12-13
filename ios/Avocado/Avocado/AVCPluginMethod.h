#import "AVCPluginCall.h"
#import "AVCPlugin.h"

typedef enum {
  AVCPluginMethodArgumentNotNullable,
  AVCPluginMethodArgumentNullable
} AVCPluginMethodArgumentNullability;

typedef NSString AVCPluginReturnType;
typedef void (^AVCSuccessCallback)(id result);
typedef void (^AVCErrorCallback)(NSError *error);

/**
 * Represents a single argument to a plugin method.
 */
@interface AVCPluginMethodArgument : NSObject

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, assign) AVCPluginMethodArgumentNullability nullability;

- (instancetype)initWithName:(NSString *)name nullability:(AVCPluginMethodArgumentNullability)nullability type:(NSString *)type;

@end

/**
 * Represents a method that a plugin supports, with the ability
 * to compute selectors and invoke the method.
 */
@interface AVCPluginMethod : NSObject

// Raw method name
@property (nonatomic, strong) NSString *name;
// Raw method type string
@property (nonatomic, strong) NSString *types;
// Computed method argument object
@property (nonatomic, strong) NSArray<AVCPluginMethodArgument *> *params;
// Return type of method (i.e. callback/promise/sync)
@property (nonatomic, strong) AVCPluginReturnType *returnType;
// Stored selector for the method
@property (nonatomic, assign) SEL selector;

- (instancetype)initWithNameAndTypes:(NSString *)name types:(NSString *)types returnType:(AVCPluginReturnType *)returnType;

- (SEL)getSelector;
- (void)invoke:(AVCPluginCall *)pluginCall onPlugin:(AVCPlugin *)plugin;

@end