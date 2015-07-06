/*	_ReportManager.h
 *
 *	Класс, генерирующий отчеты // в формате .docx
 *
 *	необходимо установить OpenXml SDK 2.5
 *	и добавить ссылку на DocumentFormat.OpenXml и WindowsBase
 *
 *	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
 *	All rights reserved.
 */
#pragma once
#include "stdafx.h"
using namespace System;



namespace zias {

	class ReportManager {
	private:
		static std::shared_ptr<ReportManager> _instance;

		static void commonReport(const FormDataArgs&, String ^);
		static void ankerCommonReport(const FormDataArgs&, String ^ , String ^ );
		static void commonConcreteSlabsReport(const FormDataArgs&, String ^);
		static void maximaMediumNoAnkerReport(const FormDataArgs&, String ^);
		static void maximaNoAnkerReport(const FormDataArgs&, String ^);
		static void maximaAnkerReport(const FormDataArgs&, String ^);

		//static void checkExistsFile(String ^ nameFile);

	public:
		static std::shared_ptr<ReportManager>& Instance();

		static void generateReport(const FormDataArgs&, const String^);
	public:
		~ReportManager();
	private:
		ReportManager();
	};
} // zias