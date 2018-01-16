#pragma once

#include "ConfigCacheIni.h"
#include "ConfigHandler.generated.h"


UCLASS()
class UConfigIniHelper: public UBlueprintFunctionLibrary
{

	GENERATED_BODY()


public:
	UConfigIniHelper();
	~UConfigIniHelper();

	//open a ini config
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static void OpenIniConfigFile(const FString&  iniFileName);

	//get string value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static FString GetString(const FString Section, const FString Key = "value");

	//get text value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static FText GetText(const FString Section, const FString Key = "value");
	
	//get string value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static int32 GetInteger32(const FString Section, const FString Key = "value");

	//get string value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static float GetFloat(const FString Section, const FString Key = "value");

	//get bool value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static bool GetBool(const FString Section, const FString Key = "value");

	//set string value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static void SetBool(const bool Value, const FString Section, const FString Key = "value");

	//set int value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static void SetInteger(const int32 Value, const FString Section, const FString Key = "value");

	//set string value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static void SetString(const FString Value,const FString Section, const FString Key = "value");

	//set text value by section an key
	UFUNCTION(BlueprintCallable, Category = "AliceUtile|ConfigIni")
	static void SetText(const FText Value, const FString Section, const FString Key = "value");


private:

	static FString m_filePath;

	static FConfigFile m_fileOp;
		

};

