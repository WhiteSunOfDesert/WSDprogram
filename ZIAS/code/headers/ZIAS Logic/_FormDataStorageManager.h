/*	_FormDataStorageManager.h
 *
 *	Хранилище сущностей, которые учавствуют в проекте...
 *  создает, заполняет, хранит и предоставляет доступ к этим сущностям
 *
 *	бла-бла-бла
 *	бла-бла-бла
 *
 *	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
 *	All rights reserved.
 */

#pragma once

namespace zias {
	
	struct WindDistrict {
		short id;
		std::wstring name;

		WindDistrict(short my_id = -1, std::wstring my_name = L"") : id(my_id), name(my_name) {}
	};

	struct IceDistrict {
		short id;
		std::wstring name;

		IceDistrict(short my_id = -1, std::wstring my_name = L"") : id(my_id), name(my_name) {}
	};

	struct City {
		short id;
		std::wstring name;
		std::shared_ptr<WindDistrict> wind_district;
		std::shared_ptr<IceDistrict> ice_district;

		City(short my_id = -1, std::wstring my_name = L"", std::shared_ptr<WindDistrict> my_wind_district = nullptr, std::shared_ptr<IceDistrict> ice_district = nullptr)
			: id(my_id)
			, name(my_name)
			, wind_district(my_wind_district)
			, ice_district(ice_district) {}
	};

	struct LocationType {
		short id;
		std::wstring name;

		LocationType(short my_id = -1, std::wstring my_name = L"") : id(my_id), name(my_name) {}
	};

	struct Facing {
		short id;
		std::wstring name;
		short weight;
		std::wstring ziasN;

		Facing(short my_id = -1, std::wstring my_name = L"", short my_weight = -1, std::wstring my_ziasN = L"")
			  : id(my_id),
			  name(my_name),
			  weight(my_weight),
			  ziasN(my_ziasN) {}
	};

	struct Bracket {
		short id;
		std::wstring name;

		Bracket(short my_id = -1, std::wstring my_name = L"") : id(my_id), name(my_name) {}
	};

	struct Profile {
		short id;
		std::wstring name;
		short weight;

		Profile(short my_id = -1, std::wstring my_name = L"", short my_weight = -1) : id(my_id), name(my_name), weight(my_weight) {}
	};

	struct Subsystem {
		short id;
		std::wstring name;
		std::shared_ptr<Bracket> bracket;
		std::shared_ptr<Profile> profile_first;
		std::shared_ptr<Profile> profile_second;
		std::wstring solution;

		Subsystem(short my_id = -1, std::wstring my_name = L"", std::shared_ptr<Bracket> my_bracket = nullptr, std::shared_ptr<Profile> my_profile_first = nullptr, std::shared_ptr<Profile> my_profile_second = nullptr, std::wstring my_solution = L"")
				 : id(my_id),
				 name(my_name),
				 bracket(my_bracket),
				 profile_first(my_profile_first),
				 profile_second(my_profile_second),
				 solution(my_solution) {}
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
								const std::wstring& my_name,
								std::shared_ptr<WindDistrict> my_wind_district, 
								std::shared_ptr<IceDistrict> my_ice_district);

			static void addWindDistrict(const short& my_id, const std::wstring& my_name);
			static void addIceDistrict(const short& my_id, const std::wstring& my_name);
			static void addLocationType(const short& my_id, const std::wstring& my_name);
			static void addFacing(	const short& my_id,
									const std::wstring& my_name,
									const short& my_weight,
									const std::wstring& my_ziasN);

			static void addSubsystem(	const short& my_id,
										const std::wstring& my_name,
										std::shared_ptr<Bracket> my_bracket,
										std::shared_ptr<Profile> my_profile_first,
										std::shared_ptr<Profile> my_profile_second,
										const std::wstring& my_solution);

			static void addBracket(const short& my_id, const std::wstring& my_name);
			static void addProfile(const short& my_id, const std::wstring& my_name, const short& my_weight);

			static std::shared_ptr<City> getCity(const short& my_id);
			static std::shared_ptr<City> getCity(const std::wstring& my_name);

			static std::shared_ptr<WindDistrict> getWindDistrict(const short& my_id);
			static std::shared_ptr<WindDistrict> getWindDistrict(const std::wstring& my_name);

			static std::shared_ptr<IceDistrict> getIceDistrict(const short& my_id);
			static std::shared_ptr<IceDistrict> getIceDistrict(const std::wstring& my_name);

			static std::shared_ptr<LocationType> getLocationType(const short& my_id);
			static std::shared_ptr<LocationType> getLocationType(const std::wstring& my_name);

			static std::shared_ptr<Facing> getFacing(const short& my_id);
			static std::shared_ptr<Facing> getFacing(const std::wstring& my_name);

			static std::shared_ptr<Subsystem> getSubsystem(const short& my_id);
			static std::shared_ptr<Subsystem> getSubsystem(const std::wstring& my_name);

			static std::shared_ptr<Bracket> getBracket(const short& my_id);
			static std::shared_ptr<Bracket> getBracket(const std::wstring& my_name);

			static std::shared_ptr<Profile> getProfile(const short& my_id);
			static std::shared_ptr<Profile> getProfile(const std::wstring& my_name);
			
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
