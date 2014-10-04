#include "EventLogger.h"

using namespace std;


string EventLogger::levelSring(int level){
	switch(level){
	case DEBUG: return "DEBUG"; break;
	case WARNING: return "WARNING"; break;
	case LOG_ERROR:	return "ERROR"; break;
	default: return "UNKNOW"; break;
	}
}
string EventLogger::pathArchivo = "Log.txt";


	void EventLogger::InicializarArchivo(){
	fstream archivo;
	archivo.open(pathArchivo.c_str(), ios::out | ios::app);
	Append("------------------------------------------------------");
	AgregarEvento("Comienza Nueva Ejecucion");
	archivo.flush();
	archivo.close();
}
void EventLogger::RecrearArchivo(){
	fstream archivo;
	archivo.open(pathArchivo.c_str(), ios::out | ios::trunc);
	Append("------------------------------------------------------");
	AgregarEvento("Comienza Nueva Ejecucion");
	archivo.flush();
	archivo.close();
}
void EventLogger::Append(string msg){
	fstream archivo;
	archivo.open(pathArchivo.c_str(), ios::out | ios::app);
		archivo << msg << endl;
		archivo.flush();
		archivo.close();
}
void EventLogger::AgregarEvento(string msgEvento,int prioridad){
	if (prioridad < LOGLEVEL)
		return;
	try{
		string msgAux;
		string timestamp; 
		
		//Fecha y Hora
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
	
		//Armo mensaje de manera amigable	
		timestamp = asctime(timeinfo);
		timestamp = timestamp.substr(0, timestamp.length() -1) ;
		msgAux.append(timestamp);
		msgAux.append(" - " );
		msgAux.append(EventLogger::levelSring(prioridad));
		msgAux.append(" --> " );
		msgAux.append(msgEvento);
		
		//Append
		Append(msgAux);
	}
	catch( exception e) {
	}
}

void EventLogger::AgregarEvento(const char * filename, int line, string msgEvento,int prioridad){
	string msg = string(filename) + ":" + to_string(long long(line)) + " " + msgEvento;
	EventLogger::AgregarEvento(msg,prioridad);
}

void EventLogger::AgregarEvento(string msgEvento){
	EventLogger::AgregarEvento(msgEvento,1);
}


string EventLogger::itos(int i){
	ostringstream convert;
	convert << i;
	return convert.str();
}


