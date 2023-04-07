TEMPLATE     = vcapp
TARGET       = PushPullEscape
CONFIG      += warn_on qt debug windows console
HEADERS     += \
	screen_game.h \
	screen_home.h \
	screen_select_level.h \
	screen_settings.h \
	subscreen_game_grid.h \
	window_main.h \
	inputmanager.h \
	maploader.h \
	position.h \
	userProfile.h
SOURCES     += \
	screen_game.cpp \
	screen_home.cpp \
	screen_select_level.cpp \
	screen_settings.cpp \
	subscreen_game_grid.cpp \
	window_main.cpp \
	inputmanager.cpp \
	maploader.cpp \
	position.cpp \
	userProfile.cpp \
	main.cpp
QT          += widgets
