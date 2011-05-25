#pragma once



#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtGui/QMainWindow>

#include <Ogre.h>
//using namespace Ogre;


class OgreWidget;
class SceneViewWidget;
class LayerViewWidget;
class GeneralPropertiesViewWidget;
class CustomPropertiesViewWidget;
class EntityViewWidget;
class TemplateViewWidget;
class ColourPickerWidget;
class ObjectsViewWidget;
class ActionToolbar;
class OgitorPreferencesWidget;
class PreferencesManager;
class LineEditWithHistory;

class TerrainToolsWidget;



struct TabWidgetData
{
	Ogre::String  mCaption;
	void         *mHandle;
};

typedef Ogre::vector<TabWidgetData>::type TabWidgetDataList;



class MainWindow : public QMainWindow
{
 Q_OBJECT
public:
	//MainWindow(void);
	~MainWindow(void);
	MainWindow(QString args = "", QWidget *parent = 0);

	void setApplicationObject(QObject *obj);

	QObject                 *mApplicationObject;

	bool                     mAppActive;

	QTimer                  *mTimer;


	OgreWidget*  mOgreWidget;

	void createSceneRenderWindow();


	QTabWidget*  mEditorTab;

	void createCustomTabWindows();


	void initHiddenRenderWindow();

public Q_SLOTS:
		void timerLoop();


private:
	QString mstrTime;


};

extern MainWindow *mOgitorMainWindow;
