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
        wxMessageBox("Не найден файл конфигурации Eador.cfg. Программа будет закрыта.","Предупреждение");
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
    russianLang["MAIN SETTINGS"].name                        = "ОСНОВНЫЕ НАСТРОЙКИ";
    russianLang["Sound (0 - off/1 - on)"].name               = "Звук (0 - нет/1 - да)";
    russianLang["Windowed (0 - off/1 - on)"].name            = "Оконный режим (0 - нет/1 - да)";
    russianLang["Run background (0 - off/1 - on)"].name      = "Работать в фоне (0 - нет/1 - да)";          //???
    russianLang["Refresh delay (default 40)"].name           = "Задержка обновления (по умолчанию 40)";
    russianLang["Poll mouse delay (default 25)"].name        = "Задержка опроса мыши (по умолчанию 25)";
    russianLang["Keyboard delay (default 500)"].name         = "Задержка клавиатуры (по умолчанию 500)";
    russianLang["Keyboard repeat (default 500)"].name        = "Повтор клавиатуры (по умолчанию 500)";
    russianLang["Sound buffer (default 20000)"].name         = "Звуковой буфер (по умолчанию 20000)";
    russianLang["Color depth (16/24/32, default 32)"].name   = "Глубина цвета (16/24/32, по умолчанию 32)";
    russianLang["Sleep time (default 50)"].name              = "Время сна (по умолчанию 50)";               //????
    russianLang["Antiblink Delay (default 1)"].name          = "Задержка от мерцания (по умолчанию 1)";
    russianLang["YuPlay (0 - off/1 - on)"].name              = "YuPlay (0 - нет/1 - да)";
    russianLang["Intro (0 - off/1 - on)"].name               = "Заставка (0 - нет/1 - да)";
    russianLang["Wallpaper (0 - off/1 - on)"].name           = "Обои (0 - нет/1 - да)";                      //??

    russianLang["GAMEPLAY PARAMS"].name                      = "ПАРАМЕТРЫ ГЕЙМПЛЕЯ";
    russianLang["Static loot (0 - off/1 - on)"].name         = "Постоянный лут (0 - нет/1 - да)";
    russianLang["Static event (0 - off/1 - on)"].name        = "Постоянные события (0 - нет/1 - да)";
    russianLang["Resource price modifier (default 5)"].name  = "Модификатор цены ресурсов (по умолчанию 5)";
    russianLang["Max percentage profit (default 500)"].name  = "Максимальный процент прибыли (по умолчанию 500)";
    russianLang["Mercenary change time (default 7)"].name    = "Время смены наёмников (по умолчанию 7)";
    russianLang["Event possibility (default 30)"].name       = "Вероятность событий (по умолчанию 30)";
    russianLang["Max battle duration (default 40)"].name     = "Максимальная длительность боя (по умолчанию 40)";

    russianLang["ADDITIONAL SETTINGS"].name                  = "ДОПОЛНИТЕЛЬНЫЕ НАСТРОЙКИ";
    russianLang["Max illustration (default 107, max 300)"].name              = "Количество иллюстраций (по умолчанию 107, макс. 300)";
    russianLang["Max herb (default 26, max 150)"].name                       = "Количество гербов (по умолчанию 26, макс. 150)";
    russianLang["Max avatar portrait (default 21, max 100)"].name            = "Количество аватаров (по умолчанию 21, макс. 100)";
    russianLang["Max path (default 20)"].name                                = "Максимальный путь (по умолчанию 20)";
    russianLang["Lake ships (0 - off/1 - on, default 0)"].name               = "Корабли в озёрах (0 - нет/1 - да, по умолчанию 0)";
    russianLang["Manual guard control (0 - off/1 - on, default 0)"].name     = "Ручное управление стражей (0 - нет/1 - да, по умолчанию 0)";
    russianLang["Skip tutorial (0 - off/1 - on, default 0)"].name            = "Пропустить обучение (0 - нет/1 - да, по умолчанию 0)";
    russianLang["Choice of basic skill (0 - off/1 - on, default 0)"].name    = "Выбор начального навыка (0 - нет/1 - да, по умолчанию 0)";
    russianLang["Animation (0 - off/1 - on, default 1)"].name                = "Анимация (0 - нет/1 - да, по умолчанию 1)";

