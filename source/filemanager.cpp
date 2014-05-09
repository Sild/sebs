
#include "../header/filemanager.h"

boost::filesystem::path get_app_path() {
	return boost::filesystem::current_path();
}