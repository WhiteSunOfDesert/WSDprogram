#pragma once

namespace zias {
	
	struct WindDistrict {
		short id;
		std::string name;

		WindDistrict(short my_id = -1, std::string my_name = "") : id(my_id), name(my_name) {}
	};

	struct IceDistrict {
		short id;
		std::string name;

		IceDistrict(short my_id = -1, std::string my_name = "") : id(my_id), name(my_name) {}
	};

	struct City {
		short id;
		std::string name;
		std::shared_ptr<WindDistrict> wind_district;
		std::shared_ptr<IceDistrict> ice_district;

		City(short my_id = -1, std::string my_name = "", std::shared_ptr<WindDistrict> my_wind_district = nullptr, std::shared_ptr<IceDistrict> ice_district = nullptr)
			: id(my_id)
			, name(my_name)
			, wind_district(my_wind_district)
			, ice_district(ice_district) {}
	};

	struct LocationType {
		short id;
		std::string name;

		LocationType(short my_id = -1, std::string my_name = "") : id(my_id), name(my_name) {}
	};

	struct Facing {
		short id;
		std::string name;
		short weight;
		std::string ziasN;

		Facing(short my_id = -1, std::string my_name = "", short my_weight = -1, std::string my_ziasN = "")
			  : id(my_id),
			  name(my_name),
			  weight(my_weight),
			  ziasN(my_ziasN) {}
	};

	struct Subsystem {
		short id;
		std::string name;
		std::string solution;

		Subsystem(short my_id = -1, std::string my_name = "", std::string my_solution = "")
				 : id(my_id),
				 name(my_name),
				 solution(my_solution) {}
	};

	struct Bracket {
		short id;
		std::string name;

		Bracket(short my_id = -1, std::string my_name = "") : id(my_id), name(my_name) {}
	};

	struct Profile {
		short id;
		std::string name;

		Profile(short my_id = -1, std::string my_name = "") : id(my_id), name(my_name) {}
	};

	class FormDataStorageManager {
		private:
			static std::shared_ptr<FormDataStorageManager> _instance;

			static std::vector<std::shared_ptr<City>> _cities;
			static std::vector<std::shared_ptr<WindDistrict>> _wind_districts;
			static std::vector<std::shared_ptr<IceDistrict>> _ice_district;
			static std::vector<std::shared_ptr<LocationType>> _location_types;
			static std::vector<std::shared_ptr<Facing>> _facings;
			static std::vector<std::shared_ptr<Subsystem>> _subsystems;
			static std::vector<std::shared_ptr<Bracket>> _brackets;
			static std::vector<std::shared_ptr<Profile>> _profiles;
		public:
			static std::shared_ptr<FormDataStorageManager>& Instance();

			static void addCity(const short& my_id, 
								const std::string& my_name, 
								std::shared_ptr<WindDistrict> my_wind_district, 
								std::shared_ptr<IceDistrict> my_ice_district);

			static void addWindDistrict(const short& my_id, const std::string& my_name);
			static void addIceDistrict(const short& my_id, const std::string& my_name);
			static void addLocationType(const short& my_id, const std::string& my_name);
			static void addFacing(const short& my_id,
								  const std::string& my_name,
								  const short& my_weight,
								  const std::string& my_ziasN);

			static void addSubsystem(const short& my_id,
									 const std::string& my_name,
									 const std::string& my_solution);

			static void addBracket(const short& my_id, const std::string& my_name);
			static void addProfile(const short& my_id, const std::string& my_name);

			static std::shared_ptr<City> getCity(const short& my_id);
			static std::shared_ptr<City> getCity(const std::string& my_name);

			static std::shared_ptr<WindDistrict> getWindDistrict(const short& my_id);
			static std::shared_ptr<WindDistrict> getWindDistrict(const std::string& my_name);

			static std::shared_ptr<IceDistrict> getIceDistrict(const short& my_id);
			static std::shared_ptr<IceDistrict> getIceDistrict(const std::string& my_name);

			static std::shared_ptr<LocationType> getLocationType(const short& my_id);
			static std::shared_ptr<LocationType> getLocationType(const std::string& my_name);

			static std::shared_ptr<Facing> getFacing(const short& my_id);
			static std::shared_ptr<Facing> getFacing(const std::string& my_name);

			static std::shared_ptr<Subsystem> getSubsystem(const short& my_id);
			static std::shared_ptr<Subsystem> getSubsystem(const std::string& my_name);

			static std::shared_ptr<Bracket> getBracket(const short& my_id);
			static std::shared_ptr<Bracket> getBracket(const std::string& my_name);

			static std::shared_ptr<Profile> getProfile(const short& my_id);
			static std::shared_ptr<Profile> getProfile(const std::string& my_name);
			
			static std::vector<std::shared_ptr<City>> getCities();
			static std::vector<std::shared_ptr<WindDistrict>> getWindDistricts();
			static std::vector<std::shared_ptr<IceDistrict>> getIceDistricts();
			static std::vector<std::shared_ptr<LocationType>> getLocationTypes();
			static std::vector<std::shared_ptr<Facing>> getFacings();
			static std::vector<std::shared_ptr<Subsystem>> getSubsystems();
			static std::vector<std::shared_ptr<Bracket>> getBrackets();
			static std::vector<std::shared_ptr<Profile>> getProfiles();
		public:
			~FormDataStorageManager();
		private:
			FormDataStorageManager();
	};
} // zias
