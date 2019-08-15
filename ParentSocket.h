// Copyright 2019 Marcin Swiderski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParentSocket.generated.h"

USTRUCT()
struct FParentSocket
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere)
    FName Name;

    FParentSocket() {}

    explicit FParentSocket(FName InName)
        : Name(InName)
    {}

    FORCEINLINE bool operator==(const FParentSocket& Other) const
    {
        return Name == Other.Name;
    }

	FORCEINLINE bool operator!=(const FParentSocket& Other) const
	{
		return Name != Other.Name;
	}

	FORCEINLINE bool operator<(const FParentSocket& Other) const
	{
		return Name < Other.Name;
	}

	FORCEINLINE bool operator>(const FParentSocket& Other) const
	{
		return Name > Other.Name;
	}

};
