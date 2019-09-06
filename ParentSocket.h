// Copyright 2019 Marcin Swiderski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/EngineVersionComparison.h"
#include "ParentSocket.generated.h"

USTRUCT()
struct FParentSocket
{
    GENERATED_BODY()
    
    UPROPERTY(Category = "Socket", EditAnywhere)
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

#if UE_VERSION_OLDER_THAN(4, 23, 0)
	FORCEINLINE bool operator<(const FParentSocket& Other) const
	{
		return Name < Other.Name;
	}

	FORCEINLINE bool operator>(const FParentSocket& Other) const
	{
		return Name > Other.Name;
	}
#else
    FORCEINLINE bool FastLess(const FParentSocket& Other) const
    {
        return Name.FastLess(Other.Name);
    }

    FORCEINLINE bool LexicalLess(const FParentSocket& Other) const
    {
        return Name.FastLess(Other.Name);
    }
#endif

    FORCEINLINE bool IsNone() const
    {
        return Name.IsNone();
    }
};
