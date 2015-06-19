#include "stdafx.h"

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<FormDataStorageManager> FormDataStorageManager::_instance = nullptr;
	std::vector<std::shared_ptr<City>> FormDataStorageManager::_cities;
	std::vector<std::shared_ptr<WindDistrict>> FormDataStorageManager::_wind_districts;
	std::vector<std::shared_ptr<IceDistrict>> FormDataStorageManager::_ice_district;
	std::vector<std::shared_ptr<LocationType>> FormDataStorageManager::_location_types;
	std::vector<std::shared_ptr<Facing>> FormDataStorageManager::_facings;
	std::vector<std::shared_ptr<Subsystem>> FormDataStorageManager::_subsystems;
	std::vector<std::shared_ptr<Bracket>> FormDataStorageManager::_brackets;
	std::vector<std::shared_ptr<Profile>> FormDataStorageManager::_profiles;
	// ---------------------
	
	FormDataStorageManager::FormDataStorageManager() {
		_cities.clear();
		_wind_districts.clear();
		_ice_district.clear();
		_location_types.clear();
		_facings.clear();
		_subsystems.clear();
		_brackets.clear();
		_profiles.clear();
	}

	FormDataStorageManager::~FormDataStorageManager() {
		_cities.clear();
		_wind_districts.clear();
		_ice_district.clear();
		_location_types.clear();
		_facings.clear();
		_subsystems.clear();
		_brackets.clear();
		_profiles.clear();
	}

	std::shared_ptr<FormDataStorageManager>& FormDataStorageManager::Instance() {
		if (_instance == nullptr) {
			_instance.reset(new FormDataStorageManager());

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
							if (zias::utils::equals(data_source->name(), "Entity_Store")) {
								for (auto entity_store = data_source->first_node(); entity_store != nullptr; entity_store = entity_store->next_sibling()) {
									if (zias::utils::equals(entity_store->name(), "Wind_Districts")) {
										for (auto wind_districts = entity_store->first_node(); wind_districts != nullptr; wind_districts = wind_districts->next_sibling()) {
											if (zias::utils::equals(wind_districts->name(), "wind_district")) {
												short id = zias::utils::lexical_cast<short>(wind_districts->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(wind_districts->first_attribute("name")->value());
												
												addWindDistrict(id, name);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Ice_Districts")) {
										for (auto ice_districts = entity_store->first_node(); ice_districts != nullptr; ice_districts = ice_districts->next_sibling()) {
											if (zias::utils::equals(ice_districts->name(), "ice_district")) {
												short id = zias::utils::lexical_cast<short>(ice_districts->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(ice_districts->first_attribute("name")->value());
	
												addIceDistrict(id, name);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Location_Types")) {
										for (auto location_types = entity_store->first_node(); location_types != nullptr; location_types = location_types->next_sibling()) {
											if (zias::utils::equals(location_types->name(), "location_type")) {
												short id = zias::utils::lexical_cast<short>(location_types->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(location_types->first_attribute("name")->value());

												addLocationType(id, name);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Cities")) {
										for (auto cities = entity_store->first_node(); cities != nullptr; cities = cities->next_sibling()) {
											if (zias::utils::equals(cities->name(), "city")) {
												short id = zias::utils::lexical_cast<short>(cities->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(cities->first_attribute("name")->value());
												short wind_district = zias::utils::lexical_cast<short>(cities->first_attribute("wind_district_id")->value());
												short ice_district = zias::utils::lexical_cast<short>(cities->first_attribute("ice_district_id")->value());

												addCity(id, name, getWindDistrict(wind_district), getIceDistrict(ice_district));
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Facings")) {
										for (auto facings = entity_store->first_node(); facings != nullptr; facings = facings->next_sibling()) {
											if (zias::utils::equals(facings->name(), "facing")) {
												short id = zias::utils::lexical_cast<short>(facings->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(facings->first_attribute("name")->value());
												short weight = zias::utils::lexical_cast<short>(facings->first_attribute("weight")->value());
												std::string ziasN = zias::utils::lexical_cast<std::string>(facings->first_attribute("zias")->value());

												addFacing(id, name, weight, ziasN);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Subsystems")) {
										for (auto subsystems = entity_store->first_node(); subsystems != nullptr; subsystems = subsystems->next_sibling()) {
											if (zias::utils::equals(subsystems->name(), "subsystem")) {
												short id = zias::utils::lexical_cast<short>(subsystems->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(subsystems->first_attribute("name")->value());
												short bracket = zias::utils::lexical_cast<short>(subsystems->first_attribute("bracket_id")->value());
												short profile_first = zias::utils::lexical_cast<short>(subsystems->first_attribute("profile_id_first")->value());
												short profile_second = zias::utils::lexical_cast<short>(subsystems->first_attribute("profile_id_second")->value());
												std::string solution = zias::utils::lexical_cast<std::string>(subsystems->first_attribute("solution")->value());

												addSubsystem(id, name, getBracket(bracket), getProfile(profile_first), getProfile(profile_second), solution);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Brackets")) {
										for (auto brackets = entity_store->first_node(); brackets != nullptr; brackets = brackets->next_sibling()) {
											if (zias::utils::equals(brackets->name(), "bracket")) {
												short id = zias::utils::lexical_cast<short>(brackets->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(brackets->first_attribute("name")->value());
												
												addBracket(id, name);
											}
										}
									}
									if (zias::utils::equals(entity_store->name(), "Profiles")) {
										for (auto profiles = entity_store->first_node(); profiles != nullptr; profiles = profiles->next_sibling()) {
											if (zias::utils::equals(profiles->name(), "profile")) {
												short id = zias::utils::lexical_cast<short>(profiles->first_attribute("id")->value());
												std::string name = zias::utils::lexical_cast<std::string>(profiles->first_attribute("name")->value());
												short weight = zias::utils::lexical_cast<short>(profiles->first_attribute("weight")->value());

												addProfile(id, name, weight);
											}
										}
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
			} else {
				throw std::runtime_error("Not found file: \"data_source.xml\"");
			}
		}

		return _instance;
	}

	void FormDataStorageManager::addCity(const short& my_id, 
										 const std::string& my_name, 
										 std::shared_ptr<WindDistrict> my_wind_district, 
										 std::shared_ptr<IceDistrict> my_ice_district) {

		if (!getCity(my_id) && !getCity(my_name)) {
			_cities.emplace_back(new City(my_id, my_name, my_wind_district, my_ice_district));
		}
	}

	void FormDataStorageManager::addWindDistrict(const short& my_id, const std::string& my_name) {
		if (!getWindDistrict(my_id) && !getWindDistrict(my_name)) {
			_wind_districts.emplace_back(new WindDistrict(my_id, my_name));
		}
	}

	void FormDataStorageManager::addIceDistrict(const short& my_id, const std::string& my_name) {
		if (!getIceDistrict(my_id) && !getIceDistrict(my_name)) {
			_ice_district.emplace_back(new IceDistrict(my_id, my_name));
		}
	}

	void FormDataStorageManager::addLocationType(const short& my_id, const std::string& my_name) {
		if (!getLocationType(my_id) && !getLocationType(my_name)) {
			_location_types.emplace_back(new LocationType(my_id, my_name));
		}
	}

	void FormDataStorageManager::addFacing(const short& my_id,
										   const std::string& my_name,
										   const short& my_weight,
										   const std::string& my_ziasN) {
		if (!getFacing(my_id) && !getFacing(my_name)) {
			_facings.emplace_back(new Facing(my_id, my_name, my_weight, my_ziasN));
		}
	}

	void FormDataStorageManager::addSubsystem(const short& my_id,
											  const std::string& my_name,
											  std::shared_ptr<Bracket> my_bracket,
											  std::shared_ptr<Profile> my_profile_first,
											  std::shared_ptr<Profile> my_profile_second,
											  const std::string& my_solution) {
		if (!getSubsystem(my_id) && !getSubsystem(my_name)) {
			_subsystems.emplace_back(new Subsystem(my_id, my_name, my_bracket, my_profile_first, my_profile_second, my_solution));
		}
	}

	void FormDataStorageManager::addBracket(const short& my_id, const std::string& my_name) {
		if (!getBracket(my_id) && !getBracket(my_name)) {
			_brackets.emplace_back(new Bracket(my_id, my_name));
		}
	}

	void FormDataStorageManager::addProfile(const short& my_id,
											const std::string& my_name,
											const short& my_weight) {
		if (!getProfile(my_id) && !getProfile(my_name)) {
			_profiles.emplace_back(new Profile(my_id, my_name, my_weight));
		}
	}

	std::shared_ptr<City> FormDataStorageManager::getCity(const short& my_id) {
		for (auto& value : _cities) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<City> FormDataStorageManager::getCity(const std::string& my_name) {
		for (auto& value : _cities) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<WindDistrict> FormDataStorageManager::getWindDistrict(const short& my_id) {
		for (auto& value : _wind_districts) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<WindDistrict> FormDataStorageManager::getWindDistrict(const std::string& my_name) {
		for (auto& value : _wind_districts) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<IceDistrict> FormDataStorageManager::getIceDistrict(const short& my_id) {
		for (auto& value : _ice_district) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<IceDistrict> FormDataStorageManager::getIceDistrict(const std::string& my_name) {
		for (auto& value : _ice_district) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<LocationType> FormDataStorageManager::getLocationType(const short& my_id) {
		for (auto& value : _location_types) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<LocationType> FormDataStorageManager::getLocationType(const std::string& my_name) {
		for (auto& value : _location_types) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Facing> FormDataStorageManager::getFacing(const short& my_id) {
		for (auto& value : _facings) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Facing> FormDataStorageManager::getFacing(const std::string& my_name) {
		for (auto& value : _facings) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Subsystem> FormDataStorageManager::getSubsystem(const short& my_id) {
		for (auto& value : _subsystems) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Subsystem> FormDataStorageManager::getSubsystem(const std::string& my_name) {
		for (auto& value : _subsystems) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Bracket> FormDataStorageManager::getBracket(const short& my_id) {
		for (auto& value : _brackets) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Bracket> FormDataStorageManager::getBracket(const std::string& my_name) {
		for (auto& value : _brackets) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Profile> FormDataStorageManager::getProfile(const short& my_id) {
		for (auto& value : _profiles) {
			if (value->id == my_id) {
				return value;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Profile> FormDataStorageManager::getProfile(const std::string& my_name) {
		for (auto& value : _profiles) {
			if (value->name == my_name) {
				return value;
			}
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<City>> FormDataStorageManager::getCities() {
		return _cities;
	}

	std::vector<std::shared_ptr<WindDistrict>> FormDataStorageManager::getWindDistricts() {
		return _wind_districts;
	}

	std::vector<std::shared_ptr<IceDistrict>> FormDataStorageManager::getIceDistricts() {
		return _ice_district;
	}

	std::vector<std::shared_ptr<LocationType>> FormDataStorageManager::getLocationTypes() {
		return _location_types;
	}

	std::vector<std::shared_ptr<Facing>> FormDataStorageManager::getFacings() {
		return _facings;
	}

	std::vector<std::shared_ptr<Subsystem>> FormDataStorageManager::getSubsystems() {
		return _subsystems;
	}

	std::vector<std::shared_ptr<Bracket>> FormDataStorageManager::getBrackets() {
		return _brackets;
	}

	std::vector<std::shared_ptr<Profile>> FormDataStorageManager::getProfiles() {
		return _profiles;
	}
} // zias
