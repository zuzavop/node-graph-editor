#include "command.h"
#include "main_window.h"

void SaveCommand::execute() {
	_window->saveToFile("");
}

void LoadCommand::execute() { 
	_window->loadFromFile(""); 
}

void LoadFromPSCommand::execute() { 
	_window->loadFromPSFile(""); 
}

void LayoutCommand::execute() { 
	_window->layoutGraph(); 
}

void ExportCommand::execute() { 
	_window->exportToPSFile(""); 
}

