#include "stdafx.h"
//#include <vld.h>							// раскомментировать для теста утечек памяти

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	zias::MainForm my_form;
	Application::Run(%my_form);

	return 0;
}