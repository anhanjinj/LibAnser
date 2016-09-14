// Fill out your copyright notice in the Description page of Project Settings.
/************************************************************************/
/*
	��ʹ�÷���
	1.��������ص���ģ����Ҫ�����Ľڵ��£������ֱ��ϵ��������£�
	2.������ͼ�ӿ�GrabComponent��targetComponent��������һ����ץȡ�����staticmesh��ʵ��ץȡ
	3.������ͼ�ӿ�ReleaseComponent�������ͷű�ץȡ����

	ע�⣺
	1.��ץȡ������������1��meshCompoenent
	2.�������ץȡ��Ϊ�գ�������������meshComponent������OverlapActor
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
	

	//ץȡActor����
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	AActor * GrabActor( AActor* ActorToGrab = nullptr, TSubclassOf<AActor> ClassFilter = nullptr);

	//�ͷ�����
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	void ReleaseGrab();

	//���ץȡ����
	UFUNCTION(BlueprintCallable, Category = "MyPhysicsHandle")
	AActor * GetGrabObject() const { return  m_GrabObject; }

private:
	//������ץȡ���������Ч��
	void SetGrabedActorEnablePhysics(UPrimitiveComponent & upSubCom);

	void RecoverTargetPhysicsBackup();

private:

	UPhysicsHandleComponent * m_physicsHandle;

	UMeshComponent * m_Parent;	

	FTransform m_ComposeTrans;

	AActor * m_GrabObject;

	//��ץȡ��������״̬����;
	bool m_GrabedTargetPhysicsEnableBak;
};
