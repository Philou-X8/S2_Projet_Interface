#include "screen_select_level.h"

screen_select_level::screen_select_level() : QWidget(),
	profile(nullptr)
{
	profile = new UserProfile("default");
}
screen_select_level::screen_select_level(UserProfile* p) : QWidget(),
	profile(nullptr)
{
	profile = p;
}

screen_select_level::~screen_select_level() {

}