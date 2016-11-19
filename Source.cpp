#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <unordered_map>

enum struct execute_type {
	move_next,
	move_previous,
	pointer_increment,
	pointer_decrement,
	input_from_stdin,
	output_to_stdout,
	loop_start,
	loop_end,
	unknown
};

//This is so chikarawaza
//TODO:
//		This method can exchange the using unorderd_map
//		If I find the way to create hash from std::pair<std::string, std::string> like boost.hash_combine without boost,
//		I will try to refine.
//
execute_type get_execute_type(const std::string& first_token, const std::string& second_token) {
	if (first_token == "ちゃま。" && second_token == "ちゃま？") {
		return execute_type::move_next;
	}
	else if (first_token == "ちゃま？" && second_token == "ちゃま。") {
		return execute_type::move_previous;
	}
	else if (first_token == "ちゃま。" && second_token == "ちゃま。") {
		return execute_type::pointer_increment;
	}
	else if (first_token == "ちゃま！" && second_token == "ちゃま！") {
		return execute_type::pointer_decrement;
	}
	else if (first_token == "ちゃま。" && second_token == "ちゃま！") {
		return execute_type::input_from_stdin;
	}
	else if (first_token == "ちゃま！" && second_token == "ちゃま。") {
		return execute_type::output_to_stdout;
	}
	else if (first_token == "ちゃま！" && second_token == "ちゃま？") {
		return execute_type::loop_start;
	}
	else if (first_token == "ちゃま？" && second_token == "ちゃま！") {
		return execute_type::loop_end;
	}

	return execute_type::unknown;
}

constexpr std::size_t MAX_DATA_SIZE = 3000;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "[usage] chama.exe filename.chama" << std::endl;
		return -1;
	}

	std::string filename = argv[1];
	std::cout << "loading file" <<  filename << std::endl;

	//stacks code memorys
	std::unique_ptr<unsigned short[]> data(new unsigned short[MAX_DATA_SIZE]);
	for (int i = 0; i < MAX_DATA_SIZE; ++i) {
		data[i] = 0;
	}
	//current memory pointer
	std::size_t memory_pointer = 0;

	//row data
	//(data.size() might be even number
	//if not, return syntax error 
	std::vector<std::string> row_data;

	//converted executable data
	std::vector<execute_type> execute_data;
	
	//read input file
	std::ifstream input_file;
	input_file.open(filename, std::ios::in);

	std::string line;
	//read file and anlyzing, to container
	while (!input_file.eof()) {
		//read by line
		std::getline(input_file, line);
		
		//read by delimiter from line to line-end
		const char delimiter = ' ';
		std::string separated_string_buffer;
		std::istringstream line_separator(line);

		while (std::getline(line_separator, separated_string_buffer, delimiter)) {
			//std::cout << "[" << separated_string_buffer << "]" << std::endl;
			row_data.push_back(separated_string_buffer);
		}
	}
	//analyze ended

	//row data size check
	if (row_data.size() % 2 != 0) {
		std::cout << "syntax error!!" << std::endl;
		return -1;
	}

	//convert to executable data
	for (auto iter = row_data.begin(); iter != row_data.end(); ++iter, ++iter) {
		const auto& first_token = *iter;
		const auto& second_token = *(iter + 1);

		execute_data.push_back(get_execute_type(first_token, second_token));
	}

	//execute
	auto execute_data_iter = execute_data.begin();
	while (execute_data_iter != execute_data.end()) {
		switch (*execute_data_iter) {
		case execute_type::move_next:
			++memory_pointer;
			break;
		case execute_type::move_previous:
			--memory_pointer;
			break;
		case execute_type::pointer_increment:
			data[memory_pointer]++;
			break;
		case execute_type::pointer_decrement:
			data[memory_pointer]--;
			break;
		case execute_type::input_from_stdin:
			data[memory_pointer] = std::getchar();
			break;
		case execute_type::output_to_stdout:
			std::putchar(data[memory_pointer]);
			break;
		case execute_type::loop_start:
			if (data[memory_pointer] == 0) {
				//check for loop_end
				//check count of loop_start appear
				int appear_count = 0;
				while (true) {
					++execute_data_iter;
					if (*execute_data_iter == execute_type::loop_start) {
						++appear_count;
					}
					//if appear count is not 0
					//ignore execute_type loopend
					if (*execute_data_iter == execute_type::loop_end) {
						if (appear_count != 0) {
							--appear_count;
						}
						else {
							break;
						}
					}
				}
			}
			break;
		case execute_type::loop_end:
			//check for loop start
			//check count of loop_end appear
		{
			int appear_count = 0;
			while (true) {
				--execute_data_iter;
				if (*execute_data_iter == execute_type::loop_end) {
					++appear_count;
				}
				//if appear count is not 0
				//ignore exeucte_type loopstart
				if (*execute_data_iter == execute_type::loop_start) {
					if (appear_count != 0) {
						--appear_count;
					}
					else {
						--execute_data_iter;
						break;
					}
				}
			}
		}
		break;
		default:
			break;
		}

		++execute_data_iter;
	}

	std::cout << std::endl;
	
	return 0;
}