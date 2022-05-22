// Author: Emmanuel D. Solis.

#ifndef WORDS_COUNTER_H
#define WORDS_COUNTER_H

#include <array>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <list>
#include "Buzon.h"
#include "Semaforo.h"

#define INITIAL_AMOUNT_RESERVED_WORDS 128

class Words_counter {
private:
  std::string file_path;
  std::array<std::string, INITIAL_AMOUNT_RESERVED_WORDS> reserved_words;
  int amount_reserved_words = 0;
  std::array<unsigned, INITIAL_AMOUNT_RESERVED_WORDS> statics;
  Buzon shared_mailbox;
  int current_sender = 0;
  /**
   * @brief Takes one line and finds all the words there an it apparences.
   * 
   * @param my_line the line to be analize.
   */
  void analize_line(std::string my_line);
  void print_statics();
public:
  Words_counter(std::array<std::string, INITIAL_AMOUNT_RESERVED_WORDS> words, int real_amout_words);
  ~Words_counter();
  void set_file_to_analize(std::string my_file_path);
  int send_info_to_mailbox();
  void count_words();
  int hash(std::string word);
};

#endif  // WORDS_COUNTER_H
