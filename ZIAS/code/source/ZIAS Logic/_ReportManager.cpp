#include "stdafx.h"

using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace System::IO;

namespace zias {
	// STATIC IMPLEMENTATION
	// ---------------------
	std::shared_ptr<ReportManager> ReportManager::_instance = nullptr;
	// ---------------------

	ReportManager::ReportManager() {

	}

	ReportManager::~ReportManager() {

	}

	std::shared_ptr<ReportManager>& ReportManager::Instance() {
		if (_instance == nullptr) {
			_instance.reset(new ReportManager());

			// TODO: инициализация класса при первом обращении

		}

		return _instance;
	}

	void ReportManager::generateReport(const FormDataArgs& my_fda)
	{
		String ^ nameSubsystem = gcnew String(my_fda.subsystem->name.c_str());
		String ^ nameDoc = _PATH_TO_INPUT_REPORTS_;
		String ^ newNameDoc = _PATH_TO_OUTPUT_REPORTS_;

		if (nameSubsystem->IndexOf("Standart") != -1)
		{
			nameDoc += "Standart\\Standart";
			newNameDoc += "Standart\\Standart";
		}
		else if (nameSubsystem->IndexOf("Optima") != -1)
		{
			nameDoc += "Optima\\Optima";
			newNameDoc += "Optima\\Optima";
		}
		else if (nameSubsystem->IndexOf("Strong") != -1)
		{
			nameDoc += "Strong\\Strong";
			newNameDoc += "Strong\\Strong";
		}
		else if (nameSubsystem->IndexOf("КПР") != -1)
		{
			nameDoc += "КПР\\КПР";
			newNameDoc += "КПР\\КПР";
		}
		else if (nameSubsystem->IndexOf("Maxima") != -1)
		{
			nameDoc += "Maxima\\Maxima";
			newNameDoc += "Maxima\\Maxima";
		}
		else if (nameSubsystem->IndexOf("Maxima Medium") != -1)
		{
			nameDoc += "Maxima Medium\\Maxima Medium";
			newNameDoc += "Maxima Medium\\Maxima Medium";
		}
		else if (nameSubsystem->IndexOf("Maxima Light") != -1)
		{
			nameDoc += "Maxima Light\\Maxima Lights";
			newNameDoc += "Maxima Light\\Maxima Lights";
		}
		else if (nameSubsystem->IndexOf("Medium Strong") != -1)
		{
			nameDoc += "Medium Strong\\Medium Strong";
			newNameDoc += "Medium Strong\\Medium Strong";
		}
		else
		{
			return;
		}

		if (my_fda.checkAnker)
		{
			nameDoc += " anker.docx";
		}
		else
		{
			nameDoc += " no anker.docx";
		}

		WordprocessingDocument ^  doc = WordprocessingDocument::Open(nameDoc, true);

		String ^ docText = nullptr;
		StreamReader ^ sr = gcnew StreamReader(doc->MainDocumentPart->GetStream());
		docText = sr->ReadToEnd();
		commonReport(my_fda, docText);

		if (my_fda.checkAnker)
		{
			ankerReport(my_fda, docText, nameSubsystem);
		}

		newNameDoc += " ";
		newNameDoc += gcnew String(my_fda.objectResponsible.c_str());
		newNameDoc += ".docx";

		WordprocessingDocument ^ newDoc = WordprocessingDocument::Create(newNameDoc, WordprocessingDocumentType::Document);
		StreamWriter ^ sw = gcnew StreamWriter(newDoc->MainDocumentPart->GetStream(FileMode::Create));
		sw->Write(docText);

		sw->Close();
	}

	/*void ReportManager::checkExistsFile(String ^ nameFile)
	{
	if(File::Exists(nameFile))

	}*/

