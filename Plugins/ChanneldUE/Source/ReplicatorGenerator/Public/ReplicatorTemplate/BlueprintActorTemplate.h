﻿#pragma once

static const TCHAR* CodeGen_BP_HeadCodeTemplate =
	LR"EOF(
#pragma once

#include "CoreMinimal.h"
#include "Replication/ChanneldReplicatorBase.h"
#include "Net/UnrealNetwork.h"
#include "{File_ProtoPbHead}"

class {Declare_ReplicatorClassName} : public FChanneldReplicatorBase_BP
{
public:
  {Declare_ReplicatorClassName}(UObject* InTargetObj);
  virtual ~{Declare_ReplicatorClassName}() override;

  //~Begin FChanneldReplicatorBase Interface
  virtual google::protobuf::Message* GetDeltaState() override;
  virtual void ClearState() override;
  virtual void Tick(float DeltaTime) override;
  virtual void OnStateChanged(const google::protobuf::Message* NewState) override;
  //~End FChanneldReplicatorBase Interface

protected:
  TWeakObjectPtr<AActor> {Ref_TargetInstanceRef};

  // [Server+Client] The accumulated channel data of the target object
  {Declare_ProtoNamespace}::{Declare_ProtoStateMsgName}* FullState;
  // [Server] The accumulated delta change before next send
  {Declare_ProtoNamespace}::{Declare_ProtoStateMsgName}* DeltaState;

private:
{Declare_IndirectlyAccessiblePropertyPtrs}

};
)EOF";

static const TCHAR* CodeGen_BP_ConstructorImplTemplate =
  LR"EOF(
{Declare_ReplicatorClassName}::{Declare_ReplicatorClassName}(UObject* InTargetObj)
	: FChanneldReplicatorBase_BP(InTargetObj)
{
  {Ref_TargetInstanceRef} = CastChecked<AActor>(InTargetObj);
  // Remove the registered DOREP() properties in the Actor
  TArray<FLifetimeProperty> RepProps;
  DisableAllReplicatedPropertiesOfClass(InTargetObj->GetClass(), GetTargetClass(), EFieldIteratorFlags::ExcludeSuper, RepProps);

  FullState = new {Declare_ProtoNamespace}::{Declare_ProtoStateMsgName};
  DeltaState = new {Declare_ProtoNamespace}::{Declare_ProtoStateMsgName};

{Code_AssignPropertyPointers}
}
)EOF";
