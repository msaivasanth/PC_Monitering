// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor1.generated.h"

class UMyGameInstance;
UCLASS()
class MYPROJECT2_API AMyActor1 : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMyActor1();
	TMap<int32, UMaterialInstanceDynamic*> map;
	TMap<int32, UMaterialInstanceDynamic*> map1;
	TMap<int32, UMaterialInstanceDynamic*> map2;
	TMap<FString, int32> mactono;
	TMap<int32, FString> notomac;
	TMap<FString,int32> actortono;
	int32 c = 1;
	int32 count=1;
	AActor* a;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> Actortospawn;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UMyGameInstance* GameInstance;
	int32 lab = 0;
	int32 sys = 0;
	int32 i = 1;
};
