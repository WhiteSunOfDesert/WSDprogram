#include "stdafx.h"

namespace zias {

	// fill comboboxs
	void MainForm::FillData() {
		// �������� �������� �����, ������� ����� ����������� � �����
		std::string checking_field_mas[] = {
			utils::toStdString(_tb_name->Name),
			utils::toStdString(_tb_code->Name),
			utils::toStdString(_tb_responsible->Name),
			utils::toStdString(_tb_height->Name),
			utils::toStdString(_tb_v_step_bracket_ordinary_area->Name),
			utils::toStdString(_tb_v_step_bracket_marginal_area->Name),
			utils::toStdString(_tb_h_step_bracket_ordinary_area->Name),
			utils::toStdString(_tb_h_step_bracket_marginal_area->Name),
			utils::toStdString(_tb_conclusion->Name),
			utils::toStdString(_tb_v_step_profile_ordinary_area->Name),
			utils::toStdString(_tb_v_step_profile_marginal_area->Name),
			utils::toStdString(_tb_h_step_profile->Name),
			utils::toStdString(_tb_facing_radius->Name),
			utils::toStdString(_tb_weight->Name),
			utils::toStdString(_tb_c1->Name),
			utils::toStdString(_tb_c2->Name)
		}; 
			
		for (auto& field : checking_field_mas) {
			m_checking_field_states_map.emplace(field, fsNone);
		}

		// cities
		std::vector<std::shared_ptr<City>> cities = zias::FormDataStorageManager::Instance()->getCities();
		for (auto& value : cities) {
			String^ name = gcnew String(value->name.c_str());
			this->_cb_cities->Items->Add(name);
		}
		if (this->_cb_cities->Items->Count) {
			this->_cb_cities->SelectedIndex = 0;
		}
		_cb_cities->DropDownStyle = ComboBoxStyle::DropDownList;
		_cb_cities->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::_cb_cities_SelectedIndexChanged);
		// wind_districs
		std::vector<std::shared_ptr<WindDistrict>> wind_districs = zias::FormDataStorageManager::Instance()->getWindDistricts();
		for (auto& value : wind_districs) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_wind_districs->Items->Add(name);
		}
		if (this->_cb_wind_districs->Items->Count) {
			this->_cb_wind_districs->SelectedIndex = 0;
		}
		_cb_wind_districs->DropDownStyle = ComboBoxStyle::DropDownList;
		// ice_districs
		std::vector<std::shared_ptr<IceDistrict>> ice_districs = zias::FormDataStorageManager::Instance()->getIceDistricts();
		for (auto& value : ice_districs) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_ice_districs->Items->Add(name);
		}
		if (this->_cb_ice_districs->Items->Count) {
			this->_cb_ice_districs->SelectedIndex = 0;
		}
		_cb_ice_districs->DropDownStyle = ComboBoxStyle::DropDownList;
		// location_types
		std::vector<std::shared_ptr<LocationType>> location_types = zias::FormDataStorageManager::Instance()->getLocationTypes();
		for (auto& value : location_types) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_location_types->Items->Add(name);
		}
		if (this->_cb_location_types->Items->Count) {
			this->_cb_location_types->SelectedIndex = 0;
		}
		_cb_location_types->DropDownStyle = ComboBoxStyle::DropDownList;
		// facings
		std::vector<std::shared_ptr<Facing>> facings = zias::FormDataStorageManager::Instance()->getFacings();
		for (auto& value : facings) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_facing->Items->Add(name);
		}
		if (this->_cb_facing->Items->Count) {
			this->_cb_facing->SelectedIndex = 0;
		}
		_cb_facing->DropDownStyle = ComboBoxStyle::DropDownList;
		// subsystems
		std::vector<std::shared_ptr<Subsystem>> subsystems = zias::FormDataStorageManager::Instance()->getSubsystems();
		for (auto& value : subsystems) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_subsystem->Items->Add(name);
		}
		if (this->_cb_subsystem->Items->Count) {
			this->_cb_subsystem->SelectedIndex = 0;
		}
		_cb_subsystem->DropDownStyle = ComboBoxStyle::DropDownList;
		getConstructionFields();
		// brackets
		std::vector<std::shared_ptr<Bracket>> brackets = zias::FormDataStorageManager::Instance()->getBrackets();
		for (auto& value : brackets) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_bracket->Items->Add(name);
		}
		if (this->_cb_bracket->Items->Count) {
			this->_cb_bracket->SelectedIndex = 0;
		}
		_cb_bracket->DropDownStyle = ComboBoxStyle::DropDownList;
		// profiles
		std::vector<std::shared_ptr<Profile>> profiles = zias::FormDataStorageManager::Instance()->getProfiles();
		for (auto& value : profiles) {
			String^ name = gcnew String((value->name).c_str());
			this->_cb_profile->Items->Add(name);
		}
		if (this->_cb_profile->Items->Count) {
			this->_cb_profile->SelectedIndex = 0;
		}
		_cb_profile->DropDownStyle = ComboBoxStyle::DropDownList;
	}

	FormDataArgs MainForm::collectData() {
		FormDataArgs result_data;
		if (_rb_climate_0->Checked) {
			result_data.city = FormDataStorageManager::Instance()->getCity(utils::toStdWString(_cb_cities->Text));
			result_data.iceDistrict = result_data.city->ice_district;
			result_data.windDistrict = result_data.city->wind_district;
		} else if (_rb_climate_1->Checked) {
			result_data.city.reset();
			result_data.iceDistrict = FormDataStorageManager::Instance()->getIceDistrict(utils::toStdWString(_cb_ice_districs->Text));
			result_data.windDistrict = FormDataStorageManager::Instance()->getWindDistrict(utils::toStdWString(_cb_wind_districs->Text));
		}

		if (_rb_facing_standart->Checked) {
			result_data.facing = FormDataStorageManager::Instance()->getFacing(utils::toStdWString(_cb_facing->Text));
			result_data.weight = result_data.facing->weight;
		} else if (_rb_facing_unstandart->Checked) {
			result_data.facing.reset();
			result_data.weight = utils::toFloat(_tb_weight->Text);
		}

		result_data.subsystem = FormDataStorageManager::Instance()->getSubsystem(utils::toStdWString(_cb_subsystem->Text));
		if (!_chb_subsystem_variation->Checked) {
			result_data.profile.reset();
			result_data.bracket.reset();
		} else {
			result_data.profile = FormDataStorageManager::Instance()->getProfile(utils::toStdWString(_cb_profile->Text));
			result_data.bracket = FormDataStorageManager::Instance()->getBracket(utils::toStdWString(_cb_bracket->Text));
		}
		
		result_data.locationType = FormDataStorageManager::Instance()->getLocationType(utils::toStdWString(_cb_location_types->Text));
		result_data.objectName = utils::toStdWString(_tb_name->Text);
		result_data.objectCipher = utils::toStdWString(_tb_code->Text->ToUpper());
		result_data.objectResponsible = utils::toStdWString(_tb_responsible->Text);
		result_data.objectHeight = utils::toFloat(_tb_height->Text);
		result_data.checkAerodynamicFactor = _chb_aerodynamic_factor->Checked;
		result_data.c1 = utils::toFloat(_tb_c1->Text);
		result_data.c2 = utils::toFloat(_tb_c2->Text);
		result_data.isCityClimate = _rb_climate_0->Checked;
		result_data.checkAnker = _chb_anker->Checked;
		result_data.checkNVFConnection = _chb_nvf_elements->Checked;
		result_data.checkNVFElements = _chb_nvf_connection->Checked;
		result_data.facing_radius = utils::toFloat(_tb_facing_radius->Text);
		result_data.v_step_bracket_ordinary_area = utils::toFloat(_tb_v_step_bracket_ordinary_area->Text);
		result_data.h_step_bracket_ordinary_area = utils::toFloat(_tb_h_step_bracket_ordinary_area->Text);
		result_data.v_step_bracket_marginal_area = utils::toFloat(_tb_v_step_bracket_marginal_area->Text);
		result_data.h_step_bracket_marginal_area = utils::toFloat(_tb_h_step_bracket_marginal_area->Text);
		result_data.conclusion = utils::toStdWString(_tb_conclusion->Text);
		result_data.isFacingStandart = _rb_facing_standart->Checked;
		result_data.isSubsystemStandart = !_chb_subsystem_variation->Checked;
		result_data.v_step_profile_ordinary_area = utils::toFloat(_tb_v_step_profile_ordinary_area->Text);
		result_data.v_step_profile_marginal_area = utils::toFloat(_tb_v_step_profile_marginal_area->Text);
		result_data.h_step_profile = utils::toFloat(_tb_h_step_profile->Text);

		return result_data;
	}

	void MainForm::getConstructionFields() {
		std::shared_ptr<Construction> _construction = FormDataStorageManager::Instance()->getConstruction(
			FormDataStorageManager::Instance()->getSubsystem(utils::toStdWString(_cb_subsystem->Text))->id);

		// ������������ ��� ��������������� ����� ����������� �������� ��������� ����������
		if (_construction->v_bracket_rz) {
			_tb_v_step_bracket_ordinary_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_ordinary_area->Name)) = fsCommon;
		} else {
			_tb_v_step_bracket_ordinary_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_ordinary_area->Name)) = fsLocked;
		}

		if (_construction->v_bracket_kz) {
			_tb_v_step_bracket_marginal_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_marginal_area->Name)) = fsCommon;
		} else {
			_tb_v_step_bracket_marginal_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_marginal_area->Name)) = fsLocked;
		}

		if (_construction->h_bracket_rz) {
			_tb_h_step_bracket_ordinary_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_ordinary_area->Name)) = fsCommon;
		} else {
			_tb_h_step_bracket_ordinary_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_ordinary_area->Name)) = fsLocked;
		}

		if (_construction->h_bracket_kz) {
			_tb_h_step_bracket_marginal_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_marginal_area->Name)) = fsCommon;
		} else {
			_tb_h_step_bracket_marginal_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_marginal_area->Name)) = fsLocked;
		}

		if (_construction->v_profile_rz) {
			_tb_v_step_profile_ordinary_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_ordinary_area->Name)) = fsCommon;
		} else {
			_tb_v_step_profile_ordinary_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_ordinary_area->Name)) = fsLocked;
		}

		if (_construction->v_profile_kz) {
			_tb_v_step_profile_marginal_area->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_marginal_area->Name)) = fsCommon;
		} else {
			_tb_v_step_profile_marginal_area->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_marginal_area->Name)) = fsLocked;
		}

		if (_construction->h_profile) {
			_tb_h_step_profile->Enabled = true;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_profile->Name)) = fsCommon;
		} else {
			_tb_h_step_profile->Enabled = false;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_profile->Name)) = fsLocked;
		}
	}
	
	bool MainForm::checkDataCorrectness() {
		// TODO: �� �������� ����� ���������� ��� � ����������� ����� �� �������� �����, ������� ����� ���������
		//		 � ��� ������� ����� ����������� ����... ���������� ������ ����� �������� � ������������ ��������
		
		bool flag = true;
		if (!isCorrectFieldObjectName()) {
			
			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_name->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_name->Name)) = fsUncorrect;
			_tb_name->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldObjectCipher()) {
			
			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_code->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_code->Name)) = fsUncorrect;
			_tb_code->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldObjectResponsible()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_responsible->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_responsible->Name)) = fsUncorrect;
			_tb_responsible->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldObjectHeight()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_height->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_height->Name)) = fsUncorrect;
			_tb_height->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldWeight()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_weight->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_weight->Name)) = fsUncorrect;
			_tb_weight->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldC1()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_c1->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_c1->Name)) = fsUncorrect;
			_tb_c1->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldC2()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_c2->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_c2->Name)) = fsUncorrect;
			_tb_c2->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldFacingRadius()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_facing_radius->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_facing_radius->Name)) = fsUncorrect;
			_tb_facing_radius->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldVerticalRZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_v_step_bracket_ordinary_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_ordinary_area->Name)) = fsUncorrect;
			_tb_v_step_bracket_ordinary_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldVerticalKZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_v_step_bracket_marginal_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_marginal_area->Name)) = fsUncorrect;
			_tb_v_step_bracket_marginal_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldHorizontalRZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_h_step_bracket_ordinary_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_ordinary_area->Name)) = fsUncorrect;
			_tb_h_step_bracket_ordinary_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldHorizontalKZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_h_step_bracket_marginal_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_marginal_area->Name)) = fsUncorrect;
			_tb_h_step_bracket_marginal_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldVerticalStepRZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_v_step_profile_ordinary_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_ordinary_area->Name)) = fsUncorrect;
			_tb_v_step_profile_ordinary_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldVerticalStepKZ()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_v_step_profile_marginal_area->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_marginal_area->Name)) = fsUncorrect;
			_tb_v_step_profile_marginal_area->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}
		if (!isCorrectFieldHorizontalStep()) {

			// ������������ ���� � ������ ��������� � �������������� ������
			_tb_h_step_profile->BackColor = System::Drawing::Color::Pink;
			m_checking_field_states_map.at(utils::toStdString(_tb_h_step_profile->Name)) = fsUncorrect;
			_tb_h_step_profile->Text = L"";

			// TODO: ����� ���� � ����� ��������� ����� ��������, ��������� ����� ������ �������� ������ ���������
			//		 ��� �������� "������" ��������� � ����. ������ ������� ����������������, ��� ��� � ��� 
			//		 ��������� ���� ����� �� ������ ��� ����������

			flag = false;
		}

		return flag;
	}

	void MainForm::calculateAccount() {

		_tb_digging_anker->Text = gcnew String("" + VariableStorageManager::Instance()->getVariable("digging_anker"));
		_tb_strength_profile->Text = L"";		// ...
		_tb_strength_bracket->Text = L"";		// ...
		_tb_strength_extension->Text = L"";		// ...
		_tb_connections->Text = L"";			// ...
		_tb_Qy_0->Text = gcnew String("" + VariableStorageManager::Instance()->getVariable("qy_0"));
		_tb_Qy_1->Text = gcnew String("" + VariableStorageManager::Instance()->getVariable("qy_1"));
		_tb_Qz_0->Text = gcnew String("" + VariableStorageManager::Instance()->getVariable("qz_0"));
		_tb_Qz_1->Text = gcnew String("" + VariableStorageManager::Instance()->getVariable("qz_1"));
		
		return;
	}

	bool MainForm::isCorrectFieldObjectName() {
		
		std::string str = utils::toStdString(_tb_name->Text);
		std::regex regular("^([�-��-߸�a-zA-Z0-9.-:| ]+)$");
		std::smatch match;
		if (//std::regex_match(str, match, regular) && 
			str != "" &&
			str != "��������� �������") // �������
		{
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectCipher() {
		std::string str = utils::toStdString(_tb_code->Text);
		std::regex regular("^([�-��-߸�a-zA-Z0-9.-]+)$");
		std::smatch match;
		if (//std::regex_match(str, match, regular) &&
			str != "" &&
			str != "��������� �������") // �������
		{
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectResponsible() {
		std::string str = utils::toStdString(_tb_responsible->Text);
		std::regex regular("([�-��-߸� .-]+)?");
		std::smatch match;
		if (std::regex_match(str, match, regular) && str != ""
			&& str != "��������� �������") // �������
		{
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldObjectHeight() {
		std::string str = utils::toStdString(_tb_height->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if (std::regex_match(str, match, regular) && str != "") {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldWeight() {
		if (_rb_facing_unstandart->Checked) {
			std::string str = utils::toStdString(_tb_weight->Text);
			std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
			std::smatch match;
			if (std::regex_match(str, match, regular) && str != "") {
				return true;
			}
			return false;
		}
		return true;
	}

	bool MainForm::isCorrectFieldC1() {
		if (_chb_aerodynamic_factor->Checked) {
			std::string str = utils::toStdString(_tb_c1->Text);
			std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
			std::smatch match;
			if (std::regex_match(str, match, regular) && str != "") {
				return true;
			}
			return false;
		}
		return true;
	} 

	bool MainForm::isCorrectFieldC2() {
		if (_chb_aerodynamic_factor->Checked) {
			std::string str = utils::toStdString(_tb_c2->Text);
			std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
			std::smatch match;
			if (std::regex_match(str, match, regular) && str != "") {
				return true;
			}
			return false;
		}
		return true;
	} 

	bool MainForm::isCorrectFieldFacingRadius() {
		std::string str = utils::toStdString(_tb_facing_radius->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if (std::regex_match(str, match, regular) && str != "") {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldVerticalRZ() {
		std::string str = utils::toStdString(_tb_v_step_bracket_ordinary_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_ordinary_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	} 

	bool MainForm::isCorrectFieldVerticalKZ() {
		std::string str = utils::toStdString(_tb_v_step_bracket_marginal_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_v_step_bracket_marginal_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalRZ() {
		std::string str = utils::toStdString(_tb_h_step_bracket_ordinary_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_ordinary_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalKZ() {
		std::string str = utils::toStdString(_tb_h_step_bracket_marginal_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_h_step_bracket_marginal_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldVerticalStepRZ() {
		std::string str = utils::toStdString(_tb_v_step_profile_ordinary_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_ordinary_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldVerticalStepKZ() {
		std::string str = utils::toStdString(_tb_v_step_profile_marginal_area->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_v_step_profile_marginal_area->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}

	bool MainForm::isCorrectFieldHorizontalStep() {
		std::string str = utils::toStdString(_tb_h_step_profile->Text);
		std::regex regular("([0-9]+[.,]{0,1}[0-9]{0,2})?");
		std::smatch match;
		if ((m_checking_field_states_map.at(utils::toStdString(_tb_h_step_profile->Name)) == fsLocked) ||
			(std::regex_match(str, match, regular) && str != "")) {
			return true;
		}
		return false;
	}
	
	// clickToCheckingField
	System::Void MainForm::clickToCheckingField(System::Object^ sender, System::Windows::Forms::MouseEventArgs^  e) {
		TextBox^ check_field = (TextBox^)sender;
		switch (m_checking_field_states_map.at(utils::toStdString(check_field->Name))) {
			case fsNone: {
				check_field->ForeColor = System::Drawing::Color::Black;
				check_field->Text = L"";
				m_checking_field_states_map.at(utils::toStdString(check_field->Name)) = fsCommon;
			} case fsUncorrect: {
				check_field->BackColor = System::Drawing::Color::White;
				m_checking_field_states_map.at(utils::toStdString(check_field->Name)) = fsCommon;
			} default: {

			}
		}
	}

	// _changedValueClimateRadiobutton
	System::Void MainForm::_changedValueClimateRadiobutton(System::Object^  sender, System::EventArgs^  e) {
		// ������
		_cb_cities->Enabled = !_cb_cities->Enabled;

		// �� ������
		_cb_wind_districs->Enabled = !_cb_wind_districs->Enabled;
		_cb_ice_districs->Enabled = !_cb_ice_districs->Enabled;
	}

	// _changedValueFacingRadiobutton
	System::Void MainForm::_changedValueFacingRadiobutton(System::Object^  sender, System::EventArgs^  e) {
		// �����������
		_cb_facing->Enabled = !_cb_facing->Enabled;

		// �������������
		_tb_weight->Enabled = !_tb_weight->Enabled;

		if (!_tb_weight->Enabled) {
			_tb_weight->Text = L"";
			_tb_weight->BackColor = System::Drawing::SystemColors::Window;
			m_checking_field_states_map.at(utils::toStdString(_tb_weight->Name)) = fsLocked;
		} else {
			_tb_weight->BackColor = System::Drawing::Color::White;
			m_checking_field_states_map.at(utils::toStdString(_tb_weight->Name)) = fsCommon;
		}
	}

		// _changedValueSubsystemCheckBox
	System::Void MainForm::_changedValueSubsystemCheckBox(System::Object^  sender, System::EventArgs^  e) {
		// ��������
		_cb_bracket->Enabled = !_cb_bracket->Enabled;
		_cb_profile->Enabled = !_cb_profile->Enabled;
	}

	// _changedValueVariationsCheckBox		
	System::Void MainForm::_changedValueVariationsCheckBox(System::Object^  sender, System::EventArgs^  e) {
		_tb_c1->Enabled = !_tb_c1->Enabled;
		_tb_c2->Enabled = !_tb_c2->Enabled;

		if (!_tb_c1->Enabled || !_tb_c2->Enabled) {
			_tb_c1->Text = L"";
			_tb_c2->Text = L"";
			_tb_c1->BackColor = System::Drawing::SystemColors::Window;
			_tb_c2->BackColor = System::Drawing::SystemColors::Window;
			m_checking_field_states_map.at(utils::toStdString(_tb_c1->Name)) = fsLocked;
			m_checking_field_states_map.at(utils::toStdString(_tb_c2->Name)) = fsLocked;
		} else {
			_tb_c1->BackColor = System::Drawing::Color::White;
			_tb_c2->BackColor = System::Drawing::Color::White;
			m_checking_field_states_map.at(utils::toStdString(_tb_c1->Name)) = fsCommon;
			m_checking_field_states_map.at(utils::toStdString(_tb_c2->Name)) = fsCommon;
		}
	}

	// openDocumentation
	System::Void MainForm::openDocumentation(System::Object^  sender, System::EventArgs^  e) {
		// TODO: ��������� ���� ������������
		// ������ ����: _PATH_TO_DOCUMENTATION_ + _HELP_DOCUMENT_NAME_
		// ��������, ����� ����� ����������, ��� �� ��������� �������� ����� ����� ������� ShellExecute
		// �������� ��� ����� (�� ��� ������, ��� ��� � ������ ������ + ��������)

		String^ filename = _PATH_TO_DOCUMENTATION_ + _HELP_DOCUMENT_NAME_;
		if (std::tr2::sys::exists(std::tr2::sys::path(utils::toStdString(filename)))) {
			ShellExecute(0, "open", utils::toStdString(filename).c_str(), 0, 0, SW_SHOWNORMAL);
		} else {
			MessageBox::Show(L"������ ����� ���� ��� ������ ��� ���������", L"�� ������ ���� ������������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	// _b_calculate_account_Click
	System::Void MainForm::_b_calculate_account_Click(System::Object^  sender, System::EventArgs^  e) {
		if (checkDataCorrectness()) {
			VariableStorageManager::Instance()->updateValues(collectData());
			calculateAccount();
		} else {
			// TODO: ����� ������� ���� �� ������ ����� �������������... � ����� ���

			MessageBox::Show(L"��������� ���� ���������", L"����������� �������� ������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	// _b_generate_report_Click
	System::Void MainForm::_b_generate_report_Click(System::Object^  sender, System::EventArgs^  e) {
		if (checkDataCorrectness()) {
			FormDataArgs fda = collectData();
			VariableStorageManager::Instance()->updateValues(fda);

			// ���������� ���� �� ���������� �����
			SaveFileDialog^ ofd = gcnew SaveFileDialog();
			ofd->Filter = "DOCX Files|*.docx";
			if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
				return;
			}

			ReportManager::Instance()->generateReport(fda, ofd->FileName);

		} else {
			// TODO: ����� ������� ���� �� ������ ����� �������������... � ����� ���

			MessageBox::Show(L"��������� ���� ���������", L"������������ �������� ������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	//  _cb_subsystem_SelectedIndexChanged
	System::Void MainForm::_cb_subsystem_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		getConstructionFields();
	}
		
	//_cb_cities_SelectedIndexChanged
	System::Void MainForm::_cb_cities_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		unsigned wind_district_id = FormDataStorageManager::Instance()->getCity(utils::toStdWString(_cb_cities->Text))->wind_district->id;
		unsigned ice_districs_id = FormDataStorageManager::Instance()->getCity(utils::toStdWString(_cb_cities->Text))->ice_district->id;

		_cb_wind_districs->SelectedIndex = wind_district_id;
		_cb_ice_districs->SelectedIndex = ice_districs_id;
	}

} // zias