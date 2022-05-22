#include "./Words_counter.h"

Words_counter::Words_counter(std::array<std::string, INITIAL_AMOUNT_RESERVED_WORDS> words, int real_amout_words) {
  // Set initial data.
  reserved_words = words;
  amount_reserved_words = real_amout_words;
  for (int i = 0; i < amount_reserved_words; i++) {  // The statics array is all set to 0.
    statics[i] = 0;
  }
}

Words_counter::~Words_counter() {
  
}

void Words_counter::set_file_to_analize(std::string my_file_path){file_path = my_file_path;}

int Words_counter::hash(std::string word) {
  int current_position = 0;
  while(word.compare(reserved_words[current_position]) != 0 && current_position < reserved_words.size()) {
    ++current_position;
  }
  return current_position;
}

void Words_counter::count_words() {
  // Open the stream.
  //std::cout << "loading file to analize..." << std::endl;
  //std::cout << "reserved words are: " << amount_reserved_words << std::endl;
  std::fstream words_file;
  words_file.open(file_path, std::fstream::in);
  if(words_file.is_open()) {
    // Read the lines, this is the whole analysis.
    std::string temp_line;
    std::cout << "analizing file..." << std::endl;
    while (std::getline(words_file, temp_line)) {
      analize_line(temp_line);  // Update the statics based on this line.
    }
    //print_statics();
    words_file.close();  // Close the stream.
  } else {
    std::cerr<< "Error analizing file: " << file_path << std::endl;
  }
}

void Words_counter::analize_line(std::string my_line) {
  // Counts including words inside other words.
  if (my_line.size() > 4) {  // Otherwise is too small to have a reserved word.
    for (int iterator = 0; iterator < amount_reserved_words; iterator++) {
      std::string match_word = reserved_words[iterator];
      int auxiliar;
      int counter = 0;
      int my_line_length = my_line.size();
      int word_length = match_word.size();
      for (int i=0; i <= my_line_length; i++) {
        for (auxiliar = 0; auxiliar < word_length; auxiliar++) {
          if(my_line[i + auxiliar] != match_word[auxiliar]) {
            break;
          }
        }
        if(auxiliar == word_length) {
          counter++;
          statics[hash(reserved_words[iterator])]++;  // Search in what position should be increase.
        }
      }
    }
  }
}

void Words_counter::print_statics() {
  for (int i=0; i<amount_reserved_words; i++) {
    std::cout << reserved_words[i] << ": " << statics[i] << std::endl;
  }
}

int Words_counter::send_info_to_mailbox() {
  //std::cout << "sending data to Controller..." << std::endl;
  char *message = strdup(reserved_words[current_sender].c_str());
  shared_mailbox.enviar(message, statics[current_sender], 1);
  current_sender++;
}
