#include "stdafx.h"

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<ReportManager> ReportManager::_instance = nullptr;
	// ---------------------

	ReportManager::ReportManager() {

	}

	ReportManager::~ReportManager() {

	}

	std::shared_ptr<ReportManager>& ReportManager::Instance() {
		if (_instance == nullptr) {
			_instance.reset(new ReportManager());

			// TODO: инициализация класса при первом обращении

		}

		return _instance;
	}

	void ReportManager::generateReport(const FormDataArgs& my_fda) {
		//VariableStorageManager::Instance()->getVariable("Qz_1");
		//my_fda.facing->weight;
	}

} // zias 