// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "fpdfsdk/javascript/cjs_annot.h"

#include "fpdfsdk/javascript/JS_Define.h"
#include "fpdfsdk/javascript/JS_Object.h"
#include "fpdfsdk/javascript/JS_Value.h"
#include "fpdfsdk/javascript/cjs_event_context.h"

namespace {

CPDFSDK_BAAnnot* ToBAAnnot(CPDFSDK_Annot* annot) {
  return static_cast<CPDFSDK_BAAnnot*>(annot);
}

}  // namespace

JSPropertySpec CJS_Annot::PropertySpecs[] = {
    {"hidden", get_hidden_static, set_hidden_static},
    {"name", get_name_static, set_name_static},
    {"type", get_type_static, set_type_static},
    {0, 0, 0}};

const char* CJS_Annot::g_pClassName = "Annot";
int CJS_Annot::g_nObjDefnID = -1;

void CJS_Annot::DefineJSObjects(CFXJS_Engine* pEngine, FXJSOBJTYPE eObjType) {
  g_nObjDefnID = pEngine->DefineObj(CJS_Annot::g_pClassName, eObjType,
                                    JSConstructor<CJS_Annot, Annot>,
                                    JSDestructor<CJS_Annot>);
  DefineProps(pEngine, g_nObjDefnID, PropertySpecs);
}

Annot::Annot(CJS_Object* pJSObject) : CJS_EmbedObj(pJSObject) {}

Annot::~Annot() {}

CJS_Return Annot::get_hidden(CJS_Runtime* pRuntime) {
  if (!m_pAnnot)
    return CJS_Return(JSGetStringFromID(IDS_STRING_JSBADOBJECT));

  CPDF_Annot* pPDFAnnot = ToBAAnnot(m_pAnnot.Get())->GetPDFAnnot();
  return CJS_Return(pRuntime->NewBoolean(
      CPDF_Annot::IsAnnotationHidden(pPDFAnnot->GetAnnotDict())));
}

CJS_Return Annot::set_hidden(CJS_Runtime* pRuntime, v8::Local<v8::Value> vp) {
  // May invalidate m_pAnnot.
  bool bHidden = pRuntime->ToBoolean(vp);
  if (!m_pAnnot)
    return CJS_Return(JSGetStringFromID(IDS_STRING_JSBADOBJECT));

  uint32_t flags = ToBAAnnot(m_pAnnot.Get())->GetFlags();
  if (bHidden) {
    flags |= ANNOTFLAG_HIDDEN;
    flags |= ANNOTFLAG_INVISIBLE;
    flags |= ANNOTFLAG_NOVIEW;
    flags &= ~ANNOTFLAG_PRINT;
  } else {
    flags &= ~ANNOTFLAG_HIDDEN;
    flags &= ~ANNOTFLAG_INVISIBLE;
    flags &= ~ANNOTFLAG_NOVIEW;
    flags |= ANNOTFLAG_PRINT;
  }
  ToBAAnnot(m_pAnnot.Get())->SetFlags(flags);

  return CJS_Return(true);
}

CJS_Return Annot::get_name(CJS_Runtime* pRuntime) {
  if (!m_pAnnot)
    return CJS_Return(JSGetStringFromID(IDS_STRING_JSBADOBJECT));
  return CJS_Return(
      pRuntime->NewString(ToBAAnnot(m_pAnnot.Get())->GetAnnotName().c_str()));
}

CJS_Return Annot::set_name(CJS_Runtime* pRuntime, v8::Local<v8::Value> vp) {
  // May invalidate m_pAnnot.
  WideString annotName = pRuntime->ToWideString(vp);
  if (!m_pAnnot)
    return CJS_Return(JSGetStringFromID(IDS_STRING_JSBADOBJECT));

  ToBAAnnot(m_pAnnot.Get())->SetAnnotName(annotName);
  return CJS_Return(true);
}

CJS_Return Annot::get_type(CJS_Runtime* pRuntime) {
  if (!m_pAnnot)
    return CJS_Return(JSGetStringFromID(IDS_STRING_JSBADOBJECT));
  return CJS_Return(pRuntime->NewString(
      WideString::FromLocal(CPDF_Annot::AnnotSubtypeToString(
                                ToBAAnnot(m_pAnnot.Get())->GetAnnotSubtype())
                                .c_str())
          .c_str()));
}

CJS_Return Annot::set_type(CJS_Runtime* pRuntime, v8::Local<v8::Value> vp) {
  return CJS_Return(JSGetStringFromID(IDS_STRING_JSREADONLY));
}

void Annot::SetSDKAnnot(CPDFSDK_BAAnnot* annot) {
  m_pAnnot.Reset(annot);
}
