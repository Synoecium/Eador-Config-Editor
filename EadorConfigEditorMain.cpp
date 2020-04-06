/***************************************************************
 * Name:      EadorConfigEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Synoecium ()
 * Created:   2016-03-17
 * Copyright: Synoecium ()
 * License:
 **************************************************************/

#include "EadorConfigEditorMain.h"


//(*InternalHeaders(EadorConfigEditorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(EadorConfigEditorFrame)
const long EadorConfigEditorFrame::ID_NOTEBOOK1 = wxNewId();
const long EadorConfigEditorFrame::idMenuSave = wxNewId();
const long EadorConfigEditorFrame::idMenuQuit = wxNewId();
const long EadorConfigEditorFrame::idMenuAbout = wxNewId();
const long EadorConfigEditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EadorConfigEditorFrame,wxFrame)
    //(*EventTable(EadorConfigEditorFrame)
    //*)
END_EVENT_TABLE()

EadorConfigEditorFrame::EadorConfigEditorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EadorConfigEditorFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Eador config editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(640,480));
    SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    BoxSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuSave, _("Сохранить\tCtrl-S"), _("Сохранить изменения"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Выход\tAlt-F4"), _("Выйти из программы"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("Файл"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("О программе\tF1"), _("Показать информацию о программе"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Помощь"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();

    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EadorConfigEditorFrame::OnSave);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EadorConfigEditorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EadorConfigEditorFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&EadorConfigEditorFrame::OnClose);
    //*)

    pFrame = this;
    SetIcon(wxICON(aaaa));
    LoadRussian();
    if (!LoadConfig()) Close();

    GenerateForm();
}

EadorConfigEditorFrame::~EadorConfigEditorFrame()
{
    //(*Destroy(EadorConfigEditorFrame)
    //*)
}

void EadorConfigEditorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EadorConfigEditorFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxString msg = "Программа: Eador config editor\nАвтор: Synoecium\nВерсия: ";
    msg<<gVersion;
    wxMessageBox(msg, _("О программе \"Eador config editor\""));
}

void EadorConfigEditorFrame::OnClose(wxCloseEvent& event)
{
    if (!event.CanVeto())
    {
        Destroy();
        return;
    }
    bool isDestroy = false;
    if (gIsChanged)
    {
        wxMessageDialog dlg(this, "Сохранить изменения перед выходом?", "Есть изменения", wxYES_NO|wxCANCEL|wxCENTRE);
        int res = dlg.ShowModal();
        if (res==wxID_YES)
        {
            SaveChanges();
            isDestroy = true;
        }
        else if (res==wxID_NO)
        {
            isDestroy = true;
        }
    }
    else isDestroy = true;

    if (isDestroy) Destroy();
    else event.Veto();
}

void EadorConfigEditorFrame::OnSave(wxCommandEvent& event)
{
    SaveChanges();
    gIsChanged = false;
    SetTitle(formTitle);
}

void StatusedStaticText::OnMouseEnter(wxMouseEvent& event)
{
     pFrame->SetStatusText(m_status);
};

void StatusedStaticText::OnMouseLeave(wxMouseEvent& event)
{
     pFrame->SetStatusText("");
};

void StatusedTextCtrl::OnMouseEnter(wxMouseEvent& event)
{
     pFrame->SetStatusText(m_status);
};

void StatusedTextCtrl::OnMouseLeave(wxMouseEvent& event)
{
     pFrame->SetStatusText("");
};
