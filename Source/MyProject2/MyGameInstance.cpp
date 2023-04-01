// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "WebSocketsModule.h"
#include "Json.h"

void UMyGameInstance::Init() {
	Super::Init();
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}
	jsonstring = "";
	WebSocket = FWebSocketsModule::Get().CreateWebSocket("wss://0hqif30xkl.execute-api.us-west-2.amazonaws.com/production");

	WebSocket->OnConnected().AddLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully connected");
	});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
	});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
	});

	WebSocket->OnMessage().AddLambda([&](const FString& MessageString)
	{
		jsonstring = MessageString;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MessageString);
		//An FString containing a serialized JSON string
		//TSharedPtr<FJsonObject> MyJson = MakeShareable(new FJsonObject);
		//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageString);
		//if(FJsonSerializer::Deserialize(Reader, MyJson)){
		//	// The deserialization Passes, handle this case
		//	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, "SUCCESS");
			//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "System No:");
			/*GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "System No: " + MyJson->GetStringField("sys_no"));
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Keyboard: " + MyJson->GetStringField("key"));
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Mouse: " + MyJson->GetStringField("mouse"));*/
			/*sys_no = FCString::Atoi(*MyJson->GetStringField("sys_no"));
			if (MyJson->GetStringField("key") == "on") {
				key = 1.0f;
			}
			else if (MyJson->GetStringField("key") == "off") {
				key = 0.0f;
			}
			if (MyJson->GetStringField("mouse") == "on") {
				mouse = 1.0f;
			}
			else if (MyJson->GetStringField("mouse") == "off") {
				mouse = 0.0f;
			}*/
		/*}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, "FAILED");
		}*/
		/*if (i % 3 == 0) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "System No: " + MessageString);
			sys_no = FCString::Atoi(*MessageString);
		}
		else if (i % 3 == 1) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Keyboard: " + MessageString);
			if (MessageString == "on") {
				key = 1.0f;
			}
			else if (MessageString == "off") {
				key = 0.0f;
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "Mouse: " + MessageString);
			if (MessageString == "on") {
				mouse = 1.0f;
			}
			else if (MessageString == "off") {
				mouse = 0.0f;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("i: %d"), i);
		i++;*/
		/*UE_LOG(LogTemp, Warning, TEXT("System No: %d"), sys_no);
		UE_LOG(LogTemp, Warning, TEXT("keyboard: %f"), key);
		UE_LOG(LogTemp, Warning, TEXT("mouse: %f"), mouse);*/
	});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, "Sent message: " + MessageString);
	});

	WebSocket->Connect();
}
void UMyGameInstance::Shutdown() {
	if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}

	Super::Shutdown();
}