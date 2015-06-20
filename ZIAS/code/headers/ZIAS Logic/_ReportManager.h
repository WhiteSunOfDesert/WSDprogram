/*	_ReportManager.h
 *
 *	Класс, генерирующий отчеты // в формате .docx
 *
 *	бла-бла-бла
 *	бла-бла-бла
 *
 *	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
 *	All rights reserved.
 */

#pragma once

namespace zias {

	class ReportManager {
	private:
		static std::shared_ptr<ReportManager> _instance;

	public:
		static std::shared_ptr<ReportManager>& Instance();

		static void generateReport(const FormDataArgs&);
	public:
		~ReportManager();
	private:
		ReportManager();
	};
} // zias