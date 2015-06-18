// Леонидова вотчина
#pragma once

namespace zias {

	class ReportManager {
	private:
		static std::shared_ptr<ReportManager> _instance;

	public:
		static std::shared_ptr<ReportManager>& Instance();

		static void generateReport();
	public:
		~ReportManager();
	private:
		ReportManager();
	};
} // zias