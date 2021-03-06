// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FXJS_XFA_CJX_SUBJECTDN_H_
#define FXJS_XFA_CJX_SUBJECTDN_H_

#include "fxjs/xfa/cjx_node.h"
#include "fxjs/xfa/jse_define.h"

class CXFA_SubjectDN;

class CJX_SubjectDN final : public CJX_Node {
 public:
  explicit CJX_SubjectDN(CXFA_SubjectDN* node);
  ~CJX_SubjectDN() override;
};

#endif  // FXJS_XFA_CJX_SUBJECTDN_H_
