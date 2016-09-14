// Fill out your copyright notice in the Description page of Project Settings.
#include "AliceAllCPlus.h"
#include "CPhysicsHandl.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCPhysicsHandle::UCPhysicsHandle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	m_GrabedTargetPhysicsEnableBak = false;
	m_physicsHandle = nullptr;
	m_GrabObject = nullptr;
	m_physicsHandle = nullptr;
	// ...
}


UCPhysicsHandle::~UCPhysicsHandle()
{

}

// Called when the game starts
void UCPhysicsHandle::BeginPlay()
{
	Super::BeginPlay();
	

	//获得该组件挂载的对象
	TArray<USceneComponent*>  ArrParents;
	m_Parent = dynamic_cast<UMeshComponent*>(this->GetAttachParent());

	m_physicsHandle = NewObject<UPhysicsHandleComponent>(this);
	m_physicsHandle->RegisterComponent();

}


void UCPhysicsHandle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(m_physicsHandle))
	{
		m_physicsHandle->UnregisterComponent();
	}
}

// Called every frame
void UCPhysicsHandle::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{

	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!IsValid(m_Parent) || !IsValid(m_physicsHandle) )
	{

		return;

	}

	FTransform ftParentTrans = m_Parent->GetComponentToWorld();

	FTransform ftTickTrans = UKismetMathLibrary::ComposeTransforms(m_ComposeTrans, ftParentTrans);

	m_physicsHandle->SetTargetLocationAndRotation(m_Parent->GetComponentToWorld().GetLocation(), ftTickTrans.GetRotation().Rotator());

}

AActor * UCPhysicsHandle::GrabActor(AActor* pActorToGrab, TSubclassOf<AActor> ClassFilter)
{
	if (!IsValid(m_physicsHandle))
	{
		GLog->Log("UCPhysicsHandl - GrabCompoinent : m_physicsHandle is invalid!!!");

		return nullptr;
	}


	if (!IsValid(m_Parent))
	{
		GLog->Log("UCPhysicsHandle - GrabComponnet : m_parent is invalid.");
	}

	if (!pActorToGrab)
	{
		TArray<AActor*> overlapActors;

		m_Parent->GetOverlappingActors(overlapActors, ClassFilter);
		

		if (overlapActors.Num() == 0)
		{

			return nullptr;

		}

		AActor * firstOverlap = overlapActors[0];
		
		if (!IsValid(firstOverlap))
		{

			return nullptr;

		}


		m_GrabObject = firstOverlap;

	}else
	{

		m_GrabObject = pActorToGrab;

	}
	
	TArray<UObject*> subObjects;
	m_GrabObject->GetDefaultSubobjects(subObjects);

	if (subObjects.Num() == 0)
	{
		
		return nullptr;

	}

	//获得首个UPrimitiveComponent作为抓取对象
	UPrimitiveComponent * firstPrivate(nullptr);
	for (auto idx = 0; idx < subObjects.Num(); ++idx)
	{

		firstPrivate = dynamic_cast<UPrimitiveComponent*>(subObjects[idx]);

		if (IsValid(firstPrivate))
		{
			break;			
		}
	}

	if (!IsValid(firstPrivate))
	{

		return nullptr;

	}

	//启用物理
	SetGrabedActorEnablePhysics(*firstPrivate);


	//组合变换
	FTransform targetTrans = firstPrivate->GetComponentToWorld();

	FTransform parentTransInv = m_Parent->GetComponentToWorld();
	parentTransInv = UKismetMathLibrary::InvertTransform(parentTransInv);
	m_ComposeTrans = UKismetMathLibrary::ComposeTransforms(targetTrans, parentTransInv);

	FVector fvParentHandLoc = m_Parent->GetComponentToWorld().GetLocation();
	m_physicsHandle->GrabComponent(firstPrivate, FName("None"), fvParentHandLoc, true);


	return m_GrabObject;

}

void UCPhysicsHandle::ReleaseGrab()
{
	
	if (!IsValid(m_GrabObject))
	{

		return;

	}


	if (IsValid(m_physicsHandle))
	{

		m_physicsHandle->ReleaseComponent();

	}

	//恢复被抓取物体的物理状态备份
	RecoverTargetPhysicsBackup();

	m_GrabObject = nullptr;

}

void UCPhysicsHandle::SetGrabedActorEnablePhysics(UPrimitiveComponent & upSubCom)
{
	m_GrabedTargetPhysicsEnableBak = upSubCom.IsSimulatingPhysics();

	if (!m_GrabedTargetPhysicsEnableBak)
	{

		upSubCom.SetSimulatePhysics(true);

	}

}

void UCPhysicsHandle::RecoverTargetPhysicsBackup()
{

	if (!IsValid(m_GrabObject))
	{

		return;

	}


	TArray<UObject*> subObjects;
	m_GrabObject->GetDefaultSubobjects(subObjects);

	if (subObjects.Num() == 0)
	{

		return;

	}

	//获得首个UPrimitiveComponent作为抓取对象
	UPrimitiveComponent * firstPrivate(nullptr);
	for (auto idx = 0; idx < subObjects.Num(); ++idx)
	{

		firstPrivate = dynamic_cast<UPrimitiveComponent*>(subObjects[idx]);

		if (IsValid(firstPrivate))
		{
			break;
		}
	}

	if (!IsValid(firstPrivate))
	{

		return;

	}

	firstPrivate->SetSimulatePhysics(m_GrabedTargetPhysicsEnableBak);

}

