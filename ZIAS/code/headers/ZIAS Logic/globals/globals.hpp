/*	_globals.hpp
 *
 *	Глобальные переменные и дефайны, имееющие отношение непосредственно к проекту, как к приложению
 *  верисия проекта, авторы, прочая фигня
 *
 *
 *	up: добавленны пути к рабочим директориям
 *
 *	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
 *	All rights reserved.
 */

#pragma once

// версия проекта
#define _BUILD_			"PreAlpha"
#define _VERSION_		"0.01"

// название проекта
#define _PROJECT_		L"ZIAS FACADE SYSTEM - РАСЧЕТНЫЙ КОМПЛЕКС (2015а)" + L" " + _BUILD_ + L" v." + _VERSION_

// пути к рабочим директориям
#define _PATH_TO_DATA_XML_			"..\\bin\\data\\data_source.xml"		// путь к xml c данными сущностей и численных переменных
#define _PATH_TO_INPUT_REPORTS_		"..\\bin\\reports\\input\\"				// путь к "входным" отчетам для обработки
#define _PATH_TO_OUTPUT_REPORTS_	"..\\bin\\reports\\output\\"			// путь к "генерируемым" отчетам
#define _PATH_TO_DOCUMENTATION_		"..\\bin\\documentation\\"				// путь к папке с докупентацией
// ...

// название файлов отчетов
#define _REPORT_NAME_OPTIMA_		"ПР (100.01)Optima 2 мм.doc"
#define _REPORT_NAME_STANDART_		"ПР (100.01)Standart 2 мм.doc"
#define _REPORT_NAME_STRONG_1_2_	"Расчет Strong 1,2 мм.doc"
#define _REPORT_NAME_STRONG_1_5_	"Расчет Strong 1,5 мм.doc"
#define _REPORT_NAME_STRONG_2_		"Расчет Strong 2 мм.doc"
#define _REPORT_NAME_KPR_			"Расчет КПР 1,2 мм.doc"

#define _HELP_DOCUMENT_NAME_		"Documntation.pdf"						// файл документации, которая будет выводится при клике
																			// на иконку "книжки" в главной форме
// ...

// Типы подсистем
#define _SUBSYSTEM_STANDARD_		L"Standard"
#define _SUBSYSTEM_KPR_				L"КПР"
#define _SUBSYSTEM_OPTIMA_			L"Optima"
#define _SUBSYSTEM_STRONG			L"Strong"
#define _SUBSYSTEM_MAXIMA_			L"Maxima"
#define _SUBSYSTEM_MAXIMA_MEDIUM_	L"MaximaMedium"
#define _SUBSYSTEM_MAXIMA_LIGHT_	L"MaximaLight"
#define _SUBSYSTEM_MEDIUM_STRONG	L"MediumStrong"
