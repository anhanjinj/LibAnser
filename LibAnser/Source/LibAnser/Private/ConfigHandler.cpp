
#include"AliceUtilePrivatePCH.h"
#include "ConfigHandler.h"
#include "Kismet/KismetStringLibrary.h"

FString UConfigIniHelper::m_filePath;

FConfigFile UConfigIniHelper::m_fileOp;
UConfigIniHelper::UConfigIniHelper()
{
}


UConfigIniHelper::~UConfigIniHelper()
{
}

void  UConfigIniHelper::OpenIniConfigFile(const FString&  iniFile)
{

	FString strPath = /*FPaths::GamePluginsDir() + "/" +*/ iniFile;

	m_filePath = strPath;
	m_fileOp.Read(strPath);
	
}

FString UConfigIniHelper::GetString(const FString Section, const FString Key)
{
	FString strRet;

	m_fileOp.GetString(*Section, *Key, strRet);


	return strRet;
}

FText UConfigIniHelper::GetText(const FString Section, const FString Key)
{
	FText txtRet;

	m_fileOp.GetText(*Section, *Key, txtRet);

	return txtRet;
}

int32 UConfigIniHelper::GetInteger32(const FString Section, const FString Key /*= "value"*/)
{
	int64 nRet;

	m_fileOp.GetInt64(*Section, *Key, nRet);

	return nRet;

}

float UConfigIniHelper::GetFloat(const FString Section, const FString Key /*= "value"*/)
{


	FString strFloat = GetString(Section, Key);
	
	return UKismetStringLibrary::Conv_StringToFloat(strFloat);

}

bool UConfigIniHelper::GetBool(const FString Section, const FString Key /*= "value"*/)
{
	FString strTmp;
	 
   strTmp =	GetString(Section, Key);

   if (strTmp.Equals(FString("true") , ESearchCase::IgnoreCase))
   {
	   return true;
   }
   else
   {
	   return false;
   }
}

void UConfigIniHelper::SetBool(const bool Value, const FString Section, const FString Key )
{

	if (Value)
	{
		SetString(FString("true"), Section, Key);
	}
	else
	{
		SetString(FString("false"), Section, Key);
	}

	return;
}

void UConfigIniHelper::SetInteger(const int32 Value, const FString Section, const FString Key /*= "value"*/)
{
	SetString(FString::FromInt(Value), Section, Key);
	
	return;
}

void UConfigIniHelper::SetString(const FString Value, const FString Section, const FString Key)
{

	m_fileOp.SetString(*Section, *Key, *Value);

	m_fileOp.Write(m_filePath);

}

void UConfigIniHelper::SetText(const FText Value, const FString Section, const FString Key)
{

	m_fileOp.SetText(*Section, *Key, Value);

	m_fileOp.Write(m_filePath);
}




