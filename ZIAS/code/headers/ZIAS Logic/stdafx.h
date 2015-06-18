// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// !! этот хедер должен включаться первым в каждый .cpp-файл !!

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include <initializer_list>
#include <regex>

// собственная библиотека утилитных функций
#include <utils/utils.hpp>

// библиотека для работы с xml файлами
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

// менеджеры
#include "_FormDataStorageManager.h"
#include "_VariableStorageManager.h"
#include "_ReportManager.h"

// форма
#include "MainForm.h"

