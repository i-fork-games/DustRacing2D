// This file is part of Dust Racing 2D.
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>
#include <QTimer>

#include "settings.hpp"

class AudioThread;
class EventHandler;
class InputHandler;
class Renderer;
class Scene;
class Speedometer;
class Startlights;
class StartlightsOverlay;
class StateMachine;
class TimingOverlay;
class TrackLoader;
class MCObjectFactory;
class MCAssetManager;

//! The main game class.
class Game : public QObject
{
    Q_OBJECT

public:

    enum GameMode
    {
        OnePlayerRace = 0,
        TwoPlayerRace,
        TimeTrial,
        Duel
    };

    enum SplitType
    {
        Horizontal,
        Vertical
    };

    //! Constructor
    Game();

    //! Destructor
    virtual ~Game();

    //! Return the game instance.
    static Game & instance();

    //! Set target value for frames per second. Default is 60.
    void setFps(unsigned int fps);

    //! \return The renderer.
    Renderer & renderer() const;

    //! Init the game.
    //! \return True on success.
    bool init();

    //! Start the game.
    void start();

    //! Stop scene.
    void stop();

    //! Set the game mode.
    void setMode(GameMode gameMode);

    //! Get the game mode.
    GameMode mode() const;

    //! Set the split type on two-player game.
    void setSplitType(SplitType splitType);

    //! Get the split type.
    SplitType splitType() const;

    //! Set the lap count.
    void setLapCount(int lapCount);

    //! Get the lap count.
    int lapCount() const;

    //! \return True if the current mode has two human players.
    bool hasTwoHumanPlayers() const;

    //! \return True if the current mode has computer players.
    bool hasComputerPlayers() const;

    EventHandler & eventHandler() const;

    AudioThread & audioThread();

    const std::string & fontName() const;

public slots:

    void togglePause();
    void exitGame();
    void showCursor();
    void hideCursor();

private slots:

    void updateFrame();
    void renderFrame();
    void countRenderFps();

private:

    void adjustSceneSize(int hRes, int vRes, bool fullScreen);
    void createRenderer();
    void initScene();
    bool loadTracks();
    void loadFonts();

    Settings          m_settings;
    InputHandler    * m_inputHandler;
    EventHandler    * m_eventHandler;
    StateMachine    * m_stateMachine;
    Renderer        * m_renderer;
    Scene           * m_scene;
    MCAssetManager  * m_assetManager;
    MCObjectFactory * m_objectFactory;
    TrackLoader     * m_trackLoader;
    unsigned int      m_updateFps;
    unsigned int      m_updateDelay;
    float             m_timeStep;
    unsigned int      m_renderFps;
    unsigned int      m_renderDelay;
    unsigned int      m_renderCount;
    int               m_availableRenderTime;
    int               m_lapCount;
    bool              m_paused;
    QTimer            m_updateTimer;
    QTimer            m_renderTimer;
    GameMode          m_mode;
    SplitType         m_splitType;
    AudioThread     * m_audioThread;

    static Game * m_instance;
};

#endif // GAME_HPP
