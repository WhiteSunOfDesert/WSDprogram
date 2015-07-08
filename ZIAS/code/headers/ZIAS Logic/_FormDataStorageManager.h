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
		short x;
		short b;
		short c;

		Bracket(short my_id = -1, std::wstring my_name = L"", short my_x = -1, short my_b = -1, short my_c = -1)
			: id(my_id),
			name(my_name),
			x(my_x),
			b(my_b),
			c(my_c){}
	};

	struct Profile {
		short id;
		std::wstring name;
		float weight;

		Profile(short my_id = -1, std::wstring my_name = L"", float my_weight = -1) : id(my_id), name(my_name), weight(my_weight) {}
	};

	struct Subsystem {
		short id;
		std::wstring name;
		std::shared_ptr<Bracket> bracket;
		std::shared_ptr<Profile> profile_first;
		std::shared_ptr<Profile> profile_second;
		std::wstring solution;
		std::vector<std::shared_ptr<Bracket>> brackets;
		std::vector<std::shared_ptr<Profile>> profiles;

		Subsystem(short my_id = -1, std::wstring my_name = L"", std::shared_ptr<Bracket> my_bracket = nullptr, std::shared_ptr<Profile> my_profile_first = nullptr, std::shared_ptr<Profile> my_profile_second = nullptr, std::wstring my_solution = L"")
				 : id(my_id),
				 name(my_name),
				 bracket(my_bracket),
				 profile_first(my_profile_first),
				 profile_second(my_profile_second),
				 solution(my_solution) {}
	};

	struct Construction {
		short id;
		short subsystem_id;
		bool v_bracket_rz;
		bool v_bracket_kz;
		bool h_bracket_rz;
		bool h_bracket_kz;
		bool v_profile_rz;
		bool v_profile_kz;
		bool h_profile;

		Construction(short my_id = -1, short my_subsystem_id = -1, bool my_v_bracket_rz = false, bool my_v_bracket_kz = false, bool my_h_bracket_rz = false, bool my_h_bracket_kz = false, bool my_v_profile_rz = false, bool my_v_profile_kz = false, bool my_h_profile = false)
			: id(my_id),
			subsystem_id(my_subsystem_id),
			v_bracket_rz(my_v_bracket_rz),
			v_bracket_kz(my_v_bracket_kz),
			h_bracket_rz(my_h_bracket_rz),
			h_bracket_kz(my_h_bracket_kz),
			v_profile_rz(my_v_profile_rz),
			v_profile_kz(my_v_profile_kz),
			h_profile(my_h_profile) {}
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
			static std::vector<std::shared_ptr<Construction>> _constructions;
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
			
			static void addConstruction(const short& my_id,
				const short& my_subsystem_id,
				const bool& my_v_bracket_rz,
				const bool& my_v_bracket_kz,
				const bool& my_h_bracket_rz,
				const bool& my_h_bracket_kz,
				const bool& my_v_profile_rz,
				const bool& my_v_profile_kz,
				const bool& my_h_profile);

			static void addBracket(	const short& my_id,
									const std::wstring& my_name,
									const short& my_x,
									const short& my_b,
									const short& my_c);

			static void addProfile(const short& my_id, const std::wstring& my_name, const float& my_weight);

			static void addSubBr(const short& my_id, const short& my_sub_id, const short& my_br_id);
			static void addSubPr(const short& my_id, const short& my_sub_id, const short& my_pr_id);

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

			static std::shared_ptr<Construction> getConstruction(const short& my_subsystem_id);

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
			static std::vector<std::shared_ptr<Construction>> getConstructions();
			static std::vector<std::shared_ptr<Bracket>> getBrackets();
			static std::vector<std::shared_ptr<Profile>> getProfiles();
		
		public:
			~FormDataStorageManager();
		private:
			FormDataStorageManager();
	};
} // zias
