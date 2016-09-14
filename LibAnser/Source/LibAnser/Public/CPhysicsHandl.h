// Fill out your copyright notice in the Description page of Project Settings.
/************************************************************************/
/*
	·使用方法
	1.将组件挂载到手模型需要碰触的节点下（比如手柄上的碰触球下）
	2.调用蓝图接口GrabComponent（targetComponent），传入一个被抓取物体的staticmesh，实现抓取
	3.调用蓝图接口ReleaseComponent（），释放被抓取物体

	注意：
	1.被抓取物体需至少有1个meshCompoenent
	2.若传入的抓取物为空，则组件需挂载在meshComponent用以求OverlapActor
*/
/************************************************************************/
#pragma once

#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CPhysicsHandl.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALICEALLCPLUS_API UCPhysicsHandle : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPhysicsHandle();

	~UCPhysicsHandle();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


public:
	

	//抓取Actor物体
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	AActor * GrabActor( AActor* ActorToGrab = nullptr, TSubclassOf<AActor> ClassFilter = nullptr);

	//释放物体
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	void ReleaseGrab();

	//获得抓取物体
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	AActor * GetGrabObject() const { return  m_GrabObject; }

private:
	//开启被抓取对象的物理效果
	void SetGrabedActorEnablePhysics(UPrimitiveComponent & upSubCom);

	void RecoverTargetPhysicsBackup();

private:

	UPhysicsHandleComponent * m_physicsHandle;

	UMeshComponent * m_Parent;	

	FTransform m_ComposeTrans;

	AActor * m_GrabObject;

	//被抓取物体物理状态备份;
	bool m_GrabedTargetPhysicsEnableBak;
};
