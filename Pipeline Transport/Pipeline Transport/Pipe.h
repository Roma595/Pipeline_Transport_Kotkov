#ifndef Pipe_h
#define Pipe_h



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
void read_Pipes();
void view_all_pipes();

#endif // !Pipe_h
