/***************************************************************
 * Name:      EadorConfigEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Synoecium ()
 * Created:   2016-03-17
 * Copyright: Synoecium ()
 * License:
 **************************************************************/

#ifndef EADORCONFIGEDITORMAIN_H
#define EADORCONFIGEDITORMAIN_H

//(*Headers(EadorConfigEditorFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/scrolwin.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/valnum.h>
#include <wx/msgdlg.h>
#include <map>

struct tRecord{
    wxString key;
    wxString name;
    wxString description;
    int value;
};

struct tArea{
    wxString key;
    wxString name;
    wxVector<tRecord> value;
};

struct tTranslate
{
    wxString name;
    wxString description;
};




class MySubScrolledWindow : public wxScrolledWindow
{
public:
    MySubScrolledWindow(wxWindow *parent)
        : wxScrolledWindow(parent, wxID_ANY)
    {
        SetScrollbars(10, 10, 50, 50);
        Connect(wxEVT_SIZE, wxSizeEventHandler(MySubScrolledWindow::OnSize));
    }

private:
    void OnSize(wxSizeEvent& WXUNUSED(event))
    {
        Layout();
        AdjustScrollbars();
    }
};

class StatusedStaticText : public wxStaticText
{
public:
    StatusedStaticText(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition,
                       const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxStaticTextNameStr)
                       : wxStaticText(parent, id, label, pos, size, style, name)
    {

    }
    void SetStatus(wxString newStatus){m_status = newStatus;};
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

private:
    wxString m_status;

};

class StatusedTextCtrl : public wxTextCtrl
{
public:
    StatusedTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos=wxDefaultPosition,
                       const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr)
                       : wxTextCtrl(parent, id, value, pos, size, style, validator, name)
    {

    }
    void SetStatus(wxString newStatus){m_status = newStatus;};
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

private:
    wxString m_status;

};


class EadorConfigEditorFrame: public wxFrame
{
    public:

        EadorConfigEditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EadorConfigEditorFrame();

        wxVector<tArea> gConfig;
        bool gIsChanged = false;
        bool gIsInitialized = false;
        bool LoadConfig();
        void GenerateForm();
        void SaveChanges();
        void LoadRussian();
        void OnTextCtrlAnyText(wxCommandEvent& event);
        wxString formTitle = "Eador config editor";
        wxString gVersion = "1.2";
        std::map<wxString,tTranslate> russianLang;

    private:

        //(*Handlers(EadorConfigEditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnSave(wxCommandEvent& event);
        //*)

        //(*Identifiers(EadorConfigEditorFrame)
        static const long ID_NOTEBOOK1;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(EadorConfigEditorFrame)
        wxNotebook* Notebook1;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

static EadorConfigEditorFrame* pFrame;

#endif // EADORCONFIGEDITORMAIN_H
