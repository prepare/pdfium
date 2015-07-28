// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FPDFSDK_INCLUDE_PDFWINDOW_PWL_NOTE_H_
#define FPDFSDK_INCLUDE_PDFWINDOW_PWL_NOTE_H_

#include "PWL_Button.h"
#include "PWL_Edit.h"
#include "PWL_ListCtrl.h"
#include "PWL_ScrollBar.h"
#include "PWL_Wnd.h"

class CPWL_Label;
class CPWL_Note;
class CPWL_NoteItem;
class CPWL_Note_CloseBox;
class CPWL_Note_Contents;
class CPWL_Note_Edit;
class CPWL_Note_Icon;
class CPWL_Note_LBBox;
class CPWL_Note_Options;
class CPWL_Note_RBBox;
class IPWL_NoteHandler;
class IPWL_NoteItem;
class IPWL_NoteNotify;
class IPopup_Note;

class IPWL_NoteNotify
{
public:
	virtual ~IPWL_NoteNotify() { }
	virtual void						OnNoteMove(const FX_RECT& rtWin) = 0;
	virtual void						OnNoteShow(FX_BOOL bShow) = 0;
	virtual void						OnNoteActivate(FX_BOOL bActive) = 0;
	virtual void						OnNoteClose() = 0;
	virtual void						OnItemCreate(IPWL_NoteItem* pItem) = 0;
	virtual void						OnItemDelete(IPWL_NoteItem* pItem) = 0;
	virtual void						OnSetAuthorName(IPWL_NoteItem* pItem) = 0;
	virtual void						OnSetBkColor(IPWL_NoteItem* pItem) = 0;
	virtual void						OnSetContents(IPWL_NoteItem* pItem) = 0;
	virtual void						OnSetDateTime(IPWL_NoteItem* pItem) = 0;
	virtual void						OnSetSubjectName(IPWL_NoteItem* pItem) = 0;
	virtual void						OnPopupMenu(int32_t x, int32_t y) = 0;
	virtual void						OnPopupMenu(IPWL_NoteItem* pItem, int32_t x, int32_t y) = 0;
};

class IPWL_NoteHandler
{
public:
	virtual ~IPWL_NoteHandler() { }
	virtual void						OnNoteColorChanged(const CPWL_Color& color) = 0;
};

class IPWL_NoteItem
{
public:
	virtual ~IPWL_NoteItem() { }
	virtual void						SetPrivateData(void* pData) = 0;
	virtual void						SetBkColor(const CPWL_Color& color) = 0;
	virtual void						SetSubjectName(const CFX_WideString& sName) = 0;
	virtual void						SetAuthorName(const CFX_WideString& sName) = 0;
	virtual void						SetDateTime(FX_SYSTEMTIME time) = 0;
	virtual void						SetContents(const CFX_WideString& sContents) = 0;

	virtual IPWL_NoteItem*				CreateSubItem() = 0;
	virtual int32_t					CountSubItems() const = 0;
	virtual IPWL_NoteItem*				GetSubItems(int32_t index) const = 0;
	virtual void						DeleteSubItem(IPWL_NoteItem* pNoteItem) = 0;
	virtual void						SetFocus() = 0;

	virtual IPWL_NoteItem*				GetParentItem() const = 0;
	virtual void*						GetPrivateData() const = 0;
	virtual CFX_WideString				GetAuthorName() const = 0;
	virtual CPWL_Color					GetBkColor() const = 0;
	virtual CFX_WideString				GetContents() const = 0;
	virtual FX_SYSTEMTIME				GetDateTime() const = 0;
	virtual CFX_WideString				GetSubjectName() const = 0;

	virtual CPWL_Edit*					GetEdit() const = 0;
};

class CPWL_Note_Icon : public CPWL_Wnd
{
public:
	CPWL_Note_Icon();
	virtual ~CPWL_Note_Icon();

	void								SetIconType(int32_t nType);

public:

protected:
	virtual void						DrawThisAppearance(CFX_RenderDevice* pDevice, CPDF_Matrix* pUser2Device);

private:
	int32_t							m_nType;
};

class CPWL_Note_CloseBox : public CPWL_Button
{
public:
	CPWL_Note_CloseBox();
	virtual ~CPWL_Note_CloseBox();

protected:
	virtual void						DrawThisAppearance(CFX_RenderDevice* pDevice, CPDF_Matrix* pUser2Device);
	virtual FX_BOOL						OnLButtonDown(const CPDF_Point & point, FX_DWORD nFlag);
	virtual FX_BOOL						OnLButtonUp(const CPDF_Point & point, FX_DWORD nFlag);

private:
	FX_BOOL								m_bMouseDown;
};

class CPWL_Note_LBBox : public CPWL_Wnd
{
public:
	CPWL_Note_LBBox();
	virtual ~CPWL_Note_LBBox();

protected:
	virtual void						DrawThisAppearance(CFX_RenderDevice* pDevice, CPDF_Matrix* pUser2Device);
};

