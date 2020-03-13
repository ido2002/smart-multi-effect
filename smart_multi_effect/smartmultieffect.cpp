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

    InitializePresets();
    InitializeSongs();
    InitializeMenu();

    UpdateWindow();
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
        ButtonsUpdate();
    });
}

void SmartMultiEffect::InitializeSoundProcessor()
{
    soundProcessor = new sound_processing::SoundProcessor();
}

void SmartMultiEffect::InitializePresets()
{
    PresetFrame* pf1 = new PresetFrame("rock");
    using element = hardware_ctrl::Effect::EffectControlLayoutEllements;

    pf1->p1.name = "acdc1";
    pf1->p1.preset = hardware_ctrl::Preset({hardware_ctrl::EffectInfo(
                                            CONF::NAMES::OVERDRIVE, true,
                                            {{element::Gain, 5}, {element::Tone, 5}, {element::Volume, 50}}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::TREMOLO, false,
                                            {}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::DELAY, true,
                                            {}
                                            )}, 0, 0);
    pf1->p2.name = "acdc2";
    pf1->p2.preset = hardware_ctrl::Preset({hardware_ctrl::EffectInfo(
                                            CONF::NAMES::OVERDRIVE, true,
                                            {{element::Gain, 60}, {element::Tone, 60}, {element::Volume, 50}}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::TREMOLO, false,
                                            {}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::DELAY, true,
                                            {{element::Repeat, 50}, {element::Mix,50}, {element::Delay, 50}}
                                            )}, 0, 0);
    pf1->p3.name = "Hendrix";
    pf1->p3.preset = hardware_ctrl::Preset({hardware_ctrl::EffectInfo(
                                            CONF::NAMES::OVERDRIVE, true,
                                            {{element::Gain, 40}, {element::Tone, 40}, {element::Volume, 50}}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::TREMOLO, false,
                                            {}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::DELAY, false,
                                            {}
                                            )}, 0, 0);
    pf1->p4.name = "evh";
    pf1->p4.preset = hardware_ctrl::Preset({hardware_ctrl::EffectInfo(
                                            CONF::NAMES::OVERDRIVE, true,
                                            {{element::Gain, 100}, {element::Tone, 80}, {element::Volume, 60}}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::TREMOLO, false,
                                            {}
                                            ), hardware_ctrl::EffectInfo(
                                            CONF::NAMES::DELAY, true,
                                            {{element::Repeat, 50}, {element::Mix,50}, {element::Delay, 30}}
                                            )}, 1000, 1);
    guiManager->getPresetsWindow()->AddFrame(pf1);

    PresetFrame* pf2 = new PresetFrame("metal");
    pf2->p1.name = "metal1";
    pf2->p2.name = "metal2";
    pf2->p3.name = "jh";
    pf2->p4.name = "kh";
    guiManager->getPresetsWindow()->AddFrame(pf2);
}

void SmartMultiEffect::InitializeSongs()
{

}

void SmartMultiEffect::InitializeMenu()
{
    guiManager->getMenu()->AddItem(new MenuItem("test", [&](){
        return (int)WindowState::test;
    }));

    guiManager->getMenu()->AddItem(new MenuItem("rec-n", [&](){
        return (int)WindowState::recordNote;
    }));

    guiManager->getMenu()->AddItem(new MenuItem("rec-o", [&](){
        return (int)WindowState::recordOctave;
    }));

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
           TestGui::show_volume_test(*soundProcessor, 200, 400);
        });
        button3->AddFunction([&](){
           TestGui::show_fft_test(*soundProcessor, 800, 400, 0, 0.02, 8);
        });
        button4->AddFunction([&](){
           TestGui::show_notes_test(*soundProcessor, 400, 400);
        });
        button5->AddFunction([&](){
           TestGui::show_octave_test(*soundProcessor, 200, 400);
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
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);

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
        if(guiManager->getSongsWindow()->getCurrentSong() == nullptr) {
            windowState = songs;
            UpdateWindow();
            return;
        }
        button1->SetText("reset");
        button2->SetText("hold");
        button3->SetText("skip");
        button4->SetText("start");
        button5->SetText("back");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::ORANGE);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);

        button1->AddFunction([&](){
            guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("start");
        });
        button2->AddFunction([&](){
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
            if(guiManager->getButtonByName(BUTTON_4.toStdString())->getText() == "stop") {
                guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("resume");
            } else if (guiManager->getButtonByName(BUTTON_4.toStdString())->getText() == "start") {
                guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("stop");
            } else if (guiManager->getButtonByName(BUTTON_4.toStdString())->getText() == "resume") {
                guiManager->getButtonByName(BUTTON_4.toStdString())->SetText("stop");
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
        button1->SetText(guiManager->getPresetsWindow()->getCurrentPreset()->p1.name);
        button2->SetText(guiManager->getPresetsWindow()->getCurrentPreset()->p2.name);
        button3->SetText(guiManager->getPresetsWindow()->getCurrentPreset()->p3.name);
        button4->SetText(guiManager->getPresetsWindow()->getCurrentPreset()->p4.name);
        button5->SetText("back");
        button1->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button2->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button3->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button4->SetTextColor(CONF::GUI_PARAMETERS::COLORS::BRIGHT_BLUE);
        button5->SetTextColor(CONF::GUI_PARAMETERS::COLORS::RED);

        button1->AddFunction([&](){
            controller->SetPreset(guiManager->getPresetsWindow()->getCurrentPreset()->p1.preset);
        });
        button2->AddFunction([&](){
            controller->SetPreset(guiManager->getPresetsWindow()->getCurrentPreset()->p2.preset);
        });
        button3->AddFunction([&](){
            controller->SetPreset(guiManager->getPresetsWindow()->getCurrentPreset()->p3.preset);
        });
        button4->AddFunction([&](){
            controller->SetPreset(guiManager->getPresetsWindow()->getCurrentPreset()->p4.preset);
        });
        button5->AddFunction([&](){
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
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
        });
        button5->AddFunction([&](){
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
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
        });
        button5->AddFunction([&](){
        });
        break;

    case train:
        button1->SetText("back");
        button2->SetText("^");
        button3->SetText("v");
        button4->SetText("train");
        button5->SetText("manage");
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
        });
        button3->AddFunction([&](){
        });
        button4->AddFunction([&](){
        });
        button5->AddFunction([&](){
            windowState = manage;
            updateWindowFlag = true;
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

void SmartMultiEffect::ButtonsUpdate()
{
    controller->UpdateButtons();
    guiManager->UpdateButtons();

    if(updateWindowFlag) {
        UpdateWindow();
        updateWindowFlag = false;
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
    }
    SetButtonsFunctions();

    if(buttonsTimerState) {
        buttonsTimer->start();
    }

}
