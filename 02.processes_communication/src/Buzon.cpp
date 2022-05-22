#include "Buzon.h"
#include <iostream>
// Constructor de la clase.
Buzon::Buzon() {
  // Crear el Buzón con msgget
  this->id = msgget((key_t)KEY2, IPC_CREAT | 0660);
}

// Método encargado de eliminar el buzón.
void Buzon::destructor() {
  // Eliminar el buzón con msgctl
  int error = msgctl(this->id, IPC_RMID, NULL);
  if(error==0) {
    std::cout << "Destruido exitosamente." <<std::endl;
  } else {
    //std::cout << "No se pudo destruir." <<std::endl;
  }
}

// Método encargado de enviar un mensaje al buzón.
void Buzon::enviar(char* mensaje, unsigned repeticiones, long mid) {
  // Inicializar el contenido del mensaje con msgbuf
  strcpy(msgBuffer.mtext, mensaje);
  msgBuffer.mtype = mid;
  msgBuffer.repeticiones = repeticiones;

  // Enviar el mensaje con msgsnd
  msgsnd(this->id, &msgBuffer, sizeof(msgBuffer) - sizeof(msgBuffer.mtype), 0);
}

// Método encargado de recibir un mensaje.
void Buzon::recibir(char* mensaje, unsigned& repeticiones, int len, long mid) {
  // Recibir el mensaje con msgrcv
  msgrcv(this->id, &msgBuffer, /*Len*/sizeof(msgBuffer) - sizeof(msgBuffer.mtype), mid, 0);

  // Sacar el mensaje del buzón. Sugerencia: strcpy
  strcpy(mensaje, msgBuffer.mtext);
  repeticiones = msgBuffer.repeticiones;
}
