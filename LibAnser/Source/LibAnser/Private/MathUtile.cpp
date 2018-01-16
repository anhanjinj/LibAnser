// Fill out your copyright notice in the Description page of Project Settings.

#include "MathUtile.h"


FRotator UMathUtile::GetRotatorToTargetNormal(FRotator rCurrent, FVector vForward, FVector to)
{
	FQuat qTmp = FQuat::FindBetween(vForward, to);
	qTmp = qTmp * rCurrent.Quaternion();

	return qTmp.Rotator();

}

float UMathUtile::GetNormalsXYAngle(const FVector& A, const FVector& B)
{
	FVector2D A2D(A.X, A.Y);
	FVector2D B2D(B.X, B.Y);


	return FMath::Acos((FVector2D::DotProduct(A2D, B2D) / (A2D.Size() * B2D.Size())));
}


EQuadrant UMathUtile::GetXYQuadrant(const FVector& Origin, const FVector& TargetPoint)
{
	//normalize

	FVector Normalized = TargetPoint - Origin;

	if (Normalized.X == 0)
	{
		if (Normalized.Y == 0)
		{
			return EQuadrant::Origin;
		}
		else if(Normalized.Y > 0)
		{
			return EQuadrant::UpYAxis;
		}
		else
		{
			return EQuadrant::DownYAxis;
		}

	}
	else 
	{
		if (Normalized.Y == 0)
		{
			if (Normalized.X > 0)
			{
				return EQuadrant::RightXAxis;
			}
			else
			{
				return EQuadrant::LeftXAxis;
			}
		}
		else
		{
			if (Normalized.X > 0)
			{
				if (Normalized.Y > 0)
				{
					return EQuadrant::First;
				}
				else
				{
					return EQuadrant::Secend;
				}
			}
			else
			{
				if (Normalized.Y > 0)
				{
					return EQuadrant::Fourth;
				}
				else
				{
					return EQuadrant::Third;
				}
			}
		}

	}
}

FVector UMathUtile::GetXYRotatedPointAroundPoint(const FVector& SrcPoint, const FVector& RoundPoint, const float& RotateAngle)
{
	float X, Y;


	/*
		x = (src.X - RP.x)*cos(a) - (src.y - RP.y)*sin(a) + RP.x
	*/
	X = (SrcPoint.X - RoundPoint.X) * FMath::Cos(RotateAngle) - (SrcPoint.Y - RoundPoint.Y) * FMath::Sin(RotateAngle) + RoundPoint.X;

	/*
		y = (SRC.x - RP.x)* sin(a) + (Src.Y - RP.y) * cos(a) + RP.y
	*/
	Y = (SrcPoint.X - RoundPoint.X) * FMath::Sin(RotateAngle) + (SrcPoint.Y - RoundPoint.Y) * FMath::Cos(RotateAngle) + RoundPoint.Y;

	return FVector(X, Y, SrcPoint.Z);
}

// bool UMathUtile::GetVectorALeftOrRightVectorB(const FVector& A, const FVector& B)
// {
// 	EQuadrant BQuadrant = GetXYQuadrant(FVector::ZeroVector, B);
// 
// 	switch (BQuadrant)
// 	{
// 	case EQuadrant::Origin:
// 	{
// 		return true;
// 	}
// 	case eq
// 
// 	default:
		break;
// 	}
// }
