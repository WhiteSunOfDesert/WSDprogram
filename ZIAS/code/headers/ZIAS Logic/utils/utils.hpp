/*	utils.hpp
*
*	Самописная библиотека утилит, которые могут использоваться в проекте ZIAS
*
*	бла-бла-бла
*	бла-бла-бла
*
*	Copyright(c) 20.06.2015 "НАЗВАНИЕ НАШЕЙ СУПЕРФИРМЫ"
*	All rights reserved.
*/

#pragma once

namespace zias {
	namespace utils {
		
		/// сравнение двух строковых констант
		/// true - при полном равенстве, false - false 
		inline bool equals(const char* my_str_1, const char* my_str_2) {
			if (my_str_1 == nullptr || my_str_2 == nullptr) {
				return false;
			}
			while (*my_str_1 == *my_str_2) {
				if (*my_str_1 == '\0') {
					return true;
				}
				my_str_1++; 
				my_str_2++;
			}
			return false;
		}
		
		/// lexical_cast<>
		/// приведение к лексематичному виду стоковых переменных
		template <typename T>
		inline T lexical_cast(const char*);

		template <typename T>
		inline T lexical_cast(const std::string& my_str) { 
			return lexical_cast<T>(my_str.c_str());
		}

		template <>
		inline std::wstring lexical_cast(const char* my_str) {
			size_t size = MultiByteToWideChar(CP_UTF8, 0, my_str, -1, NULL, 0);

			if (!size) {
				return L"";
			}
				
			std::vector<wchar_t> w_vector(size);
			MultiByteToWideChar(CP_UTF8, 0, my_str, -1, &w_vector[0], size);

			wchar_t* w_char = new wchar_t[size + 1];
			for (size_t i = 0; i < size; i++) {
				w_char[i] = w_vector.at(i);
			}
			w_char[size] = '\0';

			return w_char;
		}

		template <>
		inline std::string lexical_cast(const std::string& my_str) {
			return my_str;
		}

		template <>
		inline std::string lexical_cast(const char* my_str)	{
			return my_str;
		}

		template <>
		inline float lexical_cast(const char* my_str) {
			if (my_str != nullptr) {
				return (float)std::atof(my_str);
			}
			return 0.f;
		}

		template <>
		inline bool lexical_cast(const char* my_str) {
			if (my_str != nullptr) {
				return (bool)std::atoi(my_str);
			}
			return false;
		}

		template <>
		inline short lexical_cast(const char* my_str) {
			if (my_str != nullptr) {
				return (short)std::atoi(my_str);
			}
			return 0;
		}

		template <>
		inline int lexical_cast(const char* my_str) {
			if (my_str != nullptr) {
				return std::atoi(my_str);
			}
			return 0;
		}
		
		/// преобразование String^ к std::string с сохранением локали
		inline std::string toStdString(System::String^ my_str){
			using namespace System::Runtime::InteropServices;
			char* char_str = (char*)(Marshal::StringToHGlobalAnsi(my_str)).ToPointer();
			std::string result = static_cast<std::string>(char_str);
			Marshal::FreeHGlobal(System::IntPtr((void*)char_str));
			return result;
		}
		
		/// преобразование String^ к std::wstring с сохранением локали
		inline std::wstring toStdWString(System::String^ my_str, std::locale my_loc = std::locale("russian")){
			std::string stemp = toStdString(my_str);
			std::wstring result(stemp.length(), 0);
			
			std::wstring::iterator w_iter = result.begin();
			for (std::string::const_iterator s_iter = stemp.begin(); s_iter != stemp.end(); ++s_iter, ++w_iter) {
				*w_iter = std::use_facet<std::ctype<wchar_t>>(my_loc).widen(*s_iter);
			}

			return result;
		}
		
		/// преобразование std::wstring к std::string с сохранением локали
		inline std::string toStdString(std::wstring my_str, std::locale my_loc = std::locale("russian")){
			std::string result(my_str.length(), 0);

			std::string::iterator s_iter = result.begin();
			for (std::wstring::const_iterator w_iter = my_str.begin(); w_iter != my_str.end(); ++s_iter, ++w_iter) {
				*s_iter = std::use_facet<std::ctype<wchar_t>>(my_loc).narrow(*w_iter);
			}

			return result;
		}
		
		/// преобразование String^ к float
		/// в качестве плавающей точки может выступать как '.', так и ','
		inline float toFloat(System::String^ my_str){
			float result = 0.f;
			std::string s_number = toStdString(my_str);
			
			int digit[2] = {0, 0};
			for (auto iter = s_number.begin(); iter != s_number.end(); ++iter) {
				if (digit[1] == 0) {
					digit[0]++;
				} else {
					digit[1]++;
				}
				if (*iter == ',' || *iter == '.') {
					digit[1]++;
					digit[0]--;
				}
			}
			digit[1]--;
			
			int temp = digit[1] + 1;
			for (auto iter = s_number.begin(); iter != s_number.end(); ++iter) {
				if (*iter == ',' || *iter == '.') {
					continue;
				}
	
				result += (*iter - 48.f) * std::pow(10.f, digit[0] ? --digit[0] : digit[1]-- - temp);
			}

			return result;
		}
		
		/// преобразование String^ к int
		inline int toInt(System::String^ my_str) {
			return std::atoi(toStdString(my_str).c_str());
		}
		
		/// округление переменной my_number типа float c заданной точностью my_precision
		inline float doRound(const float& my_number, const unsigned& my_precision) {
			unsigned factor = 1;
			for (unsigned i = 0; i < my_precision; i++) {
				factor *= 10;
			}

			if (my_number > 0.f) {
				return floor(my_number * factor + 0.5f) / factor;
			} else {
				return ceil(my_number * factor - 0.5f) / factor;
			}

			return 0.f;
		}

		// по двум входящим векторам и значению, выдает интерполированное значение...
		template <typename T1, typename T2>
		T2 Interpolate(std::vector<T1> my_vector_1, std::vector<T2> my_vector_2, T1 my_value_1) {
			if (my_vector_1.size() == my_vector_2.size()) {
				std::cerr << "\nvectors size mismatch\n";
			}

			int i = 0;
			for ( ; i < static_cast<int>(my_vector_1.size()); i++) {
				if (my_vector_1[i] > my_value_1) {
					break;
				}
			}

			if (i == 0)	{
				return my_vector_2[0];
			} else if (i == static_cast<int>(my_vector_1.size())) {
				return my_vector_2[my_vector_2.size() - 1];
			} else {
				T1 value_11 = my_vector_1[i - 1];
				T1 value_12 = my_vector_1[i];
				T2 value_21 = my_vector_2[i - 1];
				T2 value_22 = my_vector_2[i];

				T2 value = (T2)(((my_value_1 - value_11) / (value_12 - value_11)) * (value_22 - value_21)) + value_21;

				return value;
			}	
		}
	}	// utils
} // zias