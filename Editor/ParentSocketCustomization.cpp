// Copyright 2019 Marcin Swiderski. All Rights Reserved.

#include "ParentSocketCustomization.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Components/SceneComponent.h"
#include "IPropertyUtilities.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "Toolkits/AssetEditorManager.h"
#include "BlueprintEditor.h"
#include "SSCSEditor.h"

void FParentSocketCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomPropertyTypeLayout("ParentSocket", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FParentSocketCustomization::MakeInstance));
}

void FParentSocketCustomization::Unregister()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.UnregisterCustomPropertyTypeLayout("ParentSocket");
}

void FParentSocketCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    InitOptionsList(InPropertyHandle);
    NamePropertyHandle = InPropertyHandle->GetChildHandle("Name");

    HeaderRow
        .ValueContent()
        [
            SNew(SHorizontalBox)
		    + SHorizontalBox::Slot()
		    .VAlign(VAlign_Center)
		    .FillWidth(1.0f)
		    .Padding(1.0f, 1.0f)
		    [
                SNew(SComboBox<TSharedPtr<FName>>)
                .OptionsSource(&OptionsList)
                .OnGenerateWidget(this, &FParentSocketCustomization::OnGenerateWidget)
                .OnSelectionChanged(this, &FParentSocketCustomization::OnSelectionChanged)
		        [
                    SNew(SMultiLineEditableText)
                    .AllowMultiLine(false)
                    .Text(this, &FParentSocketCustomization::GetSocketName)
                    .OnTextCommitted(this, &FParentSocketCustomization::OnTextCommitted)
                ]
		    ]
        ];
}

void FParentSocketCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{

}

FText FParentSocketCustomization::GetSocketName() const
{
    FText Text;
    NamePropertyHandle->GetValueAsDisplayText(Text);
    return Text;
}

static USceneComponent* FindSceneComponentParentInEditor(USceneComponent* SceneComp)
{
    for (UObject* EditedAsset : FAssetEditorManager::Get().GetAllEditedAssets())
    {
        if (UBlueprint* Blueprint = Cast<UBlueprint>(EditedAsset))
        {
            for (IAssetEditorInstance* AssetEditor : FAssetEditorManager::Get().FindEditorsForAsset(EditedAsset))
            {
                if (FBlueprintEditor* BlueprintEditor = static_cast<FBlueprintEditor*>(AssetEditor))
                {
                    if (TSharedPtr<SSCSEditor> SCSEditor = BlueprintEditor->GetSCSEditor())
                    {
                        if (FSCSEditorTreeNodePtrType SceneCompNode = SCSEditor->GetNodeFromActorComponent(SceneComp))
                        {
                            if (FSCSEditorTreeNodePtrType ParentCompNode = SceneCompNode->GetParent())
                            {
                                return Cast<USceneComponent>(ParentCompNode->GetEditableComponentTemplate(Blueprint));
                            }
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

void FParentSocketCustomization::InitOptionsList(TSharedRef<IPropertyHandle> InPropertyHandle)
{
    OptionsList.Add(MakeShareable(new FName()));

    TArray<UObject*> OuterObjects;
    InPropertyHandle->GetOuterObjects(OuterObjects);

    if (OuterObjects.Num() > 0)
    {
        if (USceneComponent* SceneComp = Cast<USceneComponent>(OuterObjects[0]))
        {
            USceneComponent* ParentComp = SceneComp->GetAttachParent();
            if (!ParentComp)
            {
                ParentComp = FindSceneComponentParentInEditor(SceneComp);
            }
            if (ParentComp)
            {
                TArray<FName> SocketNames = ParentComp->GetAllSocketNames();
                OptionsList.Reserve(SocketNames.Num() + 1);
                for (FName Socket : SocketNames)
                {
                    OptionsList.Add(MakeShareable(new FName(Socket)));
                }
            }
        }
    }
}

TSharedRef<SWidget> FParentSocketCustomization::OnGenerateWidget(TSharedPtr<FName> Option)
{
    return SNew(STextBlock)
        .Text(FText::FromName(*Option));
}

void FParentSocketCustomization::OnSelectionChanged(TSharedPtr<FName> Option, ESelectInfo::Type SelectionType)
{
    NamePropertyHandle->SetValue(*Option);
}

void FParentSocketCustomization::OnTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    NamePropertyHandle->SetValue(FName(*Text.ToString()));
}
