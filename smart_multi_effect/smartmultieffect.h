#ifndef SMARTMULTIEFFECT_H
#define SMARTMULTIEFFECT_H

#include "EffectController/effectcontroller.h"
#include "GUI/Elements/guimanager.h"
#include "GUI/Elements/testgui.h"
#include "SoundProcessing/soundprocessor.h"
#include "RiffRecognition/riffrecognition.h"

#include "mytimer.h"
#include <thread>

class SmartMultiEffect
{
public:
    enum WindowState { test, songs, presets, song, preset, menu, recordNote, recordOctave, train, manage, loading};
public:
    SmartMultiEffect();
    ~SmartMultiEffect();

    void Run();

private:
    void InitializeEffects();
    void InitializeGui();
    void InitializeButtons();
    void InitializeSoundProcessor();

    void InitializePresets();
    void InitializeSongs();
    void InitializeMenu();

    void SetButtonsFunctions();

    void BindHardwareButtonToGuiButton(std::string& hardwareButtonName, std::string& guiButtonName);

    void Update();

    void UpdateWindow();

private:
    hardware_ctrl::EffectController* controller = nullptr;
    GUI_elements::GuiManager* guiManager = nullptr;
    sound_processing::SoundProcessor* soundProcessor = nullptr;
    RiffRecognition* riffRecognition = nullptr;

    MyTimer* buttonsTimer = nullptr;

    WindowState windowState = loading;
    WindowState lastWindowState = presets;

    std::thread* loadingThread = nullptr;

    bool updateWindowFlag = false;
};

#endif // SMARTMULTIEFFECT_H
