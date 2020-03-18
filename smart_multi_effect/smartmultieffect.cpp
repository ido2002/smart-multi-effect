#include "smartmultieffect.h"
#include "conf.h"
#include <unistd.h>
#include <iostream>

SmartMultiEffect::SmartMultiEffect()
{
    buttonsTimer = new MyTimer();

    InitializeEffects();
    InitializeGui();
    InitializeButtons();
    InitializeSoundProcessor();
    InitializeMenu();

    UpdateWindow();
}

SmartMultiEffect::~SmartMultiEffect()
{
    if(buttonsTimer) {
        if(buttonsTimer->isRunning())
            buttonsTimer->stop();
        delete buttonsTimer;
    }

    if(controller) {
        delete controller;
    }

    if(guiManager) {
        guiManager->getPresetsWindow()->SaveAll();
        guiManager->getSongsWindow()->SaveAll();
        delete guiManager;
    }

    if(soundProcessor) {
        delete soundProcessor;
    }

    if(riffRecognition) {
        delete riffRecognition;
    }
}

void SmartMultiEffect::Run()
{
    soundProcessor->Start();
    buttonsTimer->start(10);
}

void SmartMultiEffect::InitializeEffects()
{
    using namespace hardware_ctrl;
    using namespace CONF::HARDWARE;
    controller = new EffectController(INC_PIN, UD_PIN);
    controller->Initialize();
    controller->SetAllToValue_Long();
}

void SmartMultiEffect::InitializeGui()
{
    using namespace GUI_elements;
    guiManager = new GuiManager;
}

void SmartMultiEffect::InitializeButtons()
{
    using namespace CONF::GUI_PARAMETERS::CUSTON_BUTTON;
    using namespace CONF::HARDWARE;
    controller->AddButton(BUTTON_1.toStdString(), BUTTON1);
    controller->AddButton(BUTTON_2.toStdString(), BUTTON2);
    controller->AddButton(BUTTON_3.toStdString(), BUTTON3);
    controller->AddButton(BUTTON_4.toStdString(), BUTTON4);
    controller->AddButton(BUTTON_5.toStdString(), BUTTON5);

    BindHardwareButtonToGuiButton(*(new std::string(BUTTON_1.toStdString())), *(new std::string(BUTTON_1.toStdString())));
    BindHardwareButtonToGuiButton(*(new std::string(BUTTON_2.toStdString())), *(new std::string(BUTTON_2.toStdString())));
    BindHardwareButtonToGuiButton(*(new std::string(BUTTON_3.toStdString())), *(new std::string(BUTTON_3.toStdString())));
    BindHardwareButtonToGuiButton(*(new std::string(BUTTON_4.toStdString())), *(new std::string(BUTTON_4.toStdString())));
    BindHardwareButtonToGuiButton(*(new std::string(BUTTON_5.toStdString())), *(new std::string(BUTTON_5.toStdString())));

    buttonsTimer->AddFunction([&](){
        Update();
    });
}

void SmartMultiEffect::InitializeSoundProcessor()
{
    using namespace sound_processing;

    riffRecognition = new RiffRecognition();
    soundProcessor = new SoundProcessor();
}

