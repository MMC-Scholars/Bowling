// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MMC_BOWLING_bowling_system_generated_h
#error "bowling_system.generated.h already included, missing '#pragma once' in bowling_system.h"
#endif
#define MMC_BOWLING_bowling_system_generated_h

#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetNumberOfCurrentFrame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetNumberOfCurrentFrame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetAbsoluteScore) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetAbsoluteScore(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetGame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetGame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetStringScoreOfFrame) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_frameNumber); \
		P_GET_PROPERTY(UByteProperty,Z_Param_type); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=this->GetStringScoreOfFrame(Z_Param_frameNumber,ScoreType(Z_Param_type)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetScoreOfFrame) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_frameNumber); \
		P_GET_PROPERTY(UByteProperty,Z_Param_type); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetScoreOfFrame(Z_Param_frameNumber,ScoreType(Z_Param_type)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCalculateScore) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CalculateScore(); \
		P_NATIVE_END; \
	}


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetNumberOfCurrentFrame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetNumberOfCurrentFrame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetAbsoluteScore) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetAbsoluteScore(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetGame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetGame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetStringScoreOfFrame) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_frameNumber); \
		P_GET_PROPERTY(UByteProperty,Z_Param_type); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=this->GetStringScoreOfFrame(Z_Param_frameNumber,ScoreType(Z_Param_type)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetScoreOfFrame) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_frameNumber); \
		P_GET_PROPERTY(UByteProperty,Z_Param_type); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=this->GetScoreOfFrame(Z_Param_frameNumber,ScoreType(Z_Param_type)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCalculateScore) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CalculateScore(); \
		P_NATIVE_END; \
	}


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_EVENT_PARMS
extern MMC_BOWLING_API  FName MMC_BOWLING_OnGameover;
extern MMC_BOWLING_API  FName MMC_BOWLING_OnSpare;
extern MMC_BOWLING_API  FName MMC_BOWLING_OnStrike;
#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_CALLBACK_WRAPPERS
#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAbowling_system(); \
	friend MMC_BOWLING_API class UClass* Z_Construct_UClass_Abowling_system(); \
	public: \
	DECLARE_CLASS(Abowling_system, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/MMC_Bowling"), NO_API) \
	DECLARE_SERIALIZER(Abowling_system) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_INCLASS \
	private: \
	static void StaticRegisterNativesAbowling_system(); \
	friend MMC_BOWLING_API class UClass* Z_Construct_UClass_Abowling_system(); \
	public: \
	DECLARE_CLASS(Abowling_system, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/MMC_Bowling"), NO_API) \
	DECLARE_SERIALIZER(Abowling_system) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API Abowling_system(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(Abowling_system) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Abowling_system); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Abowling_system); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API Abowling_system(Abowling_system&&); \
	NO_API Abowling_system(const Abowling_system&); \
public:


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API Abowling_system(Abowling_system&&); \
	NO_API Abowling_system(const Abowling_system&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Abowling_system); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Abowling_system); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Abowling_system)


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_32_PROLOG \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_EVENT_PARMS


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_RPC_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_CALLBACK_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_INCLASS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_CALLBACK_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_INCLASS_NO_PURE_DECLS \
	MMC_Bowling_Source_MMC_Bowling_bowling_system_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MMC_Bowling_Source_MMC_Bowling_bowling_system_h


#define FOREACH_ENUM_ENDGAMETYPE(op) \
	op(Undetermined) \
	op(DefaultEnding) \
	op(SpareEnding) \
	op(StrikeEnding) 
#define FOREACH_ENUM_SCORETYPE(op) \
	op(FirstThrow) \
	op(SecondThrow) \
	op(NativeScore) \
	op(AbsoluteNativeScore) \
	op(AbsoluteScore) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
