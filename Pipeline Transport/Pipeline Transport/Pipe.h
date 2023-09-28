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
};

Pipe add_Pipe();
void view_all_pipes(Pipe pipe);
void push_pipe_in_file(Pipe pipe);
void load_all_pipes(Pipe& pipe);
void edit_pipe(Pipe& pipe);

#endif // !Pipe_h
