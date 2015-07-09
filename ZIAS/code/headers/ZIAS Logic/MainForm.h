/*	_MainForm.h
 *
 *	Главная форма, основа основ приложения ZIAS
 *  весь интерактив с пользователем протекает здесь
 *
 *	бла-бла-бла
 *	бла-бла-бла
 *
 *	all rights reserved (*) 20.06.2015
 */

#pragma once

namespace zias {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
		
	struct FormDataArgs {
		std::shared_ptr<City>			city;
		std::shared_ptr<WindDistrict>	windDistrict;
		std::shared_ptr<IceDistrict>	iceDistrict;
		std::shared_ptr<LocationType>	locationType;
		std::shared_ptr<Facing>			facing;
		std::shared_ptr<Subsystem>		subsystem;
		std::shared_ptr<Bracket>		bracket;
		std::shared_ptr<Profile>		profile;
		std::wstring					objectName;
		std::wstring					objectCipher;
		std::wstring					objectResponsible;
		float							objectHeight;
		bool							isCityClimate;
		bool							checkAerodynamicFactor;
		float							c1;
		float							c2;
		bool							checkAnker;
		bool							checkNVFConnection;
		bool							checkNVFElements;
		float							weight;
		bool							isFacingStandart;
		bool							isSubsystemStandart;
		float							v_step_profile_ordinary_area;
		float							v_step_profile_marginal_area;
		float							h_step_profile;
		float							facing_radius;
		float							v_step_bracket_ordinary_area;
		float							v_step_bracket_marginal_area;
		float							h_step_bracket_ordinary_area;
		float							h_step_bracket_marginal_area;
		std::wstring					conclusion;

		FormDataArgs() : 
			city(nullptr),
			windDistrict(nullptr),
			iceDistrict(nullptr),
			locationType(nullptr),
			facing(nullptr),
			subsystem(nullptr),
			bracket(nullptr),
			profile(nullptr),
			objectName(L""),
			objectCipher(L""),
			objectResponsible(L""),
			objectHeight(0.f),
			checkAerodynamicFactor(false),
			c1(0.f),
			c2(0.f),
			checkAnker(false),
			checkNVFConnection(false),
			checkNVFElements(false),
			weight(0.f),
			isFacingStandart(true),
			isSubsystemStandart(true),
			v_step_profile_ordinary_area(0.f),
			v_step_profile_marginal_area(0.f),
			h_step_profile(0.f),
			facing_radius(0.f),
			v_step_bracket_ordinary_area(0.f),
			v_step_bracket_marginal_area(0.f),
			h_step_bracket_ordinary_area(0.f),
			h_step_bracket_marginal_area(0.f),
			conclusion(L"")
		{}
	};
	
	// состояние полей
	enum eFieldStates {
		fsNone,				// заглушка, на всякий случай для полей с неопределенным состоянием
		fsCommon,			// обычное состояние (можно вводить данные в поле)
		fsUncorrect,		// состояние неправильно введеных данных (когда проверка выдает ошибку заполнения поля)
		fsLocked,			// поле заблокированно (нельзя вводить данные в поле)
		fsUnlocked,			// fsNone для полей, которые могут быть в состоянии fsLocked

		fsCount				// количество возможных состояний
	};
	