void SmartMultiEffect::InitializePresets()
{
    if(!guiManager->getPresetsWindow()->LoadAll()) {
        using element = hardware_ctrl::Effect::EffectControlLayoutEllements;
        using colors = hardware_ctrl::ColorSet;
        using namespace CONF::GUI_PARAMETERS::COLORS;
        using namespace CONF::NAMES;
        using map = std::map<element, int>;
        using pair = std::pair<element, int>;

        hardware_ctrl::Preset basicPreset(
        {new hardware_ctrl::EffectInfo(colors(BROWN, WHITE, WHITE), OVERDRIVE, false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_MAGENTA, WHITE, WHITE), TREMOLO, false, map({
                  pair(element::Depth, 50),
                  pair(element::Speed, 50),
                  pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_GREEN, WHITE, WHITE), DELAY, false, map({
                  pair(element::Regen, 50),
                  pair(element::Mix, 50),
                  pair(element::Delay, 50)
         }))}, 0, 0);

        PresetWindow* pw1 = new PresetWindow("rock");
        pw1->setP1(new Preset("rock", "clean", new hardware_ctrl::Preset(
        {new hardware_ctrl::EffectInfo(colors(BROWN, WHITE, WHITE), OVERDRIVE, false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_MAGENTA, WHITE, WHITE), TREMOLO, true, map({
                  pair(element::Depth, 50),
                  pair(element::Speed, 50),
                  pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_GREEN, WHITE, WHITE), DELAY, true, map({
                  pair(element::Regen, 50),
                  pair(element::Mix, 50),
                  pair(element::Delay, 50)
         }))}, 0, 0), guiManager->getEngine(), guiManager->getViewArea()));

        pw1->setP2(new Preset("rock", "low gain", new hardware_ctrl::Preset(
        {new hardware_ctrl::EffectInfo(colors(BROWN, WHITE, WHITE), OVERDRIVE, true, map({
             pair(element::Gain, 10),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_MAGENTA, WHITE, WHITE), TREMOLO, false, map({
                  pair(element::Depth, 50),
                  pair(element::Speed, 50),
                  pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_GREEN, WHITE, WHITE), DELAY, true, map({
                  pair(element::Regen, 50),
                  pair(element::Mix, 50),
                  pair(element::Delay, 50)
         }))}, 0, 0), guiManager->getEngine(), guiManager->getViewArea()));

        pw1->setP3(new Preset("rock", "high gain", new hardware_ctrl::Preset(
        {new hardware_ctrl::EffectInfo(colors(BROWN, WHITE, WHITE), OVERDRIVE, true, map({
             pair(element::Gain, 100),
             pair(element::Tone, 70),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_MAGENTA, WHITE, WHITE), TREMOLO, false, map({
                  pair(element::Depth, 50),
                  pair(element::Speed, 50),
                  pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_GREEN, WHITE, WHITE), DELAY, true, map({
                  pair(element::Regen, 50),
                  pair(element::Mix, 50),
                  pair(element::Delay, 50)
         }))}, 0, 0), guiManager->getEngine(), guiManager->getViewArea()));

        pw1->setP4(new Preset("rock", "all off", new hardware_ctrl::Preset(basicPreset),
                              guiManager->getEngine(), guiManager->getViewArea()));
        guiManager->getPresetsWindow()->AddPresetWindow(pw1);

        PresetWindow* pw2 = new PresetWindow("test");
        pw2->setP1(new Preset("test", "6 effects", new hardware_ctrl::Preset(
        {new hardware_ctrl::EffectInfo(colors(BROWN, WHITE, WHITE), OVERDRIVE, false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_MAGENTA, WHITE, WHITE), TREMOLO, false, map({
                  pair(element::Depth, 50),
                  pair(element::Speed, 50),
                  pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_GREEN, WHITE, WHITE), DELAY, false, map({
                  pair(element::Regen, 50),
                  pair(element::Mix, 50),
                  pair(element::Delay, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_RED, WHITE, WHITE), "comp", false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(DARK_BLUE, WHITE, WHITE), "chorus", false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)})),
         new hardware_ctrl::EffectInfo(colors(GREY, WHITE, WHITE), "deth Metal", false, map({
             pair(element::Gain, 50),
             pair(element::Tone, 50),
             pair(element::Volume, 50)}))
        }, 0, 0), guiManager->getEngine(), guiManager->getViewArea()));

        pw2->setP2(new Preset("test", "empty", new hardware_ctrl::Preset(
        {}, 0, 0), guiManager->getEngine(), guiManager->getViewArea()));
        guiManager->getPresetsWindow()->AddPresetWindow(pw2);

        for(int i = 2; i <= 99; i++) {
            PresetWindow* pw = new PresetWindow(QString::number(i));
            pw->setP1(new Preset(QString::number(i), "1", new hardware_ctrl::Preset(basicPreset),
                                  guiManager->getEngine(), guiManager->getViewArea()));
            pw->setP2(new Preset(QString::number(i), "2", new hardware_ctrl::Preset(basicPreset),
                                  guiManager->getEngine(), guiManager->getViewArea()));
            pw->setP3(new Preset(QString::number(i), "3", new hardware_ctrl::Preset(basicPreset),
                                  guiManager->getEngine(), guiManager->getViewArea()));
            pw->setP4(new Preset(QString::number(i), "4", new hardware_ctrl::Preset(basicPreset),
                                  guiManager->getEngine(), guiManager->getViewArea()));
            guiManager->getPresetsWindow()->AddPresetWindow(pw);
        }
        guiManager->getPresetsWindow()->SaveAll();
    }
}

void SmartMultiEffect::InitializeSongs()
{
    if(!guiManager->getSongsWindow()->LoadAll()) {
        guiManager->getSongsWindow()->AddSet(new AutoSwitchSetWindowEdit("sweet child O' mine", guiManager->getEngine(), guiManager->getViewArea()));
        guiManager->getSongsWindow()->AddSet(new AutoSwitchSetWindowEdit("fade to black", guiManager->getEngine(), guiManager->getViewArea()));
        guiManager->getSongsWindow()->AddSet(new AutoSwitchSetWindowEdit("test", guiManager->getEngine(), guiManager->getViewArea()));

        for(int i = 4; i < 10; i++) {
            guiManager->getSongsWindow()->AddSet(new AutoSwitchSetWindowEdit(QString::number(i), guiManager->getEngine(), guiManager->getViewArea()));
        }
        guiManager->getSongsWindow()->SaveAll();
    }
}

void SmartMultiEffect::InitializeMenu()
{
    guiManager->getMenu()->AddItem(new MenuItem("test", [&](){
        return (int)WindowState::test;
    }));

    guiManager->getMenu()->AddItem(new MenuItem("record", [&](){
        return (int)WindowState::recordNote;
    }));

//    guiManager->getMenu()->AddItem(new MenuItem("rec-o", [&](){
//        return (int)WindowState::recordOctave;
//    }));

    guiManager->getMenu()->AddItem(new MenuItem("train", [&](){
        return (int)WindowState::train;
    }));
}

void SmartMultiEffect::SetButtonsFunctions()
{
    using namespace CONF::GUI_PARAMETERS::CUSTON_BUTTON;
    using namespace GUI_elements;

    GuiButton* button1 = guiManager->getButtonByName(BUTTON_1.toStdString());
    GuiButton* button2 = guiManager->getButtonByName(BUTTON_2.toStdString());
    GuiButton* button3 = guiManager->getButtonByName(BUTTON_3.toStdString());
    GuiButton* button4 = guiManager->getButtonByName(BUTTON_4.toStdString());
    GuiButton* button5 = guiManager->getButtonByName(BUTTON_5.toStdString());

    button1->ClearFunctions();
    button2->ClearFunctions();
    button3->ClearFunctions();
    button4->ClearFunctions();
    button5->ClearFunctions();


    button1->ResetTextColor();
    button2->ResetTextColor();
    button3->ResetTextColor();
    button4->ResetTextColor();
    button5->ResetTextColor();

    switch (windowState) {
    case test:
        button1->SetText("back");
        button2->SetText("volume");
        button3->SetText("fft");
        button4->SetText("notes");
        button5->SetText("octave");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
           TestGui::show_volume_test(*soundProcessor, 300, 400);
        });
        button3->AddFunction([&](){
           TestGui::show_fft_test(*soundProcessor, 800, 400, 0, 0.05, 8);
        });
        button4->AddFunction([&](){
           TestGui::show_notes_test(*soundProcessor, 600, 400);
        });
        button5->AddFunction([&](){
           TestGui::show_octave_test(*soundProcessor, 400, 400);
        });
        break;

    case songs:
        button1->SetText("menu");
        button2->SetText("presets");
        button3->SetText("<");
        button4->SetText(">");
        button5->SetText("choose");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::GREEN);

        button1->AddFunction([&](){
            lastWindowState = songs;
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            windowState = presets;
            updateWindowFlag = true;
        });
        button3->AddFunction([&](){
            guiManager->getSongsWindow()->left();
        });
        button4->AddFunction([&](){
            guiManager->getSongsWindow()->right();
        });
        button5->AddFunction([&](){
            guiManager->getSongsWindow()->choose();
            windowState = song;
            updateWindowFlag = true;
        });
        break;

    case presets:
        button1->SetText("menu");
        button2->SetText("songs");
        button3->SetText("<");
        button4->SetText(">");
        button5->SetText("choose");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::GREEN);

        button1->AddFunction([&](){
            lastWindowState = presets;
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            windowState = songs;
            updateWindowFlag = true;
        });
        button3->AddFunction([&](){
            guiManager->getPresetsWindow()->left();
        });
        button4->AddFunction([&](){
            guiManager->getPresetsWindow()->right();
        });
        button5->AddFunction([&](){
            guiManager->getPresetsWindow()->choose();
            windowState = preset;
            updateWindowFlag = true;
        });
        break;

    case song:
        if(guiManager->getSongsWindow()->getCurrentSet() == nullptr) {
            windowState = songs;
            UpdateWindow();
            return;
        }
        button1->SetText(guiManager->getSongsWindow()->getCurrentSet()->getName_1());
        button2->SetText(guiManager->getSongsWindow()->getCurrentSet()->getName_2());
        button3->SetText(guiManager->getSongsWindow()->getCurrentSet()->getName_3());
        button4->SetText("auto");
        button5->SetText("back");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::GREEN);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);

        button1->AddFunction([&](){
            guiManager->getSongsWindow()->getCurrentSet()->activate_1(controller, guiManager->getPresetsWindow());
        });
        button2->AddFunction([&](){
            guiManager->getSongsWindow()->getCurrentSet()->activate_2(controller, guiManager->getPresetsWindow());
        });
        button3->AddFunction([&](){
            guiManager->getSongsWindow()->getCurrentSet()->activate_3(controller, guiManager->getPresetsWindow());
        });
        button4->AddFunction([&](){
            if(guiManager->getButtonByName(BUTTON_4.toStdString())->getText() == "stop") {
                guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("auto");
                //button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::GREEN);
                guiManager->getSongsWindow()->getCurrentSet()->autoMod(false);
            } else if (guiManager->getButtonByName(BUTTON_4.toStdString())->getText() == "auto") {
                guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("stop");
                //button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
                guiManager->getSongsWindow()->getCurrentSet()->autoMod(true);
            }
        });
        button5->AddFunction([&](){
            windowState = songs;
            updateWindowFlag = true;
        });
        break;

    case preset:
        if(guiManager->getPresetsWindow()->getCurrentPreset() == nullptr) {
            windowState = presets;
            UpdateWindow();
            return;
        }
        {
            auto cp = guiManager->getPresetsWindow()->getCurrentPreset();
            if(cp->getP1())
                button1->SetText(cp->getP1()->getName());
            else button1->SetText("");
            if(cp->getP2())
                button2->SetText(cp->getP2()->getName());
            else button2->SetText("");
            if(cp->getP3())
                button3->SetText(cp->getP3()->getName());
            else button3->SetText("");
            if(cp->getP4())
                button4->SetText(cp->getP4()->getName());
            else button4->SetText("");
        }
        button5->SetText("back");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);

        if(button1->getText() != "")
            button1->AddFunction([&](){
                auto p = guiManager->getPresetsWindow()->getCurrentPreset();
                p->setActivePreset(p->getP1());
                updateWindowFlag = true;
            });
        if(button2->getText() != "")
            button2->AddFunction([&](){
                auto p = guiManager->getPresetsWindow()->getCurrentPreset();
                p->setActivePreset(p->getP2());
                updateWindowFlag = true;
            });
        if(button3->getText() != "")
            button3->AddFunction([&](){
                auto p = guiManager->getPresetsWindow()->getCurrentPreset();
                p->setActivePreset(p->getP3());
                updateWindowFlag = true;
            });
        if(button4->getText() != "")
            button4->AddFunction([&](){
                auto p = guiManager->getPresetsWindow()->getCurrentPreset();
                p->setActivePreset(p->getP4());
                updateWindowFlag = true;
            });
        button5->AddFunction([&](){
            guiManager->getPresetsWindow()->getCurrentPreset()->getActivePreset()->Save();
            windowState = presets;
            updateWindowFlag = true;
        });
        break;

    case menu:
        button1->SetText("back");
        button2->SetText("<");
        button3->SetText(">");
        button4->SetText(guiManager->getMenu()->getCurrent(0)->getName());
        button5->SetText(guiManager->getMenu()->getCurrent(1)->getName());
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = lastWindowState;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            guiManager->getMenu()->left();
            updateWindowFlag = true;
        });
        button3->AddFunction([&](){
            guiManager->getMenu()->right();
            updateWindowFlag = true;
        });
        button4->AddFunction([&](){
            windowState = (WindowState)guiManager->getMenu()->getCurrent(0)->onClick();
            updateWindowFlag = true;
        });
        button5->AddFunction([&](){
            windowState = (WindowState)guiManager->getMenu()->getCurrent(1)->onClick();
            updateWindowFlag = true;
        });
        break;

    case recordNote:
        button1->SetText("back");
        button2->SetText("^");
        button3->SetText("add");
        button4->SetText("remove");
        button5->SetText("record");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            guiManager->getRecordNotePage()->up();
        });
        button3->AddFunction([&](){
            guiManager->getRecordNotePage()->add();
        });
        button4->AddFunction([&](){
            guiManager->getRecordNotePage()->remove();
        });
        button5->AddFunction([&](){
            guiManager->getRecordNotePage()->record(soundProcessor);
        });
        break;

    case recordOctave:
        button1->SetText("back");
        button2->SetText("^");
        button3->SetText("add");
        button4->SetText("remove");
        button5->SetText("record");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            guiManager->getRecordOctavePage()->up();
        });
        button3->AddFunction([&](){
            guiManager->getRecordOctavePage()->add();
        });
        button4->AddFunction([&](){
            guiManager->getRecordOctavePage()->remove();
        });
        button5->AddFunction([&](){
            guiManager->getRecordOctavePage()->record(soundProcessor);
        });
        break;

    case train:
        button1->SetText("back");
        button2->SetText("^");
        button3->SetText("v");
        button4->SetText("train");
        button5->SetText("save");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = menu;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
            guiManager->getTrainingPage()->up();
        });
        button3->AddFunction([&](){
            guiManager->getTrainingPage()->down();
        });
        button4->AddFunction([&](){
            guiManager->getTrainingPage()->learn(soundProcessor);
        });
        button5->AddFunction([&](){
            guiManager->getTrainingPage()->save(soundProcessor);
        });
        break;

    case manage:
        button1->SetText("back");
        button2->SetText("^");
        button3->SetText("v");
        button4->SetText("remove");
        button5->SetText("");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
            windowState = train;
            updateWindowFlag = true;
        });
        button2->AddFunction([&](){
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
        });
        button5->AddFunction([&](){
        });
        break;

    case loading:
        button1->SetText("");
        button2->SetText("");
        button3->SetText("");
        button4->SetText("");
        button5->SetText("");
        button1->ResetTextColor();
        button2->ResetTextColor();
        button3->ResetTextColor();
        button4->ResetTextColor();
        button5->ResetTextColor();

        button1->AddFunction([&](){
        });
        button2->AddFunction([&](){
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
        });
        button5->AddFunction([&](){
        });
        break;
    }
}

