#include "screen_home.h"

screen_home::screen_home() : QWidget(),
	homeLayout(nullptr),
	homeTestText(nullptr),
	levelSelect(nullptr),
	continueGame(nullptr),
	settings(nullptr),
	quit(nullptr)
{


	// create layout
	homeLayout = new QGridLayout(this);

	// create label
	homeTestText = new QLabel(this);
	homeTestText->setText("test text");

	levelSelect = new QPushButton("Select Level", this);
	QObject::connect(
		levelSelect, SIGNAL(clicked()), 
		this, SIGNAL(SelectLevelSignal())
	); 


	// fill layout
	homeLayout->addWidget(homeTestText, 0, 0);
	homeLayout->addWidget(levelSelect, 1, 0);

	setLayout(homeLayout);
	setWindowTitle("test title");
}

screen_home::~screen_home() {

}

void screen_home::onKeyEvent(char key) {
	homeTestText->setText(QString(key));
}
void screen_home::setNewText(QString text) {
	homeTestText->setText(text);
}