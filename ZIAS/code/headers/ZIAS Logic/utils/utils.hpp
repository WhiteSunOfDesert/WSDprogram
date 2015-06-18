#pragma once

namespace zias {
	namespace utils {
	
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

		// lexical_cast<>
		template <typename T>
		inline T lexical_cast(const char*);

		template <typename T>
		inline T lexical_cast(const std::string& my_str) { 
			return lexical_cast<T>(my_str.c_str());
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

		inline std::string toStdString(System::String^ my_str){
			using namespace System::Runtime::InteropServices;
			char* char_str = (char*)(Marshal::StringToHGlobalAnsi(my_str)).ToPointer();
			std::string result = static_cast<std::string>(char_str);
			Marshal::FreeHGlobal(System::IntPtr((void*)char_str));
			return result;
		}

		inline float toFloat(System::String^ my_str){
			return (float)std::atof(toStdString(my_str).c_str());
		}

		inline int toInt(System::String^ my_str){
			return std::atoi(toStdString(my_str).c_str());
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