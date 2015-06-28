/*	_ReportManager.h
*
*	�����, ������������ ������ // � ������� .docx
*
*	���������� ���������� OpenXml SDK 2.5
*	� �������� ������ �� DocumentFormat.OpenXml � WindowsBase
*
*	Copyright(c) 20.06.2015 "�������� ����� ����������"
*	All rights reserved.
*/

#pragma once

namespace zias {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	class ReportManager {
	private:
		static std::shared_ptr<ReportManager> _instance;

		static void commonReport(const FormDataArgs&, String ^ doctext);
		static void ankerReport(const FormDataArgs&, String ^ docText, String ^ subsystem);
		static void checkExistsFile(String ^ nameFile);

	public:
		static std::shared_ptr<ReportManager>& Instance();

		static void generateReport(const FormDataArgs&);
	public:
		~ReportManager();
	private:
		ReportManager();
	};
} // zias