	void ReportManager::ankerReport(const FormDataArgs& my_fda, String ^ docText, String ^ subsystem)
	{
		docText = docText->Replace("#subsystem_2#", subsystem);
		docText = docText->Replace("#x#", Convert::ToString(my_fda.bracket->x));
		docText = docText->Replace("#b#", Convert::ToString(my_fda.bracket->b));
		docText = docText->Replace("#c#", Convert::ToString(my_fda.bracket->c));
		docText = docText->Replace("#e#", Convert::ToString(my_fda.weight));
		docText = docText->Replace("#S_1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_1")));
		docText = docText->Replace("#R_z1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_1")));
		docText = docText->Replace("#N_y1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_1")));
		docText = docText->Replace("#R_1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_1")));
		docText = docText->Replace("#S_2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_2")));
		docText = docText->Replace("#R_z2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_2")));
		docText = docText->Replace("#N_y2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_2")));
		docText = docText->Replace("#R_2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_2")));
		docText = docText->Replace("#S_3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_3")));
		docText = docText->Replace("#R_z3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_3")));
		docText = docText->Replace("#N_y3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_3")));
		docText = docText->Replace("#R_3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_3")));
	}

	void ReportManager::commonReport(const FormDataArgs& my_fda, String ^ docText)
	{
		//спросить про zias(в каком формате будет)
		docText = docText->Replace("#zias#", gcnew String(my_fda.facing->ziasN.c_str()));
		docText = docText->Replace("#subsystem_1#", gcnew String(my_fda.subsystem->name.c_str()));
		docText = docText->Replace("#nameObject#", gcnew String(my_fda.objectName.c_str()));
		docText = docText->Replace("#cipher#", gcnew String(my_fda.objectCipher.c_str()));
		docText = docText->Replace("#responsible#", gcnew String(my_fda.objectResponsible.c_str()));

		time_t timer;
		struct tm *tblock;
		timer = time(NULL);
		tblock = localtime(&timer);
		std::string str = std::to_string(tblock->tm_mday);
		str += '/';
		str += std::to_string(tblock->tm_mon + 1);
		str += '/';
		str += std::to_string(tblock->tm_year + 1900);

		//что в поле name у  bracket и profile 
		docText = docText->Replace("#date#", gcnew String(str.c_str()));
		docText = docText->Replace("#facing#", gcnew String(my_fda.facing->name.c_str()));
		docText = docText->Replace("#bracket#", gcnew String(my_fda.bracket->name.c_str()));
		docText = docText->Replace("#profile#", gcnew String(my_fda.profile->name.c_str()));
		docText = docText->Replace("#H_1#", Convert::ToString(my_fda.v_step_profile));
		docText = docText->Replace("#B_1#", Convert::ToString(my_fda.v_step_bracket_ordinary_area));
		docText = docText->Replace("#B_2#", Convert::ToString(my_fda.v_step_bracket_marginal_area));
		docText = docText->Replace("#height#", Convert::ToString(my_fda.objectHeight));
		docText = docText->Replace("#wind_district#", gcnew String(my_fda.city->wind_district->name.c_str()));
		docText = docText->Replace("#location_type#", gcnew String(my_fda.locationType->name.c_str()));
		docText = docText->Replace("#ice_district#", gcnew String(my_fda.city->ice_district->name.c_str()));
		docText = docText->Replace("#weight_1#", Convert::ToString(my_fda.facing->weight));
		docText = docText->Replace("#q_z_n#", Convert::ToString(VariableStorageManager::Instance()->getVariable("qz_0")));
		docText = docText->Replace("#q_z#", Convert::ToString(VariableStorageManager::Instance()->getVariable("qz_1")));
		docText = docText->Replace("#gamma_f1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_1")));
		docText = docText->Replace("#weight_2#", Convert::ToString(my_fda.profile->weight));
		docText = docText->Replace("#q_zh#", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H")));
		docText = docText->Replace("#gamma_f2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_2")));
		docText = docText->Replace("#sum_q_z#", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum")));
		docText = docText->Replace("#w_0#", Convert::ToString(VariableStorageManager::Instance()->getVariable("w_0")));
		docText = docText->Replace("#k_z1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ze")));
		docText = docText->Replace("#ksi_z#", Convert::ToString(VariableStorageManager::Instance()->getVariable("ksi_ze")));
		docText = docText->Replace("#c_1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_1")));
		docText = docText->Replace("#c_2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_2")));
		docText = docText->Replace("#nu#", Convert::ToString(VariableStorageManager::Instance()->getVariable("nu")));
		docText = docText->Replace("#Q_y_n_winter_ordinary#", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_311")));
		docText = docText->Replace("#q_y1#", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_311")));
		docText = docText->Replace("#gamma_f3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_3")));
		docText = docText->Replace("#ice_thickness#", Convert::ToString(VariableStorageManager::Instance()->getVariable("b")));
		docText = docText->Replace("#k_z2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ice")));
		docText = docText->Replace("#mu_2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("mu_2")));
		docText = docText->Replace("#rho#", Convert::ToString(VariableStorageManager::Instance()->getVariable("rho")));
		docText = docText->Replace("#i_z_n#", Convert::ToString(VariableStorageManager::Instance()->getVariable("I_312")));
		docText = docText->Replace("#i_z#", Convert::ToString(VariableStorageManager::Instance()->getVariable("i_312")));
		docText = docText->Replace("#gamma_f4#", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_4")));
		docText = docText->Replace("#Q_y_n_summer_ordinary#", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_321")));
		docText = docText->Replace("#q_y2#", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_321")));
		docText = docText->Replace("#Q_y_n_edge#", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_411")));
		docText = docText->Replace("#q_y3#", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_411")));
		docText = docText->Replace("#output#", gcnew String(my_fda.conclusion.c_str()));
	}

} // zias 