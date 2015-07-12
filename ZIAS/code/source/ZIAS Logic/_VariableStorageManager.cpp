#include "stdafx.h"

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<VariableStorageManager> VariableStorageManager::_instance = nullptr;
	
	std::map<std::string, float> VariableStorageManager::_variables;
	std::map<short, float> VariableStorageManager::_table_b_ice;
	std::map<short, float> VariableStorageManager::_table_w_0;
	std::map<float, float> VariableStorageManager::_table_k_ice;
	std::map<float, std::array<float, 3>> VariableStorageManager::_table_k_ze;
	std::map<float, std::array<float, 3>> VariableStorageManager::_table_ksi_ze;
	// ---------------------

	VariableStorageManager::VariableStorageManager() {
		_variables.clear();

		_table_b_ice.clear();
		_table_w_0.clear();
		_table_k_ice.clear();
		_table_k_ze.clear();
		_table_ksi_ze.clear();
	}

	VariableStorageManager::~VariableStorageManager() {
		if (!_variables.empty()) _variables.clear();
		
		if (!_table_b_ice.empty()) _table_b_ice.clear();
		if (!_table_w_0.empty()) _table_w_0.clear();
		if (!_table_k_ice.empty()) _table_k_ice.clear();
		if (!_table_k_ze.empty()) _table_k_ze.clear();
		if (!_table_ksi_ze.empty()) _table_ksi_ze.clear();
	}

	std::shared_ptr<VariableStorageManager>& VariableStorageManager::Instance() {
		if (_instance == nullptr) {
			_instance.reset(new VariableStorageManager());

			// запихиваем в мапу переменные, которые НЕ будут браться из xml-ки
			std::string vars[] = {
				"weight_1",
				"weight_2",
				"weight_3",
				"Q_2",
				"q_2",
				"H_1",
				"H_2",
				"H_3",
				"B_1",
				"B_2",
				"q_H_1",
				"q_H_2",
				"q_H_3",
				"q_sum_1",
				"q_sum_2",
				"Q_311",
				"Q_321",
				"Q_411",
				"q_311",
				"q_321",
				"q_411",
				"S_1",
				"P_1",
				"N_1",
				"P_2",
				"N_2",
				"S_2",
				"P_3",
				"N_3",
				"qy_0",
				"qy_1",
				"qz_0",
				"qz_1",
				"R_1_1",
				"R_2_1",
				"R_3_1",
				"R_1_2",
				"R_2_2",
				"R_3_2",
				"i_312",
				"I_312",
				"c_1",
				"c_2",
				"digging_anker",
			};

			for (auto& var : vars) {
				addVariable(var, 0.f);
			}
			
			if (std::tr2::sys::exists(std::tr2::sys::path(_PATH_TO_DATA_XML_))) {
				try {
					rapidxml::file<> file(_PATH_TO_DATA_XML_);
					rapidxml::xml_document<> add_config;
					add_config.parse<0>(file.data());
					auto root = add_config.first_node();

					if (!root) {
						throw std::runtime_error("No root node");
					}

					while (root) {
						for (auto data_source = root->first_node(); data_source != nullptr; data_source = data_source->next_sibling()) {
							if (utils::equals(data_source->name(), "Var_Store")) {
								for (auto var_store = data_source->first_node(); var_store != nullptr; var_store = var_store->next_sibling()) {
									if (utils::equals(var_store->name(), "b_ice")) {
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (utils::equals(var_it->name(), "var")) {
												short ice_district_id = utils::lexical_cast<short>(var_it->first_attribute("ice_district_id")->value());
												float value = utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_b_ice(ice_district_id, value);
											}
										}

										addVariable(name, 0.f);
									}
									if (utils::equals(var_store->name(), "w_0")) {
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (utils::equals(var_it->name(), "var")) {
												short wind_district_id = utils::lexical_cast<short>(var_it->first_attribute("wind_district_id")->value());
												float value = utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_w_0(wind_district_id, value);
											}
										}

										addVariable(name, 0.f);
									}
									if (utils::equals(var_store->name(), "k_ice")) {
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (utils::equals(var_it->name(), "var")) {
												float height = utils::lexical_cast<float>(var_it->first_attribute("height")->value());
												float value = utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_k_ice(height, value);
											}
										}
										
										addVariable(name, 0.f);
									}
									if (utils::equals(var_store->name(), "k_ze")) {
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (utils::equals(var_it->name(), "var")) {
												float height = utils::lexical_cast<float>(var_it->first_attribute("z_e")->value());
												float valueA = utils::lexical_cast<float>(var_it->first_attribute("A_value")->value());
												float valueB = utils::lexical_cast<float>(var_it->first_attribute("B_value")->value());
												float valueC = utils::lexical_cast<float>(var_it->first_attribute("C_value")->value());

												addToTable_k_ze(height, valueA, valueB, valueC);
											}
										}

										addVariable(name, 0.f);
									}
									if (utils::equals(var_store->name(), "ksi_ze")) {
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (utils::equals(var_it->name(), "var")) {
												float height = utils::lexical_cast<float>(var_it->first_attribute("z_e")->value());
												float valueA = utils::lexical_cast<float>(var_it->first_attribute("A_value")->value());
												float valueB = utils::lexical_cast<float>(var_it->first_attribute("B_value")->value());
												float valueC = utils::lexical_cast<float>(var_it->first_attribute("C_value")->value());

												addToTable_ksi_ze(height, valueA, valueB, valueC);
											}
										}

										addVariable(name, 0.f);
									}
									if (   utils::equals(var_store->name(), "mu_2")
										|| utils::equals(var_store->name(), "rho")
										|| utils::equals(var_store->name(), "g")
										|| utils::equals(var_store->name(), "nu")
										|| utils::equals(var_store->name(), "c_1_default")
										|| utils::equals(var_store->name(), "c_2_default")
										|| utils::equals(var_store->name(), "gamma_f_1")
										|| utils::equals(var_store->name(), "gamma_f_2")
										|| utils::equals(var_store->name(), "gamma_f_3")
										|| utils::equals(var_store->name(), "gamma_f_4")
										) {
										
										std::string name = utils::lexical_cast<std::string>(var_store->name());
										float value = utils::lexical_cast<float>(var_store->first_attribute("value")->value());
									
										addVariable(name, value);
									}
								}
							}
						}
						root = root->next_sibling("Data_Source");
					}
				}
				catch (std::exception const& my_error) {
					std::cerr << my_error.what();
				}
			}
			else {
				throw std::runtime_error("Not found file: \"data_source.xml\"");
			}
		}

		return _instance;
	}

	void  VariableStorageManager::addVariable(const std::string& my_name, const float& my_value) {
		_variables.emplace(my_name, my_value);
	}

	float VariableStorageManager::getVariable(const std::string& my_name) {
		auto variable = _variables.find(my_name);
		if (variable != end(_variables)) {
			return utils::doRound(_variables[my_name], 2);
		}
		return 0.f;
	}

	std::map<std::string, float> VariableStorageManager::getVariables() {
		return _variables;
	}

	void VariableStorageManager::addToTable_b_ice(const short& my_ice_district_id, const float& my_value) {
		auto variable = _table_b_ice.find(my_ice_district_id);
		if (variable == end(_table_b_ice)) {
			_table_b_ice.emplace(my_ice_district_id, my_value);
		}
		return;
	}

	void VariableStorageManager::addToTable_w_0(const short& my_wind_district_id, const float& my_value) {
		auto variable = _table_w_0.find(my_wind_district_id);
		if (variable == end(_table_w_0)) {
			_table_w_0.emplace(my_wind_district_id, my_value);
		}
		return;
	}

	void VariableStorageManager::addToTable_k_ice(const float& my_height, const float& my_value) {
		auto variable = _table_k_ice.find(my_height);
		if (variable == end(_table_k_ice)) {
			_table_k_ice.emplace(my_height, my_value);
		}
		return;
	}

	void VariableStorageManager::addToTable_k_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue) {
		auto variable = _table_k_ze.find(my_height);
		if (variable == end(_table_k_ze)) {
			std::array<float, 3> mas = { my_Avalue, my_Bvalue, my_Cvalue };
			_table_k_ze.emplace(std::pair<float, std::array<float, 3>>(my_height, mas));
		}

		return;
	}

	void VariableStorageManager::addToTable_ksi_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue) {
		auto variable = _table_ksi_ze.find(my_height);
		if (variable == end(_table_ksi_ze)) {
			std::array<float, 3> mas = { my_Avalue, my_Bvalue, my_Cvalue };
			_table_ksi_ze.emplace(std::pair<float, std::array<float, 3>>(my_height, mas));
		}

		return;
	}

	void VariableStorageManager::updateValues(const FormDataArgs& my_args) {
		calculate_b_ice(my_args.iceDistrict);
		calculate_w_0(my_args.windDistrict);
		calculate_k_ice(my_args.objectHeight);
		calculate_k_ze(my_args.objectHeight, my_args.locationType);
		calculate_ksi_ze(my_args.objectHeight, my_args.locationType);
		calculate_weight_1(my_args.facing, my_args.weight, my_args.isFacingStandart);
		calculate_weight_2(my_args.subsystem, my_args.profile, my_args.isSubsystemStandart);
		calculate_weight_3(my_args.subsystem, my_args.profile, my_args.isSubsystemStandart);
		calculate_Q_2();
		calculate_q_2();
		calculate_H_1(my_args.v_step_profile_ordinary_area);
		calculate_H_2(my_args.isSubsystemStandart, my_args.subsystem, my_args.v_step_profile_marginal_area);
		calculate_H_3(my_args.isSubsystemStandart, my_args.subsystem, my_args.h_step_profile);
		calculate_B_1(my_args.isSubsystemStandart, my_args.subsystem, my_args.v_step_bracket_ordinary_area, my_args.h_step_bracket_ordinary_area);
		calculate_B_2(my_args.isSubsystemStandart, my_args.subsystem, my_args.v_step_bracket_marginal_area, my_args.h_step_bracket_marginal_area);
		calculate_q_H_1(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_q_H_2(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_q_H_3(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_q_sum_1(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_q_sum_2(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_c_1(my_args.c1, my_args.checkAerodynamicFactor);
		calculate_c_2(my_args.c2, my_args.checkAerodynamicFactor);
		calculate_Q_311();
		calculate_I_312();
		calculate_Q_321();
		calculate_Q_411();
		calculate_q_311();
		calculate_i_312();
		calculate_q_321();
		calculate_q_411();
		calculate_S_1(my_args.subsystem, my_args.isSubsystemStandart);
		calculate_P_1();
		calculate_N_1();
		calculate_P_2();
		calculate_N_2();
		calculate_S_2(my_args.subsystem, my_args.isSubsystemStandart);
		calculate_P_3(my_args.subsystem, my_args.isSubsystemStandart);
		calculate_N_3();
		calculate_qy_0();
		calculate_qy_1();
		calculate_qz_0();
		calculate_qz_1(my_args.isSubsystemStandart, my_args.subsystem);
		calculate_R_1_1(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_R_2_1(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_R_3_1(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_R_1_2(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_R_2_2(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_R_3_2(my_args.subsystem, my_args.bracket, my_args.isSubsystemStandart, my_args.facing_radius);
		calculate_digging_anker();
		
		return;
	}

	void VariableStorageManager::calculate_b_ice(std::shared_ptr<IceDistrict> my_ice_district) {
		_variables.at("b_ice") = _table_b_ice.at(my_ice_district->id);
	}

	void VariableStorageManager::calculate_w_0(std::shared_ptr<WindDistrict> my_wind_district) {
		_variables.at("w_0") = 1000.f * _table_w_0.at(my_wind_district->id);
	}

	void VariableStorageManager::calculate_k_ice(const float& my_height) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		std::vector<float> heights(_table_k_ice.size());
		std::vector<float> values(_table_k_ice.size());

		for (auto& vect : _table_k_ice) {
			heights.push_back(vect.first);
			values.push_back(vect.second);
		}

		_variables.at("k_ice") = utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_k_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		short location_type_id = my_location_type->id;
		std::vector<float> heights(_table_k_ze.size());
		std::vector<float> values(_table_k_ze.size());

		for (auto& vect : _table_k_ze) {
			heights.push_back(vect.first);
			values.push_back(vect.second[location_type_id]);
		}
		
		_variables.at("k_ze") = utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_ksi_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		short location_type_id = my_location_type->id;
		std::vector<float> heights(_table_ksi_ze.size());
		std::vector<float> values(_table_ksi_ze.size());

		for (auto& vect : _table_ksi_ze) {
			heights.push_back(vect.first);
			values.push_back(vect.second[location_type_id]);
		}

		_variables.at("ksi_ze") = utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_weight_1(std::shared_ptr<Facing> my_facing, const float& my_weight, const bool& isFacing) {
		if (isFacing) {
			_variables.at("weight_1") = my_facing->weight;
		}
		else {
			_variables.at("weight_1") = my_weight;
		}
	}

	void VariableStorageManager::calculate_weight_2(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Profile> my_profile, const bool& isSubsystem) {
		if (isSubsystem) {
			_variables.at("weight_2") = my_subsystem->profile_first->weight;
		}
		else{
			if (my_subsystem->name == _SUBSYSTEM_MAXIMA_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {
				_variables.at("weight_2") = my_subsystem->profile_first->weight;
			}
			else {
				_variables.at("weight_2") = my_profile->weight;
			}
		}
	}

	void VariableStorageManager::calculate_weight_3(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Profile> my_profile, const bool& isSubsystem) {
		if (isSubsystem) {
			if (my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {

				_variables.at("weight_3") = my_subsystem->profile_second->weight;
			}
			else {
				_variables.at("weight_3") = 0.f;
			}
		}
		else{
			if (my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_) {
				_variables.at("weight_3") = my_subsystem->profile_second->weight;
			}
			else if (my_subsystem->name == _SUBSYSTEM_MAXIMA_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {
				_variables.at("weight_3") = my_profile->weight;
			}
			else {
				_variables.at("weight_3") = 0.f;
			}
		}
	}

	void VariableStorageManager::calculate_Q_2() {
		_variables.at("Q_2") = getVariable("weight_1") * getVariable("g");
	}

	void VariableStorageManager::calculate_q_2() {
		_variables.at("q_2") = getVariable("Q_2") * getVariable("gamma_f_1");
	}

	void VariableStorageManager::calculate_H_1(const float& my_v_step_profile_ordinary_area) {

		_variables.at("H_1") = my_v_step_profile_ordinary_area;
	}

	void VariableStorageManager::calculate_H_2(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem,
		const float& my_v_step_profile_marginal_area) {

		if (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
			my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
			my_subsystem->name == _SUBSYSTEM_KPR_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_2_) {

			_variables.at("H_2") = 0.f;
		}
		else {
			_variables.at("H_2") = my_v_step_profile_marginal_area;
		}
	}

	void VariableStorageManager::calculate_H_3(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem, const float& my_h_step_profile) {

		if (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_) {

			_variables.at("H_3") = my_h_step_profile;
		}
		else {
			_variables.at("H_3") = 0.f;
		}
	}

	void VariableStorageManager::calculate_B_1(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem,
		const float& my_v_step_bracket_ordinary_area, const float& my_h_step_bracket_ordinary_area) {

		if (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_) {
			_variables.at("B_1") = my_h_step_bracket_ordinary_area;
		}
		else {
			_variables.at("B_1") = my_v_step_bracket_ordinary_area;
		}
	}

	void VariableStorageManager::calculate_B_2(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem,
		const float& my_v_step_bracket_marginal_area, const float& my_h_step_bracket_marginal_area) {

		if ((!isSubsystem) || (isSubsystem && (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
			my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
			my_subsystem->name == _SUBSYSTEM_KPR_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_2_))) {

			_variables.at("B_2") = my_v_step_bracket_marginal_area;
		}
		else if (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_) {
			_variables.at("B_2") = my_h_step_bracket_marginal_area;
		}
		else {
			_variables.at("B_2") = 0.f;
		}
	}

	void VariableStorageManager::calculate_q_H_1(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("q_H_1") = getVariable("weight_2") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_3");
		}
		else {
			_variables.at("q_H_1") = getVariable("weight_2") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_1");
		}
	}

	void VariableStorageManager::calculate_q_H_2(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("q_H_2") = getVariable("weight_3") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_1");
		}
		else if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_)) {

			_variables.at("q_H_2") = getVariable("weight_2") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_2");
		}
		else {
			_variables.at("q_H_2") = 0.f;
		}
	}

	void VariableStorageManager::calculate_q_H_3(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {
		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("q_H_3") = getVariable("weight_3") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_2");
		}
		else if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_)) {
			_variables.at("q_H_3") = getVariable("weight_3") * getVariable("g") * getVariable("gamma_f_2") * 1000.f / getVariable("H_3");
		}
		else {
			_variables.at("q_H_3") = 0.f;
		}
	}

	void VariableStorageManager::calculate_q_sum_1(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("q_sum_1") = getVariable("q_2") + getVariable("q_H_1") + getVariable("q_H_2");
		}
		else if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_)) {
			_variables.at("q_sum_1") = getVariable("q_2") + getVariable("q_H_1") + getVariable("q_H_3");
		}
		else {
			_variables.at("q_sum_1") = getVariable("q_2") + getVariable("q_H_1");
		}
	}

	// междуэтажные
	void VariableStorageManager::calculate_q_sum_2(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("q_sum_2") = getVariable("q_2") + getVariable("q_H_1") + getVariable("q_H_3");
		}
		else if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ || my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_)) {
			_variables.at("q_sum_2") = getVariable("q_2") + getVariable("q_H_2") + getVariable("q_H_3");
		}
		else if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ || my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_)) {
			_variables.at("q_sum_2") = getVariable("q_2") + getVariable("q_H_2");
		}
		else {
			_variables.at("q_sum_2") = 0.f;
		}
	}

	void VariableStorageManager::calculate_c_1(const float& my_c1, const bool& my_checkAerodynamicFactor) {
		_variables.at("c_1") = my_checkAerodynamicFactor ?  my_c1 : _variables.at("c_1_default");
	}

	void VariableStorageManager::calculate_c_2(const float& my_c2, const bool& my_checkAerodynamicFactor) {
		_variables.at("c_2") = my_checkAerodynamicFactor ? my_c2 : _variables.at("c_2_default");
	}

	void VariableStorageManager::calculate_Q_311() {

		_variables.at("Q_311") = 0.25f * getVariable("w_0") * getVariable("k_ze") *
			(1.f + getVariable("ksi_ze")) * getVariable("c_1") * getVariable("nu");
	}

	void VariableStorageManager::calculate_I_312() {

		_variables.at("I_312") = getVariable("b_ice") * getVariable("k_ice") *
			getVariable("mu_2") * getVariable("rho") * getVariable("g") / 1000.f;
	}

	void VariableStorageManager::calculate_Q_321() {

		_variables.at("Q_321") = getVariable("w_0") * getVariable("k_ze") *
			(1.f + getVariable("ksi_ze")) * getVariable("c_1") * getVariable("nu");
	}

	void VariableStorageManager::calculate_Q_411() {

		_variables.at("Q_411") = getVariable("w_0") * getVariable("k_ze") *
			(1.f + getVariable("ksi_ze")) * getVariable("c_2") * getVariable("nu");
	}

	void VariableStorageManager::calculate_q_311() {

		_variables.at("q_311") = getVariable("Q_311") * getVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_i_312() {

		_variables.at("i_312") = getVariable("I_312") * getVariable("gamma_f_4");
	}

	void VariableStorageManager::calculate_q_321() {

		_variables.at("q_321") = getVariable("Q_321") * getVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_q_411() {

		_variables.at("q_411") = getVariable("Q_411") * getVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_qy_0() {
		if (getVariable("q_311") > getVariable("q_321")) {
			_variables.at("qy_0") = getVariable("q_311");
		}
		else {
			_variables.at("qy_0") = getVariable("q_321");
		}
	}

	void VariableStorageManager::calculate_S_1(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem) {

		if ((!isSubsystem) || (isSubsystem && (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
			my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
			my_subsystem->name == _SUBSYSTEM_KPR_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_1_ || 
			my_subsystem->name == _SUBSYSTEM_STRONG_2_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ || my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_))) {

			_variables.at("S_1") = getVariable("B_1") * getVariable("H_1") / 1000000.f;
		}
		else {
			_variables.at("S_1") = getVariable("B_1") * getVariable("H_3") / 1000000.f;
		}
	}

	void VariableStorageManager::calculate_P_1() {

		_variables.at("P_1") = (getVariable("i_312") + getVariable("q_sum_1")) * getVariable("S_1");
	}

	void VariableStorageManager::calculate_N_1() {
		_variables.at("N_1") = getVariable("q_311") * getVariable("S_1");
	}

	void VariableStorageManager::calculate_P_2() {

		_variables.at("P_2") = getVariable("q_sum_1") * getVariable("S_1");
	}

	void VariableStorageManager::calculate_N_2() {
		_variables.at("N_2") = getVariable("q_321") * getVariable("S_1");
	}

	void VariableStorageManager::calculate_S_2(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem) {

		if ((!isSubsystem) || (isSubsystem && (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
			my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
			my_subsystem->name == _SUBSYSTEM_KPR_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_2_))) {

			_variables.at("S_2") = getVariable("B_2") * getVariable("H_1") / 1000000.f;
		}
		else if (my_subsystem->name == _SUBSYSTEM_MAXIMA_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_) {

			_variables.at("S_2") = getVariable("B_1") * getVariable("H_2") / 1000000.f;
		}
		else {
			_variables.at("S_2") = getVariable("B_2") * getVariable("H_3") / 1000000.f;
		}
	}

	void VariableStorageManager::calculate_P_3(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem) {
		if ((!isSubsystem) || (isSubsystem && (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
			my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
			my_subsystem->name == _SUBSYSTEM_KPR_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_STRONG_2_))) {

			_variables.at("P_3") = getVariable("q_sum_1") * getVariable("S_2");
		}
		else {
			_variables.at("P_3") = getVariable("q_sum_2") * getVariable("S_2");
		}
	}

	void VariableStorageManager::calculate_N_3() {
		_variables.at("N_3") = getVariable("q_411") * getVariable("S_2");
	}

	void VariableStorageManager::calculate_qy_1() {

		_variables.at("qy_1") = getVariable("q_411");
	}

	void VariableStorageManager::calculate_qz_0() {

		_variables.at("qz_0") = getVariable("q_sum_1") + getVariable("i_312");
	}

	void VariableStorageManager::calculate_qz_1(const bool& isSubsystem, std::shared_ptr<Subsystem> my_subsystem) {

		if (isSubsystem && (my_subsystem->name == _SUBSYSTEM_MAXIMA_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
			my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
			my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_)) {
				_variables.at("qz_1") = getVariable("q_sum_2");
			}
		else {
			_variables.at("qz_1") = getVariable("q_sum_1");
		}
	}

	void VariableStorageManager::calculate_R_1_1(std::shared_ptr<Subsystem> my_subsystem,
												 std::shared_ptr<Bracket> my_bracket,
												 const bool& isSubsystem,
												 const float& my_facing_radius) {

		if (isSubsystem) {
			if (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
				my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {

				_variables.at("R_1_1") = ((my_subsystem->bracket->x + my_subsystem->bracket->b) * getVariable("N_1") / my_subsystem->bracket->b) +
					(my_facing_radius * getVariable("P_1") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_KPR_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_2_) {

				_variables.at("R_1_1") = getVariable("N_1") + (my_facing_radius * getVariable("P_1") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_) {

				_variables.at("R_1_1") = (getVariable("N_1") + (my_facing_radius * getVariable("P_1") / my_subsystem->bracket->c)) / 2;
			}
			else {
				_variables.at("R_1_1") = (getVariable("P_1") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c));
			}
		}
		else {
			_variables.at("R_1_1") = ((my_bracket->x + my_bracket->b) * getVariable("N_1") / my_bracket->b) +
				(my_facing_radius * getVariable("P_1") / my_bracket->c);
		}
	}

	void VariableStorageManager::calculate_R_2_1(std::shared_ptr<Subsystem> my_subsystem,
												 std::shared_ptr<Bracket> my_bracket,
												 const bool& isSubsystem,
												 const float& my_facing_radius) {

		if (isSubsystem) {
			if (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
				my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {

				_variables.at("R_2_1") = ((my_subsystem->bracket->x + my_subsystem->bracket->b) * getVariable("N_2") / my_subsystem->bracket->b) +
					(my_facing_radius * getVariable("P_2") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_KPR_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_2_) {

				_variables.at("R_2_1") = getVariable("N_2") + (my_facing_radius * getVariable("P_2") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_) {

				_variables.at("R_2_1") = (getVariable("N_2") + (my_facing_radius * getVariable("P_2") / my_subsystem->bracket->c)) / 2;
			}
			else {
				_variables.at("R_2_1") = (getVariable("P_2") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c));
			}
		}
		else {
			_variables.at("R_2_1") = ((my_bracket->x + my_bracket->b) * getVariable("N_2") / my_bracket->b) +
				(my_facing_radius * getVariable("P_2") / my_bracket->c);
		}
	}

	void VariableStorageManager::calculate_R_3_1(std::shared_ptr<Subsystem> my_subsystem,
		std::shared_ptr<Bracket> my_bracket,
		const bool& isSubsystem,
		const float& my_facing_radius) {

		if (isSubsystem) {
			if (my_subsystem->name == _SUBSYSTEM_STANDARD_ ||
				my_subsystem->name == _SUBSYSTEM_OPTIMA_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_MEDIUM_ ||
				my_subsystem->name == _SUBSYSTEM_MAXIMA_LIGHT_) {

				_variables.at("R_3_1") = ((my_subsystem->bracket->x + my_subsystem->bracket->b) * getVariable("N_3") /
					my_subsystem->bracket->b) + (my_facing_radius  * getVariable("P_3") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_KPR_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_STRONG_2_) {

				_variables.at("R_3_1") = getVariable("N_3") + (my_facing_radius * getVariable("P_3") / my_subsystem->bracket->c);
			}
			else if (my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_1_ ||
				my_subsystem->name == _SUBSYSTEM_MEDIUM_STRONG_2_) {

				_variables.at("R_3_1") = (getVariable("N_3") + (my_facing_radius * getVariable("P_3") / my_subsystem->bracket->c)) / 2;
			}
			else {
				_variables.at("R_3_1") = (getVariable("P_3") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c));
			}
		}
		else {
			_variables.at("R_3_1") = ((my_bracket->x + my_bracket->b) * getVariable("N_3") / my_bracket->b) +
				(my_facing_radius * getVariable("P_3") / my_bracket->c);
		}
	}

	void VariableStorageManager::calculate_R_1_2(std::shared_ptr<Subsystem> my_subsystem,
												 std::shared_ptr<Bracket> my_bracket,
												 const bool& isSubsystem,
												 const float& my_facing_radius) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {

			_variables.at("R_1_2") = (getVariable("N_1") / 2) -
				((getVariable("P_1") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c)));
		}
		else {
			_variables.at("R_1_2") = _variables.at("R_1_1");
		}
	}

	void VariableStorageManager::calculate_R_2_2(std::shared_ptr<Subsystem> my_subsystem,
												 std::shared_ptr<Bracket> my_bracket,
												 const bool& isSubsystem,
												 const float& my_facing_radius) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("R_2_2") = (getVariable("N_2") / 2) -
				((getVariable("P_2") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c)));
		}
		else {
			_variables.at("R_2_2") = _variables.at("R_2_1");
		}
	}


	void VariableStorageManager::calculate_R_3_2(std::shared_ptr<Subsystem> my_subsystem,
												 std::shared_ptr<Bracket> my_bracket,
												 const bool& isSubsystem,
												 const float& my_facing_radius) {

		if (isSubsystem && my_subsystem->name == _SUBSYSTEM_MAXIMA_) {
			_variables.at("R_3_2") = (getVariable("N_3") / 2) -
				((getVariable("P_3") * my_facing_radius) / (2 * (my_subsystem->bracket->b + my_subsystem->bracket->c)));
		}
		else {
			_variables.at("R_3_2") = _variables.at("R_3_1");
		}
	}

	void VariableStorageManager::calculate_digging_anker() {
		float tmp = getVariable("R_1_1");

		if (tmp < getVariable("R_1_2")) {
			tmp = getVariable("R_1_2");
		}
		if (tmp < getVariable("R_2_1")) {
			tmp = getVariable("R_2_1");
		}
		if (tmp < getVariable("R_2_2")) {
			tmp = getVariable("R_2_2");
		}
		if (tmp < getVariable("R_3_1")) {
			tmp = getVariable("R_3_1");
		}
		if (tmp < getVariable("R_3_2")) {
			tmp = getVariable("R_3_2");
		}
		
		_variables.at("digging_anker") = tmp;
	}

} // zias
