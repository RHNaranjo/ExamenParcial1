#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

// Para que los hilos no escriban en desorden
std::mutex file_mutex;

void writeToFile(const std::string& nombre, const std::string& mensaje, int threadID){
    //Bloquear el mutex para que no pueda escribir ningún otro
    std::lock_guard<std::mutex> bloquear(file_mutex);
    
    //Abrir el texto en modo append
    std::ofstream archivo(nombre, std::ios::app);
    
    //Verificar
    if(archivo.is_open()){
        //escribir
        archivo << "Hilo: " << threadID << ": " << mensaje << std::endl;
        
        //Cerrar el archivo
        archivo.close();
    }
}

int main(){
    //archivo de salida
    const std::string archivoSalida = "output.txt";
    
    //Limpiar el archivo si existía antes (trunc)
    std::ofstream archivo(archivoSalida, std::ios::trunc);
    archivo.close();
    
    //Vector de los hilos
    std::vector<std::thread> threads;
    
    //Crear los cinco hilos
    threads.push_back(std::thread(writeToFile, archivoSalida, "Texto hilo 1", 1));
    threads.push_back(std::thread(writeToFile, archivoSalida, "Me gustan las pizzas", 2));
    threads.push_back(std::thread(writeToFile, archivoSalida, "Tengo hambre", 3));
    threads.push_back(std::thread(writeToFile, archivoSalida, "El Señor de los Anillos es el mejor libro de la segunda mitad del siglo XX y quien opine lo contrario me cae mal JAJAJA", 4));
    threads.push_back(std::thread(writeToFile, archivoSalida, "Palabras palabras palabras", 5));
    
    //Llamar .join() por cada hilo una vez que hayan terminado
    for(auto& thread: threads)
        thread.join();
    
    std::cout << "Se terminó la escritua en " << archivoSalida << std::endl;
}