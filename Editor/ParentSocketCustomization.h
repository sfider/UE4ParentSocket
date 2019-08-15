// Copyright 2019 Marcin Swiderski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class FDetailWidgetRow;
class IDetailChildrenBuilder;

class FParentSocketCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance()
    {
        return MakeShareable(new FParentSocketCustomization());
    }
    
    static void Register();
    static void Unregister();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;

private:
    void InitOptionsList(TSharedRef<IPropertyHandle> InPropertyHandle);
    
    FText GetSocketName() const;

    TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FName> Option);
    void OnSelectionChanged(TSharedPtr<FName> Option, ESelectInfo::Type SelectionType);
    void OnTextCommitted(const FText& Text, ETextCommit::Type CommitType);

private:
    TSharedPtr<IPropertyHandle> NamePropertyHandle;
    TArray<TSharedPtr<FName>> OptionsList;
};
