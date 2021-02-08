#pragma once

#include "Management.h"
#include "ProtoMgr.h"
#include "Transform.h"
//#include "Renderer.h"
//#include "Physics.h"
//#include "Camera.h"
//#include "SphereCollider.h"
//#include "Calculator.h"
//#include "Shader.h"
//#include "ColliderObject.h"
//#include "Optimization.h"
//#include "Collider.h"
//
//// Renderer
//#include "TerrainRenderer.h"
//#include "MeshRenderer.h"
//#include "PolyRenderer.h"
//#include "SphereRenderer.h"
//#include "OrthoRenderer.h"
//
//// Manager
//#include "LightMgr.h"
//#include "CollisionMgr.h"
//#include "UserManager.h"
//#include "CameraManager.h"
//#include "RenderTargetMgr.h"

BEGIN(Engine)

// Management
inline CLayer* Get_Layer(const _tchar* pLayerTag);
inline CComponent* Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
inline CGameObject* Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag);

inline HRESULT Create_Management(CManagement** ppManagement);
inline HRESULT	SetUp_Scene(CScene* pScene);
inline _int	Update_Scene(const _float& fTimeDelta);
inline void	Render_Scene(LPDIRECT3DDEVICE9 & pGraphicDev);

// Protomgr
inline HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pInstance);
inline CComponent*		Clone(const _tchar* pProtoTag);

// Renderer
//inline CRenderer*	Get_Renderer(void);
//
//// LightMgr
//inline D3DLIGHT9*				Get_Light(const _uint& iIndex);
//inline HRESULT					Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);
//inline void						Render_Light(LPD3DXEFFECT& pEffect);
//inline void						Clear_LightList(void);
//
//// RenderTargetMgr
//inline HRESULT		Ready_RenderTarget(LPDIRECT3DDEVICE9 pGraphicDev,
//	const _tchar* pTargetTag, const _uint& iWidth,
//	const _uint& iHeight,
//	D3DFORMAT Format,
//	D3DXCOLOR Color);
//inline HRESULT		Ready_MRT(const _tchar* pMRTTag, const _tchar* pTargetTag);
//
//inline HRESULT		Begin_MRT(const _tchar* pMRTTag);
//inline HRESULT		End_MRT(const _tchar* pMRTTag);
//
//inline HRESULT		Ready_DebugBuffer(const _tchar* pTargetTag, const _float& fX, const _float& fY, const _float& fSizeX, const _float& fSizeY);
//inline void		Render_DebugBuffer(const _tchar* pMRTTag);
//inline void		Throw_RenderTargetTexture(LPD3DXEFFECT& pEffect, const _tchar* pTargetTag, const char* pConstantName);


inline void Release_Utility(void);

END

#include "Export_Utility.inl"