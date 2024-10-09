#pragma once

#include "CoreMinimal.h"
#include "ChannelDataView.h"
#include "SingleChannelDataView.generated.h"

class UChanneldConnection;

/**
 * 
 */
UCLASS()
class CHANNELDUE_API USingleChannelDataView : public UChannelDataView
{
	GENERATED_BODY()
	
public:
	USingleChannelDataView(const FObjectInitializer& ObjectInitializer);

	virtual Channeld::ChannelId GetOwningChannelId(const FNetworkGUID NetId) const override;

	UPROPERTY(EditAnywhere)
	FString Metadata;
	
	UPROPERTY(EditAnywhere)
	int GlobalChannelFanOutIntervalMs = 20;
	
	UPROPERTY(EditAnywhere)
	int GlobalChannelFanOutDelayMs = 2000;

protected:

	virtual void InitServer(bool bShouldRecover) override;
	virtual void InitClient() override;

	virtual Channeld::ChannelId GetDefaultChannelId() const override;
	virtual bool GetSendToChannelId(UChanneldNetConnection* NetConn, uint32& OutChId) const override;

	// Default implementation: Destroy the Pawn related to the NetConn and close the NetConn. 
	virtual void ServerHandleClientUnsub(Channeld::ConnectionId ClientConnId, channeldpb::ChannelType ChannelType, Channeld::ChannelId ChId) override;
};
