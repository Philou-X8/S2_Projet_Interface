#include "screen_home.h"

screen_home::screen_home() : QWidget(),
	homeLayout(nullptr),
	homeTestText(nullptr),
	levelSelect(nullptr),
	continueGame(nullptr),
	settings(nullptr),
	quit(nullptr),
	buttonList(nullptr)
{

	activeButton = 0;
	
	// create label
	homeTestText = new QLabel(this);
	homeTestText->setText("test text");

	levelSelect = new QPushButton("Select Level", this);
	QObject::connect(
		levelSelect, SIGNAL(clicked()), 
		this, SIGNAL(SelectLevelSignal())
	); 
	continueGame = new QPushButton("Continue Game", this);
	settings = new QPushButton("Settings", this);
	quit = new QPushButton("Quit", this);

	// create layout
	homeLayout = new QGridLayout(this);
	// fill layout
	homeLayout->addWidget(homeTestText, 0, 0);
	homeLayout->addWidget(levelSelect, 1, 0);
	homeLayout->addWidget(continueGame, 2, 0);
	homeLayout->addWidget(settings, 3, 0);
	homeLayout->addWidget(quit, 4, 0);

	setLayout(homeLayout);
	setWindowTitle("test title");
	buttonList = new QList<QPushButton*>();
	buttonList->append(levelSelect);
	buttonList->append(continueGame);
	buttonList->append(settings);
	buttonList->append(quit);
}

screen_home::~screen_home() {

}

void screen_home::onKeyEvent(char key) {
	homeTestText->setText(QString(key));

	switch (key)
	{
	case 'w':
	case 'i':
		if (activeButton > 0) {
			buttonList->at(activeButton)->setText("hidden");
			activeButton--;
			buttonList->at(activeButton)->setText("shown");
		}
		break;
	case 's':
	case 'k':
		if (activeButton < 3) {
			buttonList->at(activeButton)->setText("hidden");
			activeButton++;
			buttonList->at(activeButton)->setText("shown");
		}
		break;
	case ' ':
		buttonSelect(activeButton);
		break;
	default:
		break;
	}
}
void screen_home::buttonSelect(int selection) {
	switch (selection)
	{
	case 0:
		emit SelectLevelSignal();
		break;
	case 1:
		emit SelectContinueSignal();
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}
void screen_home::setNewText(QString text) {
	homeTestText->setText(text);
}



//-------------------------------------------------------
//	custom button
//-------------------------------------------------------
CustomButton::CustomButton(QPixmap base, QPixmap hi) : QLayout(),
	buttonBase(nullptr),
	buttonHi(nullptr)
{
	buttonBase = new QLabel;
	buttonBase->setAlignment(Qt::AlignCenter);
	buttonBase->setPixmap(base);

	buttonHi = new QLabel;
	buttonHi->setAlignment(Qt::AlignCenter);
	buttonHi->setPixmap(hi);
	buttonHi->hide();

	addWidget(buttonHi);
	addWidget(buttonBase);
	setAlignment(Qt::AlignCenter);
}
CustomButton::~CustomButton()
{
	delete buttonBase;
	delete buttonHi;
}
void CustomButton::onSelect() {
	buttonHi->show();
}
void CustomButton::onRelease() {
	buttonHi->hide();
}