	// мапа, хранит значения полей, требующих проверки
	// к сожаленюю вижуал ругается, если в мапе хранить String^, что влечет за собой некоторое 
	// число переконвертаций для работы с этой мапой (это порешаем на следущих итерациях, скорее всего нужно будет
	// вообще по другому зафигачить, т.к. надо еще проверки на регулярные выражения сделать одной функцией)
	static std::map<std::string, eFieldStates> m_checking_field_states_map;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void) 
		{	
			InitializeComponent();
			FillData();
		}

	protected:
		void FillData();
		bool checkDataCorrectness();
		void calculateAccount();
		FormDataArgs collectData();
		void _getConstructionFields();
		void _getBrackets();
		void _getProfiles();
		void _selectDistricts();
		void _lockUnlockField(System::Object^ sender);

		bool isCorrectFieldObjectName();
		bool isCorrectFieldObjectCipher();
		bool isCorrectFieldObjectResponsible();
		bool isCorrectFieldObjectHeight();
		bool isCorrectFieldWeight();
		bool isCorrectFieldC1();
		bool isCorrectFieldC2();
		bool isCorrectFieldFacingRadius();
		bool isCorrectFieldVerticalRZ();
		bool isCorrectFieldVerticalKZ();
		bool isCorrectFieldHorizontalRZ();
		bool isCorrectFieldHorizontalKZ();
		bool isCorrectFieldVerticalStepRZ();
		bool isCorrectFieldVerticalStepKZ();
		bool isCorrectFieldHorizontalStep();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^  _rb_climate_0;
	private: System::Windows::Forms::RadioButton^  _rb_climate_1;
	private: System::Windows::Forms::Label^  _l_climate;
	private: System::Windows::Forms::ComboBox^  _cb_cities;
	private: System::Windows::Forms::ComboBox^  _cb_wind_districs;
	private: System::Windows::Forms::ComboBox^  _cb_ice_districs;
	private: System::Windows::Forms::ComboBox^  _cb_location_types;
	private: System::Windows::Forms::Label^  _l_wind_districs;
	private: System::Windows::Forms::Label^  _l_ice_districs;
	private: System::Windows::Forms::Label^  _l_location_types;
	private: System::Windows::Forms::Label^  _l_facing;
	private: System::Windows::Forms::RadioButton^  _rb_facing_standart;
	private: System::Windows::Forms::RadioButton^  _rb_facing_unstandart;
	private: System::Windows::Forms::ComboBox^  _cb_facing;
	private: System::Windows::Forms::Label^  _l_subsystem;
	private: System::Windows::Forms::ComboBox^  _cb_subsystem;
	private: System::Windows::Forms::Label^  _l_bracket;
	private: System::Windows::Forms::ComboBox^  _cb_bracket;
	private: System::Windows::Forms::Label^  _l_profile;
	private: System::Windows::Forms::ComboBox^  _cb_profile;
	private: System::Windows::Forms::Label^  _l_variations;
	private: System::Windows::Forms::Label^  _l_account;
	private: System::Windows::Forms::CheckBox^  _chb_anker;
	private: System::Windows::Forms::CheckBox^  _chb_nvf_elements;
	private: System::Windows::Forms::CheckBox^  _chb_nvf_connection;
	private: System::Windows::Forms::Button^  _b_calculate_account;
	private: System::Windows::Forms::Button^  _b_generate_report;
	private: System::Windows::Forms::Label^  _l_results;
	private: System::Windows::Forms::Label^  _l_strength_extension;
	private: System::Windows::Forms::Label^  _l_strength_bracket;
	private: System::Windows::Forms::Label^  _l_strength_contour;
	private: System::Windows::Forms::Label^  _l_digging_anker;
	private: System::Windows::Forms::Label^  _l_connections;
	private: System::Windows::Forms::Label^  _l_qy;
	private: System::Windows::Forms::Label^  _l_qz;
	private: System::Windows::Forms::Label^  _l_sp_20_13330_2011;
	private: System::Windows::Forms::CheckBox^  _chb_aerodynamic_factor;
	private: System::Windows::Forms::Label^  _l_c2;
	private: System::Windows::Forms::Label^  _l_c1;
	private: System::Windows::Forms::TextBox^  _tb_c1;
	private: System::Windows::Forms::TextBox^  _tb_c2;
	private: System::Windows::Forms::TextBox^  _tb_digging_anker;
	private: System::Windows::Forms::TextBox^  _tb_strength_profile;
	private: System::Windows::Forms::TextBox^  _tb_strength_bracket;
	private: System::Windows::Forms::TextBox^  _tb_strength_extension;
	private: System::Windows::Forms::TextBox^  _tb_connections;
	private: System::Windows::Forms::TextBox^  _tb_Qy_0;
	private: System::Windows::Forms::TextBox^  _tb_Qy_1;
	private: System::Windows::Forms::TextBox^  _tb_Qz_0;
	private: System::Windows::Forms::TextBox^  _tb_Qz_1;
	private: System::Windows::Forms::Panel^  _pnl_climate;
	private: System::Windows::Forms::Panel^  _pnl_object;
	private: System::Windows::Forms::Panel^  _pnl_facing;
	private: System::Windows::Forms::Label^  _l_weight;
	private: System::Windows::Forms::TextBox^  _tb_weight;
	private: System::Windows::Forms::Panel^  _pnl_subsystem;
	private: System::Windows::Forms::Label^  _l_object;
	private: System::Windows::Forms::TextBox^  _tb_height;
	private: System::Windows::Forms::TextBox^  _tb_responsible;
	private: System::Windows::Forms::TextBox^  _tb_code;
	private: System::Windows::Forms::TextBox^  _tb_name;
	private: System::Windows::Forms::Label^  _l_height;
	private: System::Windows::Forms::Label^  _l_responsible;
	private: System::Windows::Forms::Label^  _l_code;
	private: System::Windows::Forms::Label^  _l_name;
	private: System::Windows::Forms::Panel^  _pnl_constructions;
	private: System::Windows::Forms::Label^  _l_constructions;
	private: System::Windows::Forms::TextBox^  _tb_h_step_profile;
	private: System::Windows::Forms::Label^  _l_h_step_profile;
	private: System::Windows::Forms::TextBox^  _tb_v_step_profile_ordinary_area;
	private: System::Windows::Forms::Label^  _l_v_step_profile;
	private: System::Windows::Forms::TextBox^  _tb_h_step_bracket_marginal_area;
	private: System::Windows::Forms::TextBox^  _tb_h_step_bracket_ordinary_area;
	private: System::Windows::Forms::Label^  _l_h_step_bracket;
	private: System::Windows::Forms::TextBox^  _tb_v_step_bracket_marginal_area;
	private: System::Windows::Forms::TextBox^  _tb_v_step_bracket_ordinary_area;
	private: System::Windows::Forms::Label^  _l_v_step_bracket;
	private: System::Windows::Forms::TextBox^  _tb_facing_radius;
	private: System::Windows::Forms::Label^  _l_facing_radius;
	private: System::Windows::Forms::Panel^  _pnl_variation;
	private: System::Windows::Forms::Panel^  _pnl_account;
	private: System::Windows::Forms::Panel^  _pnl_results;
	private: System::Windows::Forms::TextBox^  _tb_conclusion;
	private: System::Windows::Forms::PictureBox^  _pb_helper;
	private: System::Windows::Forms::PictureBox^  _pb_climate_top_left;
	private: System::Windows::Forms::PictureBox^  _pb_object_bottom_left;
	private: System::Windows::Forms::TextBox^  _tb_v_step_profile_marginal_area;
	private: System::Windows::Forms::PictureBox^  _pb_line;
	private: System::Windows::Forms::CheckBox^  _chb_subsystem_variation;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->_rb_climate_0 = (gcnew System::Windows::Forms::RadioButton());
			this->_rb_climate_1 = (gcnew System::Windows::Forms::RadioButton());
			this->_l_climate = (gcnew System::Windows::Forms::Label());
			this->_cb_cities = (gcnew System::Windows::Forms::ComboBox());
			this->_cb_wind_districs = (gcnew System::Windows::Forms::ComboBox());
			this->_cb_ice_districs = (gcnew System::Windows::Forms::ComboBox());
			this->_cb_location_types = (gcnew System::Windows::Forms::ComboBox());
			this->_l_wind_districs = (gcnew System::Windows::Forms::Label());
			this->_l_ice_districs = (gcnew System::Windows::Forms::Label());
			this->_l_location_types = (gcnew System::Windows::Forms::Label());
			this->_l_facing = (gcnew System::Windows::Forms::Label());
			this->_rb_facing_standart = (gcnew System::Windows::Forms::RadioButton());
			this->_rb_facing_unstandart = (gcnew System::Windows::Forms::RadioButton());
			this->_cb_facing = (gcnew System::Windows::Forms::ComboBox());
			this->_l_subsystem = (gcnew System::Windows::Forms::Label());
			this->_cb_subsystem = (gcnew System::Windows::Forms::ComboBox());
			this->_l_bracket = (gcnew System::Windows::Forms::Label());
			this->_cb_bracket = (gcnew System::Windows::Forms::ComboBox());
			this->_l_profile = (gcnew System::Windows::Forms::Label());
			this->_cb_profile = (gcnew System::Windows::Forms::ComboBox());
			this->_l_variations = (gcnew System::Windows::Forms::Label());
			this->_l_account = (gcnew System::Windows::Forms::Label());
			this->_chb_anker = (gcnew System::Windows::Forms::CheckBox());
			this->_chb_nvf_elements = (gcnew System::Windows::Forms::CheckBox());
			this->_chb_nvf_connection = (gcnew System::Windows::Forms::CheckBox());
			this->_b_calculate_account = (gcnew System::Windows::Forms::Button());
			this->_b_generate_report = (gcnew System::Windows::Forms::Button());
			this->_l_results = (gcnew System::Windows::Forms::Label());
			this->_l_strength_extension = (gcnew System::Windows::Forms::Label());
			this->_l_strength_bracket = (gcnew System::Windows::Forms::Label());
			this->_l_strength_contour = (gcnew System::Windows::Forms::Label());
			this->_l_digging_anker = (gcnew System::Windows::Forms::Label());
			this->_l_connections = (gcnew System::Windows::Forms::Label());
			this->_l_qy = (gcnew System::Windows::Forms::Label());
			this->_l_qz = (gcnew System::Windows::Forms::Label());
			this->_l_sp_20_13330_2011 = (gcnew System::Windows::Forms::Label());
			this->_chb_aerodynamic_factor = (gcnew System::Windows::Forms::CheckBox());
			this->_l_c2 = (gcnew System::Windows::Forms::Label());
			this->_l_c1 = (gcnew System::Windows::Forms::Label());
			this->_tb_c1 = (gcnew System::Windows::Forms::TextBox());
			this->_tb_c2 = (gcnew System::Windows::Forms::TextBox());
			this->_tb_digging_anker = (gcnew System::Windows::Forms::TextBox());
			this->_tb_strength_profile = (gcnew System::Windows::Forms::TextBox());
			this->_tb_strength_bracket = (gcnew System::Windows::Forms::TextBox());
			this->_tb_strength_extension = (gcnew System::Windows::Forms::TextBox());
			this->_tb_connections = (gcnew System::Windows::Forms::TextBox());
			this->_tb_Qy_0 = (gcnew System::Windows::Forms::TextBox());
			this->_tb_Qy_1 = (gcnew System::Windows::Forms::TextBox());
			this->_tb_Qz_0 = (gcnew System::Windows::Forms::TextBox());
			this->_tb_Qz_1 = (gcnew System::Windows::Forms::TextBox());
			this->_pnl_climate = (gcnew System::Windows::Forms::Panel());
			this->_pb_line = (gcnew System::Windows::Forms::PictureBox());
			this->_pb_climate_top_left = (gcnew System::Windows::Forms::PictureBox());
			this->_pnl_object = (gcnew System::Windows::Forms::Panel());
			this->_pb_object_bottom_left = (gcnew System::Windows::Forms::PictureBox());
			this->_tb_height = (gcnew System::Windows::Forms::TextBox());
			this->_tb_responsible = (gcnew System::Windows::Forms::TextBox());
			this->_tb_code = (gcnew System::Windows::Forms::TextBox());
			this->_tb_name = (gcnew System::Windows::Forms::TextBox());
			this->_l_height = (gcnew System::Windows::Forms::Label());
			this->_l_responsible = (gcnew System::Windows::Forms::Label());
			this->_l_code = (gcnew System::Windows::Forms::Label());
			this->_l_name = (gcnew System::Windows::Forms::Label());
			this->_l_object = (gcnew System::Windows::Forms::Label());
			this->_pnl_facing = (gcnew System::Windows::Forms::Panel());
			this->_l_weight = (gcnew System::Windows::Forms::Label());
			this->_tb_weight = (gcnew System::Windows::Forms::TextBox());
			this->_pnl_subsystem = (gcnew System::Windows::Forms::Panel());
			this->_chb_subsystem_variation = (gcnew System::Windows::Forms::CheckBox());
			this->_pnl_constructions = (gcnew System::Windows::Forms::Panel());
			this->_tb_v_step_profile_marginal_area = (gcnew System::Windows::Forms::TextBox());
			this->_tb_h_step_profile = (gcnew System::Windows::Forms::TextBox());
			this->_l_h_step_profile = (gcnew System::Windows::Forms::Label());
			this->_tb_v_step_profile_ordinary_area = (gcnew System::Windows::Forms::TextBox());
			this->_l_v_step_profile = (gcnew System::Windows::Forms::Label());
			this->_tb_h_step_bracket_marginal_area = (gcnew System::Windows::Forms::TextBox());
			this->_tb_h_step_bracket_ordinary_area = (gcnew System::Windows::Forms::TextBox());
			this->_l_h_step_bracket = (gcnew System::Windows::Forms::Label());
			this->_tb_v_step_bracket_marginal_area = (gcnew System::Windows::Forms::TextBox());
			this->_tb_v_step_bracket_ordinary_area = (gcnew System::Windows::Forms::TextBox());
			this->_l_v_step_bracket = (gcnew System::Windows::Forms::Label());
			this->_tb_facing_radius = (gcnew System::Windows::Forms::TextBox());
			this->_l_facing_radius = (gcnew System::Windows::Forms::Label());
			this->_l_constructions = (gcnew System::Windows::Forms::Label());
			this->_pnl_variation = (gcnew System::Windows::Forms::Panel());
			this->_pnl_account = (gcnew System::Windows::Forms::Panel());
			this->_pnl_results = (gcnew System::Windows::Forms::Panel());
			this->_tb_conclusion = (gcnew System::Windows::Forms::TextBox());
			this->_pb_helper = (gcnew System::Windows::Forms::PictureBox());
			this->_pnl_climate->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_line))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_climate_top_left))->BeginInit();
			this->_pnl_object->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_object_bottom_left))->BeginInit();
			this->_pnl_facing->SuspendLayout();
			this->_pnl_subsystem->SuspendLayout();
			this->_pnl_constructions->SuspendLayout();
			this->_pnl_variation->SuspendLayout();
			this->_pnl_account->SuspendLayout();
			this->_pnl_results->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_helper))->BeginInit();
			this->SuspendLayout();
			// 
			// _rb_climate_0
			// 
			this->_rb_climate_0->AutoSize = true;
			this->_rb_climate_0->Checked = true;
			this->_rb_climate_0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_rb_climate_0->Location = System::Drawing::Point(5, 39);
			this->_rb_climate_0->Name = L"_rb_climate_0";
			this->_rb_climate_0->Size = System::Drawing::Size(14, 13);
			this->_rb_climate_0->TabIndex = 0;
			this->_rb_climate_0->TabStop = true;
			this->_rb_climate_0->UseVisualStyleBackColor = true;
			this->_rb_climate_0->CheckedChanged += gcnew System::EventHandler(this, &MainForm::_changedValueClimateRadiobutton);
			// 
			// _rb_climate_1
			// 
			this->_rb_climate_1->AutoSize = true;
			this->_rb_climate_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_rb_climate_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_rb_climate_1->Location = System::Drawing::Point(5, 65);
			this->_rb_climate_1->Name = L"_rb_climate_1";
			this->_rb_climate_1->Size = System::Drawing::Size(66, 17);
			this->_rb_climate_1->TabIndex = 2;
			this->_rb_climate_1->Text = L"РАЙОН:";
			this->_rb_climate_1->UseVisualStyleBackColor = true;
			// 
			// _l_climate
			// 
			this->_l_climate->AutoSize = true;
			this->_l_climate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_climate->ForeColor = System::Drawing::SystemColors::ControlText;
			this->_l_climate->Location = System::Drawing::Point(31, 0);
			this->_l_climate->Name = L"_l_climate";
			this->_l_climate->Size = System::Drawing::Size(88, 24);
			this->_l_climate->TabIndex = 100;
			this->_l_climate->Text = L"КЛИМАТ";
			// 
			// _cb_cities
			// 
			this->_cb_cities->DropDownWidth = 165;
			this->_cb_cities->FormattingEnabled = true;
			this->_cb_cities->Location = System::Drawing::Point(25, 35);
			this->_cb_cities->Name = L"_cb_cities";
			this->_cb_cities->Size = System::Drawing::Size(120, 21);
			this->_cb_cities->TabIndex = 1;
			// 
			// _cb_wind_districs
			// 
			this->_cb_wind_districs->Enabled = false;
			this->_cb_wind_districs->FormattingEnabled = true;
			this->_cb_wind_districs->Location = System::Drawing::Point(25, 105);
			this->_cb_wind_districs->Name = L"_cb_wind_districs";
			this->_cb_wind_districs->Size = System::Drawing::Size(120, 21);
			this->_cb_wind_districs->TabIndex = 3;
			// 
			// _cb_ice_districs
			// 
			this->_cb_ice_districs->Enabled = false;
			this->_cb_ice_districs->FormattingEnabled = true;
			this->_cb_ice_districs->Location = System::Drawing::Point(25, 150);
			this->_cb_ice_districs->Name = L"_cb_ice_districs";
			this->_cb_ice_districs->Size = System::Drawing::Size(120, 21);
			this->_cb_ice_districs->TabIndex = 4;
			// 
			// _cb_location_types
			// 
			this->_cb_location_types->FormattingEnabled = true;
			this->_cb_location_types->Location = System::Drawing::Point(25, 209);
			this->_cb_location_types->Name = L"_cb_location_types";
			this->_cb_location_types->Size = System::Drawing::Size(120, 21);
			this->_cb_location_types->TabIndex = 5;
			// 
			// _l_wind_districs
			// 
			this->_l_wind_districs->AutoSize = true;
			this->_l_wind_districs->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_wind_districs->Location = System::Drawing::Point(92, 86);
			this->_l_wind_districs->Name = L"_l_wind_districs";
			this->_l_wind_districs->Size = System::Drawing::Size(55, 13);
			this->_l_wind_districs->TabIndex = 101;
			this->_l_wind_districs->Text = L"Ветровой";
			// 
			// _l_ice_districs
			// 
			this->_l_ice_districs->AutoSize = true;
			this->_l_ice_districs->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_ice_districs->Location = System::Drawing::Point(78, 131);
			this->_l_ice_districs->Name = L"_l_ice_districs";
			this->_l_ice_districs->Size = System::Drawing::Size(69, 13);
			this->_l_ice_districs->TabIndex = 102;
			this->_l_ice_districs->Text = L"Гололедный";
			// 
			// _l_location_types
			// 
			this->_l_location_types->AutoSize = true;
			this->_l_location_types->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_location_types->Location = System::Drawing::Point(22, 190);
			this->_l_location_types->Name = L"_l_location_types";
			this->_l_location_types->Size = System::Drawing::Size(101, 13);
			this->_l_location_types->TabIndex = 103;
			this->_l_location_types->Text = L"ТИП МЕСТНОСТИ";
			// 
			// _l_facing
			// 
			this->_l_facing->AutoSize = true;
			this->_l_facing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_facing->ForeColor = System::Drawing::SystemColors::ControlText;
			this->_l_facing->Location = System::Drawing::Point(13, 0);
			this->_l_facing->Name = L"_l_facing";
			this->_l_facing->Size = System::Drawing::Size(127, 24);
			this->_l_facing->TabIndex = 104;
			this->_l_facing->Text = L"ОБЛИЦОВКА";
			// 
			// _rb_facing_standart
			// 
			this->_rb_facing_standart->AutoSize = true;
			this->_rb_facing_standart->Checked = true;
			this->_rb_facing_standart->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_rb_facing_standart->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_rb_facing_standart->Location = System::Drawing::Point(5, 39);
			this->_rb_facing_standart->Name = L"_rb_facing_standart";
			this->_rb_facing_standart->Size = System::Drawing::Size(109, 17);
			this->_rb_facing_standart->TabIndex = 10;
			this->_rb_facing_standart->TabStop = true;
			this->_rb_facing_standart->Text = L"СТАНДАРТНЫЕ";
			this->_rb_facing_standart->UseVisualStyleBackColor = true;
			this->_rb_facing_standart->CheckedChanged += gcnew System::EventHandler(this, &MainForm::_changedValueFacingRadiobutton);
			// 
			// _rb_facing_unstandart
			// 
			this->_rb_facing_unstandart->AutoSize = true;
			this->_rb_facing_unstandart->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_rb_facing_unstandart->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_rb_facing_unstandart->Location = System::Drawing::Point(5, 102);
			this->_rb_facing_unstandart->Name = L"_rb_facing_unstandart";
			this->_rb_facing_unstandart->Size = System::Drawing::Size(124, 17);
			this->_rb_facing_unstandart->TabIndex = 12;
			this->_rb_facing_unstandart->Text = L"НЕСТАНДАРТНЫЕ";
			this->_rb_facing_unstandart->UseVisualStyleBackColor = true;
			// 
			// _cb_facing
			// 
			this->_cb_facing->DropDownWidth = 250;
			this->_cb_facing->FormattingEnabled = true;
			this->_cb_facing->Location = System::Drawing::Point(25, 62);
			this->_cb_facing->Name = L"_cb_facing";
			this->_cb_facing->Size = System::Drawing::Size(120, 21);
			this->_cb_facing->TabIndex = 11;
			// 
			// _l_subsystem
			// 
			this->_l_subsystem->AutoSize = true;
			this->_l_subsystem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_subsystem->Location = System::Drawing::Point(5, 0);
			this->_l_subsystem->Name = L"_l_subsystem";
			this->_l_subsystem->Size = System::Drawing::Size(145, 24);
			this->_l_subsystem->TabIndex = 105;
			this->_l_subsystem->Text = L"ПОДСИСТЕМА";
			// 
			// _cb_subsystem
			// 
			this->_cb_subsystem->FormattingEnabled = true;
			this->_cb_subsystem->Location = System::Drawing::Point(25, 35);
			this->_cb_subsystem->Name = L"_cb_subsystem";
			this->_cb_subsystem->Size = System::Drawing::Size(120, 21);
			this->_cb_subsystem->TabIndex = 14;
			this->_cb_subsystem->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::_cb_subsystem_SelectedIndexChanged);
			// 
			// _l_bracket
			// 
			this->_l_bracket->AutoSize = true;
			this->_l_bracket->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_bracket->Location = System::Drawing::Point(84, 86);
			this->_l_bracket->Name = L"_l_bracket";
			this->_l_bracket->Size = System::Drawing::Size(63, 13);
			this->_l_bracket->TabIndex = 106;
			this->_l_bracket->Text = L"Кронштейн";
			// 
			// _cb_bracket
			// 
			this->_cb_bracket->Enabled = false;
			this->_cb_bracket->FormattingEnabled = true;
			this->_cb_bracket->Location = System::Drawing::Point(25, 105);
			this->_cb_bracket->Name = L"_cb_bracket";
			this->_cb_bracket->Size = System::Drawing::Size(120, 21);
			this->_cb_bracket->TabIndex = 16;
			// 
			// _l_profile
			// 
			this->_l_profile->AutoSize = true;
			this->_l_profile->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_profile->Location = System::Drawing::Point(91, 131);
			this->_l_profile->Name = L"_l_profile";
			this->_l_profile->Size = System::Drawing::Size(53, 13);
			this->_l_profile->TabIndex = 107;
			this->_l_profile->Text = L"Профиль";
			// 
			// _cb_profile
			// 
			this->_cb_profile->Cursor = System::Windows::Forms::Cursors::Default;
			this->_cb_profile->DropDownWidth = 150;
			this->_cb_profile->Enabled = false;
			this->_cb_profile->FormattingEnabled = true;
			this->_cb_profile->Location = System::Drawing::Point(25, 150);
			this->_cb_profile->Name = L"_cb_profile";
			this->_cb_profile->Size = System::Drawing::Size(120, 21);
			this->_cb_profile->TabIndex = 17;
			// 
			// _l_variations
			// 
			this->_l_variations->AutoSize = true;
			this->_l_variations->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_variations->Location = System::Drawing::Point(18, 0);
			this->_l_variations->Name = L"_l_variations";
			this->_l_variations->Size = System::Drawing::Size(111, 24);
			this->_l_variations->TabIndex = 108;
			this->_l_variations->Text = L"ВАРИАЦИИ";
			// 
			// _l_account
			// 
			this->_l_account->AutoSize = true;
			this->_l_account->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_account->Location = System::Drawing::Point(32, 0);
			this->_l_account->Name = L"_l_account";
			this->_l_account->Size = System::Drawing::Size(84, 24);
			this->_l_account->TabIndex = 109;
			this->_l_account->Text = L"РАСЧЕТ";
			// 
			// _chb_anker
			// 
			this->_chb_anker->AutoSize = true;
			this->_chb_anker->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_chb_anker->Location = System::Drawing::Point(25, 39);
			this->_chb_anker->Name = L"_chb_anker";
			this->_chb_anker->Size = System::Drawing::Size(56, 17);
			this->_chb_anker->TabIndex = 29;
			this->_chb_anker->Text = L"анкер";
			this->_chb_anker->UseVisualStyleBackColor = true;
			// 
			// _chb_nvf_elements
			// 
			this->_chb_nvf_elements->AutoSize = true;
			this->_chb_nvf_elements->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_chb_nvf_elements->Location = System::Drawing::Point(25, 67);
			this->_chb_nvf_elements->Name = L"_chb_nvf_elements";
			this->_chb_nvf_elements->Size = System::Drawing::Size(106, 17);
			this->_chb_nvf_elements->TabIndex = 30;
			this->_chb_nvf_elements->Text = L"элементы НВФ";
			this->_chb_nvf_elements->UseVisualStyleBackColor = true;
			// 
			// _chb_nvf_connection
			// 
			this->_chb_nvf_connection->AutoSize = true;
			this->_chb_nvf_connection->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_chb_nvf_connection->Location = System::Drawing::Point(25, 95);
			this->_chb_nvf_connection->Name = L"_chb_nvf_connection";
			this->_chb_nvf_connection->Size = System::Drawing::Size(115, 17);
			this->_chb_nvf_connection->TabIndex = 31;
			this->_chb_nvf_connection->Text = L"соединения НВФ";
			this->_chb_nvf_connection->UseVisualStyleBackColor = true;
			// 
			// _b_calculate_account
			// 
			this->_b_calculate_account->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_b_calculate_account->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_b_calculate_account->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->_b_calculate_account->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->_b_calculate_account->Location = System::Drawing::Point(534, 149);
			this->_b_calculate_account->Name = L"_b_calculate_account";
			this->_b_calculate_account->Size = System::Drawing::Size(106, 27);
			this->_b_calculate_account->TabIndex = 32;
			this->_b_calculate_account->Text = L"расчет";
			this->_b_calculate_account->UseVisualStyleBackColor = false;
			this->_b_calculate_account->Click += gcnew System::EventHandler(this, &MainForm::_b_calculate_account_Click);
			// 
			// _b_generate_report
			// 
			this->_b_generate_report->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_b_generate_report->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_b_generate_report->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_b_generate_report->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->_b_generate_report->Location = System::Drawing::Point(645, 149);
			this->_b_generate_report->Name = L"_b_generate_report";
			this->_b_generate_report->Size = System::Drawing::Size(106, 27);
			this->_b_generate_report->TabIndex = 34;
			this->_b_generate_report->Text = L"отчет";
			this->_b_generate_report->UseVisualStyleBackColor = false;
			this->_b_generate_report->Click += gcnew System::EventHandler(this, &MainForm::_b_generate_report_Click);
			// 
			// _l_results
			// 
			this->_l_results->AutoSize = true;
			this->_l_results->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_results->Location = System::Drawing::Point(80, 0);
			this->_l_results->Name = L"_l_results";
			this->_l_results->Size = System::Drawing::Size(139, 24);
			this->_l_results->TabIndex = 110;
			this->_l_results->Text = L"РЕЗУЛЬТАТЫ";
			// 
			// _l_strength_extension
			// 
			this->_l_strength_extension->AutoSize = true;
			this->_l_strength_extension->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_strength_extension->Location = System::Drawing::Point(5, 133);
			this->_l_strength_extension->Name = L"_l_strength_extension";
			this->_l_strength_extension->Size = System::Drawing::Size(128, 13);
			this->_l_strength_extension->TabIndex = 111;
			this->_l_strength_extension->Text = L"Прочность удлинителя -";
			// 
			// _l_strength_bracket
			// 
			this->_l_strength_bracket->AutoSize = true;
			this->_l_strength_bracket->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_strength_bracket->Location = System::Drawing::Point(5, 103);
			this->_l_strength_bracket->Name = L"_l_strength_bracket";
			this->_l_strength_bracket->Size = System::Drawing::Size(131, 13);
			this->_l_strength_bracket->TabIndex = 112;
			this->_l_strength_bracket->Text = L"Прочность кронштейна -";
			// 
			// _l_strength_contour
			// 
			this->_l_strength_contour->AutoSize = true;
			this->_l_strength_contour->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_strength_contour->Location = System::Drawing::Point(5, 73);
			this->_l_strength_contour->Name = L"_l_strength_contour";
			this->_l_strength_contour->Size = System::Drawing::Size(114, 13);
			this->_l_strength_contour->TabIndex = 113;
			this->_l_strength_contour->Text = L"Прочность профиля -";
			// 
			// _l_digging_anker
			// 
			this->_l_digging_anker->AutoSize = true;
			this->_l_digging_anker->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_digging_anker->Location = System::Drawing::Point(5, 43);
			this->_l_digging_anker->Name = L"_l_digging_anker";
			this->_l_digging_anker->Size = System::Drawing::Size(104, 13);
			this->_l_digging_anker->TabIndex = 114;
			this->_l_digging_anker->Text = L"Вырыв анкера (Н) -";
			// 
			// _l_connections
			// 
			this->_l_connections->AutoSize = true;
			this->_l_connections->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_connections->Location = System::Drawing::Point(5, 163);
			this->_l_connections->Name = L"_l_connections";
			this->_l_connections->Size = System::Drawing::Size(74, 13);
			this->_l_connections->TabIndex = 115;
			this->_l_connections->Text = L"Соединения -";
			// 
			// _l_qy
			// 
			this->_l_qy->AutoSize = true;
			this->_l_qy->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_qy->Location = System::Drawing::Point(2, 193);
			this->_l_qy->Name = L"_l_qy";
			this->_l_qy->Size = System::Drawing::Size(52, 13);
			this->_l_qy->TabIndex = 116;
			this->_l_qy->Text = L"Q(y) (Па):";
			// 
			// _l_qz
			// 
			this->_l_qz->AutoSize = true;
			this->_l_qz->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_qz->Location = System::Drawing::Point(2, 223);
			this->_l_qz->Name = L"_l_qz";
			this->_l_qz->Size = System::Drawing::Size(52, 13);
			this->_l_qz->TabIndex = 117;
			this->_l_qz->Text = L"Q(z) (Па):";
			// 
			// _l_sp_20_13330_2011
			// 
			this->_l_sp_20_13330_2011->AutoSize = true;
			this->_l_sp_20_13330_2011->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_sp_20_13330_2011->Location = System::Drawing::Point(22, 39);
			this->_l_sp_20_13330_2011->Name = L"_l_sp_20_13330_2011";
			this->_l_sp_20_13330_2011->Size = System::Drawing::Size(103, 13);
			this->_l_sp_20_13330_2011->TabIndex = 118;
			this->_l_sp_20_13330_2011->Text = L"- СП 20.13330.2011";
			// 
			// _chb_aerodynamic_factor
			// 
			this->_chb_aerodynamic_factor->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_chb_aerodynamic_factor->Location = System::Drawing::Point(5, 57);
			this->_chb_aerodynamic_factor->Name = L"_chb_aerodynamic_factor";
			this->_chb_aerodynamic_factor->Size = System::Drawing::Size(140, 30);
			this->_chb_aerodynamic_factor->TabIndex = 26;
			this->_chb_aerodynamic_factor->Text = L"Аэродинамический коэффициент:";
			this->_chb_aerodynamic_factor->UseVisualStyleBackColor = true;
			this->_chb_aerodynamic_factor->CheckedChanged += gcnew System::EventHandler(this, &MainForm::_changedValueVariationsCheckBox);
			// 
			// _l_c2
			// 
			this->_l_c2->AutoSize = true;
			this->_l_c2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_c2->Location = System::Drawing::Point(5, 116);
			this->_l_c2->Name = L"_l_c2";
			this->_l_c2->Size = System::Drawing::Size(31, 13);
			this->_l_c2->TabIndex = 119;
			this->_l_c2->Text = L"c(2) -";
			// 
			// _l_c1
			// 
			this->_l_c1->AutoSize = true;
			this->_l_c1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_c1->Location = System::Drawing::Point(5, 91);
			this->_l_c1->Name = L"_l_c1";
			this->_l_c1->Size = System::Drawing::Size(34, 13);
			this->_l_c1->TabIndex = 120;
			this->_l_c1->Text = L"c(1) - ";
			// 
			// _tb_c1
			// 
			this->_tb_c1->Enabled = false;
			this->_tb_c1->Location = System::Drawing::Point(45, 87);
			this->_tb_c1->Name = L"_tb_c1";
			this->_tb_c1->Size = System::Drawing::Size(80, 20);
			this->_tb_c1->TabIndex = 27;
			this->_tb_c1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_c1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_c1->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_c2
			// 
			this->_tb_c2->Enabled = false;
			this->_tb_c2->Location = System::Drawing::Point(45, 112);
			this->_tb_c2->Name = L"_tb_c2";
			this->_tb_c2->Size = System::Drawing::Size(80, 20);
			this->_tb_c2->TabIndex = 28;
			this->_tb_c2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_c2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_c2->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_digging_anker
			// 
			this->_tb_digging_anker->Enabled = false;
			this->_tb_digging_anker->Location = System::Drawing::Point(175, 39);
			this->_tb_digging_anker->Name = L"_tb_digging_anker";
			this->_tb_digging_anker->Size = System::Drawing::Size(130, 20);
			this->_tb_digging_anker->TabIndex = 35;
			this->_tb_digging_anker->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_strength_profile
			// 
			this->_tb_strength_profile->Enabled = false;
			this->_tb_strength_profile->Location = System::Drawing::Point(175, 69);
			this->_tb_strength_profile->Name = L"_tb_strength_profile";
			this->_tb_strength_profile->Size = System::Drawing::Size(130, 20);
			this->_tb_strength_profile->TabIndex = 36;
			this->_tb_strength_profile->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_strength_bracket
			// 
			this->_tb_strength_bracket->Enabled = false;
			this->_tb_strength_bracket->Location = System::Drawing::Point(175, 99);
			this->_tb_strength_bracket->Name = L"_tb_strength_bracket";
			this->_tb_strength_bracket->Size = System::Drawing::Size(130, 20);
			this->_tb_strength_bracket->TabIndex = 37;
			this->_tb_strength_bracket->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_strength_extension
			// 
			this->_tb_strength_extension->Enabled = false;
			this->_tb_strength_extension->Location = System::Drawing::Point(175, 129);
			this->_tb_strength_extension->Name = L"_tb_strength_extension";
			this->_tb_strength_extension->Size = System::Drawing::Size(130, 20);
			this->_tb_strength_extension->TabIndex = 38;
			this->_tb_strength_extension->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_connections
			// 
			this->_tb_connections->Enabled = false;
			this->_tb_connections->Location = System::Drawing::Point(175, 159);
			this->_tb_connections->Name = L"_tb_connections";
			this->_tb_connections->Size = System::Drawing::Size(130, 20);
			this->_tb_connections->TabIndex = 39;
			this->_tb_connections->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_Qy_0
			// 
			this->_tb_Qy_0->Enabled = false;
			this->_tb_Qy_0->Location = System::Drawing::Point(55, 189);
			this->_tb_Qy_0->Name = L"_tb_Qy_0";
			this->_tb_Qy_0->Size = System::Drawing::Size(115, 20);
			this->_tb_Qy_0->TabIndex = 40;
			this->_tb_Qy_0->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_Qy_1
			// 
			this->_tb_Qy_1->Enabled = false;
			this->_tb_Qy_1->Location = System::Drawing::Point(175, 189);
			this->_tb_Qy_1->Name = L"_tb_Qy_1";
			this->_tb_Qy_1->Size = System::Drawing::Size(130, 20);
			this->_tb_Qy_1->TabIndex = 41;
			this->_tb_Qy_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_Qz_0
			// 
			this->_tb_Qz_0->Enabled = false;
			this->_tb_Qz_0->Location = System::Drawing::Point(55, 219);
			this->_tb_Qz_0->Name = L"_tb_Qz_0";
			this->_tb_Qz_0->Size = System::Drawing::Size(115, 20);
			this->_tb_Qz_0->TabIndex = 42;
			this->_tb_Qz_0->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _tb_Qz_1
			// 
			this->_tb_Qz_1->Enabled = false;
			this->_tb_Qz_1->Location = System::Drawing::Point(175, 219);
			this->_tb_Qz_1->Name = L"_tb_Qz_1";
			this->_tb_Qz_1->Size = System::Drawing::Size(130, 20);
			this->_tb_Qz_1->TabIndex = 43;
			this->_tb_Qz_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// _pnl_climate
			// 
			this->_pnl_climate->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_climate->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_climate->Controls->Add(this->_pb_line);
			this->_pnl_climate->Controls->Add(this->_pb_climate_top_left);
			this->_pnl_climate->Controls->Add(this->_l_climate);
			this->_pnl_climate->Controls->Add(this->_rb_climate_0);
			this->_pnl_climate->Controls->Add(this->_cb_cities);
			this->_pnl_climate->Controls->Add(this->_rb_climate_1);
			this->_pnl_climate->Controls->Add(this->_l_wind_districs);
			this->_pnl_climate->Controls->Add(this->_cb_wind_districs);
			this->_pnl_climate->Controls->Add(this->_l_ice_districs);
			this->_pnl_climate->Controls->Add(this->_cb_ice_districs);
			this->_pnl_climate->Controls->Add(this->_l_location_types);
			this->_pnl_climate->Controls->Add(this->_cb_location_types);
			this->_pnl_climate->Location = System::Drawing::Point(5, 5);
			this->_pnl_climate->Name = L"_pnl_climate";
			this->_pnl_climate->Size = System::Drawing::Size(155, 245);
			this->_pnl_climate->TabIndex = 121;
			// 
			// _pb_line
			// 
			this->_pb_line->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"_pb_line.Image")));
			this->_pb_line->Location = System::Drawing::Point(0, 173);
			this->_pb_line->Name = L"_pb_line";
			this->_pb_line->Size = System::Drawing::Size(150, 10);
			this->_pb_line->TabIndex = 122;
			this->_pb_line->TabStop = false;
			// 
			// _pb_climate_top_left
			// 
			this->_pb_climate_top_left->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"_pb_climate_top_left.Image")));
			this->_pb_climate_top_left->Location = System::Drawing::Point(0, 0);
			this->_pb_climate_top_left->Name = L"_pb_climate_top_left";
			this->_pb_climate_top_left->Size = System::Drawing::Size(25, 25);
			this->_pb_climate_top_left->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->_pb_climate_top_left->TabIndex = 123;
			this->_pb_climate_top_left->TabStop = false;
			// 
			// _pnl_object
			// 
			this->_pnl_object->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_object->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_object->Controls->Add(this->_pb_object_bottom_left);
			this->_pnl_object->Controls->Add(this->_tb_height);
			this->_pnl_object->Controls->Add(this->_tb_responsible);
			this->_pnl_object->Controls->Add(this->_tb_code);
			this->_pnl_object->Controls->Add(this->_tb_name);
			this->_pnl_object->Controls->Add(this->_l_height);
			this->_pnl_object->Controls->Add(this->_l_responsible);
			this->_pnl_object->Controls->Add(this->_l_code);
			this->_pnl_object->Controls->Add(this->_l_name);
			this->_pnl_object->Controls->Add(this->_l_object);
			this->_pnl_object->Location = System::Drawing::Point(5, 255);
			this->_pnl_object->Name = L"_pnl_object";
			this->_pnl_object->Size = System::Drawing::Size(155, 230);
			this->_pnl_object->TabIndex = 124;
			// 
			// _pb_object_bottom_left
			// 
			this->_pb_object_bottom_left->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"_pb_object_bottom_left.Image")));
			this->_pb_object_bottom_left->Location = System::Drawing::Point(0, 205);
			this->_pb_object_bottom_left->Name = L"_pb_object_bottom_left";
			this->_pb_object_bottom_left->Size = System::Drawing::Size(25, 25);
			this->_pb_object_bottom_left->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->_pb_object_bottom_left->TabIndex = 125;
			this->_pb_object_bottom_left->TabStop = false;
			// 
			// _tb_height
			// 
			this->_tb_height->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_height->Location = System::Drawing::Point(5, 184);
			this->_tb_height->Name = L"_tb_height";
			this->_tb_height->Size = System::Drawing::Size(140, 20);
			this->_tb_height->TabIndex = 9;
			this->_tb_height->Text = L"Заполняет инженер";
			this->_tb_height->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_height->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_height->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_responsible
			// 
			this->_tb_responsible->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_responsible->Location = System::Drawing::Point(5, 140);
			this->_tb_responsible->Name = L"_tb_responsible";
			this->_tb_responsible->Size = System::Drawing::Size(140, 20);
			this->_tb_responsible->TabIndex = 8;
			this->_tb_responsible->Text = L"Заполняет инженер";
			this->_tb_responsible->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_responsible->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_responsible->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_code
			// 
			this->_tb_code->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_code->Location = System::Drawing::Point(5, 96);
			this->_tb_code->Name = L"_tb_code";
			this->_tb_code->Size = System::Drawing::Size(140, 20);
			this->_tb_code->TabIndex = 7;
			this->_tb_code->Text = L"Заполняет инженер";
			this->_tb_code->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_code->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_code->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_name
			// 
			this->_tb_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_name->Location = System::Drawing::Point(5, 52);
			this->_tb_name->Name = L"_tb_name";
			this->_tb_name->Size = System::Drawing::Size(140, 20);
			this->_tb_name->TabIndex = 6;
			this->_tb_name->Text = L"Заполняет инженер";
			this->_tb_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_name->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_name->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_height
			// 
			this->_l_height->AutoSize = true;
			this->_l_height->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_height->Location = System::Drawing::Point(82, 165);
			this->_l_height->Name = L"_l_height";
			this->_l_height->Size = System::Drawing::Size(65, 13);
			this->_l_height->TabIndex = 126;
			this->_l_height->Text = L"Высота (м):";
			// 
			// _l_responsible
			// 
			this->_l_responsible->AutoSize = true;
			this->_l_responsible->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_responsible->Location = System::Drawing::Point(58, 121);
			this->_l_responsible->Name = L"_l_responsible";
			this->_l_responsible->Size = System::Drawing::Size(89, 13);
			this->_l_responsible->TabIndex = 127;
			this->_l_responsible->Text = L"Ответственный:";
			// 
			// _l_code
			// 
			this->_l_code->AutoSize = true;
			this->_l_code->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_code->Location = System::Drawing::Point(108, 77);
			this->_l_code->Name = L"_l_code";
			this->_l_code->Size = System::Drawing::Size(39, 13);
			this->_l_code->TabIndex = 128;
			this->_l_code->Text = L"Шифр:";
			// 
			// _l_name
			// 
			this->_l_name->AutoSize = true;
			this->_l_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_name->Location = System::Drawing::Point(87, 33);
			this->_l_name->Name = L"_l_name";
			this->_l_name->Size = System::Drawing::Size(60, 13);
			this->_l_name->TabIndex = 129;
			this->_l_name->Text = L"Название:";
			// 
			// _l_object
			// 
			this->_l_object->AutoSize = true;
			this->_l_object->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_object->Location = System::Drawing::Point(30, 0);
			this->_l_object->Name = L"_l_object";
			this->_l_object->Size = System::Drawing::Size(89, 24);
			this->_l_object->TabIndex = 130;
			this->_l_object->Text = L"ОБЪЕКТ";
			// 
			// _pnl_facing
			// 
			this->_pnl_facing->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_facing->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_facing->Controls->Add(this->_l_weight);
			this->_pnl_facing->Controls->Add(this->_tb_weight);
			this->_pnl_facing->Controls->Add(this->_l_facing);
			this->_pnl_facing->Controls->Add(this->_rb_facing_standart);
			this->_pnl_facing->Controls->Add(this->_cb_facing);
			this->_pnl_facing->Controls->Add(this->_rb_facing_unstandart);
			this->_pnl_facing->Location = System::Drawing::Point(165, 5);
			this->_pnl_facing->Name = L"_pnl_facing";
			this->_pnl_facing->Size = System::Drawing::Size(155, 163);
			this->_pnl_facing->TabIndex = 131;
			// 
			// _l_weight
			// 
			this->_l_weight->AutoSize = true;
			this->_l_weight->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_weight->Location = System::Drawing::Point(5, 129);
			this->_l_weight->Name = L"_l_weight";
			this->_l_weight->Size = System::Drawing::Size(49, 13);
			this->_l_weight->TabIndex = 10;
			this->_l_weight->Text = L"Вес (кг):";
			// 
			// _tb_weight
			// 
			this->_tb_weight->Enabled = false;
			this->_tb_weight->Location = System::Drawing::Point(55, 125);
			this->_tb_weight->Name = L"_tb_weight";
			this->_tb_weight->Size = System::Drawing::Size(90, 20);
			this->_tb_weight->TabIndex = 13;
			this->_tb_weight->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_weight->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_weight->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _pnl_subsystem
			// 
			this->_pnl_subsystem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_subsystem->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_subsystem->Controls->Add(this->_chb_subsystem_variation);
			this->_pnl_subsystem->Controls->Add(this->_l_subsystem);
			this->_pnl_subsystem->Controls->Add(this->_cb_subsystem);
			this->_pnl_subsystem->Controls->Add(this->_l_bracket);
			this->_pnl_subsystem->Controls->Add(this->_cb_bracket);
			this->_pnl_subsystem->Controls->Add(this->_l_profile);
			this->_pnl_subsystem->Controls->Add(this->_cb_profile);
			this->_pnl_subsystem->Location = System::Drawing::Point(325, 5);
			this->_pnl_subsystem->Name = L"_pnl_subsystem";
			this->_pnl_subsystem->Size = System::Drawing::Size(155, 480);
			this->_pnl_subsystem->TabIndex = 132;
			// 
			// _chb_subsystem_variation
			// 
			this->_chb_subsystem_variation->AutoSize = true;
			this->_chb_subsystem_variation->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_chb_subsystem_variation->Location = System::Drawing::Point(5, 65);
			this->_chb_subsystem_variation->Name = L"_chb_subsystem_variation";
			this->_chb_subsystem_variation->Size = System::Drawing::Size(86, 17);
			this->_chb_subsystem_variation->TabIndex = 15;
			this->_chb_subsystem_variation->Text = L"ВАРИАЦИИ";
			this->_chb_subsystem_variation->UseVisualStyleBackColor = true;
			this->_chb_subsystem_variation->CheckedChanged += gcnew System::EventHandler(this, &MainForm::_changedValueSubsystemCheckBox);
			// 
			// _pnl_constructions
			// 
			this->_pnl_constructions->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_constructions->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_constructions->Controls->Add(this->_tb_v_step_profile_marginal_area);
			this->_pnl_constructions->Controls->Add(this->_tb_h_step_profile);
			this->_pnl_constructions->Controls->Add(this->_l_h_step_profile);
			this->_pnl_constructions->Controls->Add(this->_tb_v_step_profile_ordinary_area);
			this->_pnl_constructions->Controls->Add(this->_l_v_step_profile);
			this->_pnl_constructions->Controls->Add(this->_tb_h_step_bracket_marginal_area);
			this->_pnl_constructions->Controls->Add(this->_tb_h_step_bracket_ordinary_area);
			this->_pnl_constructions->Controls->Add(this->_l_h_step_bracket);
			this->_pnl_constructions->Controls->Add(this->_tb_v_step_bracket_marginal_area);
			this->_pnl_constructions->Controls->Add(this->_tb_v_step_bracket_ordinary_area);
			this->_pnl_constructions->Controls->Add(this->_l_v_step_bracket);
			this->_pnl_constructions->Controls->Add(this->_tb_facing_radius);
			this->_pnl_constructions->Controls->Add(this->_l_facing_radius);
			this->_pnl_constructions->Controls->Add(this->_l_constructions);
			this->_pnl_constructions->Location = System::Drawing::Point(165, 173);
			this->_pnl_constructions->Name = L"_pnl_constructions";
			this->_pnl_constructions->Size = System::Drawing::Size(155, 312);
			this->_pnl_constructions->TabIndex = 133;
			// 
			// _tb_v_step_profile_marginal_area
			// 
			this->_tb_v_step_profile_marginal_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_v_step_profile_marginal_area->Location = System::Drawing::Point(78, 223);
			this->_tb_v_step_profile_marginal_area->Name = L"_tb_v_step_profile_marginal_area";
			this->_tb_v_step_profile_marginal_area->Size = System::Drawing::Size(67, 20);
			this->_tb_v_step_profile_marginal_area->TabIndex = 24;
			this->_tb_v_step_profile_marginal_area->Text = L"КЗ";
			this->_tb_v_step_profile_marginal_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_v_step_profile_marginal_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_v_step_profile_marginal_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_h_step_profile
			// 
			this->_tb_h_step_profile->Location = System::Drawing::Point(25, 280);
			this->_tb_h_step_profile->Name = L"_tb_h_step_profile";
			this->_tb_h_step_profile->Size = System::Drawing::Size(102, 20);
			this->_tb_h_step_profile->TabIndex = 25;
			this->_tb_h_step_profile->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_h_step_profile->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_h_step_profile->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_h_step_profile
			// 
			this->_l_h_step_profile->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_h_step_profile->Location = System::Drawing::Point(0, 248);
			this->_l_h_step_profile->Name = L"_l_h_step_profile";
			this->_l_h_step_profile->Size = System::Drawing::Size(150, 26);
			this->_l_h_step_profile->TabIndex = 134;
			this->_l_h_step_profile->Text = L"Шаг горизонтального профиля по вертикали (мм):";
			// 
			// _tb_v_step_profile_ordinary_area
			// 
			this->_tb_v_step_profile_ordinary_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_v_step_profile_ordinary_area->Location = System::Drawing::Point(5, 223);
			this->_tb_v_step_profile_ordinary_area->Name = L"_tb_v_step_profile_ordinary_area";
			this->_tb_v_step_profile_ordinary_area->Size = System::Drawing::Size(67, 20);
			this->_tb_v_step_profile_ordinary_area->TabIndex = 23;
			this->_tb_v_step_profile_ordinary_area->Text = L"РЗ";
			this->_tb_v_step_profile_ordinary_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_v_step_profile_ordinary_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_v_step_profile_ordinary_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_v_step_profile
			// 
			this->_l_v_step_profile->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_v_step_profile->Location = System::Drawing::Point(0, 191);
			this->_l_v_step_profile->Name = L"_l_v_step_profile";
			this->_l_v_step_profile->Size = System::Drawing::Size(153, 26);
			this->_l_v_step_profile->TabIndex = 135;
			this->_l_v_step_profile->Text = L"Шаг вертикального профиля по горизонтали (мм):";
			// 
			// _tb_h_step_bracket_marginal_area
			// 
			this->_tb_h_step_bracket_marginal_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_h_step_bracket_marginal_area->Location = System::Drawing::Point(78, 166);
			this->_tb_h_step_bracket_marginal_area->Name = L"_tb_h_step_bracket_marginal_area";
			this->_tb_h_step_bracket_marginal_area->Size = System::Drawing::Size(67, 20);
			this->_tb_h_step_bracket_marginal_area->TabIndex = 22;
			this->_tb_h_step_bracket_marginal_area->Text = L"КЗ";
			this->_tb_h_step_bracket_marginal_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_h_step_bracket_marginal_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_h_step_bracket_marginal_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_h_step_bracket_ordinary_area
			// 
			this->_tb_h_step_bracket_ordinary_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_h_step_bracket_ordinary_area->Location = System::Drawing::Point(5, 166);
			this->_tb_h_step_bracket_ordinary_area->Name = L"_tb_h_step_bracket_ordinary_area";
			this->_tb_h_step_bracket_ordinary_area->Size = System::Drawing::Size(67, 20);
			this->_tb_h_step_bracket_ordinary_area->TabIndex = 21;
			this->_tb_h_step_bracket_ordinary_area->Text = L"РЗ";
			this->_tb_h_step_bracket_ordinary_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_h_step_bracket_ordinary_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_h_step_bracket_ordinary_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_h_step_bracket
			// 
			this->_l_h_step_bracket->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_h_step_bracket->Location = System::Drawing::Point(5, 134);
			this->_l_h_step_bracket->Name = L"_l_h_step_bracket";
			this->_l_h_step_bracket->Size = System::Drawing::Size(140, 26);
			this->_l_h_step_bracket->TabIndex = 136;
			this->_l_h_step_bracket->Text = L"Шаг кронштейнов по горизонтали (мм):";
			// 
			// _tb_v_step_bracket_marginal_area
			// 
			this->_tb_v_step_bracket_marginal_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_v_step_bracket_marginal_area->Location = System::Drawing::Point(78, 109);
			this->_tb_v_step_bracket_marginal_area->Name = L"_tb_v_step_bracket_marginal_area";
			this->_tb_v_step_bracket_marginal_area->Size = System::Drawing::Size(67, 20);
			this->_tb_v_step_bracket_marginal_area->TabIndex = 20;
			this->_tb_v_step_bracket_marginal_area->Text = L"КЗ";
			this->_tb_v_step_bracket_marginal_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_v_step_bracket_marginal_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_v_step_bracket_marginal_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _tb_v_step_bracket_ordinary_area
			// 
			this->_tb_v_step_bracket_ordinary_area->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_v_step_bracket_ordinary_area->Location = System::Drawing::Point(5, 109);
			this->_tb_v_step_bracket_ordinary_area->Name = L"_tb_v_step_bracket_ordinary_area";
			this->_tb_v_step_bracket_ordinary_area->Size = System::Drawing::Size(67, 20);
			this->_tb_v_step_bracket_ordinary_area->TabIndex = 19;
			this->_tb_v_step_bracket_ordinary_area->Text = L"РЗ";
			this->_tb_v_step_bracket_ordinary_area->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_v_step_bracket_ordinary_area->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_v_step_bracket_ordinary_area->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_v_step_bracket
			// 
			this->_l_v_step_bracket->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_v_step_bracket->Location = System::Drawing::Point(5, 77);
			this->_l_v_step_bracket->Name = L"_l_v_step_bracket";
			this->_l_v_step_bracket->Size = System::Drawing::Size(140, 26);
			this->_l_v_step_bracket->TabIndex = 137;
			this->_l_v_step_bracket->Text = L"Шаг кронштейнов по вертикали (мм):";
			// 
			// _tb_facing_radius
			// 
			this->_tb_facing_radius->Location = System::Drawing::Point(25, 52);
			this->_tb_facing_radius->Name = L"_tb_facing_radius";
			this->_tb_facing_radius->Size = System::Drawing::Size(102, 20);
			this->_tb_facing_radius->TabIndex = 18;
			this->_tb_facing_radius->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->_tb_facing_radius->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_facing_radius->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _l_facing_radius
			// 
			this->_l_facing_radius->AutoSize = true;
			this->_l_facing_radius->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->_l_facing_radius->Location = System::Drawing::Point(15, 33);
			this->_l_facing_radius->Name = L"_l_facing_radius";
			this->_l_facing_radius->Size = System::Drawing::Size(124, 13);
			this->_l_facing_radius->TabIndex = 138;
			this->_l_facing_radius->Text = L"Вылет облицовки (мм):";
			// 
			// _l_constructions
			// 
			this->_l_constructions->AutoSize = true;
			this->_l_constructions->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->_l_constructions->Location = System::Drawing::Point(1, 0);
			this->_l_constructions->Name = L"_l_constructions";
			this->_l_constructions->Size = System::Drawing::Size(149, 24);
			this->_l_constructions->TabIndex = 139;
			this->_l_constructions->Text = L"КОНСТРУКЦИИ";
			// 
			// _pnl_variation
			// 
			this->_pnl_variation->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_variation->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_variation->Controls->Add(this->_l_variations);
			this->_pnl_variation->Controls->Add(this->_l_sp_20_13330_2011);
			this->_pnl_variation->Controls->Add(this->_chb_aerodynamic_factor);
			this->_pnl_variation->Controls->Add(this->_l_c1);
			this->_pnl_variation->Controls->Add(this->_tb_c1);
			this->_pnl_variation->Controls->Add(this->_l_c2);
			this->_pnl_variation->Controls->Add(this->_tb_c2);
			this->_pnl_variation->Location = System::Drawing::Point(485, 5);
			this->_pnl_variation->Name = L"_pnl_variation";
			this->_pnl_variation->Size = System::Drawing::Size(155, 143);
			this->_pnl_variation->TabIndex = 140;
			// 
			// _pnl_account
			// 
			this->_pnl_account->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_account->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_account->Controls->Add(this->_l_account);
			this->_pnl_account->Controls->Add(this->_chb_anker);
			this->_pnl_account->Controls->Add(this->_chb_nvf_elements);
			this->_pnl_account->Controls->Add(this->_chb_nvf_connection);
			this->_pnl_account->Location = System::Drawing::Point(645, 5);
			this->_pnl_account->Name = L"_pnl_account";
			this->_pnl_account->Size = System::Drawing::Size(155, 143);
			this->_pnl_account->TabIndex = 141;
			// 
			// _pnl_results
			// 
			this->_pnl_results->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->_pnl_results->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->_pnl_results->Controls->Add(this->_l_results);
			this->_pnl_results->Controls->Add(this->_l_qz);
			this->_pnl_results->Controls->Add(this->_l_qy);
			this->_pnl_results->Controls->Add(this->_tb_Qy_0);
			this->_pnl_results->Controls->Add(this->_tb_Qz_0);
			this->_pnl_results->Controls->Add(this->_tb_Qy_1);
			this->_pnl_results->Controls->Add(this->_tb_Qz_1);
			this->_pnl_results->Controls->Add(this->_l_connections);
			this->_pnl_results->Controls->Add(this->_tb_digging_anker);
			this->_pnl_results->Controls->Add(this->_tb_strength_profile);
			this->_pnl_results->Controls->Add(this->_l_digging_anker);
			this->_pnl_results->Controls->Add(this->_tb_strength_bracket);
			this->_pnl_results->Controls->Add(this->_tb_strength_extension);
			this->_pnl_results->Controls->Add(this->_tb_connections);
			this->_pnl_results->Controls->Add(this->_l_strength_contour);
			this->_pnl_results->Controls->Add(this->_l_strength_extension);
			this->_pnl_results->Controls->Add(this->_l_strength_bracket);
			this->_pnl_results->Location = System::Drawing::Point(485, 177);
			this->_pnl_results->Name = L"_pnl_results";
			this->_pnl_results->Size = System::Drawing::Size(315, 247);
			this->_pnl_results->TabIndex = 142;
			// 
			// _tb_conclusion
			// 
			this->_tb_conclusion->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->_tb_conclusion->Location = System::Drawing::Point(485, 429);
			this->_tb_conclusion->Multiline = true;
			this->_tb_conclusion->Name = L"_tb_conclusion";
			this->_tb_conclusion->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->_tb_conclusion->Size = System::Drawing::Size(315, 56);
			this->_tb_conclusion->TabIndex = 33;
			this->_tb_conclusion->Text = L"Вывод";
			this->_tb_conclusion->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::clickToCheckingField);
			this->_tb_conclusion->Enter += gcnew System::EventHandler(this, &MainForm::focusToCheckingField);
			// 
			// _pb_helper
			// 
			this->_pb_helper->Cursor = System::Windows::Forms::Cursors::Hand;
			this->_pb_helper->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"_pb_helper.Image")));
			this->_pb_helper->Location = System::Drawing::Point(770, 149);
			this->_pb_helper->Name = L"_pb_helper";
			this->_pb_helper->Size = System::Drawing::Size(30, 27);
			this->_pb_helper->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->_pb_helper->TabIndex = 143;
			this->_pb_helper->TabStop = false;
			this->_pb_helper->Click += gcnew System::EventHandler(this, &MainForm::openDocumentation);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(134)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->ClientSize = System::Drawing::Size(806, 490);
			this->Controls->Add(this->_pb_helper);
			this->Controls->Add(this->_tb_conclusion);
			this->Controls->Add(this->_pnl_results);
			this->Controls->Add(this->_pnl_account);
			this->Controls->Add(this->_pnl_variation);
			this->Controls->Add(this->_pnl_constructions);
			this->Controls->Add(this->_pnl_subsystem);
			this->Controls->Add(this->_pnl_facing);
			this->Controls->Add(this->_pnl_object);
			this->Controls->Add(this->_pnl_climate);
			this->Controls->Add(this->_b_generate_report);
			this->Controls->Add(this->_b_calculate_account);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"ZIAS FACADE SYSTEM - РАСЧЕТНЫЙ КОМПЛЕКС (2015а)";
			this->_pnl_climate->ResumeLayout(false);
			this->_pnl_climate->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_line))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_climate_top_left))->EndInit();
			this->_pnl_object->ResumeLayout(false);
			this->_pnl_object->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_object_bottom_left))->EndInit();
			this->_pnl_facing->ResumeLayout(false);
			this->_pnl_facing->PerformLayout();
			this->_pnl_subsystem->ResumeLayout(false);
			this->_pnl_subsystem->PerformLayout();
			this->_pnl_constructions->ResumeLayout(false);
			this->_pnl_constructions->PerformLayout();
			this->_pnl_variation->ResumeLayout(false);
			this->_pnl_variation->PerformLayout();
			this->_pnl_account->ResumeLayout(false);
			this->_pnl_account->PerformLayout();
			this->_pnl_results->ResumeLayout(false);
			this->_pnl_results->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->_pb_helper))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void clickToCheckingField(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		private: System::Void focusToCheckingField(System::Object^  sender, System::EventArgs^  e);
		private: System::Void _changedValueClimateRadiobutton(System::Object^  sender, System::EventArgs^  e); 
		private: System::Void _changedValueFacingRadiobutton(System::Object^  sender, System::EventArgs^  e);
		private: System::Void _changedValueSubsystemCheckBox(System::Object^  sender, System::EventArgs^  e);
		private: System::Void _changedValueVariationsCheckBox(System::Object^  sender, System::EventArgs^  e);
		private: System::Void openDocumentation(System::Object^  sender, System::EventArgs^  e); 
		private: System::Void _b_calculate_account_Click(System::Object^  sender, System::EventArgs^  e); 
		private: System::Void _b_generate_report_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void _cb_subsystem_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void _cb_cities_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};
} // zias
