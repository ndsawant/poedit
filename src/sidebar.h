/*
 *  This file is part of Poedit (http://poedit.net)
 *
 *  Copyright (C) 2014 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef Poedit_sidebar_h
#define Poedit_sidebar_h

#include <memory>
#include <vector>

#include <wx/panel.h>

class WXDLLIMPEXP_CORE wxSizer;
class WXDLLIMPEXP_CORE wxStaticText;

class CatalogItem;


/// Implements part of the sidebar.
class SidebarBlock
{
public:
    SidebarBlock(wxWindow *parent, const wxString& label);
    virtual ~SidebarBlock() {}

    wxSizer *GetSizer() const { return m_sizer; }

    void Show(bool show);

    void SetItem(CatalogItem *item);

    virtual bool ShouldShowForItem(CatalogItem *item) const = 0;

    virtual void Update(CatalogItem *item) = 0;

    virtual bool IsGrowable() const { return false; }

protected:
    wxSizer *m_innerSizer;

private:
    wxSizer *m_sizer;
};

/**
    Control showing Poedit's assistance sidebar.
    
    Contains TM suggestions, comments and possibly other auxiliary stuff.
 */
class Sidebar : public wxPanel
{
public:
    Sidebar(wxWindow *parent);
    ~Sidebar();

    /// Update selected item, if there's a single one. May be nullptr.
    void SetSelectedItem(CatalogItem *item);

    /// Tell the sidebar there's multiple selection.
    void SetMultipleSelection();

    /// Refreshes displayed content
    void RefreshContent();

    /// Set max height of the upper (not input-aligned) part.
    void SetUpperHeight(int size);

private:
    enum BlockPos { Top, Bottom };
    void AddBlock(SidebarBlock *block, BlockPos pos);

    void OnPaint(wxPaintEvent&);

private:
    CatalogItem *m_selectedItem;

    std::vector<std::unique_ptr<SidebarBlock>> m_blocks;

    wxSizer *m_blocksSizer;
    wxSizer *m_topBlocksSizer, *m_bottomBlocksSizer;
};

#endif // Poedit_sidebar_h
