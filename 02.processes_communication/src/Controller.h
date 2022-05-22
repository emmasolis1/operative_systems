// Author: Emmanuel D. Solis.

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <array>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <sys/types.h>
#include <sys/wait.h>

#include "Words_counter.h"

#define INITIAL_MAX_DOCUMENTS 8
#define INITIAL_AMOUNT_RESERVED_WORDS 128

class Controller {
private:
  std::array<std::string, INITIAL_MAX_DOCUMENTS> files_names;
  std::array<std::string, INITIAL_AMOUNT_RESERVED_WORDS> reserved_words;
  std::array<int, INITIAL_AMOUNT_RESERVED_WORDS> final_statics;
  std::string file_type = "Java";
  std::string file_path = "";
  int total_of_reserved_words = 0;
  int current_assing = 0;
  int words_counter = 0;
  int number_of_files = 0;
  Buzon shared_mailbox;
  Semaforo my_semaphore = Semaforo(1);
  std::string to_string_statics();
  void run_child_process(std::string my_file);
  void run_parent_process();
public:
  Controller(std::string my_reserved_words_file); 
  ~Controller();
  void load_word_list(std::string file_path);
  void create_processes();
  void save_statics_on_file(/* args */);  // TODO: save statics on file
  void print_statics(); 
  void run();
};

#endif // CONTROLLER_H
