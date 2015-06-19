#include "stdafx.h"

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<VariableStorageManager> VariableStorageManager::_instance = nullptr;
	std::map<std::string, float> VariableStorageManager::_variables;
	//std::map<std::string, String^> VariableStorageManager::_stringVariables;
	std::map<short, float> VariableStorageManager::_table_b;
	std::map<short, float> VariableStorageManager::_table_w_0;
	std::map<float, float> VariableStorageManager::_table_k_ice;
	std::map<float, float(*)[3]> VariableStorageManager::_table_k_ze;
	std::map<float, float(*)[3]> VariableStorageManager::_table_ksi_ze;
	// ---------------------

	VariableStorageManager::VariableStorageManager() {
		_variables.clear();
		//_stringVariables.clear();

		_table_b.clear();
		_table_w_0.clear();
		_table_k_ice.clear();
		_table_k_ze.clear();
		_table_ksi_ze.clear();
	}

	VariableStorageManager::~VariableStorageManager() {
		_variables.clear();
		//_stringVariables.clear();

		_table_b.clear();
		_table_w_0.clear();
		_table_k_ice.clear();
		_table_k_ze.clear();
		_table_ksi_ze.clear();
	}

	std::shared_ptr<VariableStorageManager>& VariableStorageManager::Instance() {
		if (_instance == nullptr) {
			_instance.reset(new VariableStorageManager());

			// запихиваем в мапу переменные, которые не будут браться из xml-ки
			std::string vars[] = {
				"weight_1",
				"weight_2",
				"Q_2",
				"q_2",
				"q_H",
				"q_sum",
				"Q_311",
				"Q_312",
				"Q_321",
				"Q_411",
				"q_311",
				"q_312",
				"q_321",
				"q_411",
				"qy_0",
				"qy_1",
				"qz_0",
				"qz_1",
				"S_1",
				"R_1",
				"R_2",
				"R_3"
			};

			for (auto& var : vars) {
				addVariable(var, 0.f);
			}
			// string
			/*std::string vars[] = {
				"zias",
				"subsystem"
			};

			for (auto& var : vars) {
				addStringVariable(var, "");
			}*/

			// TODO: парсим xml
			if (std::tr2::sys::exists(std::tr2::sys::path("..\\bin\\data\\data_source.xml"))) {
				try {
					rapidxml::file<> file("..\\bin\\data\\data_source.xml");
					rapidxml::xml_document<> add_config;
					add_config.parse<0>(file.data());
					auto root = add_config.first_node();

					if (!root) {
						throw std::runtime_error("No root node");
					}

					while (root) {
						for (auto data_source = root->first_node(); data_source != nullptr; data_source = data_source->next_sibling()) {
							if (zias::utils::equals(data_source->name(), "Var_Store")) {
								for (auto var_store = data_source->first_node(); var_store != nullptr; var_store = var_store->next_sibling()) {
									if (zias::utils::equals(var_store->name(), "b")) {
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (zias::utils::equals(var_it->name(), "var")) {
												short ice_district_id = zias::utils::lexical_cast<short>(var_it->first_attribute("ice_district_id")->value());
												float value = zias::utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_b(ice_district_id, value);
											}
										}

										addVariable(name, 0.f);
									}
									if (zias::utils::equals(var_store->name(), "w_0")) {
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (zias::utils::equals(var_it->name(), "var")) {
												short wind_district_id = zias::utils::lexical_cast<short>(var_it->first_attribute("wind_district_id")->value());
												float value = zias::utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_w_0(wind_district_id, value);
											}
										}

										addVariable(name, 0.f);
									}
									if (zias::utils::equals(var_store->name(), "k_ice")) {
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (zias::utils::equals(var_it->name(), "var")) {
												float height = zias::utils::lexical_cast<float>(var_it->first_attribute("height")->value());
												float value = zias::utils::lexical_cast<float>(var_it->first_attribute("value")->value());

												addToTable_k_ice(height, value);
											}
										}
										
										addVariable(name, 0.f);
									}
									if (zias::utils::equals(var_store->name(), "k_ze")) {
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (zias::utils::equals(var_it->name(), "var")) {
												float height = zias::utils::lexical_cast<float>(var_it->first_attribute("z_e")->value());
												float valueA = zias::utils::lexical_cast<float>(var_it->first_attribute("A_value")->value());
												float valueB = zias::utils::lexical_cast<float>(var_it->first_attribute("B_value")->value());
												float valueC = zias::utils::lexical_cast<float>(var_it->first_attribute("C_value")->value());

												addToTable_k_ze(height, valueA, valueB, valueC);
											}
										}

										addVariable(name, 0.f);
									}
									if (zias::utils::equals(var_store->name(), "ksi_ze")) {
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										for (auto var_it = var_store->first_node(); var_it != nullptr; var_it = var_it->next_sibling()) {
											if (zias::utils::equals(var_it->name(), "var")) {
												float height = zias::utils::lexical_cast<float>(var_it->first_attribute("z_e")->value());
												float valueA = zias::utils::lexical_cast<float>(var_it->first_attribute("A_value")->value());
												float valueB = zias::utils::lexical_cast<float>(var_it->first_attribute("B_value")->value());
												float valueC = zias::utils::lexical_cast<float>(var_it->first_attribute("C_value")->value());

												addToTable_ksi_ze(height, valueA, valueB, valueC);
											}
										}

										addVariable(name, 0.f);
									}
									if (   zias::utils::equals(var_store->name(), "mu_2")
										|| zias::utils::equals(var_store->name(), "rho")
										|| zias::utils::equals(var_store->name(), "g")
										|| zias::utils::equals(var_store->name(), "nu")
										|| zias::utils::equals(var_store->name(), "c_1")
										|| zias::utils::equals(var_store->name(), "c_2")
										|| zias::utils::equals(var_store->name(), "gamma_f_1")
										|| zias::utils::equals(var_store->name(), "gamma_f_2")
										|| zias::utils::equals(var_store->name(), "gamma_f_3")
										|| zias::utils::equals(var_store->name(), "gamma_f_4")
										) {
										
										std::string name = zias::utils::lexical_cast<std::string>(var_store->name());
										float value = zias::utils::lexical_cast<float>(var_store->first_attribute("value")->value());
									
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

	/*void  VariableStorageManager::addStringVariable(const std::string& my_name, const String^& my_value) {
		_stringVariables.emplace(my_name, my_value);
	}*/

	float VariableStorageManager::getVariable(const std::string& my_name) {
		auto variable = _variables.find(my_name);
		if (variable != end(_variables)) {
			return _variables[my_name];
		}
		return 0.f;
	}

	/*String^ VariableStorageManager::getStringVariable(const std::string& my_name) {
		auto variable = _stringVariables.find(my_name);
		if (variable != end(_stringVariables)) {
			return _stringVariables[my_name];
		}
		return "";
	}*/

	std::map<std::string, float> VariableStorageManager::getVariables() {
		return _variables;
	}

	/*std::map<std::string, String^> VariableStorageManager::getStringVariables() {
		return _stringVariables;
	}*/

	void VariableStorageManager::addToTable_b(const short& my_ice_district_id, const float& my_value) {
		auto variable = _table_b.find(my_ice_district_id);
		if (variable == end(_table_b)) {
			_table_b.emplace(my_ice_district_id, my_value);
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
			float mas[3] = { my_Avalue, my_Bvalue, my_Cvalue };
			_table_k_ze.emplace(std::pair<float, float(*)[3]>(my_height, &mas));
		}
		return;
	}

	void VariableStorageManager::addToTable_ksi_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue) {
		auto variable = _table_ksi_ze.find(my_height);
		if (variable == end(_table_ksi_ze)) {
			float mas[] = { my_Avalue, my_Bvalue, my_Cvalue };
			_table_ksi_ze.emplace(std::pair<float, float(*)[3]>(my_height, &mas));
		}
		return;
	}

	void VariableStorageManager::updateValues(const FormDataArgs& my_args) {
		calculate_b(my_args.iceDistrict);
		calculate_w_0(my_args.windDistrict);
		calculate_k_ice(my_args.objectHeight);
		calculate_k_ze(my_args.objectHeight, my_args.locationType);
		calculate_ksi_ze(my_args.objectHeight, my_args.locationType);
		calculate_weight_1(my_args.facing, my_args.weight, my_args.isFacingStandart);
		calculate_weight_2(my_args.subsystem ,my_args.profile, my_args.isSubsystemStandart);
		calculate_Q_2();
		calculate_q_2();
		calculate_q_H(my_args.v_step_profile);
		calculate_q_sum();
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
		calculate_qy_0();
		calculate_qy_1();
		calculate_qz_0();
		calculate_qz_1();
		calculate_S_1(my_args.objectHeight, my_args.weight);
		calculate_R_1();
		calculate_R_2();
		calculate_R_3();
		//calculate_ziasN(my_args.facing, my_args.isFacingStandart);
		//calculate_subsystem(my_args.subsystem, my_args.isSubsystemStandart);
		
		return;
	}

	void VariableStorageManager::calculate_b(std::shared_ptr<IceDistrict> my_ice_district) {
		_variables.at("b") = _table_b.at(my_ice_district->id);
	}

	void VariableStorageManager::calculate_w_0(std::shared_ptr<WindDistrict> my_wind_district) {
		_variables.at("w_0") = _table_w_0.at(my_wind_district->id);
	}

	void VariableStorageManager::calculate_k_ice(const float& my_height) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		std::vector<float> heights(_table_k_ice.size());
		std::vector<float> values(_table_k_ice.size());

		for (auto& vect : _table_k_ice) {
			heights.push_back(vect.first);
			values.push_back(vect.second);
		}

		_variables.at("k_ice") = zias::utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_k_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		short location_type_id = my_location_type->id;
		std::vector<float> heights(_table_k_ze.size());
		std::vector<float> values(_table_k_ze.size());

		for (auto& vect : _table_k_ze) {
			heights.push_back(vect.first);
			values.push_back(*(vect.second[location_type_id]));
		}
		
		_variables.at("k_ze") = zias::utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_ksi_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		short location_type_id = my_location_type->id;
		std::vector<float> heights(_table_ksi_ze.size());
		std::vector<float> values(_table_ksi_ze.size());

		for (auto& vect : _table_ksi_ze) {
			heights.push_back(vect.first);
			values.push_back(*(vect.second[location_type_id]));
		}

		_variables.at("ksi_ze") = zias::utils::Interpolate(heights, values, my_height);
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
			_variables.at("weight_2") = my_profile->weight;
		}
	}

	void VariableStorageManager::calculate_Q_2() {
		_variables.at("Q_2") = getVariable("weight_1") * getVariable("g");
	}

	void VariableStorageManager::calculate_q_2() {
		_variables.at("q_2") = getVariable("Q_2") * getVariable("gamma_f_1");
	}

	void VariableStorageManager::calculate_q_H(const float& my_v_step_profile) {
		_variables.at("q_H") = getVariable("weight_2") * getVariable("g") * getVariable("gamma_f_2") /
			my_v_step_profile;
	}

	void VariableStorageManager::calculate_q_sum() {
		_variables.at("q_sum") = getVariable("q_2") + getVariable("q_H");
	}

	void VariableStorageManager::calculate_c_1(const float& my_c1, const bool& my_checkAerodynamicFactor) {
		if (my_checkAerodynamicFactor) {
			_variables.at("c_1") = my_c1;
		}
	}

	void VariableStorageManager::calculate_c_2(const float& my_c2, const bool& my_checkAerodynamicFactor) {
		if (my_checkAerodynamicFactor) {
			_variables.at("c_2") = my_c2;
		}
	}

	void VariableStorageManager::calculate_Q_311() {

		_variables.at("Q_311") = 0.25 * getVariable("w_0") * getVariable("k_ze") *
			(1 + getVariable("ksi_ze")) * getVariable("c_1") * getVariable("nu");
	}

	void VariableStorageManager::calculate_I_312() {

		_variables.at("I_312") = getVariable("b") * getVariable("k_ice") *
			getVariable("mu_2") * getVariable("rho") * getVariable("g");
	}

	void VariableStorageManager::calculate_Q_321() {

		_variables.at("Q_321") = getVariable("w_0") * getVariable("k_ze") *
			(1 + getVariable("ksi_ze")) * getVariable("c_1") * getVariable("nu");
	}

	void VariableStorageManager::calculate_Q_411() {

		_variables.at("Q_411") = getVariable("w_0") * getVariable("k_ze") *
			(1 + getVariable("ksi_ze")) * getVariable("c_2") * getVariable("nu");
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
		if (getVariable("Q_311") > getVariable("Q_321")) {
			_variables.at("qy_0") = getVariable("Q_311");
		}
		else {
			_variables.at("qy_0") = getVariable("Q_321");
		}
	}

	void VariableStorageManager::calculate_qy_1() {

		_variables.at("qy_1") = getVariable("Q_411");
	}

	void VariableStorageManager::calculate_qz_0() {

		_variables.at("qz_0") = getVariable("q_sum") + getVariable("i_312");
	}

	void VariableStorageManager::calculate_qz_1() {

		_variables.at("qz_1") = getVariable("q_sum");
	}

	void VariableStorageManager::calculate_S_1(const float& my_height, const float& my_weight) {

		_variables.at("S_1") = my_height * my_weight;
	}

	void VariableStorageManager::calculate_R_1() {

		_variables.at("R_1") = 0.f;
	}

	void VariableStorageManager::calculate_R_2() {

		_variables.at("R_2") = 0.f;
	}

	void VariableStorageManager::calculate_R_3() {

		_variables.at("R_3") = 0.f;
	}

	/*void VariableStorageManager::calculate_ziasN(std::shared_ptr<Facing> my_facing, const bool& isFacing) {

		if (isFacing) {
			//_stringVariables.at("ziasN") = my_facing->name;
		}
		else {
			_stringVariables.at("ziasN") = "";
		}
	}

	void VariableStorageManager::calculate_subsystem(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem) {

		if (isSubsystem) {
			//_stringVariables.at("subsystem") = my_subsystem->name;
		}
		else {
			_stringVariables.at("subsystem") = "";
		}
	}*/
} // zias