class CPWL_Note_RBBox : public CPWL_Wnd
{
public:
	CPWL_Note_RBBox();
	virtual ~CPWL_Note_RBBox();

protected:
	virtual void						DrawThisAppearance(CFX_RenderDevice* pDevice, CPDF_Matrix* pUser2Device);
};

class CPWL_Note_Edit : public CPWL_Edit
{
public:
	CPWL_Note_Edit();
	virtual ~CPWL_Note_Edit();

	void								EnableNotify(FX_BOOL bEnable) {m_bEnableNotify = bEnable;}
	virtual FX_FLOAT					GetItemHeight(FX_FLOAT fLimitWidth);
	FX_FLOAT							GetItemLeftMargin();
	FX_FLOAT							GetItemRightMargin();

	virtual void						SetText(const FX_WCHAR* csText);

protected:
	virtual void						OnNotify(CPWL_Wnd* pWnd, FX_DWORD msg, intptr_t wParam = 0, intptr_t lParam = 0);
	virtual void						RePosChildWnd();
	virtual void						OnSetFocus();
	virtual void						OnKillFocus();

private:
	FX_BOOL								m_bEnableNotify;
	FX_FLOAT							m_fOldItemHeight;
	FX_BOOL								m_bSizeChanged;
	FX_FLOAT							m_fOldMin;
	FX_FLOAT							m_fOldMax;
};

class CPWL_Note_Options : public CPWL_Wnd
{
public:
	CPWL_Note_Options();
	virtual ~CPWL_Note_Options();

	CPDF_Rect							GetContentRect() const;
	virtual void						SetTextColor(const CPWL_Color & color);
	void								SetText(const CFX_WideString& sText);

protected:
	virtual void						RePosChildWnd();
	virtual void						CreateChildWnd(const PWL_CREATEPARAM & cp);
	virtual void						DrawThisAppearance(CFX_RenderDevice* pDevice, CPDF_Matrix* pUser2Device);

private:
	CPWL_Label*							m_pText;
};

class CPWL_Note_Contents : public CPWL_ListCtrl
{
public:
	CPWL_Note_Contents();
	virtual ~CPWL_Note_Contents();

	virtual CFX_ByteString				GetClassName() const;
	virtual void						OnNotify(CPWL_Wnd* pWnd, FX_DWORD msg, intptr_t wParam = 0, intptr_t lParam = 0);
	virtual FX_BOOL						OnLButtonDown(const CPDF_Point& point, FX_DWORD nFlag);

	void								SetEditFocus(FX_BOOL bLast);
	CPWL_Edit*							GetEdit() const;

public:
	void								SetText(const CFX_WideString& sText);
	CFX_WideString						GetText() const;

	CPWL_NoteItem*						CreateSubItem();
	void								DeleteSubItem(IPWL_NoteItem* pNoteItem);
	int32_t							CountSubItems() const;
	IPWL_NoteItem*						GetSubItems(int32_t index) const;

	virtual IPWL_NoteItem*				GetHitNoteItem(const CPDF_Point& point);
	void								EnableRead(FX_BOOL bEnabled);
	void								EnableModify(FX_BOOL bEnabled);

protected:
	virtual void						CreateChildWnd(const PWL_CREATEPARAM & cp);

private:
	CPWL_Note_Edit*						m_pEdit;
};

class CPWL_NoteItem : public CPWL_Wnd, public IPWL_NoteItem
{
public:
	CPWL_NoteItem();
	virtual ~CPWL_NoteItem();

public:
	virtual void						SetPrivateData(void* pData);
	virtual void						SetBkColor(const CPWL_Color& color);
	virtual void						SetSubjectName(const CFX_WideString& sName);
	virtual void						SetAuthorName(const CFX_WideString& sName);
	virtual void						SetDateTime(FX_SYSTEMTIME time);
	virtual void						SetContents(const CFX_WideString& sContents);

	virtual IPWL_NoteItem*				CreateSubItem();
	virtual int32_t					CountSubItems() const;
	virtual IPWL_NoteItem*				GetSubItems(int32_t index) const;
	virtual void						DeleteSubItem(IPWL_NoteItem* pNoteItem);
	virtual void						SetFocus(){SetNoteFocus(FALSE);}

	virtual IPWL_NoteItem*				GetParentItem() const;
	virtual void*						GetPrivateData() const;
	virtual CFX_WideString				GetAuthorName() const;
	virtual CPWL_Color					GetBkColor() const;
	virtual CFX_WideString				GetContents() const;
	virtual FX_SYSTEMTIME				GetDateTime() const;
	virtual CFX_WideString				GetSubjectName() const;
	virtual FX_BOOL						IsTopItem() const { return FALSE;}
	virtual CPWL_Edit*					GetEdit() const;

public:
	virtual FX_BOOL						OnLButtonDown(const CPDF_Point& point, FX_DWORD nFlag);
	virtual FX_BOOL						OnRButtonUp(const CPDF_Point & point, FX_DWORD nFlag);
	virtual CFX_ByteString				GetClassName() const;
	virtual IPWL_NoteItem*				GetHitNoteItem(const CPDF_Point& point);
	virtual IPWL_NoteItem*				GetFocusedNoteItem() const;

