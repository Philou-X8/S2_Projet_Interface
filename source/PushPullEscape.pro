TEMPLATE     = vcapp
TARGET       = PushPullEscape
CONFIG      += warn_on qt debug windows console
HEADERS     += \
	screen_game.h \
	screen_home.h \
	screen_select_level.h \
	screen_settings.h \
	subscreen_game_grid.h \
	window_main.h
SOURCES     += \
	screen_game.cpp \
	screen_home.cpp \
	screen_select_level.cpp \
	screen_settings.cpp \
	subscreen_game_grid.cpp \
	window_main.cpp \
	main.cpp
QT          += widgets
