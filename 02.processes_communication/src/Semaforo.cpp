#include "Semaforo.h"
#include "iostream"

// Método constructor de la clase.
Semaforo::Semaforo(int valorInicial) {
   // Crear semáforo con semget
  
  if(this->id = semget(KEY, 1, IPC_CREAT | 0660)) {
  } else {
    std::cout << "Error creating semaphore." << std::endl;
  }
  // Inicializar semáforo
  union semun my_semun;
  my_semun.val = valorInicial;
  semctl(this->id, /*SemNum*/0, SETVAL, my_semun);
}

// Método encargado de eliminar el semáforo.
void Semaforo::destructor() {
  // Eliminar semáforo con semctl
  int error = semctl(this->id, 0, IPC_RMID);
  std::cout << "Destroy: " << error <<std::endl;
}

// Método encargado de poner el semáforo en verde.
void Semaforo::signal() {
  struct sembuf semBuffer;
  semBuffer.sem_num = 0;
  semBuffer.sem_op = 1;
  semBuffer.sem_flg = SEM_UNDO;
  // Utilizar sembuf y semop
  semop(this->id, &semBuffer, 1);
}

// Método encargado de esperar que el semáforo esté en verde.
void Semaforo::wait() {
  struct sembuf semBuffer;
  semBuffer.sem_num = 0;
  semBuffer.sem_op = -1;
  semBuffer.sem_flg = SEM_UNDO;
  // Utilizar sembuf y semop
  semop(this->id, &semBuffer, 1);
}
