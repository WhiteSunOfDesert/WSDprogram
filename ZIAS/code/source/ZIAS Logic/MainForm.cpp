#include "stdafx.h"

namespace zias {

	// fill comboboxs
	void MainForm::FillData() {
		// cities
		std::vector<std::shared_ptr<City>> cities = zias::FormDataStorageManager::Instance()->getCities();
		for (auto& value : cities) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_cities->Items->Add(name);
		}
		if (this->_cb_cities->Items->Count) {
			this->_cb_cities->SelectedIndex = 0;
		}
		// wind_districs
		std::vector<std::shared_ptr<WindDistrict>> wind_districs = zias::FormDataStorageManager::Instance()->getWindDistricts();
		for (auto& value : wind_districs) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_wind_districs->Items->Add(name);
		}
		if (this->_cb_wind_districs->Items->Count) {
			this->_cb_wind_districs->SelectedIndex = 0;
		}
		// ice_districs
		std::vector<std::shared_ptr<IceDistrict>> ice_districs = zias::FormDataStorageManager::Instance()->getIceDistricts();
		for (auto& value : ice_districs) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_ice_districs->Items->Add(name);
		}
		if (this->_cb_ice_districs->Items->Count) {
			this->_cb_ice_districs->SelectedIndex = 0;
		}
		// location_types
		std::vector<std::shared_ptr<LocationType>> location_types = zias::FormDataStorageManager::Instance()->getLocationTypes();
		for (auto& value : location_types) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_location_types->Items->Add(name);
		}
		if (this->_cb_location_types->Items->Count) {
			this->_cb_location_types->SelectedIndex = 0;
		}
		// facings
		std::vector<std::shared_ptr<Facing>> facings = zias::FormDataStorageManager::Instance()->getFacings();
		for (auto& value : facings) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_facing->Items->Add(name);
		}
		if (this->_cb_facing->Items->Count) {
			this->_cb_facing->SelectedIndex = 0;
		}
		// subsystems
		std::vector<std::shared_ptr<Subsystem>> subsystems = zias::FormDataStorageManager::Instance()->getSubsystems();
		for (auto& value : subsystems) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_subsystem->Items->Add(name);
		}
		if (this->_cb_subsystem->Items->Count) {
			this->_cb_subsystem->SelectedIndex = 0;
		}
		// brackets
		std::vector<std::shared_ptr<Bracket>> brackets = zias::FormDataStorageManager::Instance()->getBrackets();
		for (auto& value : brackets) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_bracket->Items->Add(name);
		}
		if (this->_cb_bracket->Items->Count) {
			this->_cb_bracket->SelectedIndex = 0;
		}
		// profiles
		std::vector<std::shared_ptr<Profile>> profiles = zias::FormDataStorageManager::Instance()->getProfiles();
		for (auto& value : profiles) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_profile->Items->Add(name);
		}
		if (this->_cb_profile->Items->Count) {
			this->_cb_profile->SelectedIndex = 0;
		}
	}

	FormDataArgs MainForm::collectData() {
		FormDataArgs result_data;
		if (_rb_climate_0->Checked) {
			result_data.city = FormDataStorageManager::Instance()->getCity(zias::utils::toStdString(_cb_cities->Text));
			result_data.iceDistrict = result_data.city->ice_district;
			result_data.windDistrict = result_data.city->wind_district;
		} else if (_rb_climate_1->Checked) {
			result_data.city.reset();
			result_data.iceDistrict = FormDataStorageManager::Instance()->getIceDistrict(zias::utils::toStdString(_cb_wind_districs->Text));
			result_data.windDistrict = FormDataStorageManager::Instance()->getWindDistrict(zias::utils::toStdString(_cb_ice_districs->Text));
		}

		if (_rb_facing_standart->Checked) {
			result_data.facing = FormDataStorageManager::Instance()->getFacing(zias::utils::toStdString(_cb_facing->Text));
			result_data.weight = result_data.facing->weight;
		} else if (_rb_facing_unstandart->Checked) {
			result_data.facing.reset();
			result_data.weight = zias::utils::toFloat(_tb_weight->Text);
		}

		if (_rb_subsystem_standart->Checked) {
			result_data.subsystem = FormDataStorageManager::Instance()->getSubsystem(zias::utils::toStdString(_cb_subsystem->Text));
			result_data.profile.reset();
			result_data.bracket.reset();
		} else if (_rb_subsystem_variations->Checked) {
			result_data.subsystem.reset();
			result_data.profile = FormDataStorageManager::Instance()->getProfile(zias::utils::toStdString(_cb_profile->Text));
			result_data.bracket = FormDataStorageManager::Instance()->getBracket(zias::utils::toStdString(_cb_bracket->Text));
		}
		
		result_data.locationType = FormDataStorageManager::Instance()->getLocationType(zias::utils::toStdString(_cb_location_types->Text));
		result_data.objectName = zias::utils::toStdString(_tb_name->Text);
		result_data.objectCipher = zias::utils::toStdString(_tb_code->Text);
		result_data.objectResponsible = zias::utils::toStdString(_tb_responsible->Text);
		result_data.objectHeight = zias::utils::toFloat(_tb_height->Text);
		result_data.checkAerodynamicFactor = _chb_aerodynamic_factor->Checked;
		result_data.c1 = zias::utils::toFloat(_tb_c1->Text);
		result_data.c2 = zias::utils::toFloat(_tb_c2->Text);
		result_data.checkAnker = _chb_anker->Checked;
		result_data.checkNVFConnection = _chb_nvf_elements->Checked;
		result_data.checkNVFElements = _chb_nvf_connection->Checked;

		return result_data;
	}
	
	bool MainForm::checkDataCorrectness() {
		bool flag = true;
		if (!isCorrectFieldObjectName()) {
			
			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_name

			flag = false;
		}
		if (!isCorrectFieldObjectCipher()) {
			
			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_code

			flag = false;
		}
		if (!isCorrectFieldObjectResponsible()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_responsible

			flag = false;
		}
		if (!isCorrectFieldObjectHeight()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_height

			flag = false;
		}
		if (!isCorrectFieldWeight()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_weight

			flag = false;
		}
		if (!isCorrectFieldC1()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_c1

			flag = false;
		}
		if (!isCorrectFieldC2()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_c2

			flag = false;
		}
		if (!isCorrectFieldFacingRadius()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_facing_radius

			flag = false;
		}
		if (!isCorrectFieldVerticalRZ()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_v_step_bracket_ordinary_area

			flag = false;
		}
		if (!isCorrectFieldVerticalKZ()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_v_step_bracket_marginal_area

			flag = false;
		}
		if (!isCorrectFieldHorizontalRZ()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_h_step_bracket_ordinary_area

			flag = false;
		}
		if (!isCorrectFieldHorizontalKZ()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_h_step_bracket_marginal_area

			flag = false;
		}
		if (!isCorrectFieldVerticalStep()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_v_step_profile

			flag = false;
		}
		if (!isCorrectFieldHorizontalStep()) {

			// подсвечиваем поле и выдаем сообщение о некорректности данных
			// _tb_h_step_profile

			flag = false;
		}

		return flag;
	}

	void MainForm::calculateAccount() {

		_tb_digging_anker->Text = L"";			// ...
		_tb_strength_profile->Text = L"";		// ...
		_tb_strength_bracket->Text = L"";		// ...
		_tb_strength_extension->Text = L"";		// ...
		_tb_connections->Text = L"";			// ...
		_tb_Qy_0->Text = L"";					//VariableStorageManager::Instance()->getVariable("Qy_0");
		_tb_Qy_1->Text = L"";					//VariableStorageManager::Instance()->getVariable("Qy_1");
		_tb_Qz_0->Text = L"";					//VariableStorageManager::Instance()->getVariable("Qz_0");
		_tb_Qz_1->Text = L"";					//VariableStorageManager::Instance()->getVariable("Qz_1");
		
		return;
	}

	bool MainForm::isCorrectFieldObjectName() {
		
		std::string str = zias::utils::toStdString(_tb_name->Text);
		std::regex regular("([A-Za-z0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectCipher() {
		std::string str = zias::utils::toStdString(_tb_code->Text);
		std::regex regular("([A-Za-z0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectResponsible() {
		std::string str = zias::utils::toStdString(_tb_responsible->Text);
		std::regex regular("([A-Za-z]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectHeight() {
		std::string str = zias::utils::toStdString(_tb_height->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldWeight() {
		std::string str = zias::utils::toStdString(_tb_weight->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldC1() {
		std::string str = zias::utils::toStdString(_tb_c1->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	} 

	bool MainForm::isCorrectFieldC2() {
		std::string str = zias::utils::toStdString(_tb_c2->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	} 

	bool MainForm::isCorrectFieldFacingRadius() {
		std::string str = zias::utils::toStdString(_tb_facing_radius->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldVerticalRZ() {
		std::string str = zias::utils::toStdString(_tb_v_step_bracket_ordinary_area->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	} 

	bool MainForm::isCorrectFieldVerticalKZ() {
		std::string str = zias::utils::toStdString(_tb_v_step_bracket_marginal_area->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalRZ() {
		std::string str = zias::utils::toStdString(_tb_h_step_bracket_ordinary_area->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalKZ() {
		std::string str = zias::utils::toStdString(_tb_h_step_bracket_marginal_area->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldVerticalStep() {
		std::string str = zias::utils::toStdString(_tb_v_step_profile->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalStep() {
		std::string str = zias::utils::toStdString(_tb_h_step_profile->Text);
		std::regex regular("([0-9.]+)");
		std::smatch match;
		if (std::regex_match(str, match, regular)) {
			return true;
		}
		return false;
	}

} // zias