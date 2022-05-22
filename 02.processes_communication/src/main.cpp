// INTEGRANTES: Emmanuel D. Solis y Gilbert Marquez.

#include <string>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/types.h>

#include "Buzon.h"
#include "Controller.h"
#include "Semaforo.h"

int test_buzon();
int test_semaphore();

int main(void) {
  /*std::cout << "........Testing buzon........" << std::endl;
  int error = test_buzon();

  std::cout << "........Testing Semaphore........" << std::endl;
  int error2 = test_semaphore();*/

  std::string file_path = "./Java_reserved_words.txt";
  Controller *my_controller = new Controller(file_path);
  my_controller->~Controller();

  return 0;
}

int test_buzon(){
  int status = 0;
  int pid =  fork();
  Buzon my_buzon;

  
  if(pid == 0) { // Working on child.
    char receive_message[50];
    for (int i=0; i<sizeof(receive_message); i++) {
      receive_message[i] = '\0';
    }
    unsigned repeticiones = 0;
    std::cout<<"Recibiendo mensaje..."<<std::endl;

    my_buzon.recibir(receive_message, repeticiones, sizeof(receive_message), /*Same as the one that send uses.*/1);
    std::cout<<"Cantidad de repeticiones: "<<repeticiones<<std::endl;
    std::cout<<"Mensaje recibido: ";
    for (int i=0; i<sizeof(receive_message); i++) {
      std::cout << receive_message[i];
    }
    std::cout<<""<<std::endl;
    std::cout<<"RECIBIDO EXITOSO."<<std::endl;

    my_buzon.destructor();
  } else {
    if(pid < 0) {std::cout << "Error creating new proccess."<<std::endl;} else { // Working on parent.
      char* message = (char*)"Gilbert y Emmanuel.";
      std::cout<<"Enviando mensaje..."<<std::endl;
      my_buzon.enviar(message, /*Veces que se repite palabra*/ 80, /*Same as the one that receive uses.*/1);

      std::cout<<"ENVIO EXITOSO."<<std::endl;
    }
  }
  return status;
}

int test_semaphore() {
  Semaforo my_semaphore = Semaforo(0);
  
  int pid = fork();
  if(pid == 0) { // Working on child.
    my_semaphore.signal();
    std::cout << "El hijo esta escribiendo." << std::endl;
  } else {
    if(pid < 0) {std::cout << "Error creating new proccess."<<std::endl;} else { // Working on parent.
      my_semaphore.wait();
      std::cout << "El padre esta escribiendo." << std::endl; 
      my_semaphore.destructor();
    }
  }
  return 0;
}