#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	zias::MainForm my_form;
	Application::Run(%my_form);

	return 0;
}