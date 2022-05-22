// Author: Emmanuel D. Solis.

#include "Controller.h"
#include "Buzon.h"
#include "Semaforo.h"

Controller::Controller(std::string my_reserved_words_file) {
  file_path = my_reserved_words_file;
  for(int i=0; i<total_of_reserved_words; i++) {
    final_statics[i] = 0;
  }
  load_word_list(file_path);
  run();
  create_processes();
  print_statics();
  save_statics_on_file();
}

Controller::~Controller() {
  shared_mailbox.destructor();
  my_semaphore.destructor();
}

void Controller::load_word_list(std::string my_file_path) {
  // Open the stream.
  std::cout << "loading reserved words list..." << std::endl;
  std::fstream words_file;
  words_file.open(file_path, std::fstream::in);
  if(words_file.is_open()) {
    uint16_t current_counter = 0;
    getline(words_file, file_type);
    // Reads the words.
    while (std::getline(words_file, reserved_words[current_counter])) {
      ++current_counter;
    }
    words_file.close();  // Close the stream.
    total_of_reserved_words = current_counter;  // Saves the data.
    std::cout << "file with reserved word loaded successfully..." << std::endl;
  } else {
    std::cerr<< "Error opening file: " << file_path << std::endl;
  }
}

void Controller::create_processes() {
  /*for (int i=0; i<number_of_files; i++) {
    if(fork() == 0) {
      run_parent_process();
      print_statics();
      save_statics_on_file();
    } else {
      run_child_process(files_names[i]);
    }
  }*/

  // Code adapted from: https://gist.github.com/dgacitua/64ff00e90d5e21f9c3f7 
  static const int PROC = number_of_files;		// PROC fija la cantidad de procesos a crear

  pid_t pid;

	int status, procNum;			// procNum almacena el número del proceso

	for (procNum=0; procNum<PROC; procNum++) {
		pid = fork();	 // Creates a new process.
		
		if (pid==0) {   // If it was good created then goes out.
			break;
		} else if (pid==-1) {	  // Case of error abort.
			std::cerr << "ERROR creating fork()" << std::endl;
			exit(1);
			break;
		}
	}

  if (pid==0) {   // Child subroutine.
		std::cout << "soy el proceso " << getpid() << std::endl;
    run_child_process(files_names[current_assing]);
    current_assing++;
		//exit(0);
	} else {    // Parent subroutine.
    pid_t wpid;
    run_parent_process();
		for (int i=0; i<number_of_files; i++) {		// esperamos a que todos los hijos terminen (código mejorado)
      if ((wpid = wait(NULL)) >= 0) {
        std::cout << "Proceso " << wpid << " terminado" << std::endl;
      }
    }
	}
}

void Controller::run_child_process(std::string my_file) {
  Words_counter *my_counter = new Words_counter(reserved_words, total_of_reserved_words);
  my_counter->set_file_to_analize(my_file);
  my_counter->count_words();
  my_semaphore.wait();
  for (int i=0; i<total_of_reserved_words; i++) {
    my_counter->send_info_to_mailbox();
  }
  my_semaphore.signal();
}

void Controller::run_parent_process() {
  for (int i=0; i<total_of_reserved_words; i++) {
    char receive_message[50];
    for (int i=0; i<sizeof(receive_message); i++) {
      receive_message[i] = '\0';
    }
    unsigned repeticiones;
    shared_mailbox.recibir(receive_message, repeticiones, sizeof(receive_message), 1);
    final_statics[i] += (int) repeticiones;
    /*if(repeticiones != 0) {
      std::cout<<"Cantidad de repeticiones: "<<final_statics[i]<<std::endl;
      std::cout<<"Mensaje recibido: ";
      for (int i=0; receive_message[i] != '\0' ; i++) {
        std::cout << receive_message[i];
      }
      std::cout<<std::endl;
    }*/
  }
}

void Controller::run() {
  std::cout << "How many files do you want to analize?" << std::endl;
  std::cin >> number_of_files;
  for(int iterator = 0; iterator < number_of_files; iterator++) {
    std::cout << "Enter path of file " << iterator+1 << std::endl;
    std::cin >> files_names[iterator];
    std::cout << "file to analize: " << files_names[iterator] << std::endl;
  }
}

std::string Controller::to_string_statics() {
  std::string message = "These are the final general statics:\n\n Files:\n";
  for(int i=0; i<number_of_files; i++) {
    message += files_names[i];
    message += "\n";
  }
  message += "\nStatics are:\n";
  for (int i = 0; i < total_of_reserved_words; i++) {
    message += reserved_words[i];
    message += ": ";
    message += std::to_string(final_statics[i]);
    message += "\n";
  }
  return message;
}

void Controller::print_statics() {
  std::cout << to_string_statics() << std::endl;
}

void Controller::save_statics_on_file() {
  std::fstream my_file;
	my_file.open("results.txt", std::ios::out);
	if (!my_file) {
		std::cerr << "File could not be created." << std::endl;
	} else {
		std::cout << "File created successfully..." << std::endl;
    my_file << to_string_statics();
		my_file.close(); 
	}
}