#ifndef OGREQT_H
#define OGREQT_H

#include <QtGui/QMainWindow>
#include "ui_ogreqt.h"

class OgreQt : public QMainWindow
{
	Q_OBJECT

public:
	OgreQt(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OgreQt();

private:
	Ui::OgreQtClass ui;

	
};

#endif // OGREQT_H
