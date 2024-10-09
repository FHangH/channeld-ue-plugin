#pragma once

#include "CoreMinimal.h"
#include "ChanneldTypes.h"
#include "Tools/TintActor.h"
#include "Tools/OutlinerActor.h"
#include "View/PlayerStartLocator.h"
#include "View/SingleChannelDataView.h"
#include "ChanneldSettings.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FLaunchServerDelegate, const FServerLaunchGroup&);


USTRUCT(BlueprintType, Blueprintable)
struct FServerLaunchGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "16"))
	int32 ServerNum = 1;

	// How long to wait before launching the servers (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime = 0.f;

	// If not set, the open map in the Editor will be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="World"))
	FSoftObjectPath ServerMap;

	// If not set, the ChannelDataViewClass in the UChanneldSettings will be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UChannelDataView> ServerViewClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText AdditionalArgs;
};

/**
 * 
 */
UCLASS(BlueprintType, config = ChanneldUE)
class CHANNELDUE_API UChanneldSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UChanneldSettings(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitProperties() override;
	bool IsNetworkingEnabled() const;
	void ToggleNetworkingEnabled();
	void UpdateNetDriverDefinitions();

	UPROPERTY(Config, EditAnywhere, Category="View")
	TSubclassOf<class UChannelDataView> ChannelDataViewClass = USingleChannelDataView::StaticClass();
	// The default channel data message name for each channel type. The entries will be registered in UChannelDataView::Initialize.
	// Every time the replication code is generated, the entries will be updated with the message names in the generated code.
	UPROPERTY(Config, BlueprintReadOnly, Category="View")
	TMap<EChanneldChannelType, FString> DefaultChannelDataMsgNames =
	{
		{EChanneldChannelType::ECT_Global, TEXT("tpspb.TestRepChannelData")},
		{EChanneldChannelType::ECT_SubWorld, TEXT("tpspb.TestRepChannelData")},
		{EChanneldChannelType::ECT_Spatial, TEXT("unrealpb.SpatialChannelData")},
	};

	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	bool bEnableNetworking = false;
	
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	FString ChanneldIpForClient = "127.0.0.1";
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	int32 ChanneldPortForClient = 12108;
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	FString ChanneldIpForServer = "127.0.0.1";
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	int32 ChanneldPortForServer = 11288;
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	bool bUseReceiveThread = true;

	// If true, UE's default handshaking process will be skipped and the server will expect NMT_Hello as the first message.
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	bool bDisableHandshaking = true;
	// If true, UNetConnection::SetInternalAck() will be called to internally ack all packets. Should be turned on for reliable connection (TCP) to save bandwidth.
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	bool bSetInternalAck = true;
	// How many times an RPC will be redirected from a server that couldn't handle it to another server. 0 = No redirection. Setting this to a too high value can cause the RPC bouncing between servers and saturate the network.
	UPROPERTY(Config, EditAnywhere, Category = "Transport")
	int32 RpcRedirectionMaxRetries = 1;

	// Should the server and client skip the custom replication system and use UE's default one. All traffic still goes through channeld either way.
	UPROPERTY(Config, EditAnywhere, Category = "Replication")
	bool bSkipCustomReplication = false;

	UPROPERTY(Config, EditAnywhere, Category = "Spatial")
	TSubclassOf<UPlayerStartLocatorBase> PlayerStartLocatorClass = UPlayerStartLocator_ModByConnId::StaticClass();

	// If true, Actor::IsNetRelevantFor() will be called to determine whether an actor should be destroyed on the client when leaving player's the interest area.
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Client Interest")
	bool bUseNetRelevancyForUninterestedActors = false;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Client Interest")
	TArray<FClientInterestSettingsPreset> ClientInterestPresets;
	
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug")
	bool bEnableSpatialVisualizer = false;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	TSubclassOf<ATintActor> RegionBoxClass;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	FVector RegionBoxMinSize;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	FVector RegionBoxMaxSize;
	// If set to true, the region boxes will be spawned on the floor. The actual Z value will be set to the floor height.
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	bool bRegionBoxOnFloor = true;
	// FVector RegionBoxOffset;
	
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	TSubclassOf<ATintActor> SubscriptionBoxClass;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	FVector SubscriptionBoxMinSize;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	FVector SubscriptionBoxMaxSize;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	FVector SubscriptionBoxOffset;
	UPROPERTY(Config, EditAnywhere, Category = "Spatial|Debug", meta=(EditCondition="bEnableSpatialVisualizer"))
	TSubclassOf<AOutlinerActor> SpatialOutlinerClass;

	// If set to true, the RPC with the actor that hasn't been exported to the client will be postponed until being exported.
	UPROPERTY(Config, EditAnywhere, Category = "Server")
	bool bQueueUnexportedActorRPC = false;
	// Delay the calling of UChannelDataView::Initialize() for attaching the debugger or other purpose.
	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	float DelayViewInitInSeconds = 0;
	// If set to true, the simulated proxy actors and their components will not tick.
	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	bool bDisableSimulatedProxyTick = false;
	// If set the true, the static GUID registry will not load, which may cause the replication issues of the assets and the static objects.
	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	bool bDisableStaticGuidRegistry = false;
	
	FLaunchServerDelegate OnLaunchServer;

private:
	void AddChanneldNetDriverDefinition();
	void AddFallbackNetDriverDefinition();
	bool ParseNetAddr(const FString& Addr, FString& OutIp, int32& OutPort);
};