void SmartMultiEffect::BindHardwareButtonToGuiButton(std::string& hardwareButtonName, std::string& guiButtonName)
{
    controller->AddButtonPressEvent(hardwareButtonName, [&](hardware_ctrl::EffectController*){
        guiManager->getButtonByName(guiButtonName)->SetPressed(true);
    });
    controller->AddButtonReleaseEvent(hardwareButtonName, [&](hardware_ctrl::EffectController*){
        guiManager->getButtonByName(guiButtonName)->SetPressed(false);
    });
}

void SmartMultiEffect::Update()
{
    if(windowState == loading) {
        if(loadingThread == nullptr) {
            soundProcessor->Stop();
            loadingThread = new std::thread([&](){
                soundProcessor->getNoteRecognition().Load();
                usleep(CONF::GUI_PARAMETERS::LOAD_EXTRA_UTIME);
                windowState = lastWindowState;
        });
        }
    } else {
        if(loadingThread != nullptr) {
            loadingThread = nullptr;
            InitializePresets();
            InitializeSongs();
            guiManager->getSongsWindow()->UpdatePresets(guiManager->getPresetsWindow());
            soundProcessor->Start();
            updateWindowFlag = true;
        }
    }
    if(windowState == recordNote) {
        guiManager->getRecordNotePage()->update();
    }
    if(windowState == recordOctave) {
        guiManager->getRecordOctavePage()->update();
    }
    if(windowState == train) {
        guiManager->getTrainingPage()->update();
    }

    controller->UpdateButtons();
    guiManager->UpdateButtons();

    if(windowState == song) {
        guiManager->getSongsWindow()->getCurrentSet()->Update(controller, soundProcessor, guiManager->getPresetsWindow());
    }

    if(updateWindowFlag) {
        UpdateWindow();
        updateWindowFlag = false;
    }

    if(windowState == preset && guiManager->getPresetsWindow()->getCurrentPreset()->getActivePreset() != nullptr) {
        guiManager->getPresetsWindow()->getCurrentPreset()->getActivePreset()->Update();
        controller->SetPreset(*guiManager->getPresetsWindow()->getCurrentPreset()->getActivePreset()->getPreset());
    }
}

void SmartMultiEffect::UpdateWindow()
{
    bool buttonsTimerState = buttonsTimer->isRunning();
    buttonsTimer->stop();

    using va_content = GUI_elements::GuiManager::ViewAreaContent;

    WindowState ws = windowState;
    if(windowState == menu) ws = lastWindowState;

    switch (ws) {
    case test:
        break;

    case songs:
        guiManager->SetViewAreaTo(va_content::songs);
        break;

    case presets:
        guiManager->SetViewAreaTo(va_content::presets);
        break;

    case song:
        guiManager->SetViewAreaTo(va_content::song);
        break;

    case preset:
        guiManager->SetViewAreaTo(va_content::preset);
        break;

    case menu:
        break;

    case recordNote:
        guiManager->SetViewAreaTo(va_content::recordNote);
        break;

    case recordOctave:
        guiManager->SetViewAreaTo(va_content::recordOctave);
        break;

    case train:
        guiManager->SetViewAreaTo(va_content::train);
        break;

    case manage:
        guiManager->SetViewAreaTo(va_content::manage);
        break;

    case loading:
        guiManager->SetViewAreaTo(va_content::loading);
        break;
    }
    SetButtonsFunctions();

    if(buttonsTimerState) {
        buttonsTimer->start();
    }

}
