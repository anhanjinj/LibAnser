// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathUtile.generated.h"


/*
Math Quadrant
				UpY
		4th		|     1st
				|
   LeftX------origin--------- RightX
				|
		3rd		|    2nd
				DownY
*/
class enum EQuadrant : uint8
{
	Origin = 0,
	UpYAxis,
	First,
	RightXAxis,
	Secend,
	DownYAxis,
	Third,
	LeftXAxis,
	Fourth
};


/**
 * 
 */
UCLASS(Blueprintable)
class UMathUtile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	/*
		GET rotator  by current rotator , current forward rotator , target  forward
	*/
	UFUNCTION(Category = "Utile|Math", BlueprintPure)
		static FRotator GetRotatorToTargetNormal(FRotator rCurrent, FVector vForward, FVector to);


	/**
		Get xy angle between 2 normals


		a . b
		------  == cos <a,b>
		|a|.|b|
		
	**/
	UFUNCTION(Category = "Utile|Math", BlueprintPure)
		static float GetNormalsXYAngle(const FVector& A, const  FVector& B);


	/**
	Get 3d angle between 2 normals


	a . b
	------  == cos <a,b>
	|a|.|b|

	**/
	UFUNCTION(Category = "Utile|Math", BlueprintPure)
	FORCEINLINE	static float GetNormals3DAngle(const FVector& A, const  FVector& B) 
	{
		return FMath::Acos((FVector::DotProduct(A, B) / (A.Size() * B.Size())));
	};



	/**
	
	  Get Targetpoint in which quadrant of origin

				|     * (1st)
				|  
	  -------origin--------- 
				|     
				|   
	*/


	UFUNCTION(Category = "Utile|Math", BlueprintPure)
		static EQuadrant GetXYQuadrant(const FVector& Origin, const FVector& TargetPoint);


	/**
		Rotate SrcPT  Around RoundPT by RotateAngle				
	*/


	UFUNCTION(Category = "Utile|Math", BlueprintPure)
		static FVector GetXYRotatedPointAroundPoint(const FVector& SrcPoint, const FVector& RoundPoint, const float& RotateAngle);


	/**
		
		true: Right
		false: Left
	*/
// 	UFUNCTION(Category = "Utile|Math", BlueprintPure)
// 		static bool GetVectorALeftOrRightVectorB(const FVector& A, const FVector& B);
};
