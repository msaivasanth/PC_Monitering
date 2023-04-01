// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "MyActor1.h"
#include "MyActor.generated.h"

class UMaterialInstanceDynamic;
class UMyGameInstance;
class AMyActor1;
class USphereComponent;

UCLASS()
class MYPROJECT2_API AMyActor : public AActor
{
	GENERATED_BODY()
		UStaticMeshComponent* root;
		UStaticMeshComponent* FirstActorMesh;
		UStaticMeshComponent* fam;
		UStaticMeshComponent* computer;

	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* r;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category	= "Learning About Components")
		class UStaticMeshComponent* mouse;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* keyboard;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* pc;
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class USphereComponent* LightSphere;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> Actortospawn;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UMaterialInstanceDynamic* material;
	UMaterialInstanceDynamic* material1;
	UMaterialInstanceDynamic* material2;
	UMyGameInstance* GameInstance;
	AMyActor1* spawnactor;
};