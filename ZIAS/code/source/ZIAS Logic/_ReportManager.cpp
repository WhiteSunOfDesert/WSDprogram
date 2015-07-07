#include "stdafx.h"
#include <windows.h>
#include <string>
using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace System::IO;
using namespace System;

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

	void ReportManager::generateReport(const FormDataArgs& my_fda, String^ my_file_name)
	{
		String ^ nameSubsystem;
		std::string nameDoc = _PATH_TO_INPUT_REPORTS_;
		std::string newNameDoc = utils::toStdString(my_file_name);
		int checkNameDocument = 0;

		//Определение типа документа
		if (!my_fda.isSubsystemStandart)
		{
			nameDoc += "Standart\\Standart";
			checkNameDocument = 1;
			nameSubsystem = "";
		}
		else
		{
			nameSubsystem = gcnew String(my_fda.subsystem->name.c_str());
			if (nameSubsystem->IndexOf("Standart") != -1)
			{
				nameDoc += "Standart\\Standart";
				checkNameDocument = 1;
			}
			else if (nameSubsystem->IndexOf("Optima") != -1)
			{
				nameDoc += "Optima\\Optima";
				checkNameDocument = 2;
			}
			else if (nameSubsystem->IndexOf("Strong") != -1)
			{
				if (nameSubsystem->IndexOf("Medium") != -1)
				{
					nameDoc += "Medium Strong\\Medium Strong";
					checkNameDocument = 8;
				}
				else
				{
					nameDoc += "Strong\\Strong";
					checkNameDocument = 3;
				}
			}
			else if (nameSubsystem->IndexOf("КПР") != -1)
			{
				nameDoc += "КПР\\КПР";
				checkNameDocument = 4;
			}
			else if (nameSubsystem->IndexOf("Maxima") != -1)
			{
				if (nameSubsystem->IndexOf("Medium") != -1)
				{
					nameDoc += "Maxima Medium\\Maxima Medium";
					checkNameDocument = 6;
				}
				else if (nameSubsystem->IndexOf("Light") != -1)
				{
					nameDoc += "Maxima Light\\Maxima Light";
					checkNameDocument = 7;
				}
				else
				{
					nameDoc += "Maxima\\Maxima";
					checkNameDocument = 5;
				}
			}
			else
			{
				return;
			}
		}

		//с анкером или без анкера
		if (my_fda.checkAnker)
		{
			nameDoc += " anker.docx";
			checkNameDocument += 10;
		}
		else
		{
			nameDoc += " no anker.docx";
		}

		//newNameDoc += ".docx";
		CopyFile(nameDoc.c_str(), newNameDoc.c_str(), false); 
	
		//по типу документа вызываем соответствующие функции
		switch (checkNameDocument)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			commonReport(my_fda, gcnew String(newNameDoc.c_str()));
			break;
		case 5:
			maximaNoAnkerReport(my_fda, gcnew String(newNameDoc.c_str()));
			break;
		case 6:
		case 7:
			commonConcreteSlabsReport(my_fda, gcnew String(newNameDoc.c_str()));
			break;
		case 8:
			maximaMediumNoAnkerReport(my_fda, gcnew String(newNameDoc.c_str()));
			break;
		case 11:
		case 12:
		case 13:
		case 14:
			commonReport(my_fda, gcnew String(newNameDoc.c_str()));
			ankerCommonReport(my_fda, gcnew String(newNameDoc.c_str()), nameSubsystem);
			break;
		case 15:
			maximaNoAnkerReport(my_fda, gcnew String(newNameDoc.c_str()));
			maximaAnkerReport(my_fda, gcnew String(newNameDoc.c_str()));
			break;
		case 16:
		case 17:
			commonConcreteSlabsReport(my_fda, gcnew String(newNameDoc.c_str()));
			ankerCommonReport(my_fda, gcnew String(newNameDoc.c_str()), nameSubsystem);
			break;
		case 18:
			maximaMediumNoAnkerReport(my_fda, gcnew String(newNameDoc.c_str()));
			ankerCommonReport(my_fda, gcnew String(newNameDoc.c_str()), nameSubsystem);
			break;
		}

	}

	void ReportManager::maximaNoAnkerReport(const FormDataArgs& my_fda, String ^ namedoc)
	{
		String ^ docText1 = nullptr;

		WordprocessingDocument ^  docx = WordprocessingDocument::Open(namedoc, true);
		StreamReader ^ sr = gcnew StreamReader(docx->MainDocumentPart->GetStream());
		docText1 = sr->ReadToEnd();

		sr->Close();

		docText1 = docText1->Replace("subsystem1", gcnew String(my_fda.subsystem->name.c_str()));
		docText1 = docText1->Replace("nameObject", gcnew String(my_fda.objectName.c_str()));
		docText1 = docText1->Replace("cipher", gcnew String(my_fda.objectCipher.c_str()));
		docText1 = docText1->Replace("responsible", gcnew String(my_fda.objectResponsible.c_str()));

		time_t timer;
		struct tm *tblock;
		timer = time(NULL);
		tblock = localtime(&timer);
		std::string str = std::to_string(tblock->tm_mday);
		str += '/';
		str += std::to_string(tblock->tm_mon + 1);
		str += '/';
		str += std::to_string(tblock->tm_year + 1900);

		docText1 = docText1->Replace("date", gcnew String(str.c_str()));

		if (my_fda.isFacingStandart)
		{
			docText1 = docText1->Replace("facing", gcnew String(my_fda.facing->name.c_str()));
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("zias", gcnew String(my_fda.facing->ziasN.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("facing", "");
			docText1 = docText1->Replace("zias", "");
		}

		docText1 = docText1->Replace("bracket", gcnew String(my_fda.subsystem->bracket->name.c_str()));
		docText1 = docText1->Replace("profile1", gcnew String(my_fda.subsystem->profile_first->name.c_str()));
		docText1 = docText1->Replace("weightTwo", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));
		docText1 = docText1->Replace("profile2", gcnew String(my_fda.subsystem->profile_second->name.c_str()));
		docText1 = docText1->Replace("weightThree", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_3")));

		docText1 = docText1->Replace("constH1", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_1")));
		docText1 = docText1->Replace("constH2", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_2")));
		docText1 = docText1->Replace("constH3", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_3")));
		docText1 = docText1->Replace("constB1", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_1")));

		docText1 = docText1->Replace("height", Convert::ToString(my_fda.objectHeight));
		docText1 = docText1->Replace("locationType", gcnew String(my_fda.locationType->name.c_str()));

		if (my_fda.isCityClimate)
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.city->wind_district->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.city->ice_district->name.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.windDistrict->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.iceDistrict->name.c_str()));
		}

		docText1 = docText1->Replace("qzn", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_2")));
		docText1 = docText1->Replace("qzh1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_1")));
		docText1 = docText1->Replace("qzh2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_2")));
		docText1 = docText1->Replace("qzh3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_3")));

		docText1 = docText1->Replace("gammaf1", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_1")));
		docText1 = docText1->Replace("gammaf2", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_2")));
		docText1 = docText1->Replace("sumqz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_1")));
		docText1 = docText1->Replace("sumqz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_2")));
		docText1 = docText1->Replace("qz", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_2")));
		docText1 = docText1->Replace("w0", Convert::ToString(VariableStorageManager::Instance()->getVariable("w_0")));
		docText1 = docText1->Replace("kz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ze")));
		docText1 = docText1->Replace("ksiz", Convert::ToString(VariableStorageManager::Instance()->getVariable("ksi_ze")));

		if (!my_fda.checkAerodynamicFactor)
		{
			docText1 = docText1->Replace("c1", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_1")));
			docText1 = docText1->Replace("c2", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_2")));
		}
		else
		{
			docText1 = docText1->Replace("c1", Convert::ToString(my_fda.c1));
			docText1 = docText1->Replace("c2", Convert::ToString(my_fda.c2));
		}

		docText1 = docText1->Replace("NU", Convert::ToString(VariableStorageManager::Instance()->getVariable("nu")));
		docText1 = docText1->Replace("QynWinterOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_311")));
		docText1 = docText1->Replace("qy1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_311")));
		docText1 = docText1->Replace("gammaf3", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_3")));
		docText1 = docText1->Replace("iceThickness", Convert::ToString(VariableStorageManager::Instance()->getVariable("b_ice")));
		docText1 = docText1->Replace("kz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ice")));
		docText1 = docText1->Replace("mu2", Convert::ToString(VariableStorageManager::Instance()->getVariable("mu_2")));
		docText1 = docText1->Replace("rho", Convert::ToString(VariableStorageManager::Instance()->getVariable("rho")));
		docText1 = docText1->Replace("IZN", Convert::ToString(VariableStorageManager::Instance()->getVariable("I_312")));
		docText1 = docText1->Replace("IZ", Convert::ToString(VariableStorageManager::Instance()->getVariable("i_312")));
		docText1 = docText1->Replace("gammaf4", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_4")));
		docText1 = docText1->Replace("QynSummerOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_321")));
		docText1 = docText1->Replace("qy2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_321")));
		docText1 = docText1->Replace("QynEdge", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_411")));
		docText1 = docText1->Replace("qy3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_411")));
		docText1 = docText1->Replace("output", gcnew String(my_fda.conclusion.c_str()));

		StreamWriter ^ sw = gcnew StreamWriter(docx->MainDocumentPart->GetStream(FileMode::Create));

		sw->Write(docText1);

		sw->Close();
		docx->Close();
	}

	void ReportManager::maximaAnkerReport(const FormDataArgs& my_fda, String ^ namedoc)
	{
		String ^ docText2 = nullptr;

		WordprocessingDocument ^  docx1 = WordprocessingDocument::Open(namedoc, true);
		StreamReader ^ sr1 = gcnew StreamReader(docx1->MainDocumentPart->GetStream());
		docText2 = sr1->ReadToEnd();
		sr1->Close();
		
		if (my_fda.isSubsystemStandart)
		{
			docText2 = docText2->Replace("constB", Convert::ToString(my_fda.subsystem->bracket->b));
			docText2 = docText2->Replace("constC", Convert::ToString(my_fda.subsystem->bracket->c));
		}
		else
		{
			docText2 = docText2->Replace("constB", Convert::ToString(my_fda.bracket->b));
			docText2 = docText2->Replace("constC", Convert::ToString(my_fda.bracket->c));
		}

		docText2 = docText2->Replace("constE", Convert::ToString(my_fda.facing_radius));
		docText2 = docText2->Replace("S1", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_1")));
		docText2 = docText2->Replace("S2", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_2")));
		docText2 = docText2->Replace("Pz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_1")));
		docText2 = docText2->Replace("Ny1", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_1")));
		docText2 = docText2->Replace("Pz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_2")));
		docText2 = docText2->Replace("Ny2", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_2")));
		docText2 = docText2->Replace("S3", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_3")));
		docText2 = docText2->Replace("Pz3", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_3")));
		docText2 = docText2->Replace("Ny3", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_3")));
		docText2 = docText2->Replace("R11k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_1_1")) / 1000.f));
		docText2 = docText2->Replace("R21k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_2_1")) / 1000.f));
		docText2 = docText2->Replace("R31k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_3_1")) / 1000.f));
		docText2 = docText2->Replace("R12k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_1_2")) / 1000.f));
		docText2 = docText2->Replace("R22k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_2_2")) / 1000.f));
		docText2 = docText2->Replace("R32k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_3_2")) / 1000.f));
		docText2 = docText2->Replace("R11", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_1_1")));
		docText2 = docText2->Replace("R12", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_1_2")));
		docText2 = docText2->Replace("R21", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_2_1")));
		docText2 = docText2->Replace("R22", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_2_2")));
		docText2 = docText2->Replace("R31", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_3_1")));
		docText2 = docText2->Replace("R32", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_3_2")));

		StreamWriter ^ sw1 = gcnew StreamWriter(docx1->MainDocumentPart->GetStream(FileMode::Create));

		sw1->Write(docText2);
		sw1->Close();
		docx1->Close();
	}

	void ReportManager::maximaMediumNoAnkerReport(const FormDataArgs& my_fda, String ^ namedoc)
	{
		String ^ docText1 = nullptr;

		WordprocessingDocument ^  docx = WordprocessingDocument::Open(namedoc, true);
		StreamReader ^ sr = gcnew StreamReader(docx->MainDocumentPart->GetStream());
		docText1 = sr->ReadToEnd();

		sr->Close();

		docText1 = docText1->Replace("subsystem1", gcnew String(my_fda.subsystem->name.c_str()));
		docText1 = docText1->Replace("nameObject", gcnew String(my_fda.objectName.c_str()));
		docText1 = docText1->Replace("cipher", gcnew String(my_fda.objectCipher.c_str()));
		docText1 = docText1->Replace("responsible", gcnew String(my_fda.objectResponsible.c_str()));

		time_t timer;
		struct tm *tblock;
		timer = time(NULL);
		tblock = localtime(&timer);
		std::string str = std::to_string(tblock->tm_mday);
		str += '/';
		str += std::to_string(tblock->tm_mon + 1);
		str += '/';
		str += std::to_string(tblock->tm_year + 1900);

		docText1 = docText1->Replace("date", gcnew String(str.c_str()));

		if (my_fda.isFacingStandart)
		{
			docText1 = docText1->Replace("facing", gcnew String(my_fda.facing->name.c_str()));
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("zias", gcnew String(my_fda.facing->ziasN.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));
			docText1 = docText1->Replace("facing", "");
			docText1 = docText1->Replace("zias", "");
		}

		docText1 = docText1->Replace("bracket", gcnew String(my_fda.subsystem->bracket->name.c_str()));
		docText1 = docText1->Replace("profile", gcnew String(my_fda.subsystem->profile_first->name.c_str()));
		docText1 = docText1->Replace("weightTwo", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));

		docText1 = docText1->Replace("constH1", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_1")));
		docText1 = docText1->Replace("constH2", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_2")));
		docText1 = docText1->Replace("constB1", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_1")));

		docText1 = docText1->Replace("locationType", gcnew String(my_fda.locationType->name.c_str()));

		docText1 = docText1->Replace("height", Convert::ToString(my_fda.objectHeight));
		if (my_fda.isCityClimate)
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.city->wind_district->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.city->ice_district->name.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.windDistrict->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.iceDistrict->name.c_str()));
		}

		docText1 = docText1->Replace("qzn", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_2")));
		docText1 = docText1->Replace("qzh1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_1")));
		docText1 = docText1->Replace("qzh2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_2")));


		docText1 = docText1->Replace("gammaf1", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_1")));
		docText1 = docText1->Replace("gammaf2", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_2")));
		docText1 = docText1->Replace("sumqz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_1")));
		docText1 = docText1->Replace("sumqz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_2")));
		docText1 = docText1->Replace("qz", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_2")));
		docText1 = docText1->Replace("w0", Convert::ToString(VariableStorageManager::Instance()->getVariable("w_0")));
		docText1 = docText1->Replace("kz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ze")));
		docText1 = docText1->Replace("ksiz", Convert::ToString(VariableStorageManager::Instance()->getVariable("ksi_ze")));

		if (!my_fda.checkAerodynamicFactor)
		{
			docText1 = docText1->Replace("c1", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_1")));
			docText1 = docText1->Replace("c2", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_2")));
		}
		else
		{
			docText1 = docText1->Replace("c1", Convert::ToString(my_fda.c1));
			docText1 = docText1->Replace("c2", Convert::ToString(my_fda.c2));
		}

		docText1 = docText1->Replace("NU", Convert::ToString(VariableStorageManager::Instance()->getVariable("nu")));
		docText1 = docText1->Replace("QynWinterOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_311")));
		docText1 = docText1->Replace("qy1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_311")));
		docText1 = docText1->Replace("gammaf3", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_3")));
		docText1 = docText1->Replace("iceThickness", Convert::ToString(VariableStorageManager::Instance()->getVariable("b_ice")));
		docText1 = docText1->Replace("kz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ice")));
		docText1 = docText1->Replace("mu2", Convert::ToString(VariableStorageManager::Instance()->getVariable("mu_2")));
		docText1 = docText1->Replace("rho", Convert::ToString(VariableStorageManager::Instance()->getVariable("rho")));
		docText1 = docText1->Replace("IZN", Convert::ToString(VariableStorageManager::Instance()->getVariable("I_312")));
		docText1 = docText1->Replace("IZ", Convert::ToString(VariableStorageManager::Instance()->getVariable("i_312")));
		docText1 = docText1->Replace("gammaf4", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_4")));
		docText1 = docText1->Replace("QynSummerOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_321")));
		docText1 = docText1->Replace("qy2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_321")));
		docText1 = docText1->Replace("QynEdge", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_411")));
		docText1 = docText1->Replace("qy3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_411")));
		docText1 = docText1->Replace("output", gcnew String(my_fda.conclusion.c_str()));

		StreamWriter ^ sw = gcnew StreamWriter(docx->MainDocumentPart->GetStream(FileMode::Create));

		sw->Write(docText1);

		sw->Close();
		docx->Close();
	}
	void ReportManager::commonConcreteSlabsReport(const FormDataArgs& my_fda, String ^ namedoc)
	{
		String ^ docText1 = nullptr;

		WordprocessingDocument ^  docx = WordprocessingDocument::Open(namedoc, true);
		StreamReader ^ sr = gcnew StreamReader(docx->MainDocumentPart->GetStream());
		docText1 = sr->ReadToEnd();

		sr->Close();

		docText1 = docText1->Replace("subsystem1", gcnew String(my_fda.subsystem->name.c_str()));
		docText1 = docText1->Replace("nameObject", gcnew String(my_fda.objectName.c_str()));
		docText1 = docText1->Replace("cipher", gcnew String(my_fda.objectCipher.c_str()));
		docText1 = docText1->Replace("responsible", gcnew String(my_fda.objectResponsible.c_str()));

		time_t timer;
		struct tm *tblock;
		timer = time(NULL);
		tblock = localtime(&timer);
		std::string str = std::to_string(tblock->tm_mday);
		str += '/';
		str += std::to_string(tblock->tm_mon + 1);
		str += '/';
		str += std::to_string(tblock->tm_year + 1900);

		docText1 = docText1->Replace("date", gcnew String(str.c_str()));
		if (my_fda.isFacingStandart)
		{
			docText1 = docText1->Replace("facing", gcnew String(my_fda.facing->name.c_str()));
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("zias", gcnew String(my_fda.facing->ziasN.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("facing", "");
			docText1 = docText1->Replace("zias", "");
		}
	
		docText1 = docText1->Replace("bracket", gcnew String(my_fda.subsystem->bracket->name.c_str()));
		docText1 = docText1->Replace("profile1", gcnew String(my_fda.subsystem->profile_first->name.c_str()));
		docText1 = docText1->Replace("weightTwo", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));
		docText1 = docText1->Replace("profile2", gcnew String(my_fda.subsystem->profile_second->name.c_str()));
		docText1 = docText1->Replace("weightThree", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));


		docText1 = docText1->Replace("constH1", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_1")));
		docText1 = docText1->Replace("constH2", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_2")));
		docText1 = docText1->Replace("constH3", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_3")));
		docText1 = docText1->Replace("constB1", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_1")));
		docText1 = docText1->Replace("constB2", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_2")));

		docText1 = docText1->Replace("height", Convert::ToString(my_fda.objectHeight));
		docText1 = docText1->Replace("locationType", gcnew String(my_fda.locationType->name.c_str()));
		if (my_fda.isCityClimate)
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.city->wind_district->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.city->ice_district->name.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.windDistrict->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.iceDistrict->name.c_str()));
		}

		docText1 = docText1->Replace("qzn", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_2")));
		docText1 = docText1->Replace("qzh1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_1")));
		docText1 = docText1->Replace("qzh2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_2")));
		docText1 = docText1->Replace("qzh3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_3")));
		
		docText1 = docText1->Replace("gammaf1", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_1")));
		docText1 = docText1->Replace("gammaf2", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_2")));
		docText1 = docText1->Replace("sumqz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_1")));
		docText1 = docText1->Replace("sumqz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_2")));
		docText1 = docText1->Replace("qz", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_2")));
		docText1 = docText1->Replace("w0", Convert::ToString(VariableStorageManager::Instance()->getVariable("w_0")));
		docText1 = docText1->Replace("kz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ze")));
		docText1 = docText1->Replace("ksiz", Convert::ToString(VariableStorageManager::Instance()->getVariable("ksi_ze")));

		if (!my_fda.checkAerodynamicFactor)
		{
			docText1 = docText1->Replace("c1", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_1")));
			docText1 = docText1->Replace("c2", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_2")));
		}
		else
		{
			docText1 = docText1->Replace("c1", Convert::ToString(my_fda.c1));
			docText1 = docText1->Replace("c2", Convert::ToString(my_fda.c2));
		}

		docText1 = docText1->Replace("NU", Convert::ToString(VariableStorageManager::Instance()->getVariable("nu")));
		docText1 = docText1->Replace("QynWinterOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_311")));
		docText1 = docText1->Replace("qy1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_311")));
		docText1 = docText1->Replace("gammaf3", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_3")));
		docText1 = docText1->Replace("iceThickness", Convert::ToString(VariableStorageManager::Instance()->getVariable("b_ice")));
		docText1 = docText1->Replace("kz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ice")));
		docText1 = docText1->Replace("mu2", Convert::ToString(VariableStorageManager::Instance()->getVariable("mu_2")));
		docText1 = docText1->Replace("rho", Convert::ToString(VariableStorageManager::Instance()->getVariable("rho")));
		docText1 = docText1->Replace("IZN", Convert::ToString(VariableStorageManager::Instance()->getVariable("I_312")));
		docText1 = docText1->Replace("IZ", Convert::ToString(VariableStorageManager::Instance()->getVariable("i_312")));
		docText1 = docText1->Replace("gammaf4", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_4")));
		docText1 = docText1->Replace("QynSummerOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_321")));
		docText1 = docText1->Replace("qy2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_321")));
		docText1 = docText1->Replace("QynEdge", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_411")));
		docText1 = docText1->Replace("qy3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_411")));
		docText1 = docText1->Replace("output", gcnew String(my_fda.conclusion.c_str()));



		StreamWriter ^ sw = gcnew StreamWriter(docx->MainDocumentPart->GetStream(FileMode::Create));

		sw->Write(docText1);

		sw->Close();
		docx->Close();
	}

	void ReportManager::ankerCommonReport(const FormDataArgs& my_fda, String ^ nameDoc, String ^ subsystem)
	{
		String ^ docText2 = nullptr;

		WordprocessingDocument ^  docx1 = WordprocessingDocument::Open(nameDoc, true);
		StreamReader ^ sr1 = gcnew StreamReader(docx1->MainDocumentPart->GetStream());
		docText2 = sr1->ReadToEnd();

		sr1->Close();
		docText2 = docText2->Replace("subsystem2", subsystem);
		if (my_fda.isSubsystemStandart)
		{
			docText2 = docText2->Replace("constX", Convert::ToString(my_fda.subsystem->bracket->x));
			docText2 = docText2->Replace("constB", Convert::ToString(my_fda.subsystem->bracket->b));
			docText2 = docText2->Replace("constC", Convert::ToString(my_fda.subsystem->bracket->c));
		}
		else
		{
			docText2 = docText2->Replace("constX", Convert::ToString(my_fda.bracket->x));
			docText2 = docText2->Replace("constB", Convert::ToString(my_fda.bracket->b));
			docText2 = docText2->Replace("constC", Convert::ToString(my_fda.bracket->c));
		}
		docText2 = docText2->Replace("constE", Convert::ToString(my_fda.facing_radius));
		docText2 = docText2->Replace("S1", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_1")));
		docText2 = docText2->Replace("Pz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_1")));
		docText2 = docText2->Replace("Ny1", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_1")));
		docText2 = docText2->Replace("S2", Convert::ToString(VariableStorageManager::Instance()->getVariable("S_2")));
		String ^ str = Convert::ToString(VariableStorageManager::Instance()->getVariable("S_2"));
		docText2 = docText2->Replace("Pz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_2")));
		docText2 = docText2->Replace("Ny2", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_2")));
		docText2 = docText2->Replace("Pz3", Convert::ToString(VariableStorageManager::Instance()->getVariable("P_3")));
		docText2 = docText2->Replace("Ny3", Convert::ToString(VariableStorageManager::Instance()->getVariable("N_3")));
		docText2 = docText2->Replace("R1k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_1_1"))/1000.f));
		docText2 = docText2->Replace("R2k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_2_1"))/1000.f));
		docText2 = docText2->Replace("R3k", Convert::ToString((VariableStorageManager::Instance()->getVariable("R_3_1"))/1000.f));
		docText2 = docText2->Replace("R3", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_3_1")));
		docText2 = docText2->Replace("R2", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_2_1")));
		docText2 = docText2->Replace("R1", Convert::ToString(VariableStorageManager::Instance()->getVariable("R_1_1")));
		StreamWriter ^ sw1 = gcnew StreamWriter(docx1->MainDocumentPart->GetStream(FileMode::Create));

		sw1->Write(docText2);

		sw1->Close();
		docx1->Close();
	}

	void ReportManager::commonReport(const FormDataArgs& my_fda, String ^ namedoc)
	{
		String ^ docText1 = nullptr;

		WordprocessingDocument ^  docx = WordprocessingDocument::Open(namedoc, true);
		StreamReader ^ sr = gcnew StreamReader(docx->MainDocumentPart->GetStream());
		docText1 = sr->ReadToEnd();

		sr->Close();
		
		docText1 = docText1->Replace("nameObject", gcnew String(my_fda.objectName.c_str()));
		docText1 = docText1->Replace("cipher", gcnew String(my_fda.objectCipher.c_str()));
		docText1 = docText1->Replace("responsible", gcnew String(my_fda.objectResponsible.c_str()));

		time_t timer;
		struct tm *tblock;
		timer = time(NULL);
		tblock = localtime(&timer);
		std::string str = std::to_string(tblock->tm_mday);
		str += '/';
		str += std::to_string(tblock->tm_mon + 1);
		str += '/';
		str += std::to_string(tblock->tm_year + 1900);

		docText1 = docText1->Replace("date", gcnew String(str.c_str()));
		if (my_fda.isFacingStandart)
		{
			docText1 = docText1->Replace("facing", gcnew String(my_fda.facing->name.c_str()));
			docText1 = docText1->Replace("weightOne", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_1")));
			docText1 = docText1->Replace("zias", gcnew String(my_fda.facing->ziasN.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("weightOne", Convert::ToString(my_fda.weight));
			docText1 = docText1->Replace("facing", "");
			docText1 = docText1->Replace("zias", "");
		}

		if (my_fda.isSubsystemStandart)
		{
			docText1 = docText1->Replace("subsystem1", gcnew String(my_fda.subsystem->name.c_str()));
			docText1 = docText1->Replace("bracket", gcnew String(my_fda.subsystem->bracket->name.c_str()));
			docText1 = docText1->Replace("profile", gcnew String(my_fda.subsystem->profile_first->name.c_str()));
			docText1 = docText1->Replace("weightTwo", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));
		}
		else
		{
			docText1 = docText1->Replace("subsystem1", "");
			docText1 = docText1->Replace("bracket", gcnew String(my_fda.bracket->name.c_str()));
			docText1 = docText1->Replace("profile", gcnew String(my_fda.profile->name.c_str()));
			docText1 = docText1->Replace("weightTwo", Convert::ToString(VariableStorageManager::Instance()->getVariable("weight_2")));
		}

		docText1 = docText1->Replace("constH1", Convert::ToString(VariableStorageManager::Instance()->getVariable("H_1")));
		docText1 = docText1->Replace("constB1", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_1")));
		docText1 = docText1->Replace("constB2", Convert::ToString(VariableStorageManager::Instance()->getVariable("B_2")));
		docText1 = docText1->Replace("height", Convert::ToString(my_fda.objectHeight));
		docText1 = docText1->Replace("locationType", gcnew String(my_fda.locationType->name.c_str()));

		if (my_fda.isCityClimate)
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.city->wind_district->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.city->ice_district->name.c_str()));
		}
		else
		{
			docText1 = docText1->Replace("windDistrict", gcnew String(my_fda.windDistrict->name.c_str()));
			docText1 = docText1->Replace("iceDistrict", gcnew String(my_fda.iceDistrict->name.c_str()));
		}

		docText1 = docText1->Replace("qzn", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_2")));
		docText1 = docText1->Replace("qzh", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_H_1")));
		docText1 = docText1->Replace("qz", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_2")));
		docText1 = docText1->Replace("gammaf1", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_1")));
		docText1 = docText1->Replace("gammaf2", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_2")));
		docText1 = docText1->Replace("sumQz", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_sum_1")));
		docText1 = docText1->Replace("w0", Convert::ToString(VariableStorageManager::Instance()->getVariable("w_0")));
		docText1 = docText1->Replace("kz1", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ze")));
		docText1 = docText1->Replace("ksiz", Convert::ToString(VariableStorageManager::Instance()->getVariable("ksi_ze")));
		if (!my_fda.checkAerodynamicFactor)
		{
			docText1 = docText1->Replace("c1", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_1")));
			docText1 = docText1->Replace("c2", Convert::ToString(VariableStorageManager::Instance()->getVariable("c_2")));
		}
		else
		{
			docText1 = docText1->Replace("c1", Convert::ToString(my_fda.c1));
			docText1 = docText1->Replace("c2", Convert::ToString(my_fda.c2));
		}

		docText1 = docText1->Replace("NU", Convert::ToString(VariableStorageManager::Instance()->getVariable("nu")));
		docText1 = docText1->Replace("QynWinterOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_311")));
		docText1 = docText1->Replace("qy1", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_311")));
		docText1 = docText1->Replace("gammaf3", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_3")));
		docText1 = docText1->Replace("iceThickness", Convert::ToString(VariableStorageManager::Instance()->getVariable("b_ice")));
		docText1 = docText1->Replace("kz2", Convert::ToString(VariableStorageManager::Instance()->getVariable("k_ice")));
		docText1 = docText1->Replace("mu2", Convert::ToString(VariableStorageManager::Instance()->getVariable("mu_2")));
		docText1 = docText1->Replace("rho", Convert::ToString(VariableStorageManager::Instance()->getVariable("rho")));
		docText1 = docText1->Replace("IZN", Convert::ToString(VariableStorageManager::Instance()->getVariable("I_312")));
		docText1 = docText1->Replace("IZ", Convert::ToString(VariableStorageManager::Instance()->getVariable("i_312")));
		docText1 = docText1->Replace("gammaf4", Convert::ToString(VariableStorageManager::Instance()->getVariable("gamma_f_4")));
		docText1 = docText1->Replace("QynSummerOrdinary", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_321")));
		docText1 = docText1->Replace("qy2", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_321")));
		docText1 = docText1->Replace("QynEdge", Convert::ToString(VariableStorageManager::Instance()->getVariable("Q_411")));
		docText1 = docText1->Replace("qy3", Convert::ToString(VariableStorageManager::Instance()->getVariable("q_411")));
		docText1 = docText1->Replace("output", gcnew String(my_fda.conclusion.c_str()));



		StreamWriter ^ sw = gcnew StreamWriter(docx->MainDocumentPart->GetStream(FileMode::Create));

		sw->Write(docText1);
	
		sw->Close();
		docx->Close();
	}
} // zias 