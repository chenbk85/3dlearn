#include "MainWindow.h"

#include "ogrewidget.hxx"

#include <QtGui/QtGui>
#include <QtCore/QtCore>



MainWindow *mOgitorMainWindow = 0;


//MainWindow::MainWindow(void)
//{
//	resize(800, 600);
//
//}


MainWindow::MainWindow(QString args, QWidget *parent)
: QMainWindow(parent)
, mOgreWidget(0)
//, mLastTime(0), mArgsFile(args), mHasFileArgs(false)
//, mUpdateLastSceneFile1(false), mUpdateLastSceneFile2(false), mPrefManager(0)
//, mSubWindowsVisible(true)
{
	mOgitorMainWindow = this;

	resize(800, 600);

	setWindowTitle(QString("Thanks for Ogitor&ogre provide us with such a perfect code") );

	mEditorTab = new QTabWidget(this);
	mEditorTab->setObjectName("editortab");


	createSceneRenderWindow();

	createCustomTabWindows();

	setCentralWidget(mEditorTab);

	mTimer = new QTimer(this);
	mTimer->setInterval(0);
	connect(mTimer, SIGNAL(timeout()), this, SLOT(timerLoop()));
	mTimer->start(1000);


	//initHiddenRenderWindow();


}
MainWindow::~MainWindow(void)
{
	if (mTimer)
	{
		delete mTimer;
	}
}


void MainWindow::setApplicationObject(QObject *obj) 
{ 
	mApplicationObject = obj;
	mAppActive = true;
	obj->installEventFilter(this);
}

void MainWindow::timerLoop()
{
	mOgreWidget->update();

	//if(mHasFileArgs)
	//{
	//    if(mOgreWidget->mOgreInitialised)
}

//------------------------------------------------------------------------------
void MainWindow::createCustomTabWindows()
{
	//TabWidgetDataList tabwidgets = OgitorsRoot::getSingletonPtr()->GetTabWidgets();

	//for(unsigned int i = 0;i < tabwidgets.size();i++)
	//{
	//	QWidget *widget = static_cast<QWidget*>(tabwidgets[i].mHandle);
	//	if(widget)
	//	{
	//		try
	//		{
	//			widget->setObjectName(QString(tabwidgets[i].mCaption.c_str()));
	//			mEditorTab->addTab(widget, QString(tabwidgets[i].mCaption.c_str()));
	//		}
	//		catch(...)
	//		{
	//			QMessageBox::warning(QApplication::activeWindow(), "qtOgitor", QString(tr("Invalid TabWidget ID:%1")).arg(QString(tabwidgets[i].mCaption.c_str())), QMessageBox::Ok);
	//		}
	//	}
	//}
}

void MainWindow::createSceneRenderWindow()
{
	QWidget *renderWindowWidget = new QWidget(mEditorTab);

	mOgreWidget = new OgreWidget(renderWindowWidget, true);

	QVBoxLayout *renderWindowLayout = new QVBoxLayout();
	renderWindowLayout->setSpacing(0);
	renderWindowLayout->setMargin(0);
	renderWindowLayout->addWidget(mOgreWidget, 1);

	renderWindowWidget->setLayout(renderWindowLayout);

	mEditorTab->addTab(renderWindowWidget, tr("Render"));
}

void MainWindow::initHiddenRenderWindow()
{
	Ogre::NameValuePairList hiddenParams;

	hiddenParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t) winId());

	hiddenParams["border"] = "none";
	Ogre::RenderWindow* pPrimary = Ogre::Root::getSingletonPtr()->createRenderWindow("Primary1",1,1,false,&hiddenParams);
	pPrimary->setVisible(false);
	pPrimary->setAutoUpdated(false);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Load resources

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}