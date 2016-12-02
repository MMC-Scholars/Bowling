// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MMC_BOWLING_entity_base_generated_h
#error "entity_base.generated.h already included, missing '#pragma once' in entity_base.h"
#endif
#define MMC_BOWLING_entity_base_generated_h

#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execResetWorldTransform) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetWorldTransform(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCalculateHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_delta); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CalculateHealth(Z_Param_delta); \
		P_NATIVE_END; \
	}


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execResetWorldTransform) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetWorldTransform(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCalculateHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_delta); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CalculateHealth(Z_Param_delta); \
		P_NATIVE_END; \
	}


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_EVENT_PARMS
extern MMC_BOWLING_API  FName MMC_BOWLING_OnKilled;
#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_CALLBACK_WRAPPERS
#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAentity_base(); \
	friend MMC_BOWLING_API class UClass* Z_Construct_UClass_Aentity_base(); \
	public: \
	DECLARE_CLASS(Aentity_base, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/MMC_Bowling"), NO_API) \
	DECLARE_SERIALIZER(Aentity_base) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_INCLASS \
	private: \
	static void StaticRegisterNativesAentity_base(); \
	friend MMC_BOWLING_API class UClass* Z_Construct_UClass_Aentity_base(); \
	public: \
	DECLARE_CLASS(Aentity_base, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/MMC_Bowling"), NO_API) \
	DECLARE_SERIALIZER(Aentity_base) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API Aentity_base(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(Aentity_base) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Aentity_base); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Aentity_base); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API Aentity_base(Aentity_base&&); \
	NO_API Aentity_base(const Aentity_base&); \
public:


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API Aentity_base(Aentity_base&&); \
	NO_API Aentity_base(const Aentity_base&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Aentity_base); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Aentity_base); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Aentity_base)


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_7_PROLOG \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_EVENT_PARMS


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_RPC_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_CALLBACK_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_INCLASS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_CALLBACK_WRAPPERS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_INCLASS_NO_PURE_DECLS \
	MMC_Bowling_Source_MMC_Bowling_entity_base_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MMC_Bowling_Source_MMC_Bowling_entity_base_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
