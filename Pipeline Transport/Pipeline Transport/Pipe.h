#pragma once

struct Pipe
{	
	std::string name = "None";
	double length = 0;
	int diameter = 0;
	bool in_repair = false;

};

void print(const Pipe& pipe, std::ostream& stream);
void pretty_print(const Pipe& pipe, std::ostream& stream);
bool input_pipe(Pipe& pipe, std::istream& stream);
Pipe input_pipe_interactive();

