// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FXJS_XFA_CJX_SIGNATUREPSEUDOMODEL_H_
#define FXJS_XFA_CJX_SIGNATUREPSEUDOMODEL_H_

#include "fxjs/xfa/cjx_object.h"
#include "fxjs/xfa/jse_define.h"

class CScript_SignaturePseudoModel;

class CJX_SignaturePseudoModel final : public CJX_Object {
 public:
  explicit CJX_SignaturePseudoModel(CScript_SignaturePseudoModel* model);
  ~CJX_SignaturePseudoModel() override;

  JSE_METHOD(verifySignature /*verify*/, CJX_SignaturePseudoModel);
  JSE_METHOD(sign, CJX_SignaturePseudoModel);
  JSE_METHOD(enumerate, CJX_SignaturePseudoModel);
  JSE_METHOD(clear, CJX_SignaturePseudoModel);

 private:
  static const CJX_MethodSpec MethodSpecs[];
};

#endif  // FXJS_XFA_CJX_SIGNATUREPSEUDOMODEL_H_
