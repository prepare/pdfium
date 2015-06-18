// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FXCRT_FX_ARB_H_
#define CORE_INCLUDE_FXCRT_FX_ARB_H_

#include "fx_system.h"

class IFX_BidiChar
{
public:
    static IFX_BidiChar* Create();
    virtual ~IFX_BidiChar() {}

    virtual void SetPolicy(FX_BOOL bSeparateNeutral = TRUE) = 0;
    virtual FX_BOOL AppendChar(FX_WCHAR wch) = 0;
    virtual FX_BOOL EndChar() = 0;
    virtual int32_t GetBidiInfo(int32_t &iStart, int32_t &iCount) = 0;
    virtual void Reset() = 0;
};

#endif  // CORE_INCLUDE_FXCRT_FX_ARB_H_
