#include "EadorConfigEditorMain.h"
#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/scrolwin.h>
#include <wx/valnum.h>

bool EadorConfigEditorFrame::LoadConfig()
 {
    wxString sFileName = "Eador.cfg";
    if (!wxFileExists(sFileName))
    {
        wxMessageBox("�� ������ ���� ������������ Eador.cfg. ��������� ����� �������.","��������������");
        return false;
    }

    wxTextFile fConfig;
    fConfig.Open(sFileName,wxConvLocal);
    wxString str;
    for ( str = fConfig.GetFirstLine(); !fConfig.Eof(); str = fConfig.GetNextLine() )
    {
        //wxMessageBox(str);
        if (str.IsEmpty()) continue;
        else if (str.StartsWith("***"))
        {
            tArea newArea;
            newArea.key = str.Mid(3,str.Len()-6);
            std::map<wxString,tTranslate>::iterator it = russianLang.find(newArea.key);
            if (it!=russianLang.end()) newArea.name = it->second.name;
            else newArea.name = newArea.key;
            gConfig.push_back(newArea);
        }
        else if(gConfig.size()>0)
        {
            int pos = str.Find(":");
            if (pos == wxNOT_FOUND) continue;
            tRecord newRecord;
            newRecord.key = str.Mid(0,pos);
            long val;
            str.Mid(pos+1).ToLong(&val);
            newRecord.value = val;
            std::map<wxString,tTranslate>::iterator it = russianLang.find(newRecord.key);
            if (it!=russianLang.end())
            {
                newRecord.name = it->second.name;
                newRecord.description = it->second.description;
            }
            else
            {
                //wxMessageBox("not found "+newRecord.key);
                newRecord.name = newRecord.key;
            }
            gConfig[gConfig.size()-1].value.push_back(newRecord);
            //wxMessageBox("key = "+str.Mid(0,pos)+" value = "+str.Mid(pos+1));
        }

    }

    return true;
    //wxTextFile
 }

 void EadorConfigEditorFrame::GenerateForm()
 {
    for (unsigned int i=0;i<gConfig.size();i++)
    {
        //wxPanel* newPanel = new wxPanel(Notebook1, wxNewId(), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "");
        //MySubScrolledWindow* newPanel = new MySubScrolledWindow(Notebook1, wxNewId(), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxVSCROLL|wxHSCROLL, "");
        MySubScrolledWindow* newPanel = new MySubScrolledWindow(Notebook1);
        wxFlexGridSizer* newSizer = new wxFlexGridSizer(0, 2, 0, 0);

        for (unsigned int j=0;j<gConfig[i].value.size();j++)
        {

            //wxStaticText* newText = new wxStaticText(newPanel, wxNewId(), gConfig[i].value[j].name, wxDefaultPosition, wxDefaultSize, 0, "");
            //newText->Connect(wxEVT_ENTER_WINDOW,(wxObjectEventFunction)&EadorConfigEditorFrame::OnMouseEnter);
            StatusedStaticText* newText = new StatusedStaticText(newPanel, wxNewId(), gConfig[i].value[j].name, wxDefaultPosition, wxDefaultSize, 0, "");
            newText->SetStatus(gConfig[i].value[j].key);
            newText->Connect(wxEVT_ENTER_WINDOW,(wxObjectEventFunction)&StatusedStaticText::OnMouseEnter);
            newText->Connect(wxEVT_LEAVE_WINDOW,(wxObjectEventFunction)&StatusedStaticText::OnMouseLeave);

            newText->SetToolTip(gConfig[i].value[j].description);
            newText->GetToolTip()->SetAutoPop(20000);
            newSizer->Add(newText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
            //wxString valStr = "";
            //valStr<<gConfig[i].value[j].value;
            wxIntegerValidator<int> val(&gConfig[i].value[j].value, wxNUM_VAL_THOUSANDS_SEPARATOR);
            //wxIntegerValidator<int>* val = new wxIntegerValidator<int>(&gConfig[i].value[j].value, wxNUM_VAL_THOUSANDS_SEPARATOR);
            long ctrlID = wxNewId();
            StatusedTextCtrl* newControl = new StatusedTextCtrl(newPanel, ctrlID, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, val, "");
            newControl->SetStatus(gConfig[i].value[j].key);
            newControl->Connect(wxEVT_ENTER_WINDOW,(wxObjectEventFunction)&StatusedTextCtrl::OnMouseEnter);
            newControl->Connect(wxEVT_LEAVE_WINDOW,(wxObjectEventFunction)&StatusedTextCtrl::OnMouseLeave);
            //newControl->SetHeplText("Hint");

            //wxTextCtrl* newControl = new wxTextCtrl(newPanel, wxNewId(), wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "");
            //newControl->SetValidator(wxIntegerValidator<int>(&gConfig[i].value[j].value, wxNUM_VAL_THOUSANDS_SEPARATOR));
            //newControl->TransferDataToWindow();
            newSizer->Add(newControl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
            Connect(ctrlID,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&EadorConfigEditorFrame::OnTextCtrlAnyText);

        }

        newPanel->SetSizer(newSizer);
        newSizer->Fit(newPanel);
        newSizer->SetSizeHints(newPanel);
        Notebook1->AddPage(newPanel, gConfig[i].name, false);
        //SetScrollbar(wxVERTICAL, 0, 16, 50);

    }
    TransferDataToWindow();
    gIsInitialized = true;
    //SetStatusText("TestTExt");


    /*Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);

    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("45456645644"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer1->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Notebook1->AddPage(Panel1, _("New page"), false);
    Notebook1->AddPage(Panel2, _("New page"), false);
    */
 }

 void EadorConfigEditorFrame::SaveChanges()
 {

     TransferDataFromWindow();
    //testVal->Validate(testCtrl);

     /*wxString test;
     test<<gConfig[0].value[0].value;
     wxMessageBox(test);*/

     wxString sFileName = "Eador.cfg";
     wxTextFile fConfig;
     if (!fConfig.Create(sFileName))
        fConfig.Open(sFileName);
     fConfig.Clear();

     for (unsigned int i=0;i<gConfig.size();i++)
     {
         fConfig.AddLine("***"+gConfig[i].key+"***");
         for (unsigned int j=0;j<gConfig[i].value.size();j++)
         {
             wxString str;
             str<<gConfig[i].value[j].key<<": "<<gConfig[i].value[j].value;
             fConfig.AddLine(str);
         }
         fConfig.AddLine(wxEmptyString);

     }
     fConfig.Write();


 }

 void EadorConfigEditorFrame::OnTextCtrlAnyText(wxCommandEvent& event)
 {
     if (!gIsChanged && gIsInitialized)
     {
         gIsChanged = true;
         SetTitle(formTitle+"*");
     }
 }



void EadorConfigEditorFrame::LoadRussian()
{
    russianLang["MAIN SETTINGS"].name                        = "�������� ���������";
    russianLang["Sound (0 - off/1 - on)"].name               = "���� (0 - ���/1 - ��)";
    russianLang["Windowed (0 - off/1 - on)"].name            = "������� ����� (0 - ���/1 - ��)";
    russianLang["Run background (0 - off/1 - on)"].name      = "�������� � ���� (0 - ���/1 - ��)";          //???
    russianLang["Refresh delay (default 40)"].name           = "�������� ���������� (�� ��������� 40)";
    russianLang["Poll mouse delay (default 25)"].name        = "�������� ������ ���� (�� ��������� 25)";
    russianLang["Keyboard delay (default 500)"].name         = "�������� ���������� (�� ��������� 500)";
    russianLang["Keyboard repeat (default 500)"].name        = "������ ���������� (�� ��������� 500)";
    russianLang["Sound buffer (default 20000)"].name         = "�������� ����� (�� ��������� 20000)";
    russianLang["Color depth (16/24/32, default 32)"].name   = "������� ����� (16/24/32, �� ��������� 32)";
    russianLang["Sleep time (default 50)"].name              = "����� ��� (�� ��������� 50)";               //????
    russianLang["Antiblink Delay (default 1)"].name          = "�������� �� �������� (�� ��������� 1)";
    russianLang["YuPlay (0 - off/1 - on)"].name              = "YuPlay (0 - ���/1 - ��)";
    russianLang["Intro (0 - off/1 - on)"].name               = "�������� (0 - ���/1 - ��)";
    russianLang["Wallpaper (0 - off/1 - on)"].name           = "���� (0 - ���/1 - ��)";                      //??

    russianLang["GAMEPLAY PARAMS"].name                      = "��������� ��������";
    russianLang["Static loot (0 - off/1 - on)"].name         = "���������� ��� (0 - ���/1 - ��)";
    russianLang["Static event (0 - off/1 - on)"].name        = "���������� ������� (0 - ���/1 - ��)";
    russianLang["Resource price modifier (default 5)"].name  = "����������� ���� �������� (�� ��������� 5)";
    russianLang["Max percentage profit (default 500)"].name  = "������������ ������� ������� (�� ��������� 500)";
    russianLang["Mercenary change time (default 7)"].name    = "����� ����� �������� (�� ��������� 7)";
    russianLang["Event possibility (default 30)"].name       = "����������� ������� (�� ��������� 30)";
    russianLang["Max battle duration (default 40)"].name     = "������������ ������������ ��� (�� ��������� 40)";

    russianLang["ADDITIONAL SETTINGS"].name                  = "�������������� ���������";
    russianLang["Max illustration (default 107, max 300)"].name              = "���������� ����������� (�� ��������� 107, ����. 300)";
    russianLang["Max herb (default 26, max 150)"].name                       = "���������� ������ (�� ��������� 26, ����. 150)";
    russianLang["Max avatar portrait (default 21, max 100)"].name            = "���������� �������� (�� ��������� 21, ����. 100)";
    russianLang["Max path (default 20)"].name                                = "������������ ���� (�� ��������� 20)";
    russianLang["Lake ships (0 - off/1 - on, default 0)"].name               = "������� � ����� (0 - ���/1 - ��, �� ��������� 0)";
    russianLang["Manual guard control (0 - off/1 - on, default 0)"].name     = "������ ���������� ������� (0 - ���/1 - ��, �� ��������� 0)";
    russianLang["Skip tutorial (0 - off/1 - on, default 0)"].name            = "���������� �������� (0 - ���/1 - ��, �� ��������� 0)";
    russianLang["Choice of basic skill (0 - off/1 - on, default 0)"].name    = "����� ���������� ������ (0 - ���/1 - ��, �� ��������� 0)";
    russianLang["Animation (0 - off/1 - on, default 1)"].name                = "�������� (0 - ���/1 - ��, �� ��������� 1)";

//------------------------------------------- DESCRIPTION -------------------------------------------------
    //MAIN SETTINGS
    russianLang["Sound (0 - off/1 - on)"].description               = "�������� ���� � ����";
    russianLang["Windowed (0 - off/1 - on)"].description            = "��������� ���� � ���� 1024�768";
    russianLang["Run background (0 - off/1 - on)"].description      = "���� ���������� ��������, ����� ���� ���������";          //???
    russianLang["Refresh delay (default 40)"].description           = "����� ����� ����������� ����������� ������ � �������������. ������ �� �������� �������� � ��� (��� ������, ��� ������� ��������)";
    russianLang["Poll mouse delay (default 25)"].description        = "���� ���� ����� ��������� ����� ��������� ����� ����, ����� ����� �������������������� � ���� ����������";
    russianLang["Keyboard delay (default 500)"].description         = "";
    russianLang["Keyboard repeat (default 500)"].description        = "";
    russianLang["Sound buffer (default 20000)"].description         = "";
    russianLang["Color depth (16/24/32, default 32)"].description   = "���� ���� ������������ ������� �������, ����� ����������� ��������� 16";
    russianLang["Sleep time (default 50)"].description              = "����� ������ �� �������� �������� � ��� (��� ������, ��� ������� ��������)";               //????
    russianLang["Antiblink Delay (default 1)"].description          = "���� � ���� ����������� ��������� ������� ������, ����� ����������� ��������� 1 ��� 2";
    russianLang["YuPlay (0 - off/1 - on)"].description              = "���������� � �������� ��������������� YuPlay, ������ �����������";
    russianLang["Intro (0 - off/1 - on)"].description               = "����������� �������� ��� ������� ����";
    russianLang["Wallpaper (0 - off/1 - on)"].description           = "���������� �� �������� � ������� �� ����� �������� ���� (���� ��) ��� ��� (����� ����� ������������ �������������� �����)";

    //GAMEPLAY PARAMS
    russianLang["Static loot (0 - off/1 - on)"].description         = "������� �� ��� ����� ����������� ��� �������� � ������� (�� ����� �� ������ �����������)";
    russianLang["Static event (0 - off/1 - on)"].description        = "������� ����� ����������� ��� �������� � ������� (�� ����� �� ������ �����������)";
    russianLang["Resource price modifier (default 5)"].description  = "������� ��������� �������� ����� �� �������, ��� ���� ���� �� ������� ����� ��� ���� �������";
    russianLang["Max percentage profit (default 500)"].description  = "������������ ��������� ����� � ��������� �� ������ ���� \"������������\" (������ � ��� ������ �������� �� ������ ������ � ������)";
    russianLang["Mercenary change time (default 7)"].description    = "����� ������� ����� ����� ����������� ��������� � ��������� ������";
    russianLang["Event possibility (default 30)"].description       = "��������� ��� ����������� ������� (������� ������, ��� �� ��� ������� ��������)";
    russianLang["Max battle duration (default 40)"].description     = "�� ��������� ������������ ������������ ��� �������� �����, � ������� ����������";

    //ADDITIONAL SETTINGS
    russianLang["Max illustration (default 107, max 300)"].description              = "������������ ���������� ����������� (����� ������, ���� ����������� ����� �����������, �������� ��� �������� ����� �������)";
    russianLang["Max herb (default 26, max 150)"].description                       = "������������ ���������� ������ (����� ������, ���� ����������� ����� �����)";
    russianLang["Max avatar portrait (default 21, max 100)"].description            = "������������ ���������� ��������� ������ (����� ������, ���� ����������� ����� ��������)";
    russianLang["Max path (default 20)"].description                                = "������������ ����� ���� ����� ��������� �� �������������� ����� (��� ������ �����, ��� ������ �� ����������� �������)";
    russianLang["Lake ships (0 - off/1 - on, default 0)"].description               = "���� ��������, �� ����� ������� ����� � ���������� ����� � ������ (����, �� ���������� ������ �����)";
    russianLang["Manual guard control (0 - off/1 - on, default 0)"].description     = "���� ��������, �� ��� ��������� �� ������ �������� ������� ���������� ������� �������";
    russianLang["Skip tutorial (0 - off/1 - on, default 0)"].description            = "���������� �������� ��� ������ ����� ��������";
    russianLang["Choice of basic skill (0 - off/1 - on, default 0)"].description    = "���� ��������, �� ��� ����� ������ ����� ����� ������� ��������� �����";
    russianLang["Animation (0 - off/1 - on, default 1)"].description                = "���� ��������, �� � ��� � ��������� �������� ���������� �������������� ��������";

}


