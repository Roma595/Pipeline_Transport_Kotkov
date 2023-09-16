#ifndef Pipe_h
#define Pipe_h

#include <vector>

struct Pipe
{	

	std::string name;
	double length;
	int diameter;
	bool in_repair;

	Pipe();
	Pipe(std::string name_p, double length, int diameter, bool in_repair);
};


void add_Pipe();
void save_Pipes(std::vector<Pipe> pipes);
void read_Pipes();

#endif // !Pipe_h
