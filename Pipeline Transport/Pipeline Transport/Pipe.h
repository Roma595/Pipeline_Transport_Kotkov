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

Pipe add_Pipe();
void view_all_pipes(std::vector <Pipe> pipes);
void push_pipe_in_file(std::vector <Pipe>& pipes);

#endif // !Pipe_h
