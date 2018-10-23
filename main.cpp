#include "mainwindow.h"
#include <QApplication>
#include "MengeVis/Viewer/ViewConfig.h"
#include "MengeVis/SceneGraph/GLScene.h"
#include "MengeVis/PluginEngine/VisPluginEngine.h"
#include "MengeCore/ProjectSpec.h"
#include "MengeVis/Viewer/GLViewer.h"
#include "MengeVis/Runtime/SimSystem.h"
#include "MengeVis/Runtime/MengeContext.h"
#include "MengeVis/Runtime/EventInjectContext.h"
#include "MengeCore/Runtime/SimulatorDB.h"
#include "Menge/MengeCore/Runtime/SimulatorDBEntry.h"
#include "Menge/MengeCore/Agents/SimulatorInterface.h"
#include "MengeCore/PluginEngine/CorePluginEngine.h"


void goMenge(std::string ROOT);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::string exePath( argv[ 0 ] );
    std::string absExePath;

    std::string ROOT;
    Menge::os::path::absPath( exePath, absExePath );
    std::string tail;
    Menge::os::path::split( absExePath, ROOT, tail );

    goMenge(ROOT);
    return a.exec();
}


std::string getPluginPath(std::string ROOT) {
    // The location of the executable - for basic executable resources
#ifdef _WIN32
#ifdef NDEBUG
    return os::path::join( 2, ROOT.c_str(), "plugins" );
#else	// NDEBUG
    return os::path::join( 3, ROOT.c_str(), "plugins", "debug" );
#endif	// NDEBUG
#else	// _WIN32
    return Menge::os::path::join( 2, ROOT.c_str(), "plugins" );
#endif	// _WIN32
}



void goMenge(std::string ROOT) {
    Menge::Logger logger;

    using Menge::ProjectSpec;

    ProjectSpec projSpec;

    // parameters begin
    std::string viewCfgFile = projSpec.getView();
    std::string dumpPath = "";

    // Time step (in seconds)
    float TIME_STEP = 0.2f;
    // The number of uniform simulation steps to take between logical time steps
    size_t SUB_STEPS = 0;
    // Maximum duration of simulation (in seconds)
    float SIM_DURATION = 800.f;
    // Controls whether the simulation is verbose or not
    bool VERBOSE = false;
    size_t agentCount;
    std::string model = "orca";
   // std::string model( projSpec.getModel() );

    using Menge::SimulatorDB;

    SimulatorDB simDB;
    using Menge::PluginEngine::CorePluginEngine;
    CorePluginEngine plugins( &simDB );
    using Menge::SimulatorDBEntry;
    SimulatorDBEntry * dbEntry = simDB.getDBEntry( model );

    std::string behaveFile;

    std::string sceneFile;
    std::string outFile;
    std::string scbVersion;

    using  Menge::Agents::SimulatorInterface;
    SimulatorInterface * sim = dbEntry->getSimulator( agentCount, TIME_STEP, SUB_STEPS,
                                                      SIM_DURATION, behaveFile, sceneFile, outFile,
                                                      scbVersion, VERBOSE );

    if ( sim == nullptr ) {
        qCritical("your simulation is not loading properly!");
//        return;
    }


    using  MengeVis::PluginEngine::VisPluginEngine;

    logger << Menge::Logger::INFO_MSG << "Initializing visualization...";
    VisPluginEngine visPlugins;
    visPlugins.loadPlugins( getPluginPath(ROOT) );

      MengeVis::SceneGraph::TextWriter::setDefaultFont( Menge::os::path::join( 2, "/home/mauricio/dev/Menge", "arial.ttf" ) );
  //  MengeVis::SceneGraph::TextWriter::setDefaultFont( Menge::os::path::join( 2, ROOT.c_str(), "arial.ttf" ) );

    MengeVis::Viewer::ViewConfig viewCfg;
//    if ( VERBOSE ) {
//        logger << Logger::INFO_MSG << "Using visualizer!";
//    }
    if ( viewCfgFile == "" ) {
//        if ( VERBOSE ) {
//            logger << Logger::INFO_MSG << "\tUsing default visualization settings.";
//        }
    } else {
//        // TODO: Error handling
//        if ( viewCfg.readXML( viewCfgFile ) ) {
//            if ( VERBOSE ) {
//                logger << Logger::INFO_MSG << "\tUsing visualization from: " << viewCfgFile << "\n";
//                logger << Logger::INFO_MSG << viewCfg << "\n";
//            }
//        } else {
//            logger << Logger::ERR_MSG << "Unable to read the specified view configuration (" << viewCfgFile << "). Terminating.";
//            return 1;
//        }
    }
    using  MengeVis::Viewer::GLViewer;
    GLViewer view( viewCfg );

    view.setDumpPath( dumpPath );

//#ifdef NDEBUG
//    std::string viewTitle = "Pedestrian Simulation - " + dbEntry->viewerName();
//#else
//    std::string viewTitle = "(DEBUG) Pedestrian Simulation - " + dbEntry->viewerName();
//#endif
//    if ( !view.initViewer( viewTitle ) ) {
//        std::cerr << "Unable to initialize the viewer\n\n";
//        visualize = false;
//    } else {

    using MengeVis::SceneGraph::GLScene;
    //here we go!
        GLScene * scene = new GLScene();
        qDebug("helloagain!");


        using MengeVis::Runtime::SimSystem;
        qDebug("hello1!");
        SimSystem * system = new SimSystem( sim );
        qDebug("hello2!");
        system->populateScene( scene ); // breaks!
        qDebug("hello3!");
        scene->addSystem( system );
        qDebug("hello4!");
        view.setScene( scene );
        qDebug("hello5  !");

        view.setFixedStep( TIME_STEP );
        view.setBGColor( 0.1f, 0.1f, 0.1f );
        MengeVis::Runtime::MengeContext * ctx = new MengeVis::Runtime::MengeContext( sim );
        qDebug("hello!");

        using MengeVis::Runtime::EventInjectionContext;
        scene->setContext( new  EventInjectionContext( ctx ) );
        view.newGLContext();
//        logger.line();

        view.run();

//    }

}