	virtual void						ResetSubjectName(int32_t nItemIndex);
	void								EnableRead(FX_BOOL bEnabled);
	void								EnableModify(FX_BOOL bEnabled);

protected:
	virtual void						RePosChildWnd();
	virtual void						CreateChildWnd(const PWL_CREATEPARAM & cp);

	virtual void						OnNotify(CPWL_Wnd* pWnd, FX_DWORD msg, intptr_t wParam = 0, intptr_t lParam = 0);

public:
	virtual FX_FLOAT					GetItemHeight(FX_FLOAT fLimitWidth);
	virtual FX_FLOAT					GetItemLeftMargin();
	virtual FX_FLOAT					GetItemRightMargin();
	CPWL_NoteItem*						CreateNoteItem();
	CPWL_NoteItem*						GetParentNoteItem() const;

	void								SetNoteFocus(FX_BOOL bLast);
	void								OnContentsValidate();

	void								OnCreateNoteItem();

protected:
	void								PopupNoteItemMenu(const CPDF_Point& point);

	virtual const CPWL_Note*			GetNote() const;
	virtual IPWL_NoteNotify*			GetNoteNotify() const;

protected:
	CPWL_Label*							m_pSubject;
	CPWL_Label*							m_pDateTime;
	CPWL_Note_Contents*					m_pContents;

private:
	void*								m_pPrivateData;
	FX_SYSTEMTIME						m_dtNote;
	CFX_WideString						m_sAuthor;

	FX_FLOAT							m_fOldItemHeight;
	FX_BOOL								m_bSizeChanged;
	FX_BOOL								m_bAllowModify;
};

class CPWL_Note : public CPWL_NoteItem
{
public:
	CPWL_Note(IPopup_Note* pPopupNote, IPWL_NoteNotify* pNoteNotify, IPWL_NoteHandler* pNoteHandler);
	virtual ~CPWL_Note();

public:
	virtual void						SetSubjectName(const CFX_WideString& sName);
	virtual void						SetAuthorName(const CFX_WideString& sName);
	virtual CFX_WideString				GetAuthorName() const;
	virtual void						SetBkColor(const CPWL_Color& color);
	virtual void						ResetSubjectName(int32_t nItemIndex){}
	virtual FX_BOOL						IsTopItem() const {return TRUE;}
	virtual const CPWL_Note*			GetNote() const;
	virtual IPWL_NoteNotify*			GetNoteNotify() const;

public:
	IPWL_NoteItem*						Reply();
	void								EnableNotify(FX_BOOL bEnabled);
	void								SetIconType(int32_t nType);
	void								SetOptionsText(const CFX_WideString& sText);
	void								EnableRead(FX_BOOL bEnabled);
	void								EnableModify(FX_BOOL bEnabled);

	CFX_WideString						GetReplyString() const;
	void								SetReplyString(const CFX_WideString& string);

	//0-normal / 1-caption / 2-leftbottom corner / 3-rightbottom corner / 4-close / 5-options
	int32_t							NoteHitTest(const CPDF_Point& point) const;
	CPDF_Rect							GetCaptionRect() const {return m_rcCaption;}
	IPopup_Note*						GetPopupNote() const {return m_pPopupNote;}

public:
	virtual FX_BOOL						OnLButtonDown(const CPDF_Point & point, FX_DWORD nFlag);
	virtual FX_BOOL						OnRButtonUp(const CPDF_Point & point, FX_DWORD nFlag);
	virtual FX_BOOL						OnMouseWheel(short zDelta, const CPDF_Point & point, FX_DWORD nFlag);

protected:
	virtual void						RePosChildWnd();
	virtual void						CreateChildWnd(const PWL_CREATEPARAM & cp);

	virtual void						OnNotify(CPWL_Wnd* pWnd, FX_DWORD msg, intptr_t wParam = 0, intptr_t lParam = 0);

	FX_BOOL								ResetScrollBar();
	void								RePosNoteChildren();
	FX_BOOL								ScrollBarShouldVisible();

private:
	CPWL_Label*							m_pAuthor;
	CPWL_Note_Icon*						m_pIcon;
	CPWL_Note_CloseBox*					m_pCloseBox;
	CPWL_Note_LBBox*					m_pLBBox;
	CPWL_Note_RBBox*					m_pRBBox;
	CPWL_ScrollBar*						m_pContentsBar;
	CPWL_Note_Options*					m_pOptions;
	IPWL_NoteNotify*					m_pNoteNotify;
	FX_BOOL								m_bResizing;
	PWL_SCROLL_INFO						m_OldScrollInfo;
	CPDF_Rect							m_rcCaption;
	FX_BOOL								m_bEnalbleNotify;
	IPopup_Note*						m_pPopupNote;
	CFX_WideString						m_sReplyString;
};

#endif  // FPDFSDK_INCLUDE_PDFWINDOW_PWL_NOTE_H_
