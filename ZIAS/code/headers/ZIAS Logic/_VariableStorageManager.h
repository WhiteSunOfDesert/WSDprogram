/*	_VariableStorageManager.h
 *
 *	Менеджер численныех переменных и констант, которые учавствуют (или могут участвовать) в вычислениях
 *  создает переменные, хранит, занимается вычислением их значений... и предоставлет к ним доступ
 *
 *	бла-бла-бла
 *	бла-бла-бла
 *
 *	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
 *	All rights reserved.
 */

#pragma once

namespace zias {
	struct FormDataArgs;
	// список переменных и констант, которые желательно не забыть включить в список _variables
	/* variable names				from	isNeedCalculate
	 *					b_ice		 xml		yes
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
	 *					Qy_0		 form		yes
	 *					Qy_1		 form		yes
	 *					Qz_0		 form		yes
	 *					Qz_1		 form		yes
	 *					S_1			 form		yes		// грузовая площадь
	 *					R_1			 form		yes		// расчетное вырывающее усилие (рядовая зона - зимний период)
	 *					R_2			 form		yes		// расчетное вырывающее усилие (рядовая зона - летний период)
	 *					R_3			 form		yes		// расчетное вырывающее усилие (краевая зона - летний период)
	 */
	
	class VariableStorageManager {
	private:
		static std::shared_ptr<VariableStorageManager> _instance;

		static std::map<std::string, float> _variables;

		static std::map<short, float> _table_b_ice;
		static std::map<short, float> _table_w_0;
		static std::map<float, float> _table_k_ice;
		static std::map<float, float(*)[3]> _table_k_ze;
		static std::map<float, float(*)[3]> _table_ksi_ze;

	public:
		static std::shared_ptr<VariableStorageManager>& Instance();

		static void  addVariable(const std::string& my_name, const float& my_value);
		static float getVariable(const std::string& my_name);
		
		static std::map<std::string, float> getVariables();
		static void updateValues(const FormDataArgs& my_args);

		static void addToTable_b_ice(const short& my_ice_district_id, const float& my_value);
		static void addToTable_w_0(const short& my_wind_district_id, const float& my_value);
		static void addToTable_k_ice(const float& my_height, const float& my_value);
		static void addToTable_k_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue);
		static void addToTable_ksi_ze(const float& my_height, const float& my_Avalue, const float& my_Bvalue, const float& my_Cvalue);

	private:		
		static void calculate_b_ice(std::shared_ptr<IceDistrict> my_ice_district);
		static void calculate_w_0(std::shared_ptr<WindDistrict> my_wind_district);
		static void calculate_k_ice(const float& my_height);
		static void calculate_k_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type);
		static void calculate_ksi_ze(const float& my_height, std::shared_ptr<LocationType> my_location_type);

		// TODO: добавляем вычислительные методы для остальных переменных
		static void calculate_weight_1(std::shared_ptr<Facing> my_facing, const float& my_weight, const bool& isFacing);
		static void calculate_weight_2(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Profile> my_profile, const bool& isSubsystem);
		static void calculate_Q_2();
		static void calculate_q_2();
		static void calculate_q_H(const float& my_v_step_profile);
		static void calculate_q_sum();
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
		static void calculate_S_1(const float& my_v_step_bracket_ordinary_area, const float& my_v_step_profile);
		static void calculate_P_1();
		static void calculate_N_1();
		static void calculate_P_2();
		static void calculate_N_2();
		static void calculate_S_2(const float& my_v_step_bracket_ordinary_area, const float& my_v_step_profile);
		static void calculate_P_3();
		static void calculate_N_3();
		static void calculate_qy_0();
		static void calculate_qy_1();
		static void calculate_qz_0();
		static void calculate_qz_1();
		static void calculate_R_1(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Bracket> my_bracket, const bool& isSubsystem, const float& my_facing_radius);
		static void calculate_R_2(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Bracket> my_bracket, const bool& isSubsystem, const float& my_facing_radius);
		static void calculate_R_3(std::shared_ptr<Subsystem> my_subsystem, std::shared_ptr<Bracket> my_bracket, const bool& isSubsystem, const float& my_facing_radius);

	public:
		~VariableStorageManager();
	private:
		VariableStorageManager();
	};
} // zias