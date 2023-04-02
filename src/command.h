#ifndef COMMAND_H
#define COMMAND_H

class Command {
    public:
	virtual void execute() = 0;
};

class QuitCommand : public Command {
public:
    QuitCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;
};

#endif
