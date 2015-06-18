#include "stdafx.h"

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<VariableStorageManager> VariableStorageManager::_instance = nullptr;
	std::map<std::string, float> VariableStorageManager::_floatVariables;
	std::map<std::string, String^> VariableStorageManager::_stringVariables;
	std::map<short, float> VariableStorageManager::_table_b;
	std::map<short, float> VariableStorageManager::_table_w_0;
	std::map<float, float> VariableStorageManager::_table_k_ice;
	std::map<float, float(*)[3]> VariableStorageManager::_table_k_ze;
	std::map<float, float(*)[3]> VariableStorageManager::_table_ksi_ze;
	// ---------------------

	VariableStorageManager::VariableStorageManager() {
		_floatVariables.clear();
		_stringVariables.clear();

		_table_b.clear();
		_table_w_0.clear();
		_table_k_ice.clear();
		_table_k_ze.clear();
		_table_ksi_ze.clear();
	}

	VariableStorageManager::~VariableStorageManager() {
		_floatVariables.clear();
		_stringVariables.clear();

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
			// float
			std::string vars[] = {
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
				addFloatVariable(var, 0.f);
			}
			// string
			std::string vars[] = {
				"zias",
				"subsystem"
			};

			for (auto& var : vars) {
				addStringVariable(var, "");
			}

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

										addFloatVariable(name, 0.f);
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

										addFloatVariable(name, 0.f);
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
										
										addFloatVariable(name, 0.f);
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

										addFloatVariable(name, 0.f);
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

										addFloatVariable(name, 0.f);
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
									
										addFloatVariable(name, value);
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

	void  VariableStorageManager::addFloatVariable(const std::string& my_name, const float& my_value) {
		_floatVariables.emplace(my_name, my_value);
	}

	void  VariableStorageManager::addStringVariable(const std::string& my_name, const std::string& my_value) {
		_stringVariables.emplace(my_name, my_value);
	}

	float VariableStorageManager::getFloatVariable(const std::string& my_name) {
		auto variable = _floatVariables.find(my_name);
		if (variable != end(_floatVariables)) {
			return _floatVariables[my_name];
		}
		return 0.f;
	}

	std::string VariableStorageManager::getStringVariable(const std::string& my_name) {
		auto variable = _stringVariables.find(my_name);
		if (variable != end(_stringVariables)) {
			return _stringVariables[my_name];
		}
		return "";
	}

	std::map<std::string, float> VariableStorageManager::getFloatVariables() {
		return _floatVariables;
	}

	std::map<std::string, std::string> VariableStorageManager::getStringVariables() {
		return _stringVariables;
	}

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
		calculate_ziasN(my_args.facing, my_args.isFacingStandart);
		calculate_subsystem(my_args.subsystem, my_args.isSubsystemStandart);
		
		return;
	}

	void VariableStorageManager::calculate_b(std::shared_ptr<IceDistrict> my_ice_district) {
		_floatVariables.at("b") = _table_b.at(my_ice_district->id);
	}

	void VariableStorageManager::calculate_w_0(std::shared_ptr<WindDistrict> my_wind_district) {
		_floatVariables.at("w_0") = _table_w_0.at(my_wind_district->id);
	}

	void VariableStorageManager::calculate_k_ice(const float& my_height) {
		// TODO: вынести выборку "столбоцов" из мапы в отдельную функцию
		
		std::vector<float> heights(_table_k_ice.size());
		std::vector<float> values(_table_k_ice.size());

		for (auto& vect : _table_k_ice) {
			heights.push_back(vect.first);
			values.push_back(vect.second);
		}

		_floatVariables.at("k_ice") = zias::utils::Interpolate(heights, values, my_height);
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
		
		_floatVariables.at("k_ze") = zias::utils::Interpolate(heights, values, my_height);
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

		_floatVariables.at("ksi_ze") = zias::utils::Interpolate(heights, values, my_height);
	}

	void VariableStorageManager::calculate_c_1(const float& my_c1, const bool& my_checkAerodynamicFactor) {
		if (my_checkAerodynamicFactor) {
			_floatVariables.at("c_1") = my_c1;
		}
	}

	void VariableStorageManager::calculate_c_2(const float& my_c2, const bool& my_checkAerodynamicFactor) {
		if (my_checkAerodynamicFactor) {
			_floatVariables.at("c_2") = my_c2;
		}
	}

	void VariableStorageManager::calculate_Q_311() {

		_floatVariables.at("Q_311") = 0.25 * getFloatVariable("w_0") * getFloatVariable("k_ze") *
			(1 + getFloatVariable("ksi_ze")) * getFloatVariable("c_1") * getFloatVariable("nu");
	}

	void VariableStorageManager::calculate_I_312() {

		_floatVariables.at("I_312") = getFloatVariable("b") * getFloatVariable("k_ice") *
			getFloatVariable("mu_2") * getFloatVariable("rho") * getFloatVariable("g");
	}

	void VariableStorageManager::calculate_Q_321() {

		_floatVariables.at("Q_321") = getFloatVariable("w_0") * getFloatVariable("k_ze") *
			(1 + getFloatVariable("ksi_ze")) * getFloatVariable("c_1") * getFloatVariable("nu");
	}

	void VariableStorageManager::calculate_Q_411() {

		_floatVariables.at("Q_411") = getFloatVariable("w_0") * getFloatVariable("k_ze") *
			(1 + getFloatVariable("ksi_ze")) * getFloatVariable("c_2") * getFloatVariable("nu");
	}

	void VariableStorageManager::calculate_q_311() {

		_floatVariables.at("q_311") = getFloatVariable("Q_311") * getFloatVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_i_312() {

		_floatVariables.at("i_312") = getFloatVariable("I_312") * getFloatVariable("gamma_f_4");
	}

	void VariableStorageManager::calculate_q_321() {

		_floatVariables.at("q_321") = getFloatVariable("Q_321") * getFloatVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_q_411() {

		_floatVariables.at("q_411") = getFloatVariable("Q_411") * getFloatVariable("gamma_f_3");
	}

	void VariableStorageManager::calculate_qy_0() {
		if (getFloatVariable("Q_311") > getFloatVariable("Q_321")) {
			_floatVariables.at("qy_0") = getFloatVariable("Q_311");
		}
		else {
			_floatVariables.at("qy_0") = getFloatVariable("Q_321");
		}
	}

	void VariableStorageManager::calculate_qy_1() {

		_floatVariables.at("qy_1") = getFloatVariable("Q_411");
	}

	void VariableStorageManager::calculate_qz_0() {

		_floatVariables.at("qz_0") = 0.f;
	}

	void VariableStorageManager::calculate_qz_1() {

		_floatVariables.at("qz_1") = 0.f;
	}

	void VariableStorageManager::calculate_S_1(const float& my_height, const float& my_weight) {

		_floatVariables.at("S_1") = my_height * my_weight;
	}

	void VariableStorageManager::calculate_R_1() {

		_floatVariables.at("R_1") = 0.f;
	}

	void VariableStorageManager::calculate_R_2() {

		_floatVariables.at("R_2") = 0.f;
	}

	void VariableStorageManager::calculate_R_3() {

		_floatVariables.at("R_3") = 0.f;
	}

	void VariableStorageManager::calculate_ziasN(std::shared_ptr<Facing> my_facing, const bool& isFacing) {

		if (isFacing) {
			_stringVariables.at("ziasN") = my_facing->name;
		}
		else {
			_stringVariables.at("ziasN") = "";
		}
	}

	void VariableStorageManager::calculate_subsystem(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem) {

		if (isSubsystem) {
			_stringVariables.at("subsystem") = my_subsystem->name;
		}
		else {
			_stringVariables.at("subsystem") = "";
		}
	}
} // zias