//------------------------------------------- DESCRIPTION -------------------------------------------------
    //MAIN SETTINGS
    russianLang["Sound (0 - off/1 - on)"].description               = "Включить звук в игре";
    russianLang["Windowed (0 - off/1 - on)"].description            = "Запустить игру в окне 1024х768";
    russianLang["Run background (0 - off/1 - on)"].description      = "Игра продолжает работать, когда окно неактивно";          //???
    russianLang["Refresh delay (default 40)"].description           = "Пауза между программным обновлением экрана в миллисекундах. Влияет на скорость анимации в бою (чем меньше, тем быстрее анимация)";
    russianLang["Poll mouse delay (default 25)"].description        = "Если игра стала тормозить после установки новой мыши, имеет смысл поэкспериментировать с этим параметром";
    russianLang["Keyboard delay (default 500)"].description         = "";
    russianLang["Keyboard repeat (default 500)"].description        = "";
    russianLang["Sound buffer (default 20000)"].description         = "";
    russianLang["Color depth (16/24/32, default 32)"].description   = "Если игра периодически мерцает розовым, можно попробовать поставить 16";
    russianLang["Sleep time (default 50)"].description              = "Также влияет на скорость анимации в бою (чем меньше, тем быстрее анимация)";               //????
    russianLang["Antiblink Delay (default 1)"].description          = "Если в игре наблюдается малиновый отблеск экрана, можно попробовать поставить 1 или 2";
    russianLang["YuPlay (0 - off/1 - on)"].description              = "Интеграция с системой микротранзакций YuPlay, сейчас неактуальна";
    russianLang["Intro (0 - off/1 - on)"].description               = "Проигрывать заставку при запуске игры";
    russianLang["Wallpaper (0 - off/1 - on)"].description           = "Показывать ли картинку с дриадой во время перехода хода (хода ИИ) или нет (тогда будет показываться стратегическая карта)";

    //GAMEPLAY PARAMS
    russianLang["Static loot (0 - off/1 - on)"].description         = "Награда за бой будет повторяться при возврате в прошлое (по факту не всегда срабатывает)";
    russianLang["Static event (0 - off/1 - on)"].description        = "События будут повторяться при возврате в прошлое (по факту не всегда срабатывает)";
    russianLang["Resource price modifier (default 5)"].description  = "Процент дорожания ресурсов после их покупки, при этом цена на ресурсы общая для всех игроков";
    russianLang["Max percentage profit (default 500)"].description  = "Максимальный суммарный доход в процентах от зданий типа \"сокровищница\" (золото в ход равное проценту от запаса золота у игрока)";
    russianLang["Mercenary change time (default 7)"].description    = "Через сколько ходов будет обновляться доступный в гарнизоне наёмник";
    russianLang["Event possibility (default 30)"].description       = "Множитель для вероятности событий (следует учесть, что не все события случайны)";
    russianLang["Max battle duration (default 40)"].description     = "По истечении максимальной длительности боя наступит ничья, и стороны разойдутся";

    //ADDITIONAL SETTINGS
    russianLang["Max illustration (default 107, max 300)"].description              = "Максимальное количество иллюстраций (нужно менять, если добавляются новые иллюстрации, например при создании новых событий)";
    russianLang["Max herb (default 26, max 150)"].description                       = "Максимальное количество гербов (нужно менять, если добавляются новые гербы)";
    russianLang["Max avatar portrait (default 21, max 100)"].description            = "Максимальное количество портретов владык (нужно менять, если добавляются новые портреты)";
    russianLang["Max path (default 20)"].description                                = "Максимальная длина пути через провинции на стратегической карте (чем больше цифра, тем дольше ИИ обсчитывает маршрут)";
    russianLang["Lake ships (0 - off/1 - on, default 0)"].description               = "Если включено, то можно ставить верфи в провинциях рядом с озёрами (вода, не касающаяся границ карты)";
    russianLang["Manual guard control (0 - off/1 - on, default 0)"].description     = "Если включено, то при нападении на стражу появится вариант управления стражей вручную";
    russianLang["Skip tutorial (0 - off/1 - on, default 0)"].description            = "Пропустить обучение при старте новой кампании";
    russianLang["Choice of basic skill (0 - off/1 - on, default 0)"].description    = "Если включено, то при найме нового героя можно выбрать стартовый навык";
    russianLang["Animation (0 - off/1 - on, default 1)"].description                = "Если включено, то в бою у некоторых эффектов появляется дополнительная анимация";

}


