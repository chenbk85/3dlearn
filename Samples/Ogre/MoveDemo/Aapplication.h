/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleApplication.h
Description: Base class for all the OGRE examples
-----------------------------------------------------------------------------
*/

#ifndef __ExampleApplication_H__
#define __ExampleApplication_H__

#include "Ogre.h"
#include "OgreConfigFile.h"


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>


#include "NoxFrameListener.h"
#include "NoxMouseListener.h"




using namespace Ogre;


class Application
{
public:
	/// Standard constructor
	Application()
	{
		//mFrameListener = 0;
		mRoot = 0;
		// Provide a nice cross platform solution for locating the configuration files
		// On windows files are searched for in the current working directory, on OS X however
		// you must provide the full path, the helper function macBundlePath does this for us.
		mResourcePath = "";
		mConfigPath = mResourcePath;
		mCameraMan = NULL;

	}
	/// Standard destructor
	virtual ~Application()
	{

		if (mCameraMan)
			OGRE_DELETE mCameraMan;

		if (mRoot)
			OGRE_DELETE mRoot;

	}

	/// Start the example
	virtual void go(void)
	{
		if (!setup())
			return;

		mRoot->startRendering();

		// clean up
		destroyScene();	
	}

protected:
	Root *mRoot;
	Camera* mCamera;
	OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	Ogre::String mResourcePath;
	Ogre::String mConfigPath;


	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;



	// These internal methods package up the stages in the startup process
	/** Sets up the application - returns false if the user chooses to abandon configuration. */
	virtual bool setup(void)
	{

		String pluginsPath;
		// only use plugins.cfg if not static
#if OGRE_DEBUG_MODE
		pluginsPath = mResourcePath + "plugins_d.cfg";
#else
		pluginsPath = mResourcePath + "plugins.cfg";
#endif

		mRoot = OGRE_NEW Root(pluginsPath, 
			mConfigPath + "ogre.cfg", mResourcePath + "Ogre.log");

		setupResources();

		bool carryOn = configure();
		if (!carryOn) 
			return false;

		chooseSceneManager();
		createCamera();
		createViewports();


		// Set default mipmap level (NB some APIs ignore this)
		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();
		// Load resources
		loadResources();

		// Create the scene
		createScene();

		createListener();

		return true;

	}



	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw)
	{
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	/** Configures the application - returns false if the user chooses to abandon configuration. */
	virtual bool configure(void)
	{
		// Show the configuration dialog and initialise the system
		// You can skip this and use root.restoreConfig() to load configuration
		// settings if you were sure there are valid ones saved in ogre.cfg
		if(mRoot->showConfigDialog())
		{
			// If returned true, user clicked OK so initialise
			// Here we choose to let the system create a default rendering window by passing 'true'
			mWindow = mRoot->initialise(true);
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual void chooseSceneManager(void)
	{
		// Create the SceneManager, in this case a generic one
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");
	}
	virtual void createCamera(void)
	{
		// Create the camera
		mCamera = mSceneMgr->createCamera("PlayerCam");

		// Position it at 500 in Z direction
		mCamera->setPosition(Vector3(0,0,500));
		// Look back along -Z
		mCamera->lookAt(Vector3(0,0,-300));
		mCamera->setNearClipDistance(5);


		mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller


	}
	virtual void createListener(void)
	{
		//mFrameListener= new NoxFrameListener(mWindow, mCamera);
		//mFrameListener->showDebugOverlay(true);
		//mRoot->addFrameListener(mFrameListener);

		//! mouse
		//mMouseListener = new NoxMouseListener();
	}

	virtual void createScene(void) = 0;    // pure virtual - this has to be overridden

	virtual void destroyScene(void){}    // Optional to override this

	virtual void createViewports(void)
	{
		// Create one viewport, entire window
		Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(ColourValue(0,0,0));

		// Alter the camera aspect ratio to match the viewport
		mCamera->setAspectRatio( Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
	}

	/// Method which will define the source of resources (other than current folder)
	virtual void setupResources(void)
	{
		// Load resource paths from config file
		ConfigFile cf;
#if OGRE_DEBUG_MODE
		cf.load(mResourcePath + "resources_d.cfg");
#else
		cf.load(mResourcePath + "resources.cfg");
#endif

		// Go through all sections & settings in the file
		ConfigFile::SectionIterator seci = cf.getSectionIterator();

		String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
				// OS X does not set the working directory relative to the app,
				// In order to make things portable on OS X we need to provide
				// the loading with it's own bundle path location
				if (!StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
					archName = String(macBundlePath() + "/" + archName);
#endif
				ResourceGroupManager::getSingleton().addResourceLocation( archName, typeName, secName);

			}
		}
	}

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void)
	{

	}

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	}

};

#endif
