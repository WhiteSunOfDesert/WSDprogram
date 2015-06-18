#pragma once

namespace zias {
	struct FormDataArgs;
	// список переменных и констант, которые желательно не забыть включить в список _variables
	/* variable names				from	isNeedCalculate
	 *					b			 xml		yes
	 *					w_0			 xml		yes
	 *					k_ice		 xml		yes
	 *					k_ze		 xml		yes
	 *					ksi_ze		 xml		yes
	 *					mu_2		 xml		no
	 *					rho			 xml		no
	 *					g			 xml		no
	 *					nu			 xml		no
	 *					c_1			 xml		no
	 *					c_2			 xml		no
	 *					gamma_f_1	 xml		no
	 *					gamma_f_2	 xml		no
	 *					gamma_f_3	 xml		no
	 *					gamma_f_4	 xml		no
	 *
	 *					qy_0		 form		yes
	 *					qy_1		 form		yes
	 *					qz_0		 form		yes
	 *					qz_1		 form		yes
	 *					S_1			 form		yes		// грузовая площадь
	 *					R_1			 form		yes		// расчетное вырывающее усилие (рядовая зона - зимний период)
	 *					R_2			 form		yes		// расчетное вырывающее усилие (рядовая зона - летний период)
	 *					R_3			 form		yes		// расчетное вырывающее усилие (краевая зона - летний период)
	 */
	
	class VariableStorageManager {
	private:
		static std::shared_ptr<VariableStorageManager> _instance;

		static std::map<std::string, float> _floatVariables;
		static std::map<std::string, String^> _stringVariables;

		static std::map<short, float> _table_b;
		static std::map<short, float> _table_w_0;
		static std::map<float, float> _table_k_ice;
		static std::map<float, float(*)[3]> _table_k_ze;
		static std::map<float, float(*)[3]> _table_ksi_ze;

	public:
		static std::shared_ptr<VariableStorageManager>& Instance();

		static void  addFloatVariable(const std::string& my_name, const float& my_value);
		static void  addStringVariable(const std::string& my_name, const String^& my_value);
		static float getFloatVariable(const std::string& my_name);
		static std::string getStringVariable(const std::string& my_name);
		
		static std::map<std::string, float> getFloatVariables();
		static std::map<std::string, String^> getStringVariables();
		static void updateValues(const FormDataArgs& my_args);

		static void addToTable_b(const short& my_ice_district_id, const float& my_value);
		static void addToTable_w_0(const short& my_wind_district_id, const float& my_value);
		static void addToTable_k_ice(const float& my_height, const float& my_value);
		static void addToTable_k_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue);
		static void addToTable_ksi_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue);

	private:		
		static void calculate_b(std::shared_ptr<IceDistrict> my_ice_district);
		static void calculate_w_0(std::shared_ptr<WindDistrict> my_wind_district);
		static void calculate_k_ice(const float& my_height);
		static void calculate_k_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type);
		static void calculate_ksi_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type);

		// TODO: добавляем вычислительные методы для остальных переменных
		static void calculate_c_1(const float& my_c1, const bool& my_checkAerodynamicFactor);
		static void calculate_c_2(const float& my_c2, const bool& my_checkAerodynamicFactor);
		static void calculate_Q_311();
		static void calculate_I_312();
		static void calculate_Q_321();
		static void calculate_Q_411();
		static void calculate_q_311();
		static void calculate_i_312();
		static void calculate_q_321();
		static void calculate_q_411();
		static void calculate_qy_0();
		static void calculate_qy_1();
		static void calculate_qz_0();
		static void calculate_qz_1();
		static void calculate_S_1(const float& my_height, const float& my_weight);
		static void calculate_R_1();
		static void calculate_R_2();
		static void calculate_R_3();
		static void calculate_ziasN(std::shared_ptr<Facing> my_facing, const bool& isFacing);
		static void calculate_subsystem(std::shared_ptr<Subsystem> my_subsystem, const bool& isSubsystem);

	public:
		~VariableStorageManager();
	private:
		VariableStorageManager();
	};
} // zias