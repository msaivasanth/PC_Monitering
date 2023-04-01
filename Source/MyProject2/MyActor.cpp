// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "MyActor1.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Json.h"


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("root"));
	SetRootComponent(r);
	pc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("computer"));
	pc->SetupAttachment(r);
	mouse = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstActorMesh"));
	//SetRootComponent(mouse);
	mouse->SetupAttachment(r);
	keyboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("fam"));
	keyboard->SetupAttachment(r);
	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	//LightSphere->InitSphereRadius(300.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LightSphere->SetupAttachment(r);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//AMyActor1 a;
	/*r->SetupAttachment(mouse);
	r->SetupAttachment(keyboard);*/
	//r->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	
	material = UMaterialInstanceDynamic::Create(mouse->GetMaterial(0), NULL);
	material1 = UMaterialInstanceDynamic::Create(keyboard->GetMaterial(0), NULL);
	material2 = UMaterialInstanceDynamic::Create(pc->GetMaterial(0), NULL);
	
	mouse->SetMaterial(0, material);
	keyboard->SetMaterial(0, material1);
	pc->SetMaterial(0, material2);
	
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, material->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, material1->GetName());*/

	spawnactor = Cast<AMyActor1>(UGameplayStatics::GetActorOfClass(GetWorld(),Actortospawn));

	spawnactor->map.Add(spawnactor->count,material);
	spawnactor->map1.Add(spawnactor->count, material1);
	spawnactor->map2.Add(spawnactor->count, material2);
	//a->map1.Add(a->count, material1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, spawnactor->map[spawnactor->count]->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, spawnactor->map1[spawnactor->count]->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, spawnactor->map2[spawnactor->count]->GetName());
	spawnactor->count++;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(a->count));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(a.count1));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	//UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(sphere->GetMaterial(0), NULL);
	//if (GameInstance) {
		//UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), GameInstance->WebSocket->OnMessage());
	//}

	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		if (GameInstance->WebSocket->IsConnected())
		{
			TSharedPtr<FJsonObject> MyJson = MakeShareable(new FJsonObject);
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(GameInstance->jsonstring);
			if(FJsonSerializer::Deserialize(Reader, MyJson)){
				// The deserialization failed, handle this case
				/*GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "System No: " + MyJson->GetStringField("sys_no"));
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Keyboard: " + MyJson->GetStringField("key"));
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Mouse: " + MyJson->GetStringField("mouse"));*/
				if (MyJson->TryGetField("MAC")!=nullptr) {
					if (!spawnactor->mactono.Contains(MyJson->GetStringField("MAC"))) {
						GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "MACID: " + MyJson->GetStringField("MAC"));
						spawnactor->mactono.Add(MyJson->GetStringField("MAC"), spawnactor->c);
						spawnactor->notomac.Add(spawnactor->c, MyJson->GetStringField("MAC"));
						spawnactor->c++;
					}
					material = spawnactor->map[spawnactor->mactono[MyJson->GetStringField("MAC")]];
					material1 = spawnactor->map1[spawnactor->mactono[MyJson->GetStringField("MAC")]];
					material2 = spawnactor->map2[spawnactor->mactono[MyJson->GetStringField("MAC")]];

					/*mouse->SetMaterial(0, material);
					keyboard->SetMaterial(0, material1);*/

					if (MyJson->GetStringField("Keyboard") != "") {

						//UE_LOG(LogTemp, Warning, TEXT("key: %f"), GameInstance->key);
						material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
					}
					else {
						material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
					}
					if (MyJson->GetStringField("Mouse") != "") {

						//UE_LOG(LogTemp, Warning, TEXT("mouse: %f"), GameInstance->mouse);
						material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
					}
					else {
						material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
					}
					if (MyJson->GetStringField("SystemStatus") == "on") {

						//UE_LOG(LogTemp, Warning, TEXT("key: %f"), GameInstance->key);
						/*material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
						material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));*/
						material2->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
					}
					else {
						/*material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
						material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));*/
						material2->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
					}
				}
			}
		}
		else {
			material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
			material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
			material2->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
		}
	}
	


